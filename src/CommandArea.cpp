#include "commandarea.hpp"
#include "mytab2.hpp"
#include "textctrl.hpp"

CommandArea::CommandArea(wxWindow* parent, MyTab* parentTab, wxWindowID wx_ID)
: wxStyledTextCtrl(parent, wx_ID, wxDefaultPosition, wxSize(400, 60), wxNO_BORDER), parentTab(parentTab)
{
    // dynamically binding event handlers
    Bind(wxEVT_CHAR, &CommandArea::charEventHandler, this);
    Bind(wxEVT_KEY_DOWN, &CommandArea::keyDownEventHandler, this);

    this->SetInitialSize(wxSize(400, 60));

    // Setting it to be non editable
    this->SetEditable(false);

    //background color of the text area
    this->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(35, 35, 35, 0.2));

    //foreground color of the text area
    this->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColor("#F2F2F7FF"));

    //foreground color of the caret
    this->SetCaretForeground(wxColor("#F2F2F7FF"));

    // This will set the default styles
    this->StyleClearAll();

    // Setting the margin width to mininum and setting the background color same as default one 
    // as to make it invisible
    this->SetMarginWidth(Left_Margin, 2);
    this->StyleSetForeground(wxSTC_STYLE_LINENUMBER, this->StyleGetForeground(wxSTC_STYLE_DEFAULT));
    this->StyleSetBackground(wxSTC_STYLE_LINENUMBER, this->StyleGetBackground(wxSTC_STYLE_DEFAULT));

    // Setting margin as a line number margin
    this->SetMarginType(Left_Margin, wxSTC_MARGIN_NUMBER);

}

void CommandArea::AppendText(const wxString& text)
{
    this->SetEditable(true);
    wxStyledTextCtrl::AppendText(text);
    this->GotoLine(this->GetNumberOfLines());
    this->SetEditable(false);
    return;
}

void CommandArea::setInMultiCharCommandMode(bool multi)
    {
        this->inMultiCharCommandMode = multi; 
    }

bool CommandArea::isInMultiCharCommandMode()
{
    return this->inMultiCharCommandMode;
}

void CommandArea::enterMultiCharCommandMode()
{
    // only goes into multi character command mode if it's not already in that mode
    if(!isInMultiCharCommandMode())
    {

        // going to the last position before appending the colon.
        this->GotoPos(this->GetLastPosition());    

        // goes into new line
        this->AppendText("\n:");
        setInMultiCharCommandMode(true);
    }
}


wxString CommandArea::exitMultiCharCommandMode()
{
    // Only exits from multi character command mode if it was in that mode previously
    if(isInMultiCharCommandMode())
    {
        // goes into new line
        this->AppendText("\n");

        // getting the command before changing the inmulticommandmode value to false
        // as the function relies on the commandarea being in multicharcommandmode
        wxString command = this->getMultiCharCommand();

        this->setInMultiCharCommandMode(false);        

        return command;
    }
}


wxString CommandArea::getMultiCharCommand()
{
    if(this->isInMultiCharCommandMode())
    {
        wxString currentLineCommand = this->GetLineText(this->GetCurrentLine());

        // The command may be in previous line as when enter is pressed the position may move into the new line
        wxString previousLineCommand = this->GetLineText(this->GetCurrentLine() - 1);
        if(currentLineCommand[0]==':')
        {
            // removes the colon from the string
            return currentLineCommand.Remove(0, 1);
        }
        else if(previousLineCommand[0]==':')
        {
            // removes the colon from the string
            return previousLineCommand.Remove(0, 1);
        }
        else 
        {
            return wxString("NO COMMAND FOUND");
        }
    }
    return wxString("NO COMMAND FOUND");
}

void CommandArea::charEventHandler(wxKeyEvent& event)
{
    wxChar uc = event.GetUnicodeKey();
   
    if(uc > 31 && uc < 127)
    {
        // only append the text if the command is in command mode
        if(this->isInMultiCharCommandMode())
        {
            this->AppendText(wxString(uc));
        }
        else
        {
            event.Skip();
        }
    }
    else 
    {
        event.Skip();
    }

}

 void CommandArea::keyDownEventHandler(wxKeyEvent& event)
 {
    int commandLength;
    int keycode = event.GetKeyCode();
     if(this->isInMultiCharCommandMode())
        {
            switch (keycode)
            {
            case WXK_BACK: // For backspace key press

                // since the method won't return the first : 
                // the length will be one less than the total length

                commandLength = this->getMultiCharCommand().length();
                
                this->SetEditable(true);
                this->DeleteBack();
                this->SetEditable(false);

                // if : is the only remaining text, set the focus back to textctrl
                // and exit from multichar command mode
                if( commandLength == 0)
                {
                    this->exitMultiCharCommandMode();
                    this->getParent()->textCtrl->SetFocus();
                }
            
                break;
            case WXK_RETURN:    // for enter key press

            
            default:
                event.Skip();
                break;
            }
        }
        else
        {
            event.Skip();
        }
 }

 void CommandArea::executeMultiCharCommand(wxString command)
 {
    if(command.Cmp("wq")==0 || command.Cmp("x")==0 || command.Cmp("ZZ")==0) // save and exit
    {
        this->getParent()->textCtrl->_SaveFile();
        

    }
    else if(command.Cmp("q")==0) // quit, asks to save if there are unsaved changes
    {

    }
    else if(command.Cmp("q!") || command.Cmp("ZQ")) // quit and throw away unsaved changes
    {

    }
    else if(command.Cmp("w")==0)
    {

    }

 }