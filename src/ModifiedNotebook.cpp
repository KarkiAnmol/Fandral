
#include <wx/aui/auibook.h>

#include "modifiednotebook.hpp"

#ifdef __WXMSW__
    #include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

ModifiedNotebook::ModifiedNotebook() : wxAuiNotebook() {}

ModifiedNotebook::ModifiedNotebook(wxWindow *parent, wxWindowID id) 
: wxAuiNotebook(parent, id, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE| wxAUI_NB_BOTTOM | wxAUI_NB_CLOSE_ON_ALL_TABS)
{
    this->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &ModifiedNotebook::OnClose, this);
    this->SetMeasuringFont(wxFont(16, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    this->SetAutoLayout(true);
}

void ModifiedNotebook::OnClose(wxAuiNotebookEvent &event)
{   
    

}