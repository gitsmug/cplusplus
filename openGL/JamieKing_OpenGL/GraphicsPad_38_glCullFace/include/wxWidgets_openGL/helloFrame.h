#ifndef HELLOFRAME_H
#define HELLOFRAME_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "helloCanvas.h"

class HelloFrame : public wxFrame
{
public:
	HelloFrame(const wxString& title);

	void OnQuit(wxCommandEvent & event);

private:
	wxPanel *parentPanel;

	wxMenuBar *menubar;
	wxMenu *file;
	wxMenuItem *quit;

	HelloCanvas *glPane;
};

#endif