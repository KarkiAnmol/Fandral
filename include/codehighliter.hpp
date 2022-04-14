#if defined _CODE_HIGHLITER_H_==0
#define _CODE_HIGHLITER_H_ 1

#include "wx/stc/stc.h"

#define CODEHIGHLITER_ALICE_BLUE wxColour("#F0F8FF")
#define CODEHIGHLITER_ANTIQUE_WHITE wxColour("#FAEBD7")
#define CODEHIGHLITER_AQUA wxColour("#00FFFF")
#define CODEHIGHLITER_AQUAMARINE wxColour("#7FFFD4")
#define CODEHIGHLITER_AZURE wxColour("#F0FFFF")
#define CODEHIGHLITER_BEIGE wxColour("#F5F5DC")
#define CODEHIGHLITER_BISQUE wxColour("#FFE4C4")
#define CODEHIGHLITER_BLACK wxColour("#000000")
#define CODEHIGHLITER_BLANCHED_ALMOND wxColour("#FF3BCD")
#define CODEHIGHLITER_BLUE wxColour("#0000FF")
#define CODEHIGHLITER_BLUE_VIOLET wxColour("#8A2BE2")
#define CODEHIGHLITER_BROWN wxColour("#A52A2A")
#define CODEHIGHLITER_BLURY_WOOD wxColour("#DEB887")
#define CODEHIGHLITER_CADET_BLUE wxColour("#5F9EA0")
#define CODEHIGHLITER_CHARTREUSE wxColour("#7FFF00")
#define CODEHIGHLITER_CHOCOLATE wxColour("#D2691E")
#define CODEHIGHLITER_CORAL wxColour("#FF7F50")
#define CODEHIGHLITER_CORN_FLOWER_BLUE wxColour("#6495ED")
#define CODEHIGHLITER_CORN_SILK wxColour("#FFF8DC")
#define CODEHIGHLITER_CRIMSON wxColour("#DC143C")
#define CODEHIGHLITER_CYAN wxColour("#00FFFF")
#define CODEHIGHLITER_DARK_BLUE wxColour("#00008B")
#define CODEHIGHLITER_DARK_CYAN wxColour("#008B8B")
#define CODEHIGHLITER_DEEP_SKY_BLUE wxColour("#00BFFF")
#define CODEHIGHLITER_NAVY wxColour("#000080")
#define CODEHIGHLITER_ORCHID wxColour("#DA70D6")
#define CODEHIGHLITER_RED wxColour("#FF0000")
#define CODEHIGHLITER_VIOLET wxColour("#EE82EE")



class CodeHighliter
{
public:
    wxStyledTextCtrl* textctrl;

    int lex_language;
    
    CodeHighliter(wxStyledTextCtrl* textctrl);

    CodeHighliter(wxStyledTextCtrl* textctrl, int lex_language);

    void setLex_Language(int lex_language);

    void highlightCPP();

    void highlightPython();

    void highlightJava();

    void highlightC();

    void highlightJavaScript();

    void highlightCSharp();

    void highlightXml();

};

#endif // _CODE_HIGHLITER_H_