#include "codehighliter.hpp"

CodeHighliter::CodeHighliter(wxStyledTextCtrl* textctrl): textctrl(textctrl){};

CodeHighliter::CodeHighliter(wxStyledTextCtrl* textctrl, int lex_language): textctrl(textctrl)
{
    this->setLex_Language(lex_language);
}

void CodeHighliter::setLex_Language(int lex_language)
{
    this->lex_language = lex_language;

    switch(lex_language)
    {
        case(wxSTC_LEX_CPP):
            this->highlightCPP();
            break;
        case(wxSTC_LEX_PYTHON):
            this->highlightPython();
            break;
    }
}

bool CodeHighliter::highlightCPP()
{
    this->lex_language=wxSTC_LEX_CPP;

    this->textctrl->SetLexer(wxSTC_LEX_CPP);

    this->textctrl->StyleSetForeground(wxSTC_C_DEFAULT, this->textctrl->GetDefaultStyle().GetTextColour());
    this->textctrl->StyleSetForeground (wxSTC_C_STRING,            CODEHIGHLITER_CHOCOLATE);
    this->textctrl->StyleSetForeground (wxSTC_C_PREPROCESSOR,      CODEHIGHLITER_CRIMSON);
    this->textctrl->StyleSetForeground (wxSTC_C_IDENTIFIER,        CODEHIGHLITER_ANTIQUE_WHITE);
    this->textctrl->StyleSetForeground (wxSTC_C_NUMBER,            CODEHIGHLITER_CYAN);
    this->textctrl->StyleSetForeground (wxSTC_C_CHARACTER,         CODEHIGHLITER_BEIGE);
    this->textctrl->StyleSetForeground (wxSTC_C_WORD,              CODEHIGHLITER_VIOLET);
    this->textctrl->StyleSetForeground (wxSTC_C_OPERATOR,          wxColor("WHITE"));
    this->textctrl->StyleSetForeground (wxSTC_C_WORD2,             CODEHIGHLITER_CADET_BLUE);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENT,           CODEHIGHLITER_CORN_SILK);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTLINE,       CODEHIGHLITER_CORN_SILK);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTDOC,        CODEHIGHLITER_CORN_SILK);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, CODEHIGHLITER_BLUE_VIOLET);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, CODEHIGHLITER_RED);
    this->textctrl->StyleSetForeground (wxSTC_C_USERLITERAL,       CODEHIGHLITER_DARK_BLUE);

    // sample list of keywords, I haven't included them all to keep it short...
    this->textctrl->SetKeyWords(0, wxT("return for while break continue"));
    this->textctrl->SetKeyWords(1, wxT("const int float void char double"));
    this->textctrl->SetKeyWords(2, wxT("class struct std"));

    return true;
}

bool CodeHighliter::highlightPython()
{
    this->lex_language=wxSTC_LEX_PYTHON;

    this->textctrl->SetLexer(wxSTC_LEX_PYTHON);

}

bool CodeHighliter::highlightJava()
{

}

bool CodeHighliter::highlightC()
{

}

bool CodeHighliter::highlightJavaScript()
{

}

bool CodeHighliter::highlightCSharp()
{

}
