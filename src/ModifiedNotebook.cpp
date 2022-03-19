
#include <wx/aui/auibook.h>

#include "modifiednotebook.hpp"

#include "textctrl.hpp"
#include "mytab2.hpp"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

ModifiedNotebook::ModifiedNotebook() : wxAuiNotebook() {}

ModifiedNotebook::ModifiedNotebook(wxWindow *parent, wxWindowID id) 
: wxAuiNotebook(parent, id, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE| wxAUI_NB_BOTTOM | wxAUI_NB_CLOSE_ON_ALL_TABS)
{
    this->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &ModifiedNotebook::OnClose, this);
    this->SetMeasuringFont(wxFont(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    this->SetAutoLayout(true);
}

bool ModifiedNotebook::AddPage(MyTab* tab, bool select)
{
     //adding page to wxauinotebook
    if(wxAuiNotebook::AddPage(tab->textCtrl, tab->tabTitle, select))
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
    int selection = this->GetSelection();
    for(MyTab* tab: this->openedTabsVector)
    {
        if((selection!=wxNOT_FOUND) && (selection==tab->index))
        {
            return tab;
        }
    }
}

void ModifiedNotebook::OnClose(wxAuiNotebookEvent &event)
{   
    MyTab* activeTab = this->getCurrentlyActiveTab();
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
                event.Veto();
                activeTab->textCtrl->_SaveFileAs();
            }
            else if(confirm == 16)
            {
                // Continue as if close button wasn't pressed if user cancels the dialog
                event.Veto();
            }
        }
        else
        {
            // Ask the tab to close itself;
            this->GetPage(activeTab->index)->Close();

            //Removes the tab from the openedtabs vector after closing it
            this->openedTabsVector.erase(this->iteratorAt(activeTab));
        }
    }
    else
    {
        activeTab->textCtrl->_SaveFile();

        // Ask the tab to close itself;
        this->GetPage(activeTab->index)->Close();

        //Removes the tab from the openedtabs vector after closing it
        this->openedTabsVector.erase(this->iteratorAt(activeTab));
    }
}

std::vector<MyTab*>::iterator ModifiedNotebook::iteratorAt(MyTab* tab)
{
    std::vector<MyTab*>::iterator iterator = find(this->openedTabsVector.begin(), this->openedTabsVector.end(), tab);
    return iterator;
}