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

	void render(wxPaintEvent& evt);

private:
	wxGLContext * m_context;
	bool glInitialized;

	void SendDataToOpenGL();
	void InitializeGL();
	void InstallShaders();
};

#endif