#include "wx/notebook.h"
#include "memory"
#include <string>

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

#include "mainwindow.hpp"

#include "modifiednotebook.hpp"
#include "textctrl.hpp"
#include "mytab2.hpp"

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
    this->Center(wxBOTH);

    //The main panel on top of the main window
    wxPanel *mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0l,  "Main Panel");
    
    //This is make it possible to change colors of child widgets properly in all platforms
    mainPanel->SetBackgroundColour(wxColor(100, 100, 100));

    //Notebook for managing windows with tabs
    this->mainNotebook = new ModifiedNotebook(mainPanel, wxID_ANY);

    MyTab* firstTab = new MyTab(mainNotebook, "Untitled");

    //sizer for notebook
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(mainNotebook, 1, wxEXPAND);
    mainPanel->SetSizer(sizer);

    // Set up the sizer for the frame and resize the frame
    // according to its contents
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->Add(mainPanel, 1, wxEXPAND);
    this->Fit();
    SetSizerAndFit(topSizer);

#if wxUSE_MENUS

    /**For menu items first parameter is the id of the menu item,
     * second paramater is the text shown
     * adding & infront of any character will create
     *  an accelerator for it meaning Alt + that character will be the shortcut to open it
     * Ctrl + char will add control shortcut for particular menu item
     * and the last paramater is the paramater to change status message while mouse is hovered
     **/

    //create file menu
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(New_Window, "New Window", "Open New Window");
    fileMenu->Append(New_File, "&New\tCtrl-N", "Open new text file");
    fileMenu->Append(Open_File, "&Open", "Open saved text files");
    fileMenu->Append(Save_File, "Save\tCtrl-S", "Save the current file");
    fileMenu->Append(Save_File_As, "Save As", "Save the file as");
    fileMenu->Append(Editor_Quit, "E&xit\tAlt-X", "Quit this program");

    // create edit menu
    wxMenu *editMenu = new wxMenu;
    editMenu->Append(Find_Item, "&Find\tCtrl-F", "Find Items");
    editMenu->Append(Find_And_Replace_Item, "Find And &Replace \tCtrl-R", "Find Items and Replace");

    // create help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Editor_About, "&About\tF1", "Show about dialog");

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(helpMenu, "&Help");

    //and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(1);
    //SetStatusText (const wxString &text, int i=0)
    int statusBarFistPart = 0; // statusBarSecondPart = 1, statusBarThirdPart = 2;
    SetStatusText("Welcome! to Fandral Text Editor", statusBarFistPart);
    //SetStatusText("Don't compare with VScode", statusBarThirdPart);

#endif // wxUSE_STATUSBAR
}

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(Editor_Quit, MyFrame::OnQuit)
    EVT_MENU(Editor_About, MyFrame::OnAbout)
    EVT_MENU(New_Window, MyFrame::OnNewWindow)
    EVT_MENU(New_File, MyFrame::OnNew)
    EVT_MENU(Save_File, MyFrame::OnSave)
    EVT_MENU(Open_File, MyFrame::OnOpen)
    EVT_MENU(Save_File_As, MyFrame::OnSaveAs)
    EVT_CLOSE(MyFrame::OnClose)
wxEND_EVENT_TABLE()


// event handlers

void MyFrame::OnQuit(wxCommandEvent &WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent &WXUNUSED(event))
{
    wxMessageBox(wxString::Format(
                     "Welcome to Fandral Editor made with %s!\n"
                     "\n"
                     "This is the initial build of Fandral Editor\n"
                     "We will be adding other features soon."
                     "\nYour os Description is %s.",
                     wxVERSION_STRING,
                     wxGetOsDescription()),
                 "About Fandral Editor",
                 wxOK | wxICON_INFORMATION,
                 this);
}

void MyFrame::OnOpen(wxCommandEvent &WXUNUSED(event))
{
    wxString openLocation = wxLoadFileSelector(

        "a text",
        /**Wildcard example for file selection
          *"BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png"
          *Remember to put spaces between different extensions and keep the same extensions together.
          *correct:   PNG files (*.png)|*.png
          *incorrect: PNG files (*.png)| *.png
         **/
        "txt files (*.txt)|*.txt| XML files (*.xml)|*.xml| Markdown files (*.md)|*.md| CPP files (*.cpp)|*.cpp| Any Files (*.*)|*.*",
        "Fandral",
        this);

    //For checking if the file is already open in one of the tabs
    bool alreadyOpened=0;
    wxString path;
    for(MyTab* tab: this->mainNotebook->openedTabsVector)
    {
        if(tab->filePath.Cmp(openLocation)==0)
        {
            alreadyOpened=1;
            path = tab->filePath.Clone();

            //This will set the matching tab as active. Useful for loading text in the same text box below.
            tab->setAsActive();
            break;
        }
    }

    //if the file is already open then asks to override it with old contents
    if (alreadyOpened)
    {
        int confirm = wxMessageBox(wxString::Format("The selected file is already open in other tab.\nDo you wish to override it ?"),
                 "Confirm",
                 wxYES_NO|wxICON_INFORMATION,
                 this);
        //if confirmed the open file will be overidden by the file in the path
        if(confirm==wxYES)
        {
            //The condition to check if the file is already open would already have set the matching textctrl as the active one.
            //So, this will override that tab(text area) not the other ones.
            this->getCurrentlyActiveTab()->textCtrl->LoadFile(path);
        }
    }
    //else new tab is opened providing the new location as the file path of that tab
    else
    {   
        MyTab* tab= new MyTab(mainNotebook,  _T("Untitled"), openLocation, 1);
    }
}

void MyFrame::OnSave(wxCommandEvent &WXUNUSED(event))
{
    MyFrame::OnSave();
}

void MyFrame::OnSave()
{
    this->getCurrentlyActiveTab()->saveFile();
}

void MyFrame::OnSaveAs(wxCommandEvent &WXUNUSED(event))
{
    this->OnSaveAs();
}

void MyFrame::OnNewWindow(wxCommandEvent &event)
{
    MyFrame *secondaryWindow = new MyFrame(wxString::Format("New Window"));

    secondaryWindow->Show(true);
}

void MyFrame::OnNew(wxCommandEvent &event)
{
    MyTab* newTab = new MyTab(this->mainNotebook, _T("Untitled"));
}

void MyFrame::OnSaveAs()
{
    this->getCurrentlyActiveTab()->textCtrl->_SaveFileAs();
}

void MyFrame::OnClose(wxCloseEvent &event)
{
    if(event.CanVeto())
    {
        // vetoing the event as we don't want it to create exceptions after we're done 
        // with this method.
        // If the window can be closed the Destroy() method should be called.
        event.Veto();
    }

    for(MyTab* t: this->mainNotebook->openedTabsVector)
    {
        if((t->filePath.Cmp("-NONE-")==0) && !(t->textCtrl->IsEmpty()))
        {
            //Setting the particular tab as active one
            t->setAsActive();

            int confirm = wxMessageBox(wxString::Format("Do you wish to close this file without saving ?"),
                    "Confirm",
                    wxYES_NO|wxICON_INFORMATION,
                    this);

            /*****************************************************
            ** For some reason the return value of wxMessageBox **
            ** is 2 for yes, 8 for no and 16 for cancel         **
            *****************************************************/

            //If user wants to close file without saving it then close the tab else
            //ask for save location
            if(confirm == 8)   
            { 
                t->saveFile();
                return;     // Continue as if close button wasn't pressed
            }
            else if(confirm == 16)
            {
                return;     //Continue as if close button wasn't pressed
            }
            else if(confirm == 2)
            {   
                // Closes tab only if the tab was successfully removed from the vector
                // Not being able to remove may imply that it's isn't a proper tab object
                if(this->mainNotebook->removeTabFromVector(t))
                {
                    t->Close();
                }
            }
        }
        else if(t->textCtrl->IsEmpty())
        {
            // Closes tab only if the tab was successfully removed from the vector
            // Not being able to remove may imply that it isn't a proper tab object
            if(this->mainNotebook->removeTabFromVector(t))
            {
                t->Close();
            }
        }
        else
        {
            // Save before closing
            // Assumes that valid save location is set
            // This may be handled differently depending upon the requirements
            t->saveFile();
            t->Close();
        }
    }

    //The control will be here only if user decides not save any files
    //or all files are saved
    //or all files which aren't saved are empty
    //so destroying the frame here will be safe
    this->Destroy();

}

 MyTab* MyFrame::getCurrentlyActiveTab()
 {
    return this->mainNotebook->getCurrentlyActiveTab();
 }