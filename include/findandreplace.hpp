// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include <wx/stc/stc.h>



#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/dialog.h>

class MyFrame;

class FindDialog: public wxDialog
{
public:
    MyFrame* parentFrame;
    wxTextCtrl* findBox;
    wxTextCtrl* replaceBox;
    wxBoxSizer* findDialogSizer;

    // this makes it easier whether to repopulate the controls when replace is placed
    // if replace is on previously, we don't need to repopulate the controls
    bool isReplacing = false;

    FindDialog(MyFrame *parent, bool replace = false, wxWindowID id=wxID_ANY,
            const wxString &title = "Find And Replace",
            const wxPoint &pos = wxDefaultPosition,
            const wxSize &size = wxDefaultSize,
            long style = wxDEFAULT_DIALOG_STYLE);

    MyFrame* getParent(){return parentFrame;}
    wxTextCtrl* getFindBox(){return findBox;}
    wxTextCtrl* getReplaceBox(){return replaceBox;}

    // returns the text inside of the find box
    wxString getFindText();

    // returns the text inside of the replace box
    wxString getReplaceText();

private:
    // event handlers

    void onFind(wxCommandEvent& event);
    
    void onReplace(wxCommandEvent& event);

    void onReplaceAll(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum
{
    Editor_Find = wxID_FIND,
    Editor_Replace = wxID_REPLACE,
    Editor_Replace_All = wxID_REPLACE_ALL,
};