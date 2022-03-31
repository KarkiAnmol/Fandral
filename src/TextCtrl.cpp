
#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include "wx/stc/stc.h"

#include "textctrl.hpp"

#include "mytab2.hpp"
#include "modifiednotebook.hpp"
#include "codehighliter.hpp"

TextCtrl::TextCtrl(ModifiedNotebook* parentNotebook, wxWindowID wx_ID, const wxString name)
    : wxStyledTextCtrl(parentNotebook, wx_ID, wxDefaultPosition, wxDefaultSize,
                       wxTE_MULTILINE | wxTE_RICH, name), parentNotebook(parentNotebook)
{

    // dynamically binding event handlers
    Bind(wxEVT_KEY_DOWN, &TextCtrl::KeyEvent, this);

    // Initially setting it to be editable
    this->SetEditable(true);

    // Setting tabs spacing equal to 4 spaces
    // This should be handled as per user's requirement in the future
    this->SetTabWidth(4);

    // Setting the default style, this will also be set when all styles are cleared

    //background color of the text area
    this->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(21, 21, 24, 0.2));

    //foreground color of the text area
    this->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColor("#F2F2F7FF"));

    //foreground color of the caret
    this->SetCaretForeground(wxColor("#F2F2F7FF"));

    //font of the text inside text area
    this->StyleSetFont(wxSTC_STYLE_DEFAULT, wxFont(11, wxFONTFAMILY_SCRIPT , wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

    //clearing previous styles and setting to default ones
    this->StyleClearAll();

    // creating line numbers margin to the left
    // and setting up it's styles

    this->SetMarginWidth(MARGIN_LINE_NUMBERS, 25);

    this->StyleSetForeground(wxSTC_STYLE_LINENUMBER, this->StyleGetForeground(wxSTC_STYLE_DEFAULT));
    this->StyleSetBackground(wxSTC_STYLE_LINENUMBER, this->StyleGetBackground(wxSTC_STYLE_DEFAULT));
    this->StyleSetFont(wxSTC_STYLE_LINENUMBER, this->StyleGetFont(wxSTC_STYLE_DEFAULT));
    this->StyleSetSize(wxSTC_STYLE_LINENUMBER, 9);

    this->SetMarginType(MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);

    this->codehighliter = new CodeHighliter(this); 

}

TextCtrl::TextCtrl(ModifiedNotebook* parentNotebook, wxWindowID wx_ID, const wxString filePath, const wxString name)
    : TextCtrl(parentNotebook, wx_ID, name)
{
    this->filePath = filePath;

    //only update the name of the tab if filepath isn't empty
    if(!filePath.compare("-NONE-")==0)
    {
        this->updateNameLabel(filePath);
    }
}

void TextCtrl::KeyEvent(wxKeyEvent &event)
{

    wxChar uc = event.GetUnicodeKey();
    if (uc != WXK_NONE)
    {
        // It's a "normal" character. Notice that this includes
        // control characters in 1..31 range, e.g. WXK_RETURN or
        // WXK_BACK, so check for them explicitly.
        if (uc >= 32)
        {
            if (!this->IsEditable()) // only do this if the editor is in command mode
            {
                switch (uc)
                {
                // If i is pressed when the text ctrl is not editable, set it back to be editable
                // this is only for now, the implementation might be different in future
                case 73: // B --> 73
                    this->SetEditable(true);
                    break;

                // move cursor left
                case 72: // H--> 72
                    this->CharLeft();
                    break;

                // move cursor down
                case 74: // J--> 74
                    this->LineDown();
                    break;

                // move cursor up
                case 75: // K--> 75
                    this->LineUp();
                    break;

                // move cursor right
                case 76: // L--> 76
                    this->CharRight();
                    break;

                default:
                    event.Skip();
                }
            }
            else
                event.Skip();
        }
        else
        {
            // It's a control character
            switch (uc)
            {
            // If escape key is pressed, enter into command mode
            case WXK_ESCAPE:
                this->SetEditable(false);
                break;
            case WXK_CONTROL_S:
                this->_SaveFile();
            default:
                event.Skip();
            }
        }
    }
    else // No Unicode equivalent.
    {
        // It's a special key, deal with all the known ones:

        int keyCode = event.GetKeyCode();
        switch(keyCode)
        {
            case WXK_LEFT: // Left arrow key
                this->CharLeft();
                break;
            case WXK_RIGHT: // Right arrow key
                this->CharRight();
                break;
            case WXK_UP:    // Up arrow key
                this->LineUp();
                break;
            case WXK_DOWN:  // Down arrow key
                this->LineDown();
                break;
        }
    }
    return;
};

void TextCtrl::_SaveFile()
{
    wxString saveLocation;

    /**Opens native file explorer dialog box to select saving location
     * if the file isn't saved previously or new file is open
     **/
    if (this->filePath.Cmp(_T("-NONE-")) == 0)
    {
        this->_SaveFileAs();
        return;
    }
    else
    {
        // sets saveLocation to currently open file save location if it's known.
        saveLocation = this->filePath;
    }
    
    this->SaveFile(saveLocation);
    this->updateNameLabel(saveLocation);
}

void TextCtrl::_SaveFileAs()
{
    // Opens native file explorer dialog box to select saving location
    wxString saveLocation = wxSaveFileSelector(
        "the current text",
        "TEXT files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
        "Fandral",
        this);

    // Modifying the filepath of the tab object
    this->filePath = saveLocation;

    this->SaveFile(saveLocation);
    this->updateNameLabel(saveLocation);
}

wxString TextCtrl::updateNameLabel(const wxString &fileLocation)
{
    this->updateTabFilePaths();
    wxString tempFileLocation = fileLocation.Clone();

// The file separator in windows will be '\\' so it is replaced with '\'
#if defined __WXMSW__
    // this will be file name only
    tempFileLocation.Replace("\\", "/", true);
#endif

    wxString fileNameWithExtension = tempFileLocation.AfterLast(_T('/'));

    // Error in changing the name of tab can be here
    // Due to error in GetPageIndex as the page may not be in notebook
    // Handle this accordingly
    this->parentNotebook->SetPageText(parentNotebook->GetPageIndex(this), fileNameWithExtension);

    //Updating the highliter after each label update
    this->codehighliter->setLex_Language(this->getAppropriateHighliter(this->filePath));

    return fileNameWithExtension;
}

bool TextCtrl::updateTabFilePaths()
{
    for(MyTab* tab: parentNotebook->openedTabsVector)
    {
        if(tab->textCtrl == this)
        {
            tab->filePath = this->filePath;
            return 1;
        }
    }
    return 0;
}

wxString TextCtrl::getFileExtension()
{
    wxString fileExtension = this->filePath.AfterLast(_T('.'));

    return fileExtension;
}

int TextCtrl::getAppropriateHighliter(const wxString& fileExtension)
{
    wxString lowercaseFileExtension = fileExtension.AfterLast(_T('.'));
    lowercaseFileExtension.LowerCase();

    if(lowercaseFileExtension.compare(_T("cpp"))==0)
    {
        return wxSTC_LEX_CPP;
    }
    else if((lowercaseFileExtension.compare(_T("py"))==0))
    {
        return wxSTC_LEX_PYTHON;
    }
    else if((lowercaseFileExtension.compare(_T("c"))==0))
    {
        return wxSTC_LEX_CPP;
    }
    else
    {
        return -5;
    }
}