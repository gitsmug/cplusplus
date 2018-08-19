#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class CustomDialog : public wxDialog
{
public:
	CustomDialog(const wxString & title, const wxString &fileName);

private:
	wxTextCtrl *textCtrl;
};

#endif