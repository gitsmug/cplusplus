#ifndef ALIGNDEMO_H
#define ALIGNDEMO_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class AlignDemo : public wxFrame
{
public:
	AlignDemo(const wxString & title);

	void OnQuit(wxCommandEvent & event);

private:
	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenuItem *quitMenuItem;
};

#endif