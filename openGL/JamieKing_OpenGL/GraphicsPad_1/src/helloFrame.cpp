// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../include/wxWidgets_openGL/helloFrame.h"

HelloFrame::HelloFrame(const wxString &title)
	:wxFrame((wxFrame *)NULL, wxID_ANY, title, wxDefaultPosition, wxSize(600, 400))
{
	menubar = new wxMenuBar();
	file = new wxMenu();
	quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit"));
	file->Append(quit);
	menubar->Append(file, wxT("&File"));

	SetMenuBar(menubar);

	Connect(
		wxID_EXIT,
		wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(HelloFrame::OnQuit));


	int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};

	glPane = new HelloCanvas(this, args);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(glPane, 1, wxEXPAND);

	SetSizer(sizer);
	SetAutoLayout(true);
}

void HelloFrame::OnQuit(wxCommandEvent & /* event */)
{
	Close(true);
}