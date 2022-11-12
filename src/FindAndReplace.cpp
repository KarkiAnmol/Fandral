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

    // calculating the sizes for various values
    wxSize fontSize = parent->GetFont().GetPixelSize();

    wxSize labelSize = wxSize(fontSize.x * 8, fontSize.y * 1.2);
    wxSize buttonSize = wxSize(labelSize.x * 1.3, fontSize.y * 2 );
    wxSize findAndReplaceBoxSize = wxSize(buttonSize.x * 2 * 1.1, buttonSize.y * 1.1);

    wxUint8 verticalSpacing = fontSize.y;
    wxUint8 horizontalSpacing = fontSize.x;

    // this sizer will contain all the other sizers
    this->findDialogSizer = new wxBoxSizer(wxVERTICAL);

    // for find row
    wxBoxSizer* findRowSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* findLabel = new wxStaticText(this, wxID_ANY, "Find", wxDefaultPosition, labelSize, wxALIGN_CENTRE_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
    this->findBox = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, findAndReplaceBoxSize);

    // the children of the find row
    findRowSizer->Add(findLabel);
    findRowSizer->AddSpacer(horizontalSpacing);
    findRowSizer->Add(findBox);
    findRowSizer->AddSpacer(horizontalSpacing);

    wxBoxSizer* replaceRowSizer;
    if(replace)
    {
        replaceRowSizer = new wxBoxSizer(wxHORIZONTAL);

        wxStaticText* replaceLabel = new wxStaticText(this, wxID_ANY, "Replace", wxDefaultPosition, labelSize, wxALIGN_CENTRE_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
        this->replaceBox = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, findAndReplaceBoxSize);
        
        // the children of the replace row
        replaceRowSizer->Add(replaceLabel);
        replaceRowSizer->AddSpacer(horizontalSpacing);
        replaceRowSizer->Add(replaceBox);
        replaceRowSizer->AddSpacer(horizontalSpacing);
    }

    // for the button row
    wxBoxSizer* buttonRowSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* findButton = new wxButton(this, Editor_Find, "Find", wxDefaultPosition, buttonSize);
    wxButton* replaceButton = new wxButton(this, Editor_Replace, "Replace", wxDefaultPosition, buttonSize);

    if(!replace)
    {   // trying to center the find button
        buttonRowSizer->AddSpacer(7 * horizontalSpacing);
    }
    else
    {
        buttonRowSizer->AddSpacer(horizontalSpacing);
    }

    // the children of the button row
    buttonRowSizer->Add(findButton);
    buttonRowSizer->AddSpacer(horizontalSpacing);
    buttonRowSizer->Add(replaceButton);
    if(replace)
    {
        wxButton* replaceAllButton = new wxButton(this, Editor_Replace_All, "Replace All", wxDefaultPosition, buttonSize);
        buttonRowSizer->AddSpacer(horizontalSpacing);
        buttonRowSizer->Add(replaceAllButton);
        buttonRowSizer->AddSpacer(horizontalSpacing);
    }

    // adding to the parent sizer of the dialog
    findDialogSizer->Add(findRowSizer);
    findDialogSizer->AddSpacer(verticalSpacing);
    if(replace)
    {
        findDialogSizer->Add(replaceRowSizer);
        findDialogSizer->AddSpacer(verticalSpacing);
    }
    findDialogSizer->Add(buttonRowSizer);
    findDialogSizer->AddSpacer(verticalSpacing);

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