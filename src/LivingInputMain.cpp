/***************************************************************
 * Name:      LivingInputMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Dirk Allaerts ()
 * Created:   2023-12-06
 * Copyright: Dirk Allaerts ()
 * License:
 **************************************************************/
#include "wx/wxprec.h"
#include "wx/defs.h"
#include <wx/frame.h>
#include <wx/app.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include<cstring>
#include<vector>
#include <wx/msgdlg.h>
#include <wx/stattext.h>
#include <wx/sizer.h>
#include <wx/dir.h>
#include <wx/listbox.h>
#include <wx/arrstr.h>
#include <wx/listctrl.h>
#include <wx/imaglist.h>
#include <wx/bitmap.h>
#include <wx/button.h>
#include "/home/oem/Developments/Livinginput/mediaClass.h"
#include <wx/dcclient.h>
#include "/home/oem/Developments/Livinginput/Screen2.h"

using namespace std;

enum
  {
    TEXT_Main = wxID_HIGHEST + 1, // declares an id which will be used to call our button
    MENU_NewTv,
    MENU_NewRadio,
    MENU_NewAv,
    MENU_NewFib,
    MENU_EdTv,
    MENU_EdRadio,
    MENU_EdAv,
    MENU_EdFib,
    MENU_Save,
    MENU_Quit,
  };

screen *avItem;

// create the frame class

class MyFrame : public wxFrame
{
public:
    MyFrame();
    void NewTVChannel(wxCommandEvent& WXUNUSED(event));
    void NewRadioChannel(wxCommandEvent& WXUNUSED(event));
    void NewAvItems(wxCommandEvent& WXUNUSED(event));
    void NewFibItems(wxCommandEvent& WXUNUSED(event));
    void EdTvItems(wxCommandEvent& WXUNUSED(event));
    void EdRadioItems(wxCommandEvent& WXUNUSED(event));
    void EdAvItems(wxCommandEvent& WXUNUSED(event));
    void EdFibItems(wxCommandEvent& WXUNUSED(event));
    void Save(wxCommandEvent& WXUNUSED(event));
    void Quit(wxCommandEvent& WXUNUSED(event));
    Screen2 *frameGraph;
    // wxFrame *frameMain2;
    // wxImage myBitmap2 = wxImage("./Living_2048.png", wxBITMAP_TYPE_PNG);

private:
    DECLARE_EVENT_TABLE();
    mediaItem *tvItem, *radioItem;
};



//MyFrame constructor gh
MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Living Input", wxDefaultPosition, wxDefaultSize)
{
    CreateStatusBar(2);
    wxMenuBar *MainMenu = new wxMenuBar(0);
    wxMenu *NewMenu = new wxMenu();
    wxMenu *EditMenu = new wxMenu();
    wxMenu *FileMenu = new wxMenu();

    //New Menu
    NewMenu->Append(MENU_NewTv, wxT("TV Station"),
      wxT("Create a new TV station"));
    NewMenu->Append(MENU_NewRadio, wxT("Radio Station"),
      wxT("Create a new radio station"));
    NewMenu->Append(MENU_NewAv, wxT("AV Buttons"),
      wxT("Create a new button for audio or video command"));
    NewMenu->Append(MENU_NewFib, wxT("Fibaro Item"),
      wxT("Create a new Fibaro item"));

    //Edit menu
    EditMenu->Append(MENU_EdTv, wxT("TV Station"),
      wxT("Create a new TV station"));
    EditMenu->Append(MENU_EdRadio, wxT("Radio Station"),
      wxT("Create a new radio station"));
    EditMenu->Append(MENU_EdAv, wxT("AV Buttons"),
      wxT("Create a new button for audio or video command"));
    EditMenu->Append(MENU_EdFib, wxT("Fibaro Item"),
      wxT("Create a new Fibaro item"));

    // File Menu
    FileMenu->Append(MENU_Save, wxT("Save"),
      wxT("Save the current file"));
    FileMenu->Append(MENU_Quit, wxT("Quit"),
      wxT("Quit the editor"));

    MainMenu->Append(NewMenu, wxT("New"));
    MainMenu->Append(EditMenu, wxT("Edit"));
    MainMenu->Append(FileMenu, wxT("File"));
    SetMenuBar(MainMenu);

}

BEGIN_EVENT_TABLE (MyFrame, wxPanel)
  EVT_MENU(MENU_NewTv, MyFrame::NewTVChannel)
  EVT_MENU(MENU_NewRadio, MyFrame::NewRadioChannel)
  EVT_MENU(MENU_NewAv, MyFrame::NewAvItems)
  EVT_MENU(MENU_NewFib, MyFrame::NewFibItems)
  EVT_MENU(MENU_EdTv, MyFrame::EdTvItems)
  EVT_MENU(MENU_EdRadio, MyFrame::EdRadioItems)
  EVT_MENU(MENU_EdAv, MyFrame::EdAvItems)
  EVT_MENU(MENU_EdFib, MyFrame::EdFibItems)
  EVT_MENU(MENU_Save, MyFrame::Save)
  EVT_MENU(MENU_Quit, MyFrame::Quit)
  EVT_PAINT(MyFrame::OnPaint)
END_EVENT_TABLE()

void MyFrame::NewTVChannel(wxCommandEvent& WXUNUSED(event))
{
    wxRect myRect = wxGetClientDisplayRect();
    mediaItem *tvChannels = new mediaItem("TV Channel", wxPoint(0, 50), wxSize(myRect.width, (myRect.height - 50)), "./Data/TVs.bin", "./Pictures/TVChannels/");
    tvChannels->NewChannel("./Data/TVs.bin", "./Pictures/TVChannels/");
}

void MyFrame::NewRadioChannel(wxCommandEvent& WXUNUSED(event))
{
    wxRect myRect = wxGetClientDisplayRect();
    mediaItem *radioChannels = new mediaItem("Radio Channel", wxPoint(0, 50), wxSize(myRect.width, (myRect.height - 50)), "./Data/Radios.bin", "./Pictures/RadioChannels/");
    radioChannels->NewChannel("./Data/Radios.bin", "./Pictures/RadioChannels");
}
void MyFrame::NewAvItems(wxCommandEvent& WXUNUSED(event))
{
    frameGraph = new Screen2("Test", wxPoint(50, 50), wxSize(450, 340) );
    frameGraph->Show(true);

}
void MyFrame::NewFibItems(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::EdTvItems(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::EdRadioItems(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::EdAvItems(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::EdFibItems(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::Save(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::Quit(wxCommandEvent& WXUNUSED(event))
{
}

// start program
class MainApp : public wxApp
{
public:
	wxFrame *frameMain;
	MyFrame *frameGraph;
	// AvItem * avItem;
    MainApp() {}

    virtual ~MainApp() {}

    virtual bool OnInit()
    {

		wxInitAllImageHandlers();

		// wxRect myRect = wxGetClientDisplayRect();

		wxFrame *frameMain = new MyFrame();
		// rameMain->createSubFrame(frameMain);
		frameMain->Show(true);
		// frameGraph = new MyFrame(frameMain);
		avItem = new screen();
        // MyScreen();
		return true;

    }
};



DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)


