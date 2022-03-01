#if defined _TAB_H_==0  //_TAB_H_
#define _TAB_H_ 1

#include "mainwindow.hpp"
#include "memory"

#include "wx/notebook.h"

//Class Tab
//The tab here is to mimic a particular tab in any app.
//it only contains a text contorl (text area) for now
//tab has the filepath of the file loaded in it,
// tabname,
//index of the tab (starting from zero),
//The notebook which it belongs to
//(here we only use single notebook in a frame, so this maybe useful in future but not for now)
//and finally a static vector to store the loaded tabs. this is useful for saving and loading purposes
class Tab
{
private:
    //Static vector to store all the tabs
    static std::vector<Tab> activeTabs;

    //path of the loaded file
    wxString filePath=_(" ");

    //name of the tab, tiitle of the page in notebook, name of the text area(text ctrl) loaded in it
    wxString tabName;

    //index of the page (tab in this case) starting from zero.
    int index;

    //the wxNotebook control which the tab is associated to
    wxNotebook* notebook;

    //text area which is inside the particular tab
    TextCtrl* textCtrl;

public:
    //constructors

    //Creates a tab in the frame with name and without any file path.
    Tab(wxNotebook* notebook, const wxString& tabName, const MyFrame& frame);

    //For creating a tab in the frame with file path and
    //also provides option to load the file present in the filepath into tab
    Tab(wxNotebook* notebook, const wxString& tabName, const MyFrame& frame, wxString filePath, bool load);

    //getters
    wxString getFilePath();
    wxString getTabName();
    int getIndex();
    wxNotebook* getNotebook();
    static std::vector<Tab>& getActiveTabsVector();

    //setters
    void setFilePath(const wxString& filePath);
    void setTabName(const wxString& tabName);
    void setIndex(int index);

    //methods
    
    //Adds the particular tab to the array
    void addToActiveTabs();

    //static method to return the currently active tab
    //here pointer is returned to make it possible to return nullptr 
    //if by any chance no tab is selected
    //(filter this behaviour accordingly).
    static Tab* getCurrentlySelectedTab(MyFrame& frame);

    //method to return the currently active text area (text ctrl)
    //here pointer is returned to make it possible to return nullptr 
    //if by any chance no text box is active(consequence of being no tab active)
    //(filter this behaviour accordingly)
    TextCtrl* getCurrentlyActiveTextBox(MyFrame& frame);

    //static method to return the filepath of the currently active text area (text ctrl)
    static wxString getCurrentlyActiveFilePath(MyFrame& frame);

    //sets the given tab as active one
    void setAsActive(MyFrame& frame);

};

#endif //_TAB_H_