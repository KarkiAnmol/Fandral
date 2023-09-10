
#include <wx/aui/auibook.h>

#include "modifiednotebook.hpp"

#include "textctrl.hpp"
#include "mytab2.hpp"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include <memory>
#include <vector>
#include <bits/stdc++.h>

#include <iostream>
#include <stdexcept>

ModifiedNotebook::ModifiedNotebook() : wxAuiNotebook() {}

ModifiedNotebook::ModifiedNotebook(wxWindow *parent, wxWindowID id) 
: wxAuiNotebook(parent, id, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE| wxAUI_NB_BOTTOM | wxAUI_NB_CLOSE_ON_ACTIVE_TAB)
{
    // Initially clearing the tabs stored in openedTabsVector
    this->openedTabsVector.clear();

    this->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &ModifiedNotebook::OnClose, this);
    this->SetMeasuringFont(wxFont(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    this->SetAutoLayout(true);
}

bool ModifiedNotebook::AddPage(MyTab* tab, bool select)
{
    //adding page to wxauinotebook
    if(wxAuiNotebook::AddPage(tab, tab->tabTitle, select))
    {
        this->openedTabsVector.push_back(tab);

        return true;
    }
    else 
    {
        return false;
    }

}

MyTab* ModifiedNotebook::getCurrentlyActiveTab()
{
    for(MyTab* tab: this->openedTabsVector)
    {
        if(tab->isActive())
        {
            return tab;
        }
    }
}

void ModifiedNotebook::OnClose(wxAuiNotebookEvent &event)
{
    // This will work only if close button is enabled on active tabs
    // If it is enabled on all tabs, it will create problems.
    MyTab* activeTab = this->getCurrentlyActiveTab();

    // consuming the event as the close method of MyTab class 
    // will close this window for us
    event.Veto();

    if(activeTab->filePath.Cmp(_T("-NONE-"))==0)
    {
        //Only asks to save if the file isn't empty
        if(!activeTab->textCtrl->IsEmpty())
        {
            int confirm = wxMessageBox(wxString::Format("Do you wish to close this file without saving ?"),
                    "Confirm",
                    wxYES_NO|wxICON_INFORMATION,
                    this);

            /*****************************************************
            ** For some reason the return value of wxMessageBox **
            ** is 2 for yes, 8 for no and 16 for cancel         **
            *****************************************************/

            //If user wants to save file without saving then let the event proceed 
            //else veto it and ask for save location
            if(confirm == 8)   
            { 
                activeTab->textCtrl->_SaveFileAs();
            }
            else if(confirm==2)
            {
                activeTab->Close();
            }
        }
        else     
        { 
            activeTab->Close();         
        }
    }
    else
    {
        activeTab->textCtrl->_SaveFile();

        activeTab->Close();
    }
}

std::vector<MyTab*>::iterator ModifiedNotebook::iteratorAt(MyTab* tab)
{
    std::vector<MyTab*>::iterator iterator = find(this->openedTabsVector.begin(), this->openedTabsVector.end(), tab);
    return iterator;
}

 MyTab* ModifiedNotebook::getTab(int index)
 {
    for(int i=0; i<this->openedTabsVector.size(); i++)
    {
        if(openedTabsVector[i]->index==index)
        {
            return openedTabsVector[i];
        }
    }
 }

 std::vector<MyTab *>::iterator ModifiedNotebook::removeTabFromVector(MyTab* tabToBeRemoved)
 {
    std::vector<MyTab*>::iterator iteratorAtTabToBeRemoved = this->iteratorAt(tabToBeRemoved);

    if(iteratorAtTabToBeRemoved!=this->openedTabsVector.end())
    {
        // The erase vector returns an iterator pointing to next element or the end of the vector
        return this->openedTabsVector.erase(iteratorAtTabToBeRemoved);
    }
    else
    {
        throw std::logic_error("Couldn't find the specified tab");
    }

 }