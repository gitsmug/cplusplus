// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/panel.h>

#include "../include/wxWidgets_tutorial/Communication/displayPanel.h"

DisplayPanel::DisplayPanel(wxPanel * parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(270, 150), wxBORDER_SUNKEN)
{
    displayedText = new wxStaticText(this, -1, wxT(""), wxPoint(40, 60));
    SetText(wxT("Ready!"));
}

void DisplayPanel::SetText(const wxString& textInput)
{
	displayedText->SetLabel(textInput);
}