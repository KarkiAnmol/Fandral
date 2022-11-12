#include "mytab2.hpp"

#include "modifiednotebook.hpp"
#include "textctrl.hpp"

#include "wx/splitter.h"
#include "wx/sizer.h"
#include "commandarea.hpp"

#include <wx/display.h>

MyTab::MyTab(ModifiedNotebook *parentNotebook, const wxString &tabTitle, wxString filePath, bool load)
:wxWindow(parentNotebook, wxID_ANY), parentNotebook(parentNotebook), tabTitle(tabTitle), filePath(filePath)
{

    // For splitting the textctrl and commandarea
    tabSplitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER|wxSP_LIVE_UPDATE);

    // calculating sizes for the components of the tab
    wxDisplay currentDisplay(wxDisplay::GetFromWindow(this));
    wxRect screen = currentDisplay.GetGeometry();

    wxUint16 height = screen.GetHeight();
    wxUint16 width = screen.GetWidth();

    // setting width to 80% of the width and aspect ratio to 16:10
    wxUint16 tabWidth = 0.8 * width;
    wxUint16 tabHeight = width * 10/16;

    // sizing textctrl as to occupy 90% of available height
    wxUint16 textCtrlHeight = 0.8 * tabHeight;
    wxUint16 commandAreaHeight = tabHeight - textCtrlHeight;

    // Adding these controls as children of the splitter as to spit it later on
    this->textCtrl = new TextCtrl(tabSplitter, this, wxID_ANY, tabTitle, wxSize(tabWidth, textCtrlHeight));
    this->commandArea = new CommandArea(tabSplitter, this), wxSize(tabWidth, commandAreaHeight);

    // Splitting the window horizontally into textctrl and commandarea
    tabSplitter->SplitHorizontally(textCtrl, commandArea);

    // Minimum height of each of the controls
    tabSplitter->SetMinimumPaneSize(30);

    // Setting only the textctrl to expand when outer windows/ frames / panels are expanded
    tabSplitter->SetSashGravity(1);

    tabSplitter->SetBorderSize(2);

    // Setting the initial size of the splitter window to be the sum of sizes of it's children
    tabSplitter->SetInitialSize(tabSplitter->GetBestSize());

    // Expanding the tabsplitter window when the frame expands
    wxBoxSizer* tabSizer = new wxBoxSizer(wxVERTICAL);
    tabSizer->Add(tabSplitter, wxSizerFlags(1).Expand());
    this->SetSizerAndFit(tabSizer);

    // Finally adding the tab to the notebook 
    // This is to automate the tab creation process 
    // i.e. whenever new tab is created it is added to the ModifiedNotebook
    parentNotebook->AddPage(this, true);

    // Also updating the index of the tab to be same as the index in parentNotebook
    this->index = parentNotebook->GetPageIndex(this);

     // If properfilepath is given and load is true load the file into the textctrl
     // also update the label of the tab
    if(load && !filePath.Cmp("-NONE-")==0)
    {
        textCtrl->LoadFile(filePath);
        this->updateNameLabel(filePath);
    }
}

void MyTab::setAsActive()
{
    parentNotebook->SetSelection(parentNotebook->GetPageIndex(this));   
}

bool MyTab::Close()
{
    // remove the tab from the vector
    // we don't have to worry about dynamic allocation and deallocation here
    // as only one tab is removed
    try
    {
        this->parentNotebook->removeTabFromVector(this);
    }
    catch(std::logic_error &error)
    {
         wxMessageBox(wxString::Format("Couldn't complete the close operation."),
                "Error",
                wxOK|wxICON_INFORMATION,
                this);
        return 0; // not closing the tab as the tab couldn't be removed from the vector
    }

    // Initially removing the tab from the parentnotebook
   if(parentNotebook->RemovePage(parentNotebook->GetPageIndex(this)))
   {
        this->wxWindow::Close(true);
        return 1;
   }
   return 0;

}

bool MyTab::isActive()
{
    if(parentNotebook->GetSelection()==parentNotebook->GetPageIndex(this)) return 1;
    return 0;
}

bool MyTab::saveFile()
{
    return this->textCtrl->_SaveFile();
}

wxString MyTab::updateNameLabel(const wxString &fileLocation)
{
    wxString tempFileLocation = fileLocation.Clone();

// The file separator in windows will be '\\' so it is replaced with '\'
#if defined __WXMSW__
    // this will be file name only
    tempFileLocation.Replace("\\", "/", true);
#endif

    wxString fileNameWithExtension = tempFileLocation.AfterLast(_T('/'));

    this->parentNotebook->SetPageText(this->index, fileNameWithExtension);

    // Updating codehighliting each time the name of the tab is changed.
    this->textCtrl->updateHighlighter();
    
    return fileNameWithExtension;
}

wxString MyTab::getFileExtension()
{
    wxString fileExtension = this->filePath.AfterLast(_T('.'));

    return fileExtension;
}
