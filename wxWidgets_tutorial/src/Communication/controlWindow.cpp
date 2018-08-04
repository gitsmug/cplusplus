// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/Communication/controlWindow.h"

ControlWindow::ControlWindow(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(290, 150))
{
	parentPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	controlPanel = new ControlPanel(parentPanel);
	displayPanel = new DisplayPanel(parentPanel);

	hbox->Add(controlPanel, 1, wxEXPAND | wxALL, 5);
	hbox->Add(displayPanel, 1, wxEXPAND | wxALL, 5);

	parentPanel->SetSizer(hbox);

	Center();
}