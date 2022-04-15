#if defined _TEXT_CTRL_HPP_==0
#define _TEXT_CTRL_HPP_ 1

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

#include "wx/stc/stc.h"
#include "wx/time.h"

class ModifiedNotebook;
class CodeHighliter;
class MyTab;

// This is to store the last pressed key in an array
struct KeyAndTime
{
    int unicodeKeycode;
    wxLongLong pressedTime;

};

// The place used to display the text. 
// Remember to make it editable before appending text or deleting text
// Since, many functions leave it uneditable.

class TextCtrl: public wxStyledTextCtrl{
public:

    // The tab which it belongs to
    MyTab* parentTab;

    // Since, we don't need much combination, 
    // setting the maximum number of key to be stored to 5. 
    // Only one will be used
    struct KeyAndTime lastKeyPressesArray[5];

    // for setting the time interval between key pressed for double keys
    long timeInterval = 500;

    //constructors
    TextCtrl();

    TextCtrl(wxWindow* window, MyTab* parentTab, wxWindowID wx_ID, const wxString name);

    //methods


    MyTab* getParent()
    {
        return parentTab;
    }

    wxFont textFont =  wxFont(11, wxFONTFAMILY_SCRIPT , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    //Saves the current file
    // Performs save as operation if the file wasn't saved before
    // Returns 1 if saved successfully else returns 0
    bool _SaveFile();

    //Performs save as operation
    // Also modifies the file path of the parent tab
    // Returns 1 if valid savelocation is found else returns 0
    bool _SaveFileAs();

    //for syntax highliting with one highliter object in each textctrl
    CodeHighliter* codehighliter;

    // Updates the highliter according to the file extension
    void updateHighlighter();

    //This will return the appropriate syntax highliter if available
    //The highliting is done according to fileExtension
    int getAppropriateHighliter();

private:
    //Event handlers

    // this is to get the specific key pressed 
    // both capital and small letters 
    // but this doesn't work for modifiers like escape key, shift key and so on
    void charEventHandler(wxKeyEvent& event);


    // this is for special key like escape key, shift key and so on
    // can also be used to get the key pressed regardless of keyborad state
    // (doesn't matter if shift is capslock is on, event.GetKeyCode() will give the same value)
    void keyDownEventHandler(wxKeyEvent& event);

    void OnSave(wxCommandEvent& event);

    void OnRedo(wxCommandEvent& event);

    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();

};

enum{
    MARGIN_LINE_NUMBERS,
};

#endif