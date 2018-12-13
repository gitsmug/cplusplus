// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

//#include "wx/glcanvas.h"

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
	wxPuts(wxString::Format(wxT("%d"), glewInitResult));


	GLfloat verts[] =
	{
		+0.0f, +1.0f,
		-1.0f, -1.0f,
		+1.0f, -1.0f,
	};

	GLuint myBufferID;
	glGenBuffers(1, &myBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


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
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();
	SwapBuffers();
}