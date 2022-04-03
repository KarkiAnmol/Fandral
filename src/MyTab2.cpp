#include "mytab2.hpp"

#include "modifiednotebook.hpp"
#include "textctrl.hpp"

#include "wx/splitter.h"
#include "wx/sizer.h"
#include "commandarea.hpp"

MyTab::MyTab(ModifiedNotebook *parentNotebook, const wxString &tabTitle, wxString filePath, bool load)
:wxWindow(parentNotebook, wxID_ANY), parentNotebook(parentNotebook), tabTitle(tabTitle), filePath(filePath)
{

    // For splitting the textctrl and commandarea
    tabSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER|wxSP_LIVE_UPDATE);

    // Adding these controls as children of the splitter as to spit it later on
    this->textCtrl = new TextCtrl(tabSplitter, this, wxID_ANY, tabTitle);
    this->commandArea = new CommandArea(tabSplitter, this);

    // Splitting the window horizontally into textctrl and commandarea
    tabSplitter->SplitHorizontally(textCtrl, commandArea);

    // Minimum height of each of the controls
    tabSplitter->SetMinimumPaneSize(30);

    // Setting only the textctrl to expand when outer windows/ frames / panels are expanded
    tabSplitter->SetSashGravity(1);

    // Setting the initial size of the splitter window to be the sum of sizes of it's children
    tabSplitter->SetInitialSize(tabSplitter->GetBestSize());

    // If properfilepath is given and load is true load the file into the textctrl
    if(load && !filePath.Cmp("-NONE-")==0)
    {
        textCtrl->LoadFile(filePath);
    }

    // Expanding the tabsplitter window when the frame expands
    wxBoxSizer* tabSizer = new wxBoxSizer(wxVERTICAL);
    tabSizer->Add(tabSplitter, wxSizerFlags(1).Expand());
    this->SetSizerAndFit(tabSizer);

    // Finally adding the tab to the notebook 
    // This is to automate the tab creation process 
    // i.e. whenever new tab is created it is added to the ModifiedNotebook
    parentNotebook->AddPage(this, true);

    // Also updating the index of the tab to be same as the index in parentNotebook
    this->index = parentNotebook->GetPageIndex(this);
}

void MyTab::setAsActive()
{
    parentNotebook->SetSelection(parentNotebook->GetPageIndex(this));   
}

bool MyTab::Close()
{
    // Initially removing the tab from the parentnotebook
   if(parentNotebook->RemovePage(parentNotebook->GetPageIndex(this)))
   {
        this->wxWindow::Close(true);
   }
   return 0;

}

bool MyTab::isActive()
{
    if(parentNotebook->GetSelection()==parentNotebook->GetPageIndex(this)) return 1;
    return 0;
}

bool MyTab::saveFile()
{
    this->textCtrl->_SaveFile();
}