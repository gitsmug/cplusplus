#ifndef SANDBOXGAME_MAINFRAME_H
#define SANDBOXGAME_MAINFRAME_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "mainCanvas.h"

namespace sandboxGame
{
	class MainFrame : public wxFrame
	{
	public:
		MainFrame(const wxString& title);

		void OnQuit(wxCommandEvent & event);

	private:
		wxPanel *parentPanel;

		wxMenuBar *menubar;
		wxMenu *file;
		wxMenuItem *quit;

		MainCanvas *glPane;
	};
}
#endif