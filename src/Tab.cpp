#include "tab.h"
#include "memory"

std::vector<Tab> Tab::activeTabs;

Tab::Tab(wxNotebook* notebook, const wxString& tabName, const MyFrame& frame, wxString filePath, bool load): notebook(notebook), tabName(tabName), filePath(filePath)
{
    textCtrl = new wxTextCtrl(notebook, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, tabName);
    textCtrl->SetFont(frame.myFont);
    textCtrl->SetForegroundColour(frame.textBoxForegroundColor);
    textCtrl->SetBackgroundColour(frame.textBoxBackgroundColor);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = this->activeTabs.size();
    if(load)
    {
        textCtrl->LoadFile(filePath);
    }
}

Tab::Tab(wxNotebook *notebook, const wxString& tabName, const MyFrame& frame)
{
    textCtrl = new wxTextCtrl(notebook, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, tabName);
    textCtrl->SetFont(frame.myFont);
    textCtrl->SetForegroundColour(frame.textBoxForegroundColor);
    textCtrl->SetBackgroundColour(frame.textBoxBackgroundColor);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = this->activeTabs.size();
}

// getters
wxString Tab::getFilePath() { return filePath; }
wxString Tab::getTabName() { return tabName; }
int Tab::getIndex() { return index; }
const wxNotebook *Tab::getNotebook() { return notebook; }
std::vector<Tab> Tab::getActiveTabsVector(){ return activeTabs;}

// setters
void Tab::setFilePath(const wxString& filePath) { this->filePath = filePath.Clone(); }
void Tab::setTabName(const wxString& tabName) { this->tabName = tabName.Clone(); }
void Tab::setIndex(int index) { this->index = index; }

void Tab::addToActiveTabs()
{
    Tab::activeTabs.push_back(*this);
}

Tab* Tab::getCurrentlySelectedTab()
{
    int selection = Tab::getActiveTabsVector().front().notebook->GetSelection();
    for(Tab& t: Tab::getActiveTabsVector())
    {
        if(t.index==selection)
        {
            return &t;
        }
    }
    return nullptr;
}

wxTextCtrl* Tab::getCurrentlyActiveTextBox()
{
    if(Tab::getCurrentlySelectedTab()!=nullptr)
    {
        return Tab::getCurrentlySelectedTab()->textCtrl;
    }
    return nullptr;
}

wxString Tab::getCurrentlyActiveFilePath()
{
    return Tab::getCurrentlySelectedTab()->getFilePath();
}

void Tab::setAsActive()
{
    this->notebook->SetSelection(this->index);
}