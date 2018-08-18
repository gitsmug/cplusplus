#ifndef WINDOWMOVE_H
#define WINDOWMOVE_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class WindowMove : public wxFrame
{
public:
	WindowMove(const wxString & title);

private:
	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenuItem *quitMenuItem;

	wxStaticText *xLabel;
	wxStaticText *yLabel;

	void OnQuit(wxCommandEvent & event);
	void OnMove(wxMoveEvent & event);
	void OnButtonClick(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);

	void UpdatePositionDisplay();
};

#endif