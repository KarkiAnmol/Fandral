#include "tab.h"

std::vector<Tab> Tab::activeTabs;

Tab::Tab(wxNotebook *notebook, const std::string &tabName, const size_t index, const MyFrame& frame) : notebook(notebook), tabName(tabName), index(index)
{
    
    textCtrl = new wxTextCtrl(notebook, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, tabName);
    textCtrl->SetFont(frame.myFont);
    textCtrl->SetForegroundColour(frame.textBoxForegroundColor);
    textCtrl->SetBackgroundColour(frame.textBoxBackgroundColor);

    notebook->InsertPage(index, textCtrl, tabName, true);
}

Tab::Tab(wxNotebook *notebook, const std::string& tabName, const MyFrame& frame)
{
    textCtrl = new wxTextCtrl(notebook, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, tabName);
    textCtrl->SetFont(frame.myFont);
    textCtrl->SetForegroundColour(frame.textBoxForegroundColor);
    textCtrl->SetBackgroundColour(frame.textBoxBackgroundColor);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = notebook->GetSelection();
}

Tab::Tab(wxNotebook *notebook, const std::string &tabName, const size_t index, const MyFrame& frame, std::string filePath) : Tab(notebook, tabName, index, frame)
{
    this->filePath = filePath;
}

// getters
std::string Tab::getFilePath() { return filePath; }
std::string Tab::getTabName() { return tabName; }
int Tab::getIndex() { return index; }
const wxNotebook *Tab::getNotebook() { return notebook; }
std::vector<Tab> Tab::getActiveTabsVector(){ return activeTabs;}

// setters
void Tab::setFilePath(std::string filePath) { this->filePath = filePath; }
void Tab::setTabName(std::string tabName) { this->tabName = tabName; }
void Tab::setIndex(int indes) { this->index = index; }

void Tab::addToActiveTabs()
{
    Tab::activeTabs.push_back(*this);
}

Tab* Tab::getCurrentlySelectedTab()
{
    int selection = this->notebook->GetSelection();
    for(Tab& t: this->activeTabs)
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

