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
	}

	MainCanvas::~MainCanvas()
	{
		delete m_context;
		m_context = nullptr;
	}

	void MainCanvas::resized(wxSizeEvent& /* evt */)
	{
		Refresh();
	}

	void MainCanvas::PaintGL()
	{
		// GL_COLOR_BUFFER_BIT is wasteful if entire view is painted over (video game scenes, etc.)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		glViewport(0, 0, GetSize().x, GetSize().y);

		glFlush();
		SwapBuffers();
	}

	void MainCanvas::render( wxPaintEvent& /* evt */)
	{
		if (!IsShown()) { return; }

		InitializeGL();

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

		glInitialized = true;
	}
}