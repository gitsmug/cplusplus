// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/dialogs/customDialog.h"

CustomDialog::CustomDialog(const wxString & title, const wxString &fileName)
	: wxDialog(NULL, -1, title, wxDefaultPosition, wxSize(250, 400))
{
	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	wxButton *okButton = new wxButton(
		this,
		-1,
		wxT("Ok"),
		wxDefaultPosition,
		wxSize(70, 30));

	wxButton *closeButton = new wxButton(
		this,
		-1,
		wxT("Close"),
		wxDefaultPosition,
		wxSize(70, 30));

	textCtrl = new wxTextCtrl(
		this,
		-1,
		wxT(""),
		wxPoint(-1, -1),
		wxSize(-1, -1),
		wxTE_MULTILINE);

	hbox->Add(okButton, 1);
	hbox->Add(closeButton, 1, wxLEFT, 5);

	vbox->Add(textCtrl, 1, wxEXPAND | wxALL, 5);
	vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	textCtrl->LoadFile(fileName);

	SetSizer(vbox);
	Centre();
	ShowModal();
	Destroy();
}