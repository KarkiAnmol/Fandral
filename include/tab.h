#if defined _TAB_H_==0  //_TAB_H_
#define _TAB_H_ 1

#include "mainwindow.h"

class Tab
{
private:
    static std::vector<Tab> activeTabs;
    wxString filePath=wxString(" "), tabName;
    int index;
    wxNotebook* notebook;
    wxTextCtrl* textCtrl;
public:
    //constructors

    Tab();

    Tab(wxNotebook* notebook, const wxString& tabName, const MyFrame& frame);

    Tab(wxNotebook* notebook, const wxString& tabName, const MyFrame& frame, wxString filePath, bool load);

    //getters
    wxString getFilePath();
    wxString getTabName();
    int getIndex();
    const wxNotebook* getNotebook();
    static std::vector<Tab> getActiveTabsVector();

    //setters
    void setFilePath(const wxString& filePath);
    void setTabName(const wxString& tabName);
    void setIndex(int index);

    //methods

    void addToActiveTabs();

    static Tab* getCurrentlySelectedTab();

    wxTextCtrl* getCurrentlyActiveTextBox();

    static wxString getCurrentlyActiveFilePath();

    void setAsActive();
};

#endif //_TAB_H_