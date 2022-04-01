#include "commandarea.hpp"

CommandArea::CommandArea(wxWindow* parent, MyTab* parentTab, wxWindowID wx_ID)
: wxStyledTextCtrl(parent, wx_ID), parentTab(parentTab)
{
    this->SetCaretLineVisible(false);

    this->SetInitialSize(wxSize(500, 60));

    wxString commandModeSuggestion = "Press Esc to enter into the command mode";
    this->AppendText(commandModeSuggestion);

}

void CommandArea::AppendText(const wxString& text)
{
    this->SetEditable(true);
    wxStyledTextCtrl::AppendText(text + "\n");
    this->GotoLine(this->GetNumberOfLines());
    this->SetEditable(false);
    return;
}