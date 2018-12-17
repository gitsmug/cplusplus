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

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
GLuint programId = 0;
GLuint numIndices = 0;


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
}

HelloCanvas::~HelloCanvas()
{
	delete m_context;
	glUseProgram(0);
	glDeleteProgram(programId);
}

void HelloCanvas::resized(wxSizeEvent& /* evt */)
{
	Refresh();
}

void HelloCanvas::SendDataToOpenGL()
{
	//ShapeData shape = ShapeGenerator::MakeTriangle();
	ShapeData shape = ShapeGenerator::MakeCube();

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(glGetAttribLocation(programId, "position"));
	glVertexAttribPointer(
		glGetAttribLocation(programId, "position"),
		3,
		GL_FLOAT,
		GL_FALSE,

		VERTEX_BYTE_SIZE, // stride: length of each attribute
		//sizeof(float) * 6,

		0); // start at beginning of verts array
	glEnableVertexAttribArray(glGetAttribLocation(programId, "vertexColor"));
	glVertexAttribPointer(
		glGetAttribLocation(programId, "vertexColor"),
		3, /* length of RGB sections of verts */
		GL_FLOAT,
		GL_FALSE,

		VERTEX_BYTE_SIZE, // stride: length of each attribute
		//sizeof(float) * 6,

		(char*)(sizeof(GLfloat) * 3)); // how deep into verts before RGB data begins

	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);

	numIndices = shape.numIndices;

	shape.CleanUp();

	GLuint transformMatrixBufferId;
	glGenBuffers(1, &transformMatrixBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, transformMatrixBufferId);


	GLfloat aspectRatio = ((float)GetSize().x) / ((float)GetSize().y);

	mat4 projectionMatrix = glm::perspective(
		glm::radians(60.0f), // feild of view angle
		aspectRatio,
		0.1f, // near-plane
		10.0f); // far-plane

	mat4 fullTransforms[]
	{
		/* Cube 1
		 */
		projectionMatrix
			* glm::translate(vec3(-1.0f, 0.0f, -3.0f))
			* glm::rotate(
				glm::radians(36.0f),
				vec3(1.0f, 0.0f, 0.0f)),

		/* Cube 2
		 */
		projectionMatrix
			* glm::translate(vec3(1.0f, 0.0f, -3.75f))
			* glm::rotate(
				glm::radians(126.0f),
				vec3(0.0f, 1.0f, 0.0f)),
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransforms), fullTransforms, GL_STATIC_DRAW);

	GLuint transFormsAttribLocaion = glGetAttribLocation(programId, "fullTrasnformMatrix");

	glVertexAttribPointer(
		transFormsAttribLocaion,
		4, // mat4 fullTransforms
		GL_FLOAT,
		GL_FALSE,
		sizeof(mat4), // stride accross fullTransforms
		(void*)(sizeof(float) * 0));

	glVertexAttribPointer(transFormsAttribLocaion + 1, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(transFormsAttribLocaion + 2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(transFormsAttribLocaion + 3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 12));

	glEnableVertexAttribArray(transFormsAttribLocaion + 0);
	glEnableVertexAttribArray(transFormsAttribLocaion + 1);
	glEnableVertexAttribArray(transFormsAttribLocaion + 2);
	glEnableVertexAttribArray(transFormsAttribLocaion + 3);

	glVertexAttribDivisor(transFormsAttribLocaion + 0, 1);
	glVertexAttribDivisor(transFormsAttribLocaion + 1, 1);
	glVertexAttribDivisor(transFormsAttribLocaion + 2, 1);
	glVertexAttribDivisor(transFormsAttribLocaion + 3, 1);
}

void HelloCanvas::render( wxPaintEvent& /* evt */)
{
	if (!IsShown()) { return; }

	InitializeGL();

	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	// GL_COLOR_BUFFER_BIT is wasteful if entire view is painted over (video game scenes, etc.)
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, GetSize().x, GetSize().y);

	glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2 /* shapes */);

	glFlush();
	SwapBuffers();
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
	InstallShaders();
	SendDataToOpenGL();

	glInitialized = true;
}