#if defined _MODIFIED_NOTEBOOK_H_==0
#define _MODIFIED_NOTEBOOK_H_ 1

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/aui/auibook.h>

class ModifiedNotebook: public wxAuiNotebook
{
public:

    ModifiedNotebook();

    ModifiedNotebook(wxWindow* parent, wxWindowID id);

    // To do things before closing
    void OnClose(wxAuiNotebookEvent& event);
};

#endif //_MODIFIED_NOTEBOOK_H