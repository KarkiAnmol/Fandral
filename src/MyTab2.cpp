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

    this->textCtrl = new TextCtrl(tabSplitter, this, wxID_ANY, tabTitle, filePath);
    this->commandArea = new CommandArea(tabSplitter, this);

    tabSplitter->SplitHorizontally(textCtrl, commandArea);

    tabSplitter->SetMinimumPaneSize(30);
    tabSplitter->SetSashGravity(1);

    tabSplitter->SetInitialSize(tabSplitter->GetBestSize());

    if(load)
    {
        textCtrl->LoadFile(filePath);
    }

    // Expanding the tabsplitter window when the frame expands
    wxBoxSizer* tabSizer = new wxBoxSizer(wxVERTICAL);
    tabSizer->Add(tabSplitter, wxSizerFlags(1).Expand());
    this->SetSizerAndFit(tabSizer);

    parentNotebook->AddPage(this);
}

void MyTab::setAsActive()
{
    //This will work as long as parentnotebook is updated
    //and index is same as the index inside the parent notebook
    this->parentNotebook->SetSelection(this->index);
}