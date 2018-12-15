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

#include "../include/wxWidgets_openGL/helloCanvas.h"


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
}

void HelloCanvas::resized(wxSizeEvent& /* evt */)
{
	Refresh();
}

void HelloCanvas::SendDataToOpenGL()
{
	const GLfloat RED_TRIANGLE_Z = 0.5f;
	const GLfloat BLUE_TRIANGLE_Z = -0.5f;

	GLfloat verts[] =
	{
		// Attribute: Vertext point and RGB
		-1.0f, -1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f, // RGB(A)
		+0.0f, +1.0f, -1.0f,//RED_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f, // RGB(A)
		+1.0f, -1.0f, RED_TRIANGLE_Z,
		+1.0f, +0.0f, +0.0f, // RGB(A)

		+0.0f, +1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f, // RGB(A)
		+0.0f, -1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f, // RGB(A)
		+1.0f, +1.0f, BLUE_TRIANGLE_Z,
		+0.0f, +0.0f, +1.0f, // RGB(A)
	};

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 6, // stride: length of each attribute
		0); // start at beginning of verts array
	glEnableVertexAttribArray(1 /* verts index where RGB stuff starts */);
	glVertexAttribPointer(
		1, /* verts index where RGB stuff starts */
		3, /* length of RGB sections of verts */
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 6, // stride: length of each attribute
		(char*)(sizeof(float) * 3) // how deep into verts before RGB data begins
		);

	// Triangle indices from verts[]
	GLushort indices[] = { 0,1,2, 3,4,5 }; // blue on top
	//GLushort indices[] = { 3,4,5, 0,1,2, }; // red on top
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentSharderId);
	glLinkProgram(programId);

	if (!ProgramLinkStatus(programId))
	{
		return;
	}

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
	SendDataToOpenGL();
	InstallShaders();

	glInitialized = true;
}

void HelloCanvas::render( wxPaintEvent& /* evt */)
{
	if (!IsShown()) { return; }

	InitializeGL();

	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	glClear(GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, GetSize().x, GetSize().y);
	const int indiceCount = 6;
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_SHORT, 0);

	glFlush();
	SwapBuffers();
}