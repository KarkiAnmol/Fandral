#include "app.hpp"

#include "wx/stc/stc.h"

#include "textctrl.hpp"

TextCtrl::TextCtrl(wxWindow *parentWindow, wxWindowID wx_ID, const wxString name)
    : wxStyledTextCtrl(parentWindow, wx_ID, wxDefaultPosition, wxDefaultSize,
                       wxTE_MULTILINE | wxTE_RICH, name)
{

    //dynamically binding event handlers
    Bind(wxEVT_KEY_DOWN, &TextCtrl::KeyEvent, this);


    //Initially setting it to be editable
    this->SetEditable(true);

    //setting the initial styles

    this->StyleClearAll();

    //line numbers

    this->SetMarginWidth(MARGIN_LINE_NUMBERS, 25);

    this->StyleSetForeground(wxSTC_STYLE_LINENUMBER, wxColour(75, 75, 75));
    this->StyleSetBackground(wxSTC_STYLE_LINENUMBER, wxColour(220, 220, 220));

    this->SetMarginType(MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);
}

//Event handlers

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
            if(!this->IsEditable()) //only do this if the editor is in command mode
            {
                switch(uc)
                {
                    //If i is pressed when the text ctrl is not editable, set it back to be editable
                    //this is only for now, the implementation might be different in future
                    case 73:  //B --> 73
                        this->SetEditable(true);
                        break;

                    //move cursor left
                    case 72: //H--> 72
                        this->CharLeft();
                        break;

                    //move cursor down 
                    case 74: //J--> 74
                        this->LineDown();
                        break;

                    //move cursor up
                    case 75: //K--> 75
                        this->LineUp();
                        break;

                    //move cursor right
                    case 76: //L--> 76
                        this->CharRight();
                        break;
                    
                    default:
                        event.Skip();
                }
            }
            else event.Skip();
        }
        else
        {
            // It's a control character
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
    else // No Unicode equivalent.
    {
        // It's a special key, deal with all the known ones:
    }
    return;
};
