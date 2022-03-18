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
#include <wx/aui/auibook.h>

class ModifiedNotebook;
class CodeHighliter;


class TextCtrl: public wxStyledTextCtrl{
public:
    //Data members

    //For keeping track of the savelocation and openlocation
    wxString filePath=_T("");

    //Keeping track of the notebook which it belongs to
    ModifiedNotebook* parentNotebook;

    //constructors
    TextCtrl();

    TextCtrl(ModifiedNotebook* notebook, wxWindowID wx_ID, const wxString name);

    TextCtrl(ModifiedNotebook* notebook, wxWindowID wx_ID, const wxString filePath, const wxString name);

    //methods

    //For updating the label of the tab
    wxString updateNameLabel(const wxString& fileLocation);

    //Saves the current file
    void _SaveFile();

    //Performs save as operation
    void _SaveFileAs();

    //updates the tab file paths to the correct one
    //Taking the correct one from textctrl
    //this is done after each save and saveas operation
    bool updateTabFilePaths();

    //for syntax highliting with one highliter object in each textctrl
    CodeHighliter* codehighliter;

    //Returns the extension of currently open file (if path is set)
    wxString getFileExtension();

    //This will return the appropriate syntax highliter if available
    //The highliting is done according to fileExtension
    int getAppropriateHighliter(const wxString& fileExtension);

private:
    //Event handlers

    //Handles key event when the wxstyledtextctrl is active
    //This should handle every key event.
    //When the textctrl isn't in command mode, the keyevents are skipped and passed to default handlers
    //when esc key is pressed, the textctrl enters command mode.
    //when it is in command mode, pressing i key will exit from command mode (for now).
    //few keys performs command simiar to vim
    //such as h,j,k,l will move cursor right, down, up and left respectively so does the arrow keys
    void KeyEvent(wxKeyEvent& event);

};

enum{
    MARGIN_LINE_NUMBERS,
};

#endif