//Header file for MainWindow.cpp 


#if defined _MAIN_WINDOW_H_==0 //_MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_ 1

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

#include <AppConfig.h>

//For position of main window
#define DISPLAY_DIMENSIONS wxGetDisplaySize()
#define FULL_WIDTH DISPLAY_DIMENSIONS.GetWidth()
#define FULL_HEIGHT DISPLAY_DIMENSIONS.GetHeight()

//For size of the main window
#define MAIN_WINDOW_WIDTH FULL_WIDTH/2
#define MAIN_WINDOW_HEIGHT FULL_HEIGHT/2

//For postion of main window
#define MAIN_WINDOW_POS_X FULL_WIDTH/2 - MAIN_WINDOW_WIDTH/2
#define MAIN_WINDOW_POS_Y FULL_HEIGHT/2 - MAIN_WINDOW_HEIGHT/2

//For the text box
#include <wx/textctrl.h>

// Define a new frame type: this is going to be our main frame/window
class MyFrame : public wxFrame
{
public:
    // constructor(s)
    MyFrame(wxWindow* parent, const wxString &title);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSave();           //Overloading for taking close and other events manually
    void OnSaveAs();         //Overloading for taking close events and other events
    void OnSaveAs(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    /**the main text box of the editor
     * For now wxTextCtrl is used as it provides features and is
     * supported nativerly. We may decide to use other widgets as required.
     * So, make it as object oriented as possilbe and keep the implementation independent.
     **/
    
    wxTextCtrl *mainTextBox;

    /** Let's create array to keep track of open files for now 
     * we will be handeling this through object oriented approach in the future 
    **/
    wxArrayString* openedFiles = new wxArrayString();
    int currentlyOpenFileIndex = -2;  //Initially setting this to negative to signify no file has been opened.

    //For the background color of main text box
    wxColour mainTextBoxBackgroundColor = wxColour(8, 0, 23, 0.77);
    
    //For the text color of the text inside main text box 
    //For dark background:   wxColour(134, 188, 123, 0.77);
    wxColour mainTextBoxForegroundColor = *wxWHITE;

private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
};

enum
{
    //Windows
        Main_Window = wxID_HIGHEST + 1,

    //menu items
        //File Menu
            New_File = wxID_NEW,
            Open_File = wxID_OPEN,
            Save_File = wxID_SAVE,
            Save_File_As = wxID_SAVEAS,
            
            Editor_Quit = wxID_EXIT,

        //Edit menu
            Find_Item = wxID_FIND,
            Find_And_Replace_Item = wxID_REPLACE,


        //Help Menu
            Editor_About = wxID_ABOUT,

    //Text box
        TEXT_Main = wxID_ANY

};

#endif //_MAIN_WINDOW_H_