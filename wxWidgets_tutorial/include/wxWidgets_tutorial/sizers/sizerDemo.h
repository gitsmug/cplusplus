#ifndef SIZERDEMO_H
#define SIZERDEMO_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class SizerDemo : public wxFrame
{
public:
	SizerDemo(const wxString & title);

	void OnQuit(wxCommandEvent & event);

private:
	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenuItem *quitMenuItem;

	wxTextCtrl *textCtrl;
};

#endif