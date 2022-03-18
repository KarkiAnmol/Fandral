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

#include "AppConfig.h"

#include "modifiednotebook.hpp"

class TextCtrl;

//For position of main window
#define DISPLAY_DIMENSIONS wxGetDisplaySize()
#define FULL_WIDTH DISPLAY_DIMENSIONS.GetWidth()
#define FULL_HEIGHT DISPLAY_DIMENSIONS.GetHeight()

//For size of the main window
#define MAIN_WINDOW_WIDTH FULL_WIDTH*0.75
#define MAIN_WINDOW_HEIGHT FULL_HEIGHT*0.75

//For postion of main window
#define MAIN_WINDOW_POS_X FULL_WIDTH/2 - MAIN_WINDOW_WIDTH/2
#define MAIN_WINDOW_POS_Y FULL_HEIGHT/2 - MAIN_WINDOW_HEIGHT/2

// Define a new frame type: this is going to be our main frame/window
class MyFrame : public wxFrame
{
public:
    // constructor(s)
    MyFrame(const wxString &title);

    //for exiting the app
    void OnQuit(wxCommandEvent& event);

    //Displays about dialog box
    void OnAbout(wxCommandEvent& event);

    //Creates a new tab with a text area (tab) inside it without a file or filepath
    void OnNew(wxCommandEvent& event);

    //Creates a new instace of MyFrame which is independent of previous (parent) instance
    void OnNewWindow(wxCommandEvent &event);

    //For opening a editable file using native file selector dialog.
    //Also checks if the same file is alrady open in other tab
    //and performs operation as per user's response.
    void OnOpen(wxCommandEvent& event);

    //Performs save as behaviour if the file hasn't been saved before
    //else saves the current content.
    //
    //Only called by event handelers
    void OnSave(wxCommandEvent& event);

    //Performs save as behaviour if the file hasn't been saved before
    //else saves the current content.
    //
    //Overloading for taking close event and other function calls
    void OnSave();

    //Performs save as behaviour even if the file was saved before
    //Meaning it will open a save dialog and ask for name and extension.
    //
    //Overloaded for taking close event and other function calls
    void OnSaveAs();

    //Performs save as behaviour even if the file was saved before
    //Meaning it will open a save dialog and ask for name and extension
    //
    //Only called by event handelers
    void OnSaveAs(wxCommandEvent& event);

    //For capturing close event and performing some pre-close actions
    void OnClose(wxCloseEvent& event);

    //Setting one frame (app window) to use only one notebook
    //For now one frame will have only one notebook
    ModifiedNotebook* mainNotebook;

    //For the background color of main text box
    wxColour textBoxBackgroundColor = wxColour(0.11, 0.11, 0.12, 1.0);
    
    //For the text color of the text inside main text box 
    wxColour textBoxForegroundColor =  wxColour("#F2F2F7FF");

    //For setting the font style and size for text inside text control
    //wxFont myFont = wxFont(MAIN_WINDOW_FONT_SIZE, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    //To handel nullptr properly and get a valid text box.
    //Returns reference to currently active text box or a dummy one.
    TextCtrl& getCurrentlyActiveTextBox();

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
            New_Window,
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

};

#endif //_MAIN_WINDOW_H_