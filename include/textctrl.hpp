#include "app.hpp"

#include "wx/stc/stc.h"

class TextCtrl: public wxStyledTextCtrl{
public:
    TextCtrl();

    TextCtrl(wxWindow* parentWindow, wxWindowID wx_ID, const wxString name);
    
private:
    void KeyEvent(wxKeyEvent& event);
};

enum{
    MARGIN_LINE_NUMBERS,
};