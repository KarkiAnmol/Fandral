#if defined _TAB_H_==0  //_TAB_H_
#define _TAB_H_ 1

#include "mainwindow.h"

class Tab
{
private:
    static std::vector<Tab> activeTabs;
    std::string filePath, tabName;
    int index;
    wxNotebook* notebook;
    wxTextCtrl* textCtrl;
public:
    //constructors

    Tab();

    Tab(wxNotebook* notebook, const std::string& tabName, const size_t index, const MyFrame& frame);

    Tab(wxNotebook* notebook, const std::string& tabName, const MyFrame& frame);

    Tab(wxNotebook* notebook, const std::string& tabName, const size_t index, const MyFrame& frame, std::string filePath);

    //getters
    std::string getFilePath();
    std::string getTabName();
    int getIndex();
    const wxNotebook* getNotebook();
    static std::vector<Tab> getActiveTabsVector();

    //setters
    void setFilePath(std::string filePath);
    void setTabName(std::string tabName);
    void setIndex(int indes);

    //methods

    void addToActiveTabs();

    Tab* getCurrentlySelectedTab();

    wxTextCtrl* getCurrentlyActiveTextBox();
};

#endif //_TAB_H_