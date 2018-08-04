// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/panel.h>

#include "../include/wxWidgets_tutorial/Communication/controlPanel.h"
#include "../include/wxWidgets_tutorial/Communication/controlWindow.h"

enum PanelId : wxWindowID
{
	plusButton,
	minusButton
};

ControlPanel::ControlPanel(wxPanel * parentPanel)
	: wxPanel(parentPanel, -1, wxPoint(-1, 1), wxSize(-1, -1), wxBORDER_SUNKEN)
	, count(0)
{
	this->parentPanel = parentPanel;

	plusButton = new wxButton(this, PanelId::plusButton, wxT("+"), wxPoint(10, 10));
	minusButton = new wxButton(this, PanelId::minusButton, wxT("-"), wxPoint(10, 60));

	Connect(
		PanelId::plusButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(ControlPanel::OnPlus));

	Connect(
		PanelId::minusButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(ControlPanel::OnMinus));
}

void ControlPanel::OnPlus(wxCommandEvent & /* event */)
{
	count++;
	UpdateDisplay();
}

void ControlPanel::OnMinus(wxCommandEvent & /* event */)
{
	count--;
	UpdateDisplay();
}

void ControlPanel::UpdateDisplay()
{
	wxString countString = wxString::Format(wxT("%d"), count);

	wxPuts(wxT("ControlPanel.count=" + countString));

	ControlWindow *cw = (ControlWindow *)parentPanel->GetParent();
	cw->displayPanel->SetText(countString);
}