#if defined _TEXT_CTRL_HPP_==0
#define _TEXT_CTRL_HPP_ 1

#include "app.hpp"

#include "wx/stc/stc.h"
#include <wx/aui/auibook.h>

class TextCtrl: public wxStyledTextCtrl{
public:
    //Data members

    //For keeping track of the savelocation and openlocation
    wxString filePath=_T("");

    //Keeping track of the notebook which it belongs to
    wxAuiNotebook* parentNotebook;

    //constructors
    TextCtrl();

    TextCtrl(wxAuiNotebook* notebook, wxWindowID wx_ID, const wxString name);

    TextCtrl(wxAuiNotebook* notebook, wxWindowID wx_ID, const wxString filePath, const wxString name);

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