// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/sizers/sizerDemo.h"


SizerDemo::SizerDemo(const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(250, 180))
{
	menuBar = new wxMenuBar();
	fileMenu = new wxMenu();

	quitMenuItem = new wxMenuItem(fileMenu, wxID_EXIT, wxT("&Quit"));
	fileMenu->Append(quitMenuItem);
	menuBar->Append(fileMenu, wxT("&File"));

	SetMenuBar(menuBar);

	Connect(
		wxID_EXIT,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(SizerDemo::OnQuit));

	textCtrl = new wxTextCtrl(
		this,
		-1,
		wxT(""),
		wxPoint(-1, -1),
		//wxSize(250, 150));
		wxSize(-1, -1));

	Center();
}

void SizerDemo::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}