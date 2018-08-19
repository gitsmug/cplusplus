#ifndef MESSAGEDIALOGS_H
#define MESSAGEDIALOGS_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class MessageDialogs : public wxFrame
{
public:
	MessageDialogs(const wxString & title);

private:
	wxMenuBar *menuBar;
	wxMenu *fileMenu;
	wxMenuItem *quitMenuItem;

	wxTextCtrl *textCrl;

	void OnQuit(wxCommandEvent & event);
	void OnMove(wxMoveEvent & event);
	void OnClose(wxCloseEvent& event);

	void ShowInfoDialog(wxCommandEvent & event);
	void ShowErrorDialog(wxCommandEvent & event);
	void ShowQuestionDialog(wxCommandEvent & event);
	void ShowAlertDialog(wxCommandEvent & event);

	void ShowCustomDialog(wxCommandEvent & event);

	void OnFileOpen(wxCommandEvent & event);
};

#endif