#include "app.hpp"

#include "wx/stc/stc.h"

#include "textctrl.hpp"

#include "mytab.hpp"

TextCtrl::TextCtrl(wxNotebook* parentNotebook, wxWindowID wx_ID, const wxString name)
    : wxStyledTextCtrl(parentNotebook, wx_ID, wxDefaultPosition, wxDefaultSize,
                       wxTE_MULTILINE | wxTE_RICH, name), parentNotebook(parentNotebook)
{

    // dynamically binding event handlers
    Bind(wxEVT_KEY_DOWN, &TextCtrl::KeyEvent, this);

    // Initially setting it to be editable
    this->SetEditable(true);

    // setting the initial styles

    this->StyleClearAll();

    // line numbers

    this->SetMarginWidth(MARGIN_LINE_NUMBERS, 25);

    this->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(75, 75, 75));
    this->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(220, 220, 220));

    this->SetMarginType(MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);
}

TextCtrl::TextCtrl(wxNotebook* parentNotebook, wxWindowID wx_ID, const wxString filePath, const wxString name)
    : TextCtrl(parentNotebook, wx_ID, name)
{
    this->filePath = filePath;
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
    if (this->filePath.Cmp(_T("")) == 0)
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

    this->parentNotebook->SetPageText(this->parentNotebook->GetSelection(), fileNameWithExtension);

    return fileNameWithExtension;
}

bool TextCtrl::updateTabFilePaths()
{
    for(MyTab& t: MyTab::getActiveTabsVector())
    {
        if(t.getCurrentlyActiveTextBox() == this)
        {
            t.setFilePath(this->filePath);
            return 1;
        }
    }
    return 0;
}