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

void CodeHighliter::highlightCPP()
{
    this->lex_language=wxSTC_LEX_CPP;

    this->textctrl->SetLexer(wxSTC_LEX_CPP);

    this->textctrl->StyleSetForeground (wxSTC_C_DEFAULT,                this->textctrl->GetDefaultStyle().GetTextColour());
    this->textctrl->StyleSetForeground (wxSTC_C_STRING,                 CODEHIGHLITER_CHOCOLATE);
    this->textctrl->StyleSetForeground (wxSTC_C_PREPROCESSOR,           CODEHIGHLITER_CRIMSON);
    this->textctrl->StyleSetForeground (wxSTC_C_IDENTIFIER,             CODEHIGHLITER_ANTIQUE_WHITE);
    this->textctrl->StyleSetForeground (wxSTC_C_NUMBER,                 CODEHIGHLITER_CYAN);
    this->textctrl->StyleSetForeground (wxSTC_C_CHARACTER,              CODEHIGHLITER_BEIGE);
    this->textctrl->StyleSetForeground (wxSTC_C_WORD,                   CODEHIGHLITER_VIOLET);
    this->textctrl->StyleSetForeground (wxSTC_C_OPERATOR,               wxColor("WHITE"));
    this->textctrl->StyleSetForeground (wxSTC_C_WORD2,                  CODEHIGHLITER_CADET_BLUE);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENT,                CODEHIGHLITER_CORN_SILK);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTLINE,            CODEHIGHLITER_CORN_SILK);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTDOC,             CODEHIGHLITER_CORN_SILK);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD,      CODEHIGHLITER_BLUE_VIOLET);
    this->textctrl->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, CODEHIGHLITER_RED);
    this->textctrl->StyleSetForeground (wxSTC_C_USERLITERAL,            CODEHIGHLITER_DARK_BLUE);

    // sample list of keywords
    this->textctrl->SetKeyWords(0, "alignas asm auto bool char char16_t char32_t class clock_t concept const consteval constexpr constinit decltype double enum explicit export extern final float friend inline int int8_t int16_t int32_t int64_t int_fast8_t int_fast16_t int_fast32_t int_fast64_t intmax_t intptr_t long mutable noexcept override private protected ptrdiff_t public register requires short signed size_t ssize_t static struct template thread_local time_t typename uint8_t uint16_t uint32_t uint64_t uint_fast8_t uint_fast16_t uint_fast32_t uint_fast64_t uintmax_t uintptr_t union unsigned virtual void volatile wchar_t");
    this->textctrl->SetKeyWords(1, "alignof and and_eq bitand bitor break case catch compl const_cast continue default delete do dynamic_cast else false for goto if namespace new not not_eq nullptr operator or or_eq reinterpret_cast return sizeof static_assert static_cast switch this throw true try typedef typeid using while xor xor_eq NULL");    

}

void CodeHighliter::highlightPython()
{
    this->lex_language=wxSTC_LEX_PYTHON;

    this->textctrl->SetLexer(wxSTC_LEX_PYTHON);

}

void CodeHighliter::highlightJava()
{

}

void CodeHighliter::highlightC()
{

}

void CodeHighliter::highlightJavaScript()
{

}

void CodeHighliter::highlightCSharp()
{

}

void CodeHighliter::highlightXml()
{

    this->lex_language=wxSTC_LEX_XML;

    this->textctrl->SetLexer(wxSTC_LEX_XML);

}
