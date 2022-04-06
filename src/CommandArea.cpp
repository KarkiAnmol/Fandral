#include "commandarea.hpp"

CommandArea::CommandArea(wxWindow* parent, MyTab* parentTab, wxWindowID wx_ID)
: wxStyledTextCtrl(parent, wx_ID, wxDefaultPosition, wxSize(400, 60), wxNO_BORDER), parentTab(parentTab)
{
    this->SetInitialSize(wxSize(400, 60));

    // Setting it to be non editable
    this->SetEditable(false);

    //background color of the text area
    this->StyleSetBackground(wxSTC_STYLE_DEFAULT, wxColour(35, 35, 35, 0.2));

    //foreground color of the text area
    this->StyleSetForeground(wxSTC_STYLE_DEFAULT, wxColor("#F2F2F7FF"));

    // This will set the default styles
    this->StyleClearAll();

    // Setting the margin width to mininum and setting the background color same as default one 
    // as to make it invisible
    this->SetMarginWidth(Left_Margin, 2);
    this->StyleSetForeground(wxSTC_STYLE_LINENUMBER, this->StyleGetForeground(wxSTC_STYLE_DEFAULT));
    this->StyleSetBackground(wxSTC_STYLE_LINENUMBER, this->StyleGetBackground(wxSTC_STYLE_DEFAULT));

    // Setting margin as a line number margin
    this->SetMarginType(Left_Margin, wxSTC_MARGIN_NUMBER);

}

void CommandArea::AppendText(const wxString& text)
{
    this->SetEditable(true);
    wxStyledTextCtrl::AppendText(text + "\n");
    this->GotoLine(this->GetNumberOfLines());
    this->SetEditable(false);
    return;
}