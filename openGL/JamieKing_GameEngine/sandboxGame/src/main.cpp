// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "mainFrame.h"

using namespace sandboxGame;

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
	wxPuts(wxT("sandboxGame"));
	wxPuts(wxT("Jamie King"));
	wxPuts(wxT("https://www.youtube.com/user/1kingja"));
	wxPuts(wxT(""));

	sandboxGame::MainFrame *h = new MainFrame(
		"SandboxGame: Jamie King's Game Engine Tutorial",
		wxSize(600, 400));
	h->Show(true);

	return true;
}