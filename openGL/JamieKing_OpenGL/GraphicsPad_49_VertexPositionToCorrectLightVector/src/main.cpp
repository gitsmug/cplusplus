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
	wxPuts(wxT("Jamie King"));
	wxPuts(wxT("https://www.youtube.com/channel/UCda_RJU9-xB0Hswcrjn4SKw"));
	wxPuts(wxT(""));

	HelloFrame *h = new HelloFrame("Jamie King's OpenGL Tutorial");
	h->Show(true);

	return true;
}