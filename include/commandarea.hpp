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

    // For highliting commands
    Codehighliter* codehighliter;

private:
    //Event handlers

};


#endif