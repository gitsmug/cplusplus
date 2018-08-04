#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

// For compilers that support precompilation, includes "wx/wx.h".

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/panel.h>

class ControlPanel : public wxPanel
{
public:
	ControlPanel(wxPanel *parentPanel);

	void OnPlus(wxCommandEvent & event);
	void OnMinus(wxCommandEvent & event);

private:
	int count;
	wxPanel *parentPanel;
	wxButton *plusButton;
	wxButton *minusButton;

	void UpdateDisplay();
};

#endif