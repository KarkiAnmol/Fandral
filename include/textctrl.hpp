#if defined _TEXT_CTRL_HPP_==0
#define _TEXT_CTRL_HPP_ 1

#include "app.hpp"

#include "wx/stc/stc.h"
#include "wx/notebook.h"

class TextCtrl: public wxStyledTextCtrl{
public:
    //Data members

    //For keeping track of the savelocation and openlocation
    wxString filePath=_T("");

    //Keeping track of the notebook which it belongs to
    wxNotebook* parentNotebook;

    //constructors
    TextCtrl();

    TextCtrl(wxNotebook* notebook, wxWindowID wx_ID, const wxString name);

    TextCtrl(wxNotebook* notebook, wxWindowID wx_ID, const wxString filePath, const wxString name);

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
    void KeyEvent(wxKeyEvent& event);

};

enum{
    MARGIN_LINE_NUMBERS,
};

#endif