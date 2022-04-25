#include "findandreplace.hpp"
#include "mainwindow.hpp"
#include "mytab2.hpp"
#include "textctrl.hpp"



FindDialog::FindDialog(MyFrame *parent,
            bool replace,
            wxWindowID id,
            const wxString &title,
            const wxPoint &pos,
            const wxSize &size,
            long style)
    : wxDialog(parent, id, title, pos, size, style)
    , parentFrame(parent)
    , isReplacing(replace)
{
    wxPoint parentposition =  parent->GetPosition();
    wxSize parentSize = parent->GetSize();

    this->findDialogSizer = new wxBoxSizer(wxVERTICAL);

    // for find row
    wxBoxSizer* findRowSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* findLabel = new wxStaticText(this, wxID_ANY, "Find", wxDefaultPosition, wxSize(50, 25), wxALIGN_CENTRE_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
    this->findBox = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 25));

    findRowSizer->Add(findLabel);
    findRowSizer->AddSpacer(20);
    findRowSizer->Add(findBox);
    findRowSizer->AddSpacer(10);

    wxBoxSizer* replaceRowSizer;
    if(replace)
    {
        replaceRowSizer = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* replaceLabel = new wxStaticText(this, wxID_ANY, "Replace", wxDefaultPosition, wxSize(50, 25), wxALIGN_CENTRE_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
        this->replaceBox = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(150, 25));
        
        replaceRowSizer->Add(replaceLabel);
        replaceRowSizer->AddSpacer(20);
        replaceRowSizer->Add(replaceBox);
        replaceRowSizer->AddSpacer(10);
    }

    // for the button row
    wxBoxSizer* buttonRowSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* findButton = new wxButton(this, Editor_Find, "Find", wxDefaultPosition, wxSize(75, 25));
    wxButton* replaceButton = new wxButton(this, Editor_Replace, "Replace", wxDefaultPosition, wxSize(75, 25));

    if(!replace)
    {
        buttonRowSizer->AddSpacer(70);
    }
    else
    {
        buttonRowSizer->AddSpacer(10);
    }

    buttonRowSizer->Add(findButton);
    buttonRowSizer->AddSpacer(10);
    buttonRowSizer->Add(replaceButton);
    if(replace)
    {
        wxButton* replaceAllButton = new wxButton(this, Editor_Replace_All, "Replace All", wxDefaultPosition, wxSize(70, 25));
        buttonRowSizer->AddSpacer(10);
        buttonRowSizer->Add(replaceAllButton);
        buttonRowSizer->AddSpacer(10);
    }

    // adding to the parent sizer of the dialog
    findDialogSizer->Add(findRowSizer);
    if(replace)
    {
        findDialogSizer->Add(replaceRowSizer);
    }
    findDialogSizer->Add(buttonRowSizer);

    this->SetSizerAndFit(findDialogSizer);

    // displaying the dialog in the top right corner
    this->SetPosition(wxPoint(parentposition.x + parentSize.x - this->GetSize().x - 20,
                      parentposition.y + this->GetSize().y) );

}
//event handling
wxBEGIN_EVENT_TABLE(FindDialog, wxDialog)
    EVT_BUTTON(Editor_Find, FindDialog::onFind)
    EVT_BUTTON(Editor_Replace, FindDialog::onReplace)
    EVT_BUTTON(Editor_Replace_All, FindDialog::onReplaceAll)
wxEND_EVENT_TABLE()
//Returns the text that the user has entered in the text dialog if the user
// has pressed OK,
// or the original value if the user has pressed Cancel.
wxString FindDialog::getFindText()
{
    return this->findBox->GetValue();
}
//Returns the text that the user has entered in the replace dialog if the user
// has pressed OK,
// or the original value if the user has pressed Cancel.
wxString FindDialog::getReplaceText()
{
    if(this->isReplacing)
    {
        return this->replaceBox->GetValue();
    }
    else
    {
        return wxEmptyString;
    }
}

void FindDialog::onFind(wxCommandEvent& event)
{
    //stores the text entered by user in find dialog
    wxString textToFind =this->getFindText();
    this->parentFrame->getCurrentlyActiveTab()->textCtrl->find(textToFind);
}
    
void FindDialog::onReplace(wxCommandEvent& event)
{
    // If it wasn't in replace mode before
    // closing the current dialog and creating a new dialog with replace box
    // if it was in replacing mode before performing the replace operation
    // retrieving the text from the replace box and performing replace operation
    // to prevent getting errors, dialog is closed only before this function reaches the end
    // (return is places immediately after the dilaog is closed)
    if(!this->isReplacing)
    {   
        wxString oldFindText = this->getFindText();


        FindDialog* findDialog = new FindDialog(this->getParent(), true, wxID_ANY, "Find And Replace");
        findDialog->findBox->SetValue(oldFindText);
        findDialog->Show(true);

        this->Close(true);
        return;
    }
    else
    {
        wxString textToFind = this->getFindText();
        wxString textToReplace = this->getReplaceText();

        this->parentFrame->getCurrentlyActiveTab()->textCtrl->replace(textToFind, textToReplace, false);
    }

    return;
}

void FindDialog::onReplaceAll(wxCommandEvent& event)
{
    wxString textToFind = this->getFindText();
    wxString textToReplace = this->getReplaceText();
        
    this->parentFrame->getCurrentlyActiveTab()->textCtrl->replace(textToFind, textToReplace, true);

    return;
}