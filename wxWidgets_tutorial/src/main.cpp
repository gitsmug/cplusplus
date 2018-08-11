#include <iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/wxWidgets_helperClasses/helpers.h"
#include "../include/wxWidgets_tutorial/Communication/controlWindow.h"
#include "../include/wxWidgets_tutorial/sizers/sizerDemo.h"
#include "../include/wxWidgets_tutorial/sizers/borderDemo.h"
#include "../include/wxWidgets_tutorial/sizers/alignDemo.h"

using namespace std;

class MainApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit()
{
	/* Pro-tip: If we use cout first, then wxPuts won't work, and vice versa.
	 * https://groups.google.com/forum/#!topic/wx-users/rPk1bKmP2sI
	 */
	//cout << "Mess up wxPuts()";

	wxPuts(wxT(""));
	wxPuts(wxT("wxWidgets Intermediate Tutorial - http://zetcode.com/gui/wxwidgets/"));
	wxPuts(wxT(""));
	wxPuts(wxT(""));

/*
	Helpers *h = new Helpers(wxT("Helpers"));
	h->Show(true);
	h->CmdLnDemo();
*/
/*
	ControlWindow *controlWindow = new ControlWindow(wxT("wxWidgets Communication"));
	controlWindow->Show(true);
*/
/*
	SizerDemo *sd = new SizerDemo(wxT("wxWidgets sizer demo"));
	sd->Show(true);
*/
	BorderDemo *bd = new BorderDemo("Border");
	bd->Show(true);
/*
	AlignDemo *ad = new AlignDemo(wxT("wxWidgets alignment demo"));
	ad->Show(true);
*/

	return true;
}