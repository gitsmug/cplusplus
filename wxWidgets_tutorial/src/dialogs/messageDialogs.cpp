// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/dialogs/messageDialogs.h"
#include "../include/wxWidgets_tutorial/dialogs/customDialog.h"

enum PanelId : wxWindowID
{
	infoButton,
	errorButton,
	questionButton,
	alertButton,
	customButton
};

MessageDialogs::MessageDialogs(const wxString & title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 180))
{
	menuBar = new wxMenuBar();
	fileMenu = new wxMenu();

	quitMenuItem = new wxMenuItem(fileMenu, wxID_EXIT, wxT("&Quit"));

	fileMenu->Append(quitMenuItem);
	fileMenu->Append(wxID_OPEN, wxT("&Open"));

	menuBar->Append(fileMenu, wxT("&File"));

	SetMenuBar(menuBar);

	Connect(
		quitMenuItem->GetId(),
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(MessageDialogs::OnQuit));

	Connect(
		wxID_OPEN,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(MessageDialogs::OnFileOpen));

	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MessageDialogs::OnClose));


	wxPanel *panel = new wxPanel(this, wxID_ANY);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);
	wxGridSizer *gs = new wxGridSizer(2, 2, 2, 2);

	wxButton *infoBtn = new wxButton(panel, PanelId::infoButton, wxT("Info"));
	wxButton *errorBtn = new wxButton(panel, PanelId::errorButton, wxT("Error"));
	wxButton *questionBtn = new wxButton(panel, PanelId::questionButton, wxT("Question"));
	wxButton *alertBtn = new wxButton(panel, PanelId::alertButton, wxT("Alert"));
	wxButton *customBtn = new wxButton(panel, PanelId::customButton, wxT("Custom"));

	Connect(
		PanelId::infoButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageDialogs::ShowInfoDialog));

	Connect(
		PanelId::errorButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageDialogs::ShowErrorDialog));

	Connect(
		PanelId::questionButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageDialogs::ShowQuestionDialog));

	Connect(
		PanelId::alertButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageDialogs::ShowAlertDialog));

	Connect(
		PanelId::customButton,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageDialogs::ShowCustomDialog));

	gs->Add(infoBtn, 1, wxEXPAND);
	gs->Add(errorBtn, 1);
	gs->Add(questionBtn, 1);
	gs->Add(alertBtn, 1);
	gs->Add(customBtn, 1);

	hbox->Add(gs, 0, wxALL, 15);
	panel->SetSizer(hbox);

	Center();
}

void MessageDialogs::ShowInfoDialog(wxCommandEvent& /* event */)
{
	wxMessageDialog md(
		NULL,
		wxT("Download completed"),
		wxT("Info"),
		wxOK);

	md.ShowModal();
}

void MessageDialogs::ShowErrorDialog(wxCommandEvent& /* event */)
{
	wxMessageDialog md(
		NULL,
		wxT("Error loading file"),
		wxT("Error"),
		wxOK | wxICON_ERROR);

	md.ShowModal();
}

void MessageDialogs::ShowQuestionDialog(wxCommandEvent& /* event */)
{
	wxMessageDialog md(
		NULL,
		wxT("Are you sure to quit?"),
		wxT("Question"),
		wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION);

	md.ShowModal();
}

void MessageDialogs::ShowAlertDialog(wxCommandEvent& /* event */)
{
	wxMessageDialog md(
		NULL,
		wxT("Unallowed operation"),
		wxT("Alert"),
		wxOK | wxICON_EXCLAMATION);

	md.ShowModal();
}

void MessageDialogs::OnFileOpen(wxCommandEvent & /* event */)
{
	wxFileDialog fd(this);

	if (fd.ShowModal() == wxID_OK)
	{
		wxPuts(fd.GetPath());
	}
}

void MessageDialogs::ShowCustomDialog(wxCommandEvent& /* event */)
{
	wxFileDialog fd(this);

	if (fd.ShowModal() == wxID_OK)
	{
		CustomDialog cd(wxT("CustomDialog"), fd.GetPath());

		cd.Show(true);
	}
}

void MessageDialogs::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}

void MessageDialogs::OnClose(wxCloseEvent &event)
{
	wxMessageDialog md(
		NULL,
		wxT("Are you sure about exiting the program?"),
		wxT("Balls!"),
		wxYES_NO | wxYES_DEFAULT | wxICON_QUESTION);

	if (md.ShowModal() == wxID_YES)
	{
		event.Skip();
	}
	else
	{
		event.Veto(); // Prevent event from propogating.
	}
}