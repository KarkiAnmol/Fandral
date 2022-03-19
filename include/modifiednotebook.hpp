#if defined _MODIFIED_NOTEBOOK_H_==0
#define _MODIFIED_NOTEBOOK_H_ 1

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

#include <wx/aui/auibook.h>

class MyTab;

//Class derived publicly from wxAuiNotebook
//This aims to add tabs as the ModifiedNotebook content
//for easier manipulation of filepaths, tabnames and textctrls
//contained inside the tabs

class ModifiedNotebook: public wxAuiNotebook
{
public:
    //A vector to store the opened tabs (as pointers)
    //As ModifiedNotebook remains as long as mainwindow is open
    //there is no need to make it static for now
    //Just be sure to handle separate windows accordingly, if it gives exception
    std::vector<MyTab*> openedTabsVector;

    //Returns the iterator at the posisition matching the given tab pointer in openedTabsVector
    std::vector<MyTab*>::iterator iteratorAt(MyTab* tab);

    ModifiedNotebook();

    ModifiedNotebook(wxWindow* parent, wxWindowID id);

    //This will add a tab as a new page
    //In reality textctrl gets added to notebook and tab gets added to tab vector
    //
    //This will get textctrl contained inside tab and it's title
    //So, be sure to update those before adding.
    //Set select to false only if you want to add tab in background or not set the textctrl as the active one
    bool AddPage(MyTab* tab, bool select);

    //Returns the tab in which currently selected textctrl is contained
    MyTab* getCurrentlyActiveTab();

private:
    // Handles the closign of a particular page (tab in our case)
    void OnClose(wxAuiNotebookEvent& event);

};

#endif //_MODIFIED_NOTEBOOK_H