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

void HelloCanvas::InitializeGL()
{
	if (glInitialized) { return; }

	wxGLCanvas::SetCurrent(*m_context);
	glLoadIdentity();

	GLenum glewInitResult = glewInit();
	wxPuts(wxT("glewInit() = ") + wxString::Format(wxT("%d"), glewInitResult));


	GLfloat verts[] =
	{
		// Attribute: Vertext point and RGB
		+0.0f, +0.0f, 
		+1.0f, +0.0f, +0.0f, // RGB(A)

		+1.0f, +1.0f,
		+1.0f, +0.0f, +0.0f, // RGB(A)

		-1.0f, +1.0f,
		+1.0f, +0.0f, +0.0f, // RGB(A)

		// +0.0f, +0.0f, Shared vertice of two triangles that touch at point.
		-1.0f, -1.0f,
		+1.0f, +0.0f, +0.0f, // RGB(A)

		+1.0f, -1.0f,
		+1.0f, +0.0f, +0.0f, // RGB(A)

		// Triangle indices:  0,1,3  0,3,4
	};

	GLuint vertexBufferID;
	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5, // stride: length of each attribute
		0); // start at beginning of verts array
	glEnableVertexAttribArray(1 /* verts index where RGB stuff starts */);
	glVertexAttribPointer(
		1, /* verts index where RGB stuff starts */
		3, /* length of RGB sections of verts */
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 5, // stride: length of each attribute
		(char*)(sizeof(float) * 2) // how deep into verts before RGB data begins
		);

	// Triangle indices from verts[]
	GLushort indices[] = { 0,1,2,  0,3,4 };
	GLuint indexBufferID;
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glInitialized = true;
}

void HelloCanvas::render( wxPaintEvent& /* evt */)
{
	if (!IsShown()) { return; }

	InitializeGL();

	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	//glClearColor(1, 0, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, GetSize().x, GetSize().y);
	const int indiceCount = 6;
	glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_SHORT, 0);

	glFlush();
	SwapBuffers();
}