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
using glm::mat4;

#include "../include/wxWidgets_openGL/helloCanvas.h"
#include "primitives/shapeData.h"
#include "primitives/vertex.h"
#include "primitives/shapeGenerator.h"
#include "Camera.h"


const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
GLuint programId = 0;
GLuint cubeNumIndices = 0;
GLuint arrowNumIndices = 0;
Camera camera;
GLuint fullTransformationUniformLocation;
GLuint theBufferID;
GLuint cubeVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint cubeIndexDataByteOffset;
GLuint arrowIndexDataByteOffset;


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
	glDeleteProgram(programId);
}

void HelloCanvas::resized(wxSizeEvent& /* evt */)
{
	Refresh();
}

void HelloCanvas::SendDataToOpenGL()
{
	//ShapeData cube = ShapeGenerator::MakeCube();
	//ShapeData cube = ShapeGenerator::MakePlane();
	ShapeData cube = ShapeGenerator::makeTeapot();
	ShapeData arrow = ShapeGenerator::MakeArrow();

	glGenBuffers(1, &theBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,
		cube.vertexBufferSize()
			+ cube.indexBufferSize()
			+ arrow.vertexBufferSize()
			+ arrow.indexBufferSize(),
		0,
		GL_STATIC_DRAW);

	GLsizeiptr currentOffset = 0;

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices);
	currentOffset += cube.vertexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices);
	currentOffset += cube.indexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices);
	currentOffset += arrow.vertexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices);

	cubeNumIndices = cube.numIndices;
	arrowNumIndices = arrow.numIndices;

	// Vertex array setup

	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0); // layout(location=0) in VertexShaderCode.glsl
	glEnableVertexAttribArray(1); // verts index where RGB starts, layout(location=1)
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glVertexAttribPointer(
		0, // layout(location=0) in VertexShaderCode.glsl
		3,
		GL_FLOAT,
		GL_FALSE,
		VERTEX_BYTE_SIZE, // stride: length of each attribute
		0); // start at beginning of verts array
	glVertexAttribPointer(
		1, // verts index where RGB starts, layout(location=1)
		3, // length of RGB sections of verts
		GL_FLOAT,
		GL_FALSE,
		VERTEX_BYTE_SIZE, // stride: length of each attribute
		(void*)(sizeof(GLfloat) * 3)); // how deep into verts before RGB data begins
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);


	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0); // layout(location=0) in VertexShaderCode.glsl
	glEnableVertexAttribArray(1); // verts index where RGB starts, layout(location=1)
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);

	GLuint arrowByteOffset = cube.vertexBufferSize() + cube.indexBufferSize();

	glVertexAttribPointer(
		0, // layout(location=0) in VertexShaderCode.glsl
		3,
		GL_FLOAT,
		GL_FALSE,
		VERTEX_BYTE_SIZE, // stride: length of each attribute
		(void*)arrowByteOffset); // start at beginning of verts array
	glVertexAttribPointer(
		1, // verts index where RGB starts, layout(location=1)
		3, // length of RGB sections of verts
		GL_FLOAT,
		GL_FALSE,
		VERTEX_BYTE_SIZE, // stride: length of each attribute
		(void*)(arrowByteOffset + sizeof(GLfloat) * 3)); // how deep into verts before RGB data begins
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	cubeIndexDataByteOffset = cube.vertexBufferSize();
	arrowIndexDataByteOffset = arrowByteOffset + arrow.vertexBufferSize();

	cube.CleanUp();
	arrow.CleanUp();
}

void HelloCanvas::PaintGL()
{
	// GL_COLOR_BUFFER_BIT is wasteful if entire view is painted over (video game scenes, etc.)
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, GetSize().x, GetSize().y);

	GLfloat aspectRatio = ((float)GetSize().x) / ((float)GetSize().y);

	mat4 fullTransformMatrix;

	mat4 viewToProjectionMatrix = glm::perspective(
		glm::radians(60.0f), // feild of view angle
		aspectRatio,
		0.1f, // near-plane
		20.0f); // far-plane

	mat4 worldToViewMatrix = camera.GetWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	// Cube
	glBindVertexArray(cubeVertexArrayObjectID);
	mat4 cube1ModelToWorldMatrix =
		glm::translate(vec3(-2.0f, 0.0f, -3.0f))
		* glm::rotate(glm::radians(36.0f), vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube1ModelToWorldMatrix;

	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset);

	mat4 cube2ModelToWorldMatrix =
		glm::translate(vec3(2.0f, 0.0f, -3.75f))
		* glm::rotate(glm::radians(126.0f), vec3(0.0f, 1.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube2ModelToWorldMatrix;

	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset);


	// Arrow
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix = glm::translate(vec3(0.0f, 0.0f, -3.0f));
	fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;

	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset);


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

bool HelloCanvas::ProgramLinkStatus(GLuint programId)
{
	GLint linkStatus;
	glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

	if (GL_TRUE == linkStatus)
	{
		return true;
	}

	// Show error message from glLinkProgram
	GLint infoLogLength;
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
	GLchar* buffer = new GLchar[infoLogLength];

	GLsizei sizeOfRequestedBuffer;
	glGetProgramInfoLog(programId, infoLogLength, &sizeOfRequestedBuffer, buffer);

	wxPuts("glGetProgramInfoLog: " + wxString::FromUTF8(buffer));

	delete [] buffer;

	return false;
}

void HelloCanvas::InstallShaders()
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentSharderId = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];

	string shaderBody = ReadShaderCode("src/VertextShaderCode.glsl");
	adapter[0] = shaderBody.c_str();
	glShaderSource(vertexShaderId, 1, adapter, 0);

	shaderBody = ReadShaderCode("src/FragmentShaderCode.glsl");
	adapter[0] = shaderBody.c_str();
	glShaderSource(fragmentSharderId, 1, adapter, 0);

	glCompileShader(vertexShaderId);
	glCompileShader(fragmentSharderId);

	if (!ShaderCompileStatus(vertexShaderId)
		|| !ShaderCompileStatus(fragmentSharderId))
	{
		return;
	}

	programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentSharderId);
	glLinkProgram(programId);

	if (!ProgramLinkStatus(programId))
	{
		return;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentSharderId);

	glUseProgram(programId);
}

void HelloCanvas::InitializeGL()
{
	if (glInitialized) { return; }

	wxGLCanvas::SetCurrent(*m_context);
	glLoadIdentity();

	GLenum glewInitResult = glewInit();
	wxPuts(wxT("glewInit() = ") + wxString::Format(wxT("%d"), glewInitResult));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	SendDataToOpenGL();
	InstallShaders();
	
	fullTransformationUniformLocation = glGetUniformLocation(programId, "fullTrasnformMatrix");

	glInitialized = true;
}