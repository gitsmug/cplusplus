// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/Communication/controlWindow.h"

ControlWindow::ControlWindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(290, 440))
{
	parentPanel = new wxPanel(this, wxID_ANY);

	controlPanel = new ControlPanel(parentPanel);
	displayPanel = new DisplayPanel(parentPanel);

	//wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	//hbox->Add(controlPanel, 1, wxEXPAND | wxALL, 5);
	//hbox->Add(displayPanel, 1, wxEXPAND | wxALL, 5);

	//parentPanel->SetSizer(hbox);

	menubar = new wxMenuBar();
	file = new wxMenu();

	file->Append(wxID_ANY, wxT("&New"));
	file->Append(wxID_ANY, wxT("&Open"));
	file->Append(wxID_ANY, wxT("&Save"));
	file->AppendSeparator();

	import = new wxMenu();
	import->Append(wxID_ANY, wxT("Import this..."));
	import->Append(wxID_ANY, wxT("Import that..."));

	file->AppendSubMenu(import, wxT("Import"));

	//quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	quit = new wxMenuItem(file, wxID_EXIT, wxT("Quit"));
	file->Append(quit);

	menubar->Append(file, wxT("&File"));
	SetMenuBar(menubar);

	wxImage::AddHandler(new wxPNGHandler());
	wxBitmap exitImage = wxBitmap(wxT("img/m_icon.png"), wxBITMAP_TYPE_PNG);
	wxBitmap newImage = wxBitmap(wxT("img/a_icon.png"), wxBITMAP_TYPE_PNG);
	wxBitmap openImage = wxBitmap(wxT("img/f_icon.png"), wxBITMAP_TYPE_PNG);
	wxBitmap saveImage = wxBitmap(wxT("img/t_icon.png"), wxBITMAP_TYPE_PNG);

	toolbar1 = new wxToolBar(this, wxID_ANY);
	toolbar1->AddTool(wxID_ANY, wxT("New"), newImage);
	toolbar1->AddTool(wxID_ANY, wxT("Open"), openImage);
	toolbar1->AddTool(wxID_ANY, wxT("Save"), saveImage);
	toolbar1->Realize();

	toolbar2 = new wxToolBar(this, wxID_ANY);
	toolbar2->AddTool(wxID_EXIT, wxT("Exit"), exitImage);
	toolbar2->Realize();

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	vbox->Add(toolbar1, 0, wxEXPAND);
	vbox->Add(toolbar2, 0, wxEXPAND);

	vbox->Add(parentPanel, 1, wxEXPAND | wxALL, 5);
	//vbox->Add(displayPanel, 1, wxEXPAND | wxALL, 5);

	SetSizer(vbox);

	Connect(
		wxID_EXIT,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(ControlWindow::OnQuit));

	Center();
}

void ControlWindow::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}