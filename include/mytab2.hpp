#if defined _MY_TAB_2_H==0
#define _MY_TAB_2_H 1

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

class ModifiedNotebook;
class TextCtrl;
class CommandArea;
class wxAuiManager;
class wxSplitterWindow;


class MyTab: public wxWindow
{
public:

    //The parent wxauinotebook which the tab is contained in.
    ModifiedNotebook *parentNotebook;

    //The textctrl (inherited from wxstyledtextctrl) contained by the tab
    TextCtrl *textCtrl;

    // The command area contained by the tab
    CommandArea *commandArea;

    //File path of the currently open file in textctrl
    //This is set to be "-NONE-" at first
    //Setting it to "-NONE-" makes it easier to check if it has been saved before
    wxString filePath;

    //Title or label of the tab (auinotebookpage)
    wxString tabTitle;

    //index of the page (tab in this case) starting from zero.
    int index;

    // For creating a tab contained in parentNotebook with file path and
    // also provides option to load the file present in the filepath into tab
    //
    // The tab is automatically added to parentNotebook as page.
    MyTab(ModifiedNotebook* parentNotebook, const wxString& tabTitle, wxString filePath=_T("-NONE_"), bool load=false);

    //Sets the particular tab as active one
    //Specifically setting the textctrl contained inside the tab as active one
    void setAsActive();

    //Closes the tab
    bool close();

    // Userful for showing/ hiding the command area 
    wxSplitterWindow* tabSplitter;

};

#endif // _MY_TAB_2_H
