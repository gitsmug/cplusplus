#include <iostream>

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/wxWidgets_helperClasses/helpers.h"


Helpers::Helpers(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(270, 150))
{
	//SetIcon(wxIcon(wxT("web.xpm")));

	wxPanel *panel = new wxPanel(this, wxID_ANY);

	wxButton *button = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint(20, 20));

	Connect(
		wxID_EXIT,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(Helpers::OnQuit));

	button->SetFocus();

	Center();
}

void Helpers::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	Close(true);
}

void Helpers::CmdLnDemo()
{
	wxPuts(wxT("Helpers Demo method"));
	wxPuts(wxT(""));

	wxString funnyString = wxT("\xC3\xA0");
	wxPuts(wxT("Salut " + funnyString + " toi!"));

	int number = 5;
	wxString str;
	str.Printf(wxT("Printf example: %d"), number);
	wxPuts(str);

	wxPuts(wxT(""));

	wxPuts(wxGetHomeDir());
	wxPuts(wxGetOsDescription());
	wxPuts(wxGetUserName());
	wxPuts(wxGetFullHostName());
	long mem = wxGetFreeMemory().ToLong();
	wxPrintf(wxT("Unused RAM: %ld\n"), mem);

	wxPuts(wxT(""));

	wxDateTime now = wxDateTime::Now();
	wxPuts(now.Format());
	wxPuts(now.Format(wxT("%X")));
	wxPuts(now.Format(wxT("%x")));

	wxPuts(wxT(""));
}