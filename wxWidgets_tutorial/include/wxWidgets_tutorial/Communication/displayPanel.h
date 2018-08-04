#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/panel.h>

class DisplayPanel : public wxPanel
{
public:
	DisplayPanel(wxPanel *parentPanel);

	//void OnSetText(wxCommandEvent & event);
	void SetText(const wxString& textInput);

private:
	wxStaticText *displayedText;
};

#endif