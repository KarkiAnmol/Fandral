#include "mytab2.hpp"

#include "modifiednotebook.hpp"
#include "textctrl.hpp"

MyTab::MyTab(ModifiedNotebook *parentNotebook, const wxString &tabTitle)
: wxAuiNotebookPage(), parentNotebook(parentNotebook), tabTitle(tabTitle)
{
    this->textCtrl = new TextCtrl(parentNotebook, wxID_ANY, tabTitle);

    parentNotebook->AddPage(this, true);

    this->index = parentNotebook->GetPageIndex(textCtrl);

}

MyTab::MyTab(ModifiedNotebook *parentNotebook, const wxString &tabTitle, wxString filePath, bool load)
:wxAuiNotebookPage(), parentNotebook(parentNotebook), tabTitle(tabTitle), filePath(filePath)
{
    this->textCtrl = new TextCtrl(parentNotebook, wxID_ANY, filePath, tabTitle);

    parentNotebook->AddPage(this, true);
    
    this->index = parentNotebook->GetPageIndex(textCtrl);
    
    if(load)
    {
        textCtrl->LoadFile(filePath);
    }

}

void MyTab::setAsActive()
{
    //This will work as long as parentnotebook is updated
    //and index is same as the index inside the parent notebook
    this->parentNotebook->SetSelection(this->index);
}