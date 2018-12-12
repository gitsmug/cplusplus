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

// Vertices and faces of a simple cube to demonstrate 3D render
// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
GLfloat v[8][3];
GLint faces[6][4] =
{  /* Vertex indices for the 6 faces of a cube. */
	{0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
	{4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3}
};

HelloCanvas::HelloCanvas(wxFrame * parent, int * args)
	: wxGLCanvas(
		parent,
		wxID_ANY,
		args,
		wxDefaultPosition,
		wxDefaultSize,
		wxFULL_REPAINT_ON_RESIZE)
{
	m_context = new wxGLContext(this);

	// prepare a simple cube to demonstrate 3D render
	// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

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
	//wxPuts(wxT("HelloCanvas::resized"));

	Refresh();
}

int HelloCanvas::getWidth()
{
	return GetSize().x;
}
 
int HelloCanvas::getHeight()
{
	return GetSize().y;
}

/** Inits the OpenGL viewport for drawing in 3D. */
void HelloCanvas::prepare3DViewport(
	int topleft_x,
	int topleft_y,
	int bottomrigth_x,
	int bottomrigth_y)
{
	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
	glClearDepth(1.0f);	// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_COLOR_MATERIAL);

	glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio_w_h = (float)(bottomrigth_x-topleft_x)/(float)(bottomrigth_y-topleft_y);
	gluPerspective(45 /*view angle*/, ratio_w_h, 0.1 /*clip close*/, 200 /*clip far*/);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void HelloCanvas::render( wxPaintEvent& /* evt */)
{
	//wxPuts(wxT("HelloCanvas::render"));

	if (!IsShown()) { return; }

	wxGLCanvas::SetCurrent(*m_context);
	wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ------------- draw some 3D ----------------
	prepare3DViewport(0, 0, getWidth(), getHeight());
	glLoadIdentity();

	glColor4f(0,0,1,1);
	glTranslatef(0,0,-5);
	glRotatef(50.0f, 0.0f, 1.0f, 0.0f);

	glColor4f(1, 0, 0, 1);

	for (int i = 0; i < 6; i++)
	{
	    glBegin(GL_LINE_STRIP);
	    glVertex3fv(&v[faces[i][0]][0]);
	    glVertex3fv(&v[faces[i][1]][0]);
	    glVertex3fv(&v[faces[i][2]][0]);
	    glVertex3fv(&v[faces[i][3]][0]);
	    glVertex3fv(&v[faces[i][0]][0]);
	    glEnd();
	}

	glFlush();
	SwapBuffers();
}