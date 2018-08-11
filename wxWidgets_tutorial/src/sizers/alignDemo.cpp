// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/sizers/alignDemo.h"


AlignDemo::AlignDemo(const wxString & title)
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
		wxCommandEventHandler(AlignDemo::OnQuit));


	wxPanel *panel = new wxPanel(this, -1);

	wxButton *ok = new wxButton(panel, -1, wxT("Ok"));
	wxButton *cancel = new wxButton(panel, -1, wxT("Cancel"));

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *hbox2 = new wxBoxSizer(wxHORIZONTAL);

	hbox1->Add(new wxPanel(panel, -1));
	vbox->Add(hbox1, 1, wxEXPAND);

	hbox2->Add(ok);
	hbox2->Add(cancel);

	vbox->Add(hbox2, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);
	panel->SetSizer(vbox);

	Center();
}

void AlignDemo::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}