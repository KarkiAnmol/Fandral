
#include "app.h"
#include "mainwindow.h"

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
    if ( !wxApp::OnInit() )
        return false;

    wxString title;
    title = wxString::Format("Fandral Editor  V %d.%d    ",
        (int)Editor_VERSION_MAJOR,
        (int)Editor_VERSION_MINOR);
    
    // create the main application window
    MyFrame *frame = new MyFrame(title);

    // show the application window (the frames, unlike simple controls, are not shown when
    // created initially)
    frame->Show(true);

    // success: wxApp::OnRun() will be called which will enter the main message
    // loop and the application will run. If we returned false here, the
    // application would exit immediately.
    return true;
}
