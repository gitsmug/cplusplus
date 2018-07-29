#include <iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/wxWidgets_helperClasses/helpers.h"

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

	Helpers *h = new Helpers(wxT("Helpers"));
	h->Show(true);
	h->Demo();

	return true;
}