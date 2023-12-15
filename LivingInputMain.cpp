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

using namespace std;

struct Station {
    int counter;
    int coordinates[2];
    char logo[100];
};

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
    MENU_Quit
  };

// create the frame class

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    void NewTvItems(wxCommandEvent& WXUNUSED(event));
    void NewRadioItems(wxCommandEvent& WXUNUSED(event));
    void NewAvItems(wxCommandEvent& WXUNUSED(event));
    void NewFibItems(wxCommandEvent& WXUNUSED(event));
    void EdTvItems(wxCommandEvent& WXUNUSED(event));
    void EdRadioItems(wxCommandEvent& WXUNUSED(event));
    void EdAvItems(wxCommandEvent& WXUNUSED(event));
    void EdFibItems(wxCommandEvent& WXUNUSED(event));
    void Save(wxCommandEvent& WXUNUSED(event));
    void Quit(wxCommandEvent& WXUNUSED(event));
    void writeToFile(const vector<Station>& stations, const string& filename);
    vector<Station> readFromFile(const string& filename);
private:
    DECLARE_EVENT_TABLE();
};



//MyFrame constructor gh
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
   //: wxFrame(NULL, wxID_ANY, title, pos, size, wxMINIMIZE_BOX | wxCLOSE_BOX)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
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

    Maximize();
}

BEGIN_EVENT_TABLE (MyFrame, wxFrame)
  EVT_MENU(MENU_NewTv, MyFrame::NewTvItems)
  EVT_MENU(MENU_NewRadio, MyFrame::NewRadioItems)
  EVT_MENU(MENU_NewAv, MyFrame::NewAvItems)
  EVT_MENU(MENU_NewFib, MyFrame::NewFibItems)
  EVT_MENU(MENU_EdTv, MyFrame::EdTvItems)
  EVT_MENU(MENU_EdRadio, MyFrame::EdRadioItems)
  EVT_MENU(MENU_EdAv, MyFrame::EdAvItems)
  EVT_MENU(MENU_EdFib, MyFrame::EdFibItems)
  EVT_MENU(MENU_Save, MyFrame::Save)
  EVT_MENU(MENU_Quit, MyFrame::Quit)
END_EVENT_TABLE()

ofstream MyFrame::openStationsFile() {
    fstream file("./Data/Stations.bin", ios_base::app | ios_base::binary);
    if (!file.is_open()) {
        wxMessageDialog noFile = wxMessageDialog(this, "Coud not open the file. /n Create Stations.bin?", "Message", wxOK | wxCANCEL, wxDefaultPosition);
        if (noFile.ShowModal() == 5100) openStationsFile();
        else return NULL;
        }
}

void MyFrame::writeToFile(const vector<Station>& stations, const string& filename) {
    ofstream file(filename, ios_base::app | ios_base::binary);
    if (file.is_open()) {
        for (const auto& station1 : stations) {
            file << station1.logo << " " << station1.counter << " "
                << station1.coordinates[0] << " " << station1.coordinates[1] << endl;
        }
        file.close();
        wxMessageDialog fileOk = wxMessageDialog(this, "Data written succesfully to file.", "Message", wxOK, wxDefaultPosition);
        fileOk.ShowModal();
    } else {
        wxMessageDialog fileOk = wxMessageDialog(this, "Coud not open the file.", "Message", wxOK, wxDefaultPosition);
        fileOk.ShowModal();
    }
}

vector<Station> MyFrame::readFromFile(fstream file) {
    vector<Station> stations;
    fstream file(filename, ios_base::binary);

    if (file.is_open()) {
        string logo;
        int counter;
        int coordinates[2];

        while (file >> logo >> counter >> coordinates[0] >> coordinates[1]) {
        Station station1;
        strcpy(station1.logo, logo.c_str());
        station1.counter = counter;
        station1.coordinates[0] = coordinates[0];
        station1.coordinates[1] = coordinates[1];
        stations.push_back(station1);
        }

        file.close();

    }
    return stations;
}

bool MyFrame::NewTvItems(wxCommandEvent& WXUNUSED(event))
{
    ofstream file;
    wxString filename, filespec = "";
    int flags;
    if (openStationsFile() == NULL) return false;

    vector<Station> readData;
    readData.clear();
    int numberRecords = readData.size();
;
    if (readData = readFromFile("./Data/Stations.bin")) == NULL) return false;
    else {
        // read path to logos and put them in wxListCtrl
        wxDir logoDir = wxDir("/home/oem/Developments/LivingInput/Pictures");
        //wxArrayString tvList;
        wxImageList *tvImageList = new wxImageList(16, 16, true, numberRecords);
        wxBitmap zenderPointer;
        bool result;
        zenderPointer.Create(16,16, wxBITMAP_SCREEN_DEPTH);
        for (i = 0 ; i < numberRecords ; i++ ){
            zenderPointer.LoadFile(readData[i].logo, wxBITMAP_DEFAULT_TYPE );
            tvImageList->Add(zenderPointer, wxNullBitmap);
        }

        bool cont = logoDir.GetFirst(&filename, filespec, flags);
        while ( cont ){
            tvList.Add(filename);
            cont = logoDir.GetNext(&filename);
        }

        //if (!readData.empty()){
        //    wxMessageDialog fileOk = wxMessageDialog(this, "Data read succesfully from file.  \n Create new Record ?", "Message", wxOK | wxCANCEL, wxDefaultPosition);
        //    if (fileOk.ShowModal() = 5101) return false;
        //    else {
            SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
            wxStaticText *label1 = new wxStaticText(this, wxID_ANY, "Channel Number: ", wxPoint(10,100), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );
            wxTextCtrl *input1 = new wxTextCtrl(this,wxID_ANY,"  ", wxPoint(310,100), wxSize(40,30), wxALIGN_LEFT | wxBORDER_SIMPLE);
            wxStaticText *label2 = new wxStaticText(this, wxID_ANY, "Path to logo: ", wxPoint(10, 200), wxSize(300,30), wxALIGN_LEFT);
                // wxTextCtrl *input2 = new wxTextCtrl(this,wxID_ANY,"  ", wxPoint(310,200), wxSize(500,30), wxALIGN_LEFT | wxBORDER_SIMPLE);
            wxStaticText *label = new wxStaticText(this, wxID_ANY, "Command string: ", wxPoint(10, 600), wxSize(300,30), wxALIGN_LEFT);
            wxTextCtrl *input3 = new wxTextCtrl(this,wxID_ANY,"  ", wxPoint(310,600), wxSize(1000,30), wxALIGN_LEFT | wxBORDER_SIMPLE);



            result = zenderPointer[0].LoadFile("./Pictures/HistoryIcon.png", wxBITMAP_DEFAULT_TYPE );
            result = zenderPointer[1].LoadFile("./Pictures/HistoryIcon.png", wxBITMAP_DEFAULT_TYPE );
            result = zenderPointer[2].LoadFile("./Pictures/HistoryIcon.png", wxBITMAP_DEFAULT_TYPE );
            tvImageList->Add(zenderPointer[0], wxNullBitmap);
            tvImageList->Add(zenderPointer[1], wxNullBitmap);
            tvImageList->Add(zenderPointer[2], wxNullBitmap);

    bool cont = logoDir.GetFirst(&filename, filespec, flags);
    int i = 0;
    while ( cont )
    {
        tvList.Add(filename);
        cont = logoDir.GetNext(&filename);
        // cout << tvList[i] << endl;
        i++;
    }
    wxListBox *tvBox;
    wxListCtrl *tvCtl;
    //tvBox = new wxListBox(this, wxID_ANY, wxPoint(310,200), wxSize(500,300), 0, 0, wxLB_SORT);
    //tvBox->Append(tvList);
    tvCtl = new wxListCtrl(this, wxID_ANY, wxPoint(310,200), wxSize(500,300), wxLC_LIST | wxLC_NO_HEADER | wxLC_SINGLE_SEL |
                wxSUNKEN_BORDER, wxDefaultValidator, " Test");

    tvCtl->AssignImageList(tvImageList,  wxIMAGE_LIST_SMALL);
    tvCtl->InsertItem(0, "1---", 0);
    tvCtl->InsertItem(0, "2---", 1);
    tvCtl->InsertItem(0, "3---", 2);
    logoDir.Close();
}
void MyFrame::NewRadioItems(wxCommandEvent& WXUNUSED(event))
{
}
void MyFrame::NewAvItems(wxCommandEvent& WXUNUSED(event))
{
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
	wxFrame *frame;
    MainApp() {}

    virtual ~MainApp() {}

    virtual bool OnInit()
    {
		wxInitAllImageHandlers();
		wxRect myRect = wxGetClientDisplayRect();
		wxFrame *frame = new MyFrame("Living Input ", wxDefaultPosition, wxDefaultSize);
		frame->Show(true);
		/*wxFrame *frame2 = new AudioScreen("Audio - Video", wxPoint(300,350), wxSize(960, 600));
		frame2->Show(true);*/
		return true;

    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)


