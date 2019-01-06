#include <fstream>
#include <string>
using std::string;
#include <cassert>

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

#include "mainCanvas.h"

namespace sandboxGame
{
	MainCanvas::MainCanvas(wxFrame * parent, int * args)
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

		Connect(wxEVT_SIZE, wxSizeEventHandler(MainCanvas::Resized));
		Connect(wxEVT_PAINT, wxPaintEventHandler(MainCanvas::Render));
	}

	MainCanvas::~MainCanvas()
	{
		delete m_context;
		m_context = nullptr;
	}

	void MainCanvas::Resized(wxSizeEvent& /* evt */)
	{
		Refresh();
	}

	void MainCanvas::PaintGL()
	{
		InitializeGL();
		
		// GL_COLOR_BUFFER_BIT is wasteful if entire view is painted over (video game scenes, etc.)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, GetSize().x, GetSize().y);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glFlush();
		SwapBuffers();
	}

	void MainCanvas::Render(wxPaintEvent& /* evt */)
	{
		if (!IsShown()) { return; }

		//InitializeGL();
		wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
		PaintGL();
	}

	void MainCanvas::InitializeGL()
	{
		if (glInitialized) { return; }

		wxGLCanvas::SetCurrent(*m_context);
		glLoadIdentity();

		const GLenum glewInitResult = glewInit();

		if (GLEW_OK != glewInitResult)
		{
			wxPuts(wxT("glewInit() = ") + wxString::Format(wxT("%d"), glewInitResult));
		}

		assert(GLEW_OK == glewInitResult);

		GLfloat verts[] =
		{
			0.0f, 0.1f,
			-0.1f, -0.1f,
			0.1f, -0.1f
		};

		glGenBuffers(1, &vertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);


		glInitialized = true;
	}
}