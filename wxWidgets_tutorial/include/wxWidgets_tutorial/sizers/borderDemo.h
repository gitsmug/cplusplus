#ifndef BORDERDEMO_H
#define BORDERDEMO_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class BorderDemo : public wxFrame
{
public:
	BorderDemo(const wxString & title);

	void OnQuit(wxCommandEvent & event);

private:
	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenuItem *quitMenuItem;
};

#endif