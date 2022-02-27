#include "tab.hpp"
#include "memory"
#include "textctrl.hpp"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

std::vector<Tab> Tab::activeTabs;

Tab::Tab(wxNotebook* notebook, const wxString& tabName, const MyFrame& frame, wxString filePath, bool load): notebook(notebook), tabName(tabName), filePath(filePath)
{
    this->textCtrl = new TextCtrl(notebook, wxID_ANY, tabName);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = this->activeTabs.size();
    if(load)
    {
        textCtrl->LoadFile(filePath);
    }
}

Tab::Tab(wxNotebook *notebook, const wxString& tabName, const MyFrame& frame)
{
    this->textCtrl = new TextCtrl(notebook, wxID_ANY, tabName);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = this->activeTabs.size();
}

// getters
wxString Tab::getFilePath() { return filePath.Clone(); }
wxString Tab::getTabName() { return tabName.Clone(); }
int Tab::getIndex() { return index; }
wxNotebook* Tab::getNotebook() { return this->notebook; }
std::vector<Tab>& Tab::getActiveTabsVector(){ return activeTabs;}

// setters
void Tab::setFilePath(const wxString& filePath) { this->filePath = filePath.Clone(); }
void Tab::setTabName(const wxString& tabName) { this->tabName = tabName.Clone(); }
void Tab::setIndex(int index) { this->index = index; }

void Tab::addToActiveTabs()
{
    Tab::activeTabs.push_back(*this);
}

Tab* Tab::getCurrentlySelectedTab(MyFrame& frame)
{
    int selection = frame.mainNotebook->GetSelection();
    if(selection != wxNOT_FOUND)
    {
        for(Tab& t: Tab::getActiveTabsVector())
        {
            if(t.index==selection)
            {
                return &t;
            }
        }
    }
    return nullptr;
}

wxStyledTextCtrl* Tab::getCurrentlyActiveTextBox(MyFrame& frame)
{
    if(Tab::getCurrentlySelectedTab(frame)!=nullptr)
    {
        return Tab::getCurrentlySelectedTab(frame)->textCtrl;
    }
    return nullptr;
}

wxString Tab::getCurrentlyActiveFilePath(MyFrame& frame)
{
    return Tab::getCurrentlySelectedTab(frame)->getFilePath();
}

void Tab::setAsActive(MyFrame& frame)
{
    frame.mainNotebook->SetSelection(this->getIndex());
}