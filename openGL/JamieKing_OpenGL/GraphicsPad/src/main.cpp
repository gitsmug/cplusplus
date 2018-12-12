// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_openGL/helloFrame.h"


class MainApp : public wxApp
{
public:
	virtual bool OnInit();

private:
};

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	/* Pro-tip: If we use cout first, then wxPuts won't work, and vice versa.
	 * https://groups.google.com/forum/#!topic/wx-users/rPk1bKmP2sI
	 */
	//cout << "Mess up wxPuts()";

	wxPuts(wxT(""));
	wxPuts(wxT("https://wiki.wxwidgets.org/WxGLCanvas"));
	wxPuts(wxT(""));
	wxPuts(wxT(""));

	HelloFrame *h = new HelloFrame("Hellow, GL World.");
	h->Show(true);

	return true;
}