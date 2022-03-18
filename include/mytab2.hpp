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

#include "wx/aui/auibook.h"

class ModifiedNotebook;
class TextCtrl;


class MyTab: public wxAuiNotebookPage
{
public:

    //The parent wxauinotebook which the page is contained in.
    ModifiedNotebook *parentNotebook;

    //The textctrl (inherited from wxstyledtextctrl) contained by the page
    TextCtrl *textCtrl;

    //File path of the currently open file in textctrl
    //This is set to be empty at first
    //Setting it empty makes it easier to check if it has been saved before
    wxString filePath=_T("-NONE-");

    //Title or label of the tab (auinotebookpage)
    wxString tabTitle;

    //index of the page (tab in this case) starting from zero.
    int index;

    //Creates a tab contained in parentNotebook with name and without any file path.
    MyTab(ModifiedNotebook* parentNotebook, const wxString& tabTitle);

    //For creating a tab contained in parentNotebook with file path and
    //also provides option to load the file present in the filepath into tab
    MyTab(ModifiedNotebook* parentNotebook, const wxString& tabTitle, wxString filePath, bool load);

    //Sets the particular tab as active one
    //Specifically setting the textctrl contained inside the tab as active one
    void setAsActive();

};

#endif // _MY_TAB_2_H
