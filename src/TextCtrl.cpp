
#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include "wx/stc/stc.h"

#include "textctrl.hpp"

#include "mytab2.hpp"
#include "modifiednotebook.hpp"
#include "codehighliter.hpp"
#include "wx/splitter.h"
#include "commandarea.hpp"

TextCtrl::TextCtrl(wxWindow* window, MyTab* parentTab, wxWindowID wx_ID, const wxString name)
    : wxStyledTextCtrl(window, wx_ID, wxDefaultPosition, wxSize(200, 100), wxRESIZE_BORDER | wxNO_BORDER)
    , parentTab(parentTab)
{
    this->SetInitialSize(wxSize(400, 200));

    // dynamically binding event handlers
    Bind(wxEVT_CHAR, &TextCtrl::charEventHandler, this);
    Bind(wxEVT_KEY_DOWN, &TextCtrl::keyDownEventHandler, this);

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


    // setting the selection color
    this->SetSelBackground(true, wxColour(200,200,200) );
    this->SetSelForeground(true, wxColour(0,0,0) );

    this->SetAdditionalSelBackground( wxColor(200,200,200) );
    this->SetAdditionalSelForeground( wxColour(0,0,0) );
    this->SetAdditionalCaretsVisible(false);

    // creating line numbers margin to the left
    // and setting up it's styles

    this->SetMarginWidth(MARGIN_LINE_NUMBERS, 25);

    this->StyleSetForeground(wxSTC_STYLE_LINENUMBER, this->StyleGetForeground(wxSTC_STYLE_DEFAULT));
    this->StyleSetBackground(wxSTC_STYLE_LINENUMBER, this->StyleGetBackground(wxSTC_STYLE_DEFAULT));
    this->StyleSetFont(wxSTC_STYLE_LINENUMBER, this->StyleGetFont(wxSTC_STYLE_DEFAULT));
    this->StyleSetSize(wxSTC_STYLE_LINENUMBER, 9);

    this->SetMarginType(MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);

    this->codehighliter = new CodeHighliter(this); 


    // key event couldn't capture control + key pressed so
    // generating accelerator table for that
    wxAcceleratorEntry entries[2];
    entries[0].Set(wxACCEL_CTRL,  (int) 'R',     wxID_REDO);
    entries[1].Set(wxACCEL_CTRL, (int) 'S', wxID_SAVE);
    wxAcceleratorTable accel(2, entries);
    this->SetAcceleratorTable(accel);

}

wxBEGIN_EVENT_TABLE(TextCtrl, wxStyledTextCtrl)
    
    EVT_MENU(wxID_SAVE, TextCtrl::OnSave)
    EVT_MENU(wxID_REDO, TextCtrl::OnRedo)
    
wxEND_EVENT_TABLE()

void TextCtrl::charEventHandler(wxKeyEvent &event)
{
    CommandArea* associatedCommandArea = this->getParent()->commandArea;
    wxChar uc = event.GetUnicodeKey();
    int keycode = event.GetKeyCode();
    if (uc != WXK_NONE)
    {
        // It's a "normal" character. Notice that this includes
        // control characters in 1..31 range, e.g. WXK_RETURN or
        // WXK_BACK, so check for them explicitly.
        if (uc >= 32)
        {
            if (!this->IsEditable()) // only do this if the editor is in command mode
            {
                int pos = this->GetCurrentPos();
                switch (uc)
                {
                // enter into insertion mode at the starting of the line
                case 73: // I --> 73
                    this->GotoLine(this->GetCurrentLine());
                    this->SetEditable(true);

                    // Notifying the user the tab is in insertion mode
                    associatedCommandArea->nofifyInsertionMode();
                    break;
                
                // enter into insertion mode at the current position
                case 105: // i --> 105
                    this->SetEditable(true);
                    associatedCommandArea->nofifyInsertionMode();
                    break;

                // move cursor one character to right and set editable
                case 97: // a --> 97
                    this->CharRight();
                    this->SetEditable(true);
                    associatedCommandArea->nofifyInsertionMode();
                    break;

                // move cursor to the end of line and set editable
                case 65: // A --> 65
                    this->LineEnd();
                    this->SetEditable(true);
                    associatedCommandArea->nofifyInsertionMode();
                    break;

                // move cursor left
                case 104: // h --> 104
                    this->CharLeft();
                    break;

                // move cursor down
                case 106: // j --> 106
                    this->LineDown();
                    break;

                // move cursor up
                case 107: // k --> 107
                    this->LineUp();
                    break;

                // move cursor right
                case 108: // l--> 108
                    this->CharRight();
                    break;
                
                // open a new line below the current line
                case 111: // o --> 111
                    this->SetEditable(true);
                    this->NewLine();
                    this->SetEditable(false);
                    break;

                // open a new line above the current line 
                case 79: // O --> 79
                    this->LineUp();
                    this->SetEditable(true);
                    this->NewLine();
                    this->SetEditable(false);
                    break;
                
                // cut a character right to the cursor
                case 120: // x --> 120
                    this->SetSelection(this->GetCurrentPos(), this->GetCurrentPos() + 1);
                    this->SetEditable(true);
                    this->Cut();
                    this->SetEditable(false);

                    // moves the caret one position to left if it is the end of the line
                    if(this->GetCurrentPos() == this->GetLineEndPosition(this->GetCurrentLine()))  this->CharLeft();
                    break;

                // paste after the cursor
                case 112: // p --> 112
                    this->SetEditable(true);
                    this->Paste();
                    this->SetEditable(false);
                    break;

                // paste before the cursor
                case 80: // P --> 80
                    this->SetEditable(true);  // Implementation is incomplete, performs same operation as the above case (112)
                    this->Paste();            // Setting changing position is selecting the pasted text
                    this->SetEditable(false); // and clearing the selection is brining the caret to the first place 
                    break;
                
                // undo
                case 117: // u --> 117
                    this->SetEditable(true);
                    this->Undo();
                    this->SetEditable(false);
                    break;

                // :           for entering into multicharcommand mode
                case 58: // : --> 58
                    this->getParent()->commandArea->enterMultiCharCommandMode();
                    this->getParent()->commandArea->SetFocus();
                    
                    // Going to last position as the colon will be on the last position
                    this->getParent()->commandArea->GotoPos(this->getParent()->commandArea->GetLastPosition());
                    break;

                default:
                    event.Skip();
                }
            }
            else // When the textctrl is editable
            {
                
                event.Skip();
   
            }  
        }
        else  // Since the the app will ignore modifiers so, this is not the correct place
              // to check for ctrl + alphabet, escape character and so on  (unicode from 1 to 31)
              // This will be checked by keyDownEventHandler 
        {
            if(this->IsEditable())
            {
                switch(uc)
                {
                    // If escape key is pressed, enter into command mode
                    case WXK_ESCAPE:
                        this->SetEditable(false);
                        break;
                
                    default:
                        event.Skip();
                }
            }
        }
    }
    else // No Unicode equivalent.
         // Might be handled by keyDownEventHandler
    {
       event.Skip();
    }
    return;
};


void TextCtrl::keyDownEventHandler(wxKeyEvent &event)
{
    int keyCode = event.GetKeyCode();

    if(this->IsEditable()) // when editable
    {
        switch (keyCode)
        {
            case WXK_ESCAPE:
                this->SetEditable(false);
                break;
            case 83: // S --> 83
                if(event.ControlDown()) 
                {                       // Performs save file operation only if 
                    this->_SaveFile();  // ctrl was hold down when s was pressed  
                }
                else event.Skip();                                    
                break;
            default:
                event.Skip();
        }
    }
    else // when not editable
    {
        // Handeling the keys and other when in command mode.
        switch(keyCode)
        {
        case 82: // R --> 82
            if(event.ControlDown())
            { 
                this->Redo(); // Do redo only if shift was held down when r was pressed
            }
            else event.Skip();
            break;
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

        default: 
            event.Skip();
        }
    }
}

bool TextCtrl::_SaveFile()
{
    wxString saveLocation;
    bool returnValue = 0;

    /**Opens native file explorer dialog box to select saving location
     * if the file isn't saved previously or new file is open
     **/
    if (this->getParent()->filePath.Cmp(_T("-NONE-"))==0)
    {
        returnValue = this->_SaveFileAs();
    }
    else
    {
        // sets saveLocation to currently open file save location if it's known.
        saveLocation = this->getParent()->filePath;
        returnValue = 1;
        this->SaveFile(saveLocation);
    }
    
    if(returnValue)
    {
        this->getParent()->updateNameLabel(saveLocation);   // updating the label of the parent tab
    }

    return returnValue;
}

void TextCtrl::OnSave(wxCommandEvent& event)
{
    if(this->IsEditable())
    {
        this->_SaveFile();
    }
    else
    {
        event.Skip();
    }
}

void TextCtrl::OnRedo(wxCommandEvent& event)
{
    if(!this->IsEditable())
    {
        this->Redo();
    }
    else 
    {
        event.Skip();
    }
}

bool TextCtrl::_SaveFileAs()
{
    // Opens native file explorer dialog box to select saving location
    wxString saveLocation = wxSaveFileSelector(
        "the current text",
        "TEXT files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
        "Fandral",
        this);

    if(!saveLocation.IsEmpty())
    {
        // Modifying the filepath of the tab object
        this->getParent()->filePath = saveLocation;

        // Also updating the label of the parent tab
        this->getParent()->updateNameLabel(saveLocation);
        
        return 1;
    }
    else return 0;
}


int TextCtrl::getAppropriateHighliter()
{
    wxString lowercaseFileExtension = this->getParent()->getFileExtension();
    lowercaseFileExtension.LowerCase();

    if(lowercaseFileExtension.compare(_T("cpp"))==0 || lowercaseFileExtension.compare(_T("cxx"))==0 ||
    lowercaseFileExtension.compare(_T("hpp"))==0 || lowercaseFileExtension.compare(_T("c++"))==0 || lowercaseFileExtension.compare(_T("cc"))==0 || 
    lowercaseFileExtension.compare(_T("c++"))==0 || lowercaseFileExtension.compare(_T("h++"))==0 )
    {
        return wxSTC_LEX_CPP;
    }
    else if((lowercaseFileExtension.compare(_T("py"))==0))
    {
        return wxSTC_LEX_PYTHON;
    }
    else if((lowercaseFileExtension.compare(_T("c"))==0))
    {
        return wxSTC_LEX_CPP; // since syntax for c and cpp are same for most of the cases
    }
    else
    {
        return -5;
    }
}

void TextCtrl::updateHighlighter()
{
    //Updating the highliter after each label update
    this->codehighliter->setLex_Language(this->getAppropriateHighliter());
}