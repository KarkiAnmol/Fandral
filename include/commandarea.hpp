#if defined _COMMAND_AREA_HPP_==0  
#define _COMMAND_AREA_HPP_ 1

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

class MyTab;
class Codehighliter;

class CommandArea: public wxStyledTextCtrl
{
public:

    // The tab which contains particular command area
    MyTab* parentTab;

    // For taking a whole line command
    // as soon as the user presses : it enters into line command mode / multicharacter command mode
    bool inMultiCharCommandMode = false;

    // ctor
    CommandArea(wxWindow* parent, MyTab* parentTab, wxWindowID wx_ID=wxID_ANY);

    // Returns the tab which it is contained in
    MyTab* getParent()
    {
        return parentTab;
    }

    // For appending text
    // This is first set the CommandArea as editable then append text
    // then set it back to non editable
    void AppendText(const wxString& text);

    // appends the text to command area and applys the
    // given style to it.
    // Don't pass escape sequence inside of the text.
    void AppendTextWithStyle(const wxString& text, int style);

    // For highliting commands
    Codehighliter* codehighliter;

    // sets the desired value of multiCharacterCommand
    // Here true implies that the command area will be made editable and 
    // it will take the input after : and before pressing enter key
    void setInMultiCharCommandMode(bool multi=true);

    // Returns true if the command area is in 
    // multichar command mode
    bool isInMultiCharCommandMode();


    // Becomes ready to take multichar command.
    // Firstly checks if it is not in multicharcommand mode
    // then makes command area editable and appends "\n:"
    void enterMultiCharCommandMode();

    // Checks if it is in multichar command mode
    // and if true exits from it by
    // making it undeditable.
    // This also returns the command which was typed previously 
    // This is done to directly get the command while exiting the command mode if required
    wxString exitMultiCharCommandMode();

    // returns the command as wxstring
    // assumes that the command is in previous or the current line
    // current line takes priority over teh previous line
    // returns wxString("NO COMMAND FOUND") if there isn't colon in the starting character of 
    // previous and the current line
    wxString getMultiCharCommand();

    // execute the provided multichar command
    void executeMultiCharCommand(wxString command);

    // nofifies the user by appending the text in command area
    void nofifyInsertionMode();

private:
    // event handlers

    // this is to get the specific key pressed 
    // both capital and small letters 
    // but this doesn't work for modifiers like escape key, shift key and so on
    void charEventHandler(wxKeyEvent& event);


    // this is for special key like escape key, shift key and so on
    // can also be used to get the key pressed regardless of keyborad state
    // (doesn't matter if shift is capslock is on, event.GetKeyCode() will give the same value)
    void keyDownEventHandler(wxKeyEvent& event);


};

enum{
    styleMask = 0, 
    Left_Margin,
    Style_Error = 4,
    Style_Insertion_Mode,
    Style_Find,
    Style_Replace,
    Style_MultiChar_Command,
    Style_Operation_Successful,
   
};


#endif