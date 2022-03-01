
#include "app.hpp"
#include "mainwindow.hpp"     //For MyFrame class
#include "wx/splash.h"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

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
        (int)Editor_VERSION_MAJOR,
        (int)Editor_VERSION_MINOR);

    // create the main application window
    MyFrame *frame = new MyFrame(title);

    /*For splash screen on startup
    wxBitmap bitmap;
    if (bitmap.LoadFile(
        wxString::Format(PROJECT_ABSOLUTE_PATH
        "/resources"
        "/fandralSplash.png"
        ),
        wxBITMAP_TYPE_PNG))
    {
        wxSplashScreen* splash = new wxSplashScreen(bitmap,
            wxSPLASH_CENTRE_ON_PARENT|wxSPLASH_TIMEOUT,
            1500, frame, -1, wxPoint(MAIN_WINDOW_POS_X, MAIN_WINDOW_POS_Y), wxSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT),
            wxBORDER_SIMPLE|wxSTAY_ON_TOP);
    }
    wxYield();*/

    // show the application window (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
