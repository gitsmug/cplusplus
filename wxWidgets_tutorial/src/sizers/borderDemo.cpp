// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/sizers/borderDemo.h"


BorderDemo::BorderDemo(const wxString & title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(300, 180))
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
		wxCommandEventHandler(BorderDemo::OnQuit));


	wxColour col1, col2;
	col1.Set(wxT("#4f5049"));
	col2.Set(wxT("#ededed"));

	wxPanel *panel = new wxPanel(this, -1);
	panel->SetBackgroundColour(col1);
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

	wxPanel *midPan = new wxPanel(panel, wxID_ANY);
	midPan->SetBackgroundColour(col2);

	vbox->Add(midPan, 1, wxEXPAND | wxALL, 20);
	panel->SetSizer(vbox);

	Center();
}

void BorderDemo::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}