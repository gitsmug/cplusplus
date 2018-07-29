// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class Helpers : public wxFrame
{
public:
	Helpers(const wxString& title);
	void Demo();
};