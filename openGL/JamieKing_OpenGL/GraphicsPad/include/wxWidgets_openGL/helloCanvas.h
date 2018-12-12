#ifndef HELLOCANVAS_H
#define HELLOCANVAS_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/glcanvas.h>

class HelloCanvas : public wxGLCanvas
{
public:
	HelloCanvas(wxFrame * parent, int* args);
	virtual ~HelloCanvas();

	void resized(wxSizeEvent& evt);

	int getWidth();
	int getHeight();

	void render(wxPaintEvent& evt);
	void prepare3DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);

private:
	wxGLContext * m_context;
};

#endif