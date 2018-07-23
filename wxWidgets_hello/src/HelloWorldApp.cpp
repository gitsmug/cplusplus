#include <iostream>

// For compilers that don't support precompilation, include "wx/wx.h"
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#	include "wx/wx.h"
#endif

#include "../include/hello_project/HelloWorldApp.h"
#include "../include/hello_project/stuff/myclass.h"

IMPLEMENT_APP(HelloWorldApp)

// This is executed upon startup, like 'main()' in non-wxWidgets programs.
bool HelloWorldApp::OnInit()
{
	std::cout << "Hello, from HelloWorldApp." << std::endl;

	MyClass mc;
	mc.PrintTest();

	wxFrame *frame = new wxFrame((wxFrame*) NULL, -1, _T("Hello wxWidgets World"));
	frame->CreateStatusBar();
	frame->SetStatusText(_T("Hello World"));
	frame->Show(true);
	SetTopWindow(frame);

	return true;
}
