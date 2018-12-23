#include <fstream>
#include <string>
using std::string;

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// include OpenGL
#ifdef __WXMAC__
#include <OpenGL/glew.h>
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

using glm::vec3;
using glm::vec4;
using glm::mat4;

#include "../include/wxWidgets_openGL/helloCanvas.h"
#include "primitives/shapeData.h"
#include "primitives/vertex.h"
#include "primitives/shapeGenerator.h"
#include "Camera.h"


const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
GLuint programID = 0;

GLuint passThroughProgramID;
GLuint cubeNumIndices = 0;
GLuint planeNumIndices = 0;

Camera camera;
GLuint theBufferID;

GLuint cubeVertexArrayObjectID;
GLuint planeVertexArrayObjectID;

GLuint arrowIndexByteOffset;
GLuint planeIndexByteOffset;


HelloCanvas::HelloCanvas(wxFrame * parent, int * args)
	: wxGLCanvas(
		parent,
		wxID_ANY,
		args,
		wxDefaultPosition,
		wxDefaultSize,
		wxFULL_REPAINT_ON_RESIZE),
	glInitialized(false)
{
	m_context = new wxGLContext(this);

	// To avoid flashing on MSW
	SetBackgroundStyle(wxBG_STYLE_CUSTOM);

	Connect(wxEVT_SIZE, wxSizeEventHandler(HelloCanvas::resized));
	Connect(wxEVT_PAINT, wxPaintEventHandler(HelloCanvas::render));

	Connect(
		wxEVT_MOTION,
		wxMouseEventHandler(HelloCanvas::MouseMoveEvent),
		NULL,
		this);

	Connect(
		wxEVT_KEY_DOWN,
		wxKeyEventHandler(HelloCanvas::KeyPressEvent),
		NULL,
		this);
}

HelloCanvas::~HelloCanvas()
{
	delete m_context;
	glDeleteBuffers(1, &theBufferID);
	glUseProgram(0);
	glDeleteProgram(programID);
}

void HelloCanvas::resized(wxSizeEvent& /* evt */)
{
	Refresh();
}

void HelloCanvas::SendDataToOpenGL()
{
	//ShapeData teapot = ShapeGenerator::makeTeapot();
	ShapeData cube = ShapeGenerator::MakeCube();
	//ShapeData arrow = ShapeGenerator::MakeArrow();
	ShapeData plane = ShapeGenerator::MakePlane(20);
	//ShapeData plane = ShapeGenerator::MakePlane();

	glGenBuffers(1, &theBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,
		cube.vertexBufferSize() + cube.indexBufferSize()
			+ plane.vertexBufferSize() + plane.indexBufferSize(),
		0,
		GL_STATIC_DRAW);

	GLsizeiptr currentOffset = 0;

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices);
	currentOffset += cube.vertexBufferSize();
	arrowIndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices);
	currentOffset += cube.indexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.vertexBufferSize(), plane.vertices);
	currentOffset += plane.vertexBufferSize();
	planeIndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.indexBufferSize(), plane.indices);
	currentOffset += plane.indexBufferSize();

	cubeNumIndices = cube.numIndices;
	planeNumIndices = plane.numIndices;

	// Vertex array setup

	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &planeVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0); // layout(location=0) in VertexShaderCode.glsl
	glEnableVertexAttribArray(1); // verts index where RGB starts, layout(location=1)
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glVertexAttribPointer(
		0, // layout(location=0) in VertexShaderCode.glsl
		3,
		GL_FLOAT,
		GL_FALSE, // Don't normalize for me.
		VERTEX_BYTE_SIZE, // stride: length of each attribute
		0); // start at beginning of verts array
	glVertexAttribPointer(
		1, // verts index where RGB starts, layout(location=1)
		3, // length of RGB sections of verts
		GL_FLOAT,
		GL_FALSE, // Don't normalize for me.
		VERTEX_BYTE_SIZE, // stride: length of each attribute
		// 3 is how deep into verts before RGB data begins
		// how far into struct Vertex after position to color
		reinterpret_cast<void*>(sizeof(GLfloat) * 3));
	glVertexAttribPointer(
		2, // layout(location=2) in VertexShaderCode.glsl
		3,
		GL_FLOAT,
		GL_FLOAT,
		VERTEX_BYTE_SIZE,
		// 6 is how far into struct Vertex after position and color to normal.
		reinterpret_cast<void*>(sizeof(GLfloat) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);


	glBindVertexArray(planeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint planeByteOffset = cube.vertexBufferSize() + cube.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, reinterpret_cast<void*>(planeByteOffset));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, reinterpret_cast<void*>(planeByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, reinterpret_cast<void*>(planeByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	cube.CleanUp();
	plane.CleanUp();
}

void HelloCanvas::PaintGL()
{
	// GL_COLOR_BUFFER_BIT is wasteful if entire view is painted over (video game scenes, etc.)
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, GetSize().x, GetSize().y);

	GLfloat aspectRatio = ((float)GetSize().x) / ((float)GetSize().y);

	mat4 modelToProjectionMatrix;

	mat4 viewToProjectionMatrix = glm::perspective(
		glm::radians(60.0f), // feild of view angle
		aspectRatio,
		0.1f, // near-plane
		20.0f); // far-plane

	mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	GLuint fullTransformationUniformLocation;
	GLuint modelToWorldMatrixUniformLocation;

	glm::vec3 lightPositionWorld(0.0f, 1.5f, 0.0f);

	// Cube
	glBindVertexArray(cubeVertexArrayObjectID);
	mat4 cubeModelToWorldMatrix = 
		glm::translate(lightPositionWorld) *
		glm::scale(vec3(0.1f, 0.1f, 0.1f));
	modelToProjectionMatrix = worldToProjectionMatrix * cubeModelToWorldMatrix;
	glUseProgram(passThroughProgramID);
	fullTransformationUniformLocation = glGetUniformLocation(passThroughProgramID, "modelToProjectionMatrix");
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	modelToWorldMatrixUniformLocation = glGetUniformLocation(passThroughProgramID, "modelToWorldMatrix");
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&cubeModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(arrowIndexByteOffset));


	// Plane
	glUseProgram(programID);

	GLint ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLight");
	vec4 ambientLight(0.05f, 0.05f, 0.05f, 1.0f);
	glUniform4fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	GLint eyePositionWorldUniformLocation = glGetUniformLocation(programID, "eyePositionWorld");
	glm::vec3 eyePosition = camera.getPosition();
	glUniform3fv(eyePositionWorldUniformLocation, 1, &eyePosition[0]);
	GLint lightPositionUniformLocation = glGetUniformLocation(programID, "lightPositionWorld");
	glUniform3fv(lightPositionUniformLocation, 1, &lightPositionWorld[0]);

	glBindVertexArray(planeVertexArrayObjectID);
	mat4 planeModelToWorldMatrix = glm::mat4(1.0f);
	modelToProjectionMatrix = worldToProjectionMatrix * planeModelToWorldMatrix;
	fullTransformationUniformLocation = glGetUniformLocation(programID, "modelToProjectionMatrix");
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	modelToWorldMatrixUniformLocation = glGetUniformLocation(programID, "modelToWorldMatrix");
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&planeModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, planeNumIndices, GL_UNSIGNED_SHORT, reinterpret_cast<void*>(planeIndexByteOffset));


	glFlush();
	SwapBuffers();
}

void HelloCanvas::render( wxPaintEvent& /* evt */)
{
	if (!IsShown()) { return; }

	InitializeGL();

	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	PaintGL();
}

void HelloCanvas::MouseMoveEvent(wxMouseEvent& event)
{
	int x = event.GetX();
	int y = event.GetY();
	//wxPuts(wxT("mouse=(") + wxString::Format(wxT("%d"), x) + ", " + wxString::Format(wxT("%d"), y) + ")");

	camera.MouseUpdate(vec2(glm::radians((float)x), glm::radians((float)y)));
	PaintGL();
}

void HelloCanvas::KeyPressEvent(wxKeyEvent& event)
{
	wxChar c = event.GetUnicodeKey();
	//wxPuts(wxT("keyPress=") + wxString::Format(wxT("%d"), c));

	switch (c)
	{
		case 'A':
		case 'a':
			camera.StrafeLeft();
			break;
		case 'D':
		case 'd':
			camera.StrafeRight();
			break;
		case 'F':
		case 'f':
			camera.MoveDown();
			break;
		case 'R':
		case 'r':
			camera.MoveUp();
			break;
		case 'S':
		case 's':
			camera.MoveBackward();
			break;
		case 'w':
		case 'W':
			camera.MoveForward();
			break;
		default:
			event.Skip();
	}

	PaintGL();
}

string HelloCanvas::ReadShaderCode(const char* fileName)
{
	std::ifstream myInput(fileName);

	if (!myInput.good())
	{
		wxPuts(wxT("failed to load file [") + wxString::FromUTF8(fileName) + "]");
		exit(1);
	}

	return string(
		std::istreambuf_iterator<char>(myInput),
		std::istreambuf_iterator<char>());
}

bool HelloCanvas::ShaderCompileStatus(GLuint shaderId)
{
	GLint compileStatus;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);

	if (GL_TRUE == compileStatus)
	{
		return true;
	}

	// Show error message from glCompileShader
	GLint infoLogLength;
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
	GLchar* buffer = new GLchar[infoLogLength];

	GLsizei sizeOfRequestedBuffer;
	glGetShaderInfoLog(shaderId, infoLogLength, &sizeOfRequestedBuffer, buffer);

	wxPuts("glGetShaderInfoLog: " + wxString::FromUTF8(buffer));

	delete [] buffer;

	return false;
}

bool HelloCanvas::ProgramLinkStatus(GLuint programID)
{
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);

	if (GL_TRUE == linkStatus)
	{
		return true;
	}

	// Show error message from glLinkProgram
	GLint infoLogLength;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	GLchar* buffer = new GLchar[infoLogLength];

	GLsizei sizeOfRequestedBuffer;
	glGetProgramInfoLog(programID, infoLogLength, &sizeOfRequestedBuffer, buffer);

	wxPuts("glGetProgramInfoLog: " + wxString::FromUTF8(buffer));

	delete [] buffer;

	return false;
}

void HelloCanvas::InstallShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];

	string shaderBody = ReadShaderCode("src/VertextShaderCode.glsl");
	adapter[0] = shaderBody.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);

	shaderBody = ReadShaderCode("src/FragmentShaderCode.glsl");
	adapter[0] = shaderBody.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!ShaderCompileStatus(vertexShaderID)
		|| !ShaderCompileStatus(fragmentShaderID))
	{
		return;
	}

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!ProgramLinkStatus(programID))
	{
		return;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	shaderBody = ReadShaderCode("src/VertexShaderPassThroughCode.glsl");
	adapter[0] = shaderBody.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	shaderBody = ReadShaderCode("src/FragmentShaderPassThroughCode.glsl");
	adapter[0] = shaderBody.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!ShaderCompileStatus(vertexShaderID)
		|| !ShaderCompileStatus(fragmentShaderID))
	{
		return;
	}

	passThroughProgramID = glCreateProgram();
	glAttachShader(passThroughProgramID, vertexShaderID);
	glAttachShader(passThroughProgramID, fragmentShaderID);

	glLinkProgram(passThroughProgramID);

	if (!ProgramLinkStatus(passThroughProgramID))
	{
		return;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}

void HelloCanvas::InitializeGL()
{
	if (glInitialized) { return; }

	wxGLCanvas::SetCurrent(*m_context);
	glLoadIdentity();

	const GLenum glewInitResult = glewInit();

	if (GLEW_OK != glewInitResult)
	{
		wxPuts(wxT("glewInit() = ") + wxString::Format(wxT("%d"), glewInitResult));
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	SendDataToOpenGL();
	InstallShaders();

	glInitialized = true;
}