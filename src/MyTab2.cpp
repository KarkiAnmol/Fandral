#include "mytab2.hpp"
#include "modifiednotebook.hpp"

MyTab::MyTab(ModifiedNotebook *parentNotebook, const wxString &tabTitle)
: wxAuiNotebookPage(), parentNotebook(parentNotebook), tabTitle(tabTitle)
{
    this->textCtrl = new TextCtrl(parentNotebook, wxID_ANY, tabTitle);

    parentNotebook->AddPage(textCtrl, tabTitle, true);
}

MyTab::MyTab(ModifiedNotebook *parentNotebook, const wxString &tabTitle, wxString filePath, bool load)
:wxAuiNotebookPage(), parentNotebook(parentNotebook), tabTitle(tabTitle), filePath(filePath)
{
    this->textCtrl = new TextCtrl(parentNotebook, wxID_ANY, filePath, tabTitle);

    parentNotebook->AddPage(textCtrl, tabTitle, true);
    
    if(load)
    {
        textCtrl->LoadFile(filePath);
    }

}
