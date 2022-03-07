#include "mytab.hpp"
#include "memory"
#include "textctrl.hpp"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

std::vector<MyTab> MyTab::activeTabs;

MyTab::MyTab(ModifiedNotebook* notebook, const wxString& tabName, wxString filePath, bool load): notebook(notebook), tabName(tabName), filePath(filePath)
{
    this->textCtrl = new TextCtrl(notebook, wxID_ANY, filePath, tabName);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = this->activeTabs.size();

    if(load)
    {
        textCtrl->LoadFile(filePath);
    }
}

MyTab::MyTab(ModifiedNotebook *notebook, const wxString& tabName): notebook(notebook), tabName(tabName)
{
    this->textCtrl = new TextCtrl(notebook, wxID_ANY, tabName);

    notebook->AddPage(textCtrl, tabName, true);
    this->index = this->activeTabs.size();
}

// getters
wxString MyTab::getFilePath() { return filePath.Clone(); }
wxString MyTab::getTabName() { return tabName.Clone(); }
int MyTab::getIndex() { return index; }
ModifiedNotebook* MyTab::getNotebook() { return this->notebook; }
std::vector<MyTab>& MyTab::getActiveTabsVector(){ return activeTabs;}

// setters
void MyTab::setFilePath(const wxString& filePath) { this->filePath = filePath.Clone(); }
void MyTab::setTabName(const wxString& tabName) { this->tabName = tabName.Clone(); }
void MyTab::setIndex(int index) { this->index = index; }

void MyTab::addToActiveTabs()
{
    MyTab::activeTabs.push_back(*this);
}

MyTab* MyTab::getCurrentlySelectedTab()
{
    int selection = MyTab::getActiveTabsVector().front().getNotebook()->GetSelection();
    if(selection != wxNOT_FOUND)
    {
        for(MyTab& t: MyTab::getActiveTabsVector())
        {
            if(t.index==selection)
            {
                return &t;
            }
        }
    }
    return nullptr;

}

TextCtrl* MyTab::getCurrentlyActiveTextBox()
{
    if(MyTab::getCurrentlySelectedTab()!=nullptr)
    {
        return MyTab::getCurrentlySelectedTab()->textCtrl;
    }
    return nullptr;
}

wxString MyTab::getCurrentlyActiveFilePath()
{
    return MyTab::getCurrentlySelectedTab()->getFilePath();
}

void MyTab::setAsActive()
{
    this->getNotebook()->SetSelection(this->getIndex());
}
