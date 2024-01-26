/***************************************************************
 * Name:      LivingInputMain.h
 * Purpose:   Defines Application Frame
 * Author:    Dirk Allaerts ()
 * Created:   2023-12-06
 * Copyright: Dirk Allaerts ()
 * License:
 **************************************************************/

#ifndef LIVINGINPUTMAIN_H
#define LIVINGINPUTMAIN_H

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "LivingInputApp.h"

Class LivingInputFrame:
public wxFrame
{
public:
    LivingInputFrame(wxFrame *frame, const wxString& title);
    ~LivingInputFrame();
private:
    enum
    {
        idMenuQuit = 1000,
        idMenuAbout
    };
    void OnClose(wxCloseEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
};


#endif // LIVINGINPUTMAIN_H
