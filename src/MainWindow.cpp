#include "mainwindow.h"

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame::MyFrame(wxWindow* parent, const wxString &title)
    : wxFrame(parent, Main_Window, title, wxPoint(MAIN_WINDOW_POS_X, MAIN_WINDOW_POS_Y), wxSize(MAIN_WINDOW_HEIGHT /*Making it square for now*/, MAIN_WINDOW_HEIGHT))
{

#if wxUSE_MENUS

    mainTextBox = new wxTextCtrl(this, TEXT_Main, "", wxDefaultPosition, wxDefaultSize,
                                 wxTE_MULTILINE | wxTE_RICH, wxDefaultValidator, wxTextCtrlNameStr);
    //mainTextBox->SetBackgroundColour(mainTextBoxBackgroundColor);  //Doesn't work properly on linux
    //mainTextBox->SetForegroundColour(mainTextBoxForegroundColor);

    /**For menu items first parameter is the id of the menu item,
     * second paramater is the text shown
     * adding & infront of any character will create
     *  an accelerator for it meaning Alt + that character will be the shortcut to open it
     * Ctrl + char will add control shortcut for particular menu item
     * and the last paramater is the paramater to change status message while mouse is hovered
     **/

    //create file menu
    wxMenu *fileMenu = new wxMenu;
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
        "txt files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
        "Fandral",
        this);

    //For checking if the new location is already in the openedFiles array
    int index = MyFrame::openedFiles->Index(openLocation);

    if (index == wxNOT_FOUND)
    {
        //If it's not there then the new location is added.
        MyFrame::openedFiles->Add(openLocation);

        //for the saving purpose below.
        index = openedFiles->Index(openLocation);
    }

    //Appending class variable to keep track of currently open file.
    MyFrame::currentlyOpenFileIndex = index;

    MyFrame::mainTextBox->LoadFile(openLocation);
}

void MyFrame::OnSave(wxCommandEvent &WXUNUSED(event))
{

    wxString saveLocation;

    /**Opens native file explorer dialog box to select saving location
     * if the file isn't saved previously or new file is open 
     **/
    if(MyFrame::currentlyOpenFileIndex < 0)
    {
        saveLocation = wxSaveFileSelector(
            "the current text",
            "TEXT files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
            "Fandral",
            this);
        MyFrame::openedFiles->Add(saveLocation);
    }
    else
    {
        //sets saveLocation to currently open file save location if it's known.
        saveLocation = MyFrame::openedFiles->Item(MyFrame::currentlyOpenFileIndex);
    }

    //Keeping track of accessed locations.
    MyFrame::currentlyOpenFileIndex=openedFiles->Index(saveLocation);
    MyFrame::mainTextBox->SaveFile(saveLocation);

    //Show status for completion of save operation
    PushStatusText("Saved File successfully", 0);

    //sleep(5);     k//Need to figure another way to keep status message for some time.
    PopStatusText();
}

//Overloading for taking without arugements 
/*************************************************************************
 *********** Please figure out any other way to do this ******************
 * ***********************************************************************/
void MyFrame::OnSave()
{
    wxString saveLocation;

    /**Opens native file explorer dialog box to select saving location
     * if the file isn't saved previously or new file is open 
     **/
    if(MyFrame::currentlyOpenFileIndex < 0)
    {
        saveLocation = wxSaveFileSelector(
            "the current text",
            "TEXT files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
            "Fandral",
            this);
        MyFrame::openedFiles->Add(saveLocation);
    }
    else
    {
        //sets saveLocation to currently open file save location if it's known.
        saveLocation = MyFrame::openedFiles->Item(MyFrame::currentlyOpenFileIndex);
    }

    //Keeping track of accessed locations.
    MyFrame::currentlyOpenFileIndex=openedFiles->Index(saveLocation);
    MyFrame::mainTextBox->SaveFile(saveLocation);

    //Show status for completion of save operation
    PushStatusText("Saved File successfully", 0);

    //sleep(5);     k//Need to figure another way to keep status message for some time.
    PopStatusText();
}

void MyFrame::OnSaveAs(wxCommandEvent &WXUNUSED(event))
{
    //Opens native file explorer dialog box to select saving location
    wxString saveLocation = wxSaveFileSelector(
        "the current text",
        "TEXT files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
        "Fandral",
        this);

    //Keeping track of accessed locations.
    MyFrame::openedFiles->Add(saveLocation);
    MyFrame::currentlyOpenFileIndex=openedFiles->Index(saveLocation);

    MyFrame::mainTextBox->SaveFile(saveLocation);

    //Show status for completion of save operation
    PushStatusText("Saved File successfully", 0);
    //sleep(5);
    PopStatusText();
}

void MyFrame::OnNew(wxCommandEvent &event)
{

    MyFrame *secondaryWindow = new MyFrame(NULL, wxString::Format("New Window"));

    secondaryWindow->Show(true);
}

//For taking close events
/*************************************************************************
 *********** Please figure out any other way to do this ******************
 * ***********************************************************************/
void MyFrame::OnSaveAs()
{
    //Opens native file explorer dialog box to select saving location
    wxString saveLocation = wxSaveFileSelector(
        "the current text",
        "TEXT files (*.txt)|*.txt| DOCX files (*.docx)|*.docx| XML files (*.xml)|*.xml",
        "Fandral",
        this);

    //Keeping track of accessed locations.
    MyFrame::openedFiles->Add(saveLocation);
    MyFrame::currentlyOpenFileIndex=openedFiles->Index(saveLocation);

    MyFrame::mainTextBox->SaveFile(saveLocation);

    //Show status for completion of save operation
    PushStatusText("Saved File successfully", 0);
    //sleep(5);
    PopStatusText();
}

void MyFrame::OnClose(wxCloseEvent &event)
{
    if(MyFrame::currentlyOpenFileIndex < 0)
    {
        if(event.CanVeto()){event.Veto();}
        int confirm = wxMessageBox(wxString::Format("Do you wish to close this file without saving ?"),
                 "Confirm",
                 wxYES_NO|wxICON_INFORMATION,
                 this);

        /*****************************************************
        ** For some reason the return value of wxMessageBox **
        ** is 2 for yes, 8 for no and 16 for cancel         **
        *****************************************************/

        if(confirm == 2)  
        {
            this->Destroy();
        }
        else{
            this->OnSaveAs();
        }
    }
    else
    {
        this->OnSave();

        this->Destroy();
    }
}