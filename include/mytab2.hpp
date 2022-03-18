#if defined _MY_TAB_2_H==0
#define _MY_TAB_2_H 1

#include "wx/aui/auibook.h"

#include "modifiednotebook.hpp"
#include "textctrl.hpp"


class MyTab: public wxAuiNotebookPage
{
public:

    //The parent wxauinotebook which the page is contained in.
    ModifiedNotebook *parentNotebook;

    //The textctrl (inherited from wxstyledtextctrl) contained by the page
    TextCtrl *textCtrl;

    //File path of the currently open file in textctrl
    wxString filePath;

    //Title or label of the tab (auinotebookpage)
    wxString tabTitle;

    //index of the page (tab in this case) starting from zero.
    int index;

    //Creates a tab contained in parentNotebook with name and without any file path.
    MyTab(ModifiedNotebook* parentNotebook, const wxString& tabTitle);

    //For creating a tab contained in parentNotebook with file path and
    //also provides option to load the file present in the filepath into tab
    MyTab(ModifiedNotebook* parentNotebook, const wxString& tabTitle, wxString filePath, bool load);

};

#endif // _MY_TAB_2_H
