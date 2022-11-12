
#include "app.hpp"
#include "mainwindow.hpp"     //For MyFrame class
#include "wx/splash.h"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include <wx/display.h>

// ============================================================================
// implementation
// ============================================================================
IMPLEMENT_APP(App)
// ----------------------------------------------------------------------------
// the application class
// ----------------------------------------------------------------------------

// 'Main program' equivalent: the program execution "starts" here
bool App::OnInit()
{
    // call the base class initialization method, currently it only parses a
    // few common command-line options but it could be do more in the future
    /*if ( !wxApp::OnInit() )
        return false;*/


    wxString title;
    title = wxString::Format("Fandral Editor  V %d.%d    ",
        (int)Fandral_Editor_VERSION_MAJOR,
        (int)Fandral_Editor_VERSION_MINOR);

    // create the main application window
    MyFrame *frame = new MyFrame(title);

    // show the application window (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // determining the position to place the whole window

    wxDisplay currentDisplay(wxDisplay::GetFromWindow(frame));
    wxRect screen = currentDisplay.GetClientArea();

    wxPoint left = screen.GetTopLeft(); // leftmost position
    wxPoint windowTopLeft = wxPoint(left.x + 0.1 * screen.GetWidth(), left.y - 10); // placing it 10% to the left

    frame->SetPosition(windowTopLeft);
    frame->SetMinSize(wxSize(-1, -1)); // making it resizeable beyond minimal size
    

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
