#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "controlPanel.h"
#include "displayPanel.h"

class ControlWindow : public wxFrame
{
public:
	ControlWindow(const wxString& title);

	DisplayPanel *displayPanel;

private:
	wxPanel *parentPanel;
	ControlPanel *controlPanel;
};

#endif