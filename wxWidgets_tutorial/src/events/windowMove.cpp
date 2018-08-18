// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_tutorial/events/windowMove.h"

//const int ID_BUTTON = 1;
const int ID_BUTTON = wxID_SAVE;

class MyButton : wxButton
{
public:

	MyButton(wxPanel *parent, int id, const wxString &label);
	void OnClick(wxCommandEvent& event);
};

WindowMove::WindowMove(const wxString & title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 180))
{
	menuBar = new wxMenuBar();
	fileMenu = new wxMenu();

	quitMenuItem = new wxMenuItem(fileMenu, wxID_EXIT, wxT("&Quit"));
	fileMenu->Append(quitMenuItem);
	menuBar->Append(fileMenu, wxT("&File"));

	SetMenuBar(menuBar);

	Connect(
		quitMenuItem->GetId(),
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(WindowMove::OnQuit));

	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(WindowMove::OnClose));


	wxPanel *panel = new wxPanel(this, -1);

	xLabel = new wxStaticText(panel, -1, wxT(""), wxPoint(10, 10));
	yLabel = new wxStaticText(panel, -1, wxT(""), wxPoint(10, 30));
	UpdatePositionDisplay();

	Connect(wxEVT_MOVE, wxMoveEventHandler(WindowMove::OnMove));


	new MyButton(panel, ID_BUTTON, wxT("Button!"));

	Connect(
		ID_BUTTON,
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(WindowMove::OnButtonClick));


	Center();
}

void WindowMove::OnMove(wxMoveEvent & /* event */)
{
	//wxPoint position = event.GetPosition();
	//xLabel->SetLabel(wxString::Format(wxT("x: %d"), position.x));
	//yLabel->SetLabel(wxString::Format(wxT("y: %d"), position.y));

	UpdatePositionDisplay();
}

void WindowMove::UpdatePositionDisplay()
{
	wxPoint position = GetPosition();
	xLabel->SetLabel(wxString::Format(wxT("x: %d"), position.x));
	yLabel->SetLabel(wxString::Format(wxT("y: %d"), position.y));
}

void WindowMove::OnButtonClick(wxCommandEvent& /* event */)
{
	wxPuts(wxT("event reached WindowMove class"));
}

void WindowMove::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}

void WindowMove::OnClose(wxCloseEvent &event)
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

MyButton::MyButton(wxPanel *parent, int id, const wxString &label)
	: wxButton(parent, id, label, wxPoint(10, 50))
{
	Connect(
		GetId(),
		wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MyButton::OnClick));
}

void MyButton::OnClick(wxCommandEvent& event)
{
	wxPuts(wxT("event reached button class"));
	event.Skip(); // Propogate event to parent.
}