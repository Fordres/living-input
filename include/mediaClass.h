#ifndef MEDIAITEM_H
#define MEDIAITEM_H

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

struct Station {
    int counter;
    int coordinates[2];
    char name[100];
    char logo[100];
};

enum
  {
    TEXT_CTL_INPUT1 = wxID_HIGHEST + 1, // declares an id which will be used to call our button
    TEXT_CTL_INPUT2,
    CTL_LIST,
    SCR_FRAME
  };

using namespace std;

// create the frame class

class mediaItem : public wxFrame
{
public:
    mediaItem(const wxString& title, const wxPoint& pos, const wxSize& size, const string objectData, const string objectLogos);
    bool writeToFile(const vector<Station>& stations, const string& filename);
    vector<Station> readFromFile(const string& filename);
    bool openStationsFile(const string& filename);
    wxImageList* ReadItemsList(vector<Station> readData);
    void NewChannel(const string objectData, const string objectLogos);
    void ShowItemList(vector<Station> readData);
    void Input1Enter(wxCommandEvent& event);
    void Input2Enter(wxCommandEvent& event);
    void CtlListSelect(wxListEvent& event);
    void ConfirmMediaChanels(wxString stationFile, const string& filename);

    wxImage testpt2, largeLogo;
    wxListCtrl* ReadLogos(const string& filename);

private:
    vector<Station> readData, MyData;
    wxTextCtrl *input1, *input2;
    wxListCtrl *mediaCtl;
    DECLARE_EVENT_TABLE();
    // int menuItem;
    string mediaLogos, mediaData;
    wxFrame *mediaMainScreen;
};



//MyFrame constructor gh
mediaItem::mediaItem(const wxString& title, const wxPoint& pos, const wxSize& size, const string objectData, const string objectLogos)
{
    mediaData = objectData;
    mediaLogos = objectLogos;
    mediaMainScreen = new wxFrame(this, SCR_FRAME, title, pos, size);
    // mediaMainScreen->Show(true);
}

BEGIN_EVENT_TABLE (mediaItem, wxFrame)
  EVT_TEXT_ENTER(TEXT_CTL_INPUT1, mediaItem::Input1Enter)
  EVT_TEXT_ENTER(TEXT_CTL_INPUT2, mediaItem::Input2Enter)
  EVT_LIST_ITEM_ACTIVATED(CTL_LIST, mediaItem::CtlListSelect)
END_EVENT_TABLE()

bool mediaItem::openStationsFile(const string& mediaData) {
    fstream file(mediaData);
    if (file.is_open()) {
        file.close();
        return true;
    }
    else {
        string text = "Could not find file\n Create " + mediaData + "?";
        wxMessageDialog *fileOk = new wxMessageDialog(this, text, "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
        if (fileOk->ShowModal() == wxID_YES) {
            fstream file(mediaData, ios_base::app | ios_base::binary);
            file.close();
            return true;
        }
        else return false;
    }
}

bool mediaItem::writeToFile(const vector<Station>& stations, const string& mediaData) {
    fstream file(mediaData, ios_base::app | ios_base::binary);
    if (file.is_open()) {
        for (const auto& station1 : stations) {
            file << station1.name << " " << station1.logo << " " << station1.counter << " "
                << station1.coordinates[0] << " " << station1.coordinates[1] << endl;
        }
        file.close();
        wxMessageDialog *fileOk = new wxMessageDialog(this, "Data written succesfully to file.", "Message", wxOK, wxDefaultPosition);
        fileOk->ShowModal();
        return true;
    } else {
        wxMessageDialog *fileOk = new wxMessageDialog(this, "Coud not open the file.", "Message", wxOK, wxDefaultPosition);
        fileOk->ShowModal();
        return false;
    }
}

vector<Station> mediaItem::readFromFile(const string& filename) {
    vector<Station> stations;
    fstream file;
    file.open(filename);

    if (file.is_open()) {
        string logo, name, logoSmall ;
        file.clear();
        file.seekg(0);

        int counter, i;
        int coordinates[2];

        i = 1;
        while (file >> name >> logo >> counter >> coordinates[0] >> coordinates[1]) {
        Station station1;
        strcpy(station1.logo, logo.c_str());
        strcpy(station1.name, name.c_str());
        station1.counter = counter;
        station1.coordinates[0] = coordinates[0];
        station1.coordinates[1] = coordinates[1];
        stations.push_back(station1);
        i++;
        }

        file.close();

    }
    return stations;
}

void mediaItem::NewChannel(const string objectData, const string objectLogos)

{
    vector<wxString> channelList;

    readData.clear();

    readData = readFromFile(mediaData);
    ShowItemList(readData);

    mediaMainScreen->Show(true);
    // mediaMainScreen->SetFocus();
    wxMessageDialog *fileOk = new wxMessageDialog(this, "Create new Channel?", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
    if (fileOk->ShowModal() == wxID_YES) {
        SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        wxStaticText *label0 = new wxStaticText(mediaMainScreen, wxID_ANY, "New Channel: ", wxPoint(25,470), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );
        wxStaticText *label1 = new wxStaticText(mediaMainScreen, wxID_ANY, "Channel Number: ", wxPoint(25,500), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );


        input1 = new wxTextCtrl(mediaMainScreen,TEXT_CTL_INPUT1,"  ", wxPoint(310,500), wxSize(40,30), wxALIGN_LEFT | wxBORDER_SIMPLE | wxTE_PROCESS_ENTER);
        wxStaticText *label2 = new wxStaticText(mediaMainScreen, wxID_ANY, "Name: ", wxPoint(25, 550), wxSize(300,30), wxALIGN_LEFT);
        input2 = new wxTextCtrl(mediaMainScreen,TEXT_CTL_INPUT2,"  ", wxPoint(310,550), wxSize(100,30), wxALIGN_LEFT | wxBORDER_SIMPLE | wxTE_PROCESS_ENTER);
        wxStaticText *label3 = new wxStaticText(mediaMainScreen, wxID_ANY, "Logo: ", wxPoint(25, 600), wxSize(300,30), wxALIGN_LEFT);
        ReadLogos(mediaLogos);
    };
}

wxListCtrl* mediaItem::ReadLogos(const string& filename) {
    wxDir logoDir(filename);
    if ( !logoDir.IsOpened() ) {
        wxMessageDialog *fileOk = new wxMessageDialog(this, "Can't open file Pictures", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
        return NULL;
    }

    wxBitmap zenderPointer;
    wxImage largeLogo;
    zenderPointer.Create(16,16, wxBITMAP_SCREEN_DEPTH);
    wxArrayString files;
    size_t numberFiles, i;

    numberFiles = wxDir::GetAllFiles(filename, &files, wxEmptyString, wxDIR_FILES);
    wxImageList *mediaImageList;
    mediaImageList = new wxImageList(16, 16, true, numberFiles);

    mediaCtl = new wxListCtrl(mediaMainScreen, CTL_LIST, wxPoint(25,600), wxSize(1900,400), wxLC_LIST | wxLC_NO_HEADER | wxLC_SINGLE_SEL |
                wxSUNKEN_BORDER, wxDefaultValidator, " ");
    mediaCtl->AssignImageList(mediaImageList, wxIMAGE_LIST_SMALL);

    for(i=0; i<numberFiles; i++) {
        zenderPointer = wxBitmap(files[i], wxBITMAP_TYPE_PNG);
        largeLogo = zenderPointer.ConvertToImage();
        largeLogo.Rescale (16, 16, wxIMAGE_QUALITY_NORMAL);
        zenderPointer = *(new wxBitmap(largeLogo, -1));
        mediaImageList->Add(zenderPointer, wxNullBitmap);
        mediaCtl->InsertItem(0, files[i], i);
    };
    return mediaCtl;
}
void mediaItem::CtlListSelect(wxListEvent& event){
    wxString stationFile;
    long lSelectedItem = mediaCtl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

    if (lSelectedItem != wxNOT_FOUND) {
        stationFile = mediaCtl->GetItemText(lSelectedItem);
        wxMessageDialog *fileOk =  new wxMessageDialog(this, stationFile, "Selected Item", wxOK | wxCANCEL, wxDefaultPosition);
        if (fileOk->ShowModal() == wxID_OK) {
            ConfirmMediaChanels(stationFile, mediaData);
        }
        else {
            return;
        }
    }
    else wxMessageBox("Item not found");
}

void mediaItem::ConfirmMediaChanels(wxString stationFile, const string& filename){
    wxFrame *confirmScreen = new wxFrame(this, wxID_ANY, "Confirm data", wxPoint(0,0), wxSize(1000,1000));
    wxMessageDialog *fileOk;
    vector<Station> writeData;
    Station MyData;

    SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    wxStaticText *label0 = new wxStaticText(confirmScreen, wxID_ANY, "New Channel: ", wxPoint(25,20), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );
    wxStaticText *label1 = new wxStaticText(confirmScreen, wxID_ANY, "Channel Number: ", wxPoint(25,70), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );
    wxStaticText *answer1 = new wxStaticText(confirmScreen,wxID_ANY, input1->GetValue() , wxPoint(310,70), wxSize(40,30), wxALIGN_LEFT | wxBORDER_SIMPLE);

    wxStaticText *label2 = new wxStaticText(confirmScreen, wxID_ANY, "Name: ", wxPoint(25, 120), wxSize(300,30), wxALIGN_LEFT);
    wxStaticText *answer2 = new wxStaticText(confirmScreen,wxID_ANY, input2->GetValue() , wxPoint(310,120), wxSize(40,30), wxALIGN_LEFT | wxBORDER_SIMPLE);

    wxStaticText *label3 = new wxStaticText(confirmScreen, wxID_ANY, "Logo: ", wxPoint(25, 170), wxSize(300,30), wxALIGN_LEFT);
    wxStaticText *answer3 = new wxStaticText(confirmScreen,wxID_ANY, stationFile , wxPoint(310,170), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE);
    confirmScreen->Show(true);
    fileOk =  new wxMessageDialog(confirmScreen, "Data Correct ?", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);

    if (fileOk->ShowModal() == wxID_YES) {
        MyData.coordinates[0] = 0;
        MyData.coordinates[1] = 0;

        string strname = input2->GetValue().ToStdString();

        char str[100] = "";
        for (int i = 0; i < strname.length(); i++) {
            str[i] = strname[i];
        }
        strcpy(MyData.name, str);

        int j = 0;
        int hulp = stationFile.length();
         for (int i = 0; i < stationFile.length(); i++) {
             if (stationFile[i] == '/') j = i;
        }

        int lengte = (stationFile.length() - ++j);
        for (int i = 0; i < lengte; i++) {
             str[i] = stationFile[i+j];
        }
        strcpy(MyData.logo, str);

        MyData.counter = atoi(input1->GetValue());

        writeData.push_back(MyData);
        writeToFile(writeData, mediaData);
        confirmScreen->Close();
        mediaMainScreen->Show(false);
    };

}

void mediaItem::Input1Enter(wxCommandEvent& event) {
    wxMessageDialog *fileOk;
    int vecSize = readData.size();
    int i;

    if (atoi(input1->GetValue().c_str()) == 0) {
        fileOk =  new wxMessageDialog(this, "Channel number is not a number or is 0!\n Choose  another number", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
        input1->ChangeValue("");
        if (fileOk->ShowModal() == wxID_YES) input1->SetFocus();
        else input2->SetFocus();
    }
    else {
        for (i = 0; i< vecSize; i++) {
            if (readData[i].counter == atoi(input1->GetValue().c_str())) break;
        }

        if (i >= vecSize) input2->SetFocus();
        else {
            fileOk = new wxMessageDialog(this, "Channel number already exists!\n Choose  another number", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
            input1->ChangeValue("");
            if (fileOk->ShowModal() == wxID_YES) input1->SetFocus();
            else input2->SetFocus();
        }
    }

}

void mediaItem::Input2Enter(wxCommandEvent& event) {
    wxMessageDialog *fileOk;
    int vecSize = readData.size();
    int i;

    for (i = 0; i< vecSize; i++) {
        if (readData[i].name == input2->GetValue()) break;
        }

    if (i >= vecSize) mediaCtl->SetFocus();
    else {
        fileOk = new wxMessageDialog(this, "Channel name already exists!\n Choose  another name", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
        input2->ChangeValue("");
        if (fileOk->ShowModal() == wxID_YES) input2->SetFocus();
        else mediaCtl->SetFocus();
    }
}

wxImageList* mediaItem::ReadItemsList(vector<Station> readData){
    int numberRecords = readData.size();;
    wxImageList *mediaImageList = new wxImageList(16, 16, true, numberRecords);
    wxBitmap zenderPointer[100];
    wxImage noScaleImage;
    wxString pathAndFile, strLogo;

    for (int i = 0 ; i < numberRecords ; i++ ){
        pathAndFile = mediaLogos;
        strLogo = readData[i].logo;
        pathAndFile = pathAndFile + strLogo;

        zenderPointer[i].LoadFile(pathAndFile, wxBITMAP_DEFAULT_TYPE );
        noScaleImage = zenderPointer[i].ConvertToImage();
        noScaleImage.Rescale (16, 16, wxIMAGE_QUALITY_NORMAL);
        zenderPointer[i] = *(new wxBitmap(noScaleImage, -1));
        mediaImageList->Add(zenderPointer[i], wxNullBitmap);
    }
    return mediaImageList;
}

void mediaItem::ShowItemList(vector<Station> readData){

    long itemIndex;

    // load all logos from Stations.bin
    wxImageList *mediaImageList = ReadItemsList(readData);

    // read other data and put them in wxListCtrl
    wxArrayString channelListName, channelListCoord1, channelListCoord2, channelListNumber;
    int numberRecords = readData.size();

    for (int i = 0 ; i < numberRecords ; i++ ){
        channelListName.Add(readData[i].name);
        channelListCoord1.Add(to_string(readData[i].coordinates[0]));
        channelListCoord2.Add(to_string(readData[i].coordinates[1]));
        channelListNumber.Add(to_string(readData[i].counter));
    }

    // create the whole listCtl
    wxListCtrl *mediaCtl;
    SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
    wxStaticText *label1 = new wxStaticText(mediaMainScreen, wxID_ANY, "Already registred channels", wxPoint(25,80), wxSize(300,20), wxALIGN_LEFT | wxBORDER_SIMPLE );
    mediaCtl = new wxListCtrl(mediaMainScreen, wxID_ANY, wxPoint(25,100), wxSize(500,300), wxLC_REPORT | wxLC_SINGLE_SEL |
            wxSUNKEN_BORDER | wxLC_VRULES, wxDefaultValidator, " ");

    // Add first column
	wxListItem col0;
	col0.SetId(0);
	col0.SetText( _("Logo") );
	col0.SetWidth(50);
	mediaCtl->InsertColumn(0, col0);

	// Add second column - dummy
	wxListItem col1;
	col1.SetId(1);
	col1.SetText( _("") );
	col1.SetWidth(1);
	mediaCtl->InsertColumn(1, col1);

	// Add third column
	wxListItem col2;
	col2.SetId(2);
	col2.SetText( _("Channel Number") );
	col2.SetWidth(125);
	col2.SetAlign(wxLIST_FORMAT_RIGHT);
	mediaCtl->InsertColumn(2, col2);

	// Add forth column
	wxListItem col3;
	col3.SetId(3);
	col3.SetText( _("Name") );
	col3.SetWidth(100);
	mediaCtl->InsertColumn(3, col3);

    mediaCtl->AssignImageList(mediaImageList,  wxIMAGE_LIST_SMALL);
    for (int i = 0 ; i < numberRecords ; i++ ){
        itemIndex = mediaCtl->InsertItem(1, "");
        mediaCtl->SetItem(itemIndex, 2, channelListNumber[i]);
        mediaCtl->SetItem(itemIndex, 3, channelListName[i]);
        mediaCtl->SetItemImage(itemIndex, i);
    }
}

/*void mediaItem::NewRadioItems(wxCommandEvent& WXUNUSED(event))
{
    fstream file;
    vector<wxString> radioList;
    vector<Station> stations;
    menuItem = 2;

    file = openStationsFile("./Data/Radios.bin");
    readData.clear();
    readData = readFromFile("./Data/Radios.bin");
    ShowItemList(readData);

    wxMessageDialog *fileOk = new wxMessageDialog(this, "Create new Radio Channel?", "Message", wxYES_NO | wxCANCEL, wxDefaultPosition);
    if (fileOk->ShowModal() == wxID_YES) {
        SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
        wxStaticText *label0 = new wxStaticText(this, wxID_ANY, "New Channel: ", wxPoint(25,470), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );
        wxStaticText *label1 = new wxStaticText(this, wxID_ANY, "Channel Number: ", wxPoint(25,500), wxSize(300,30), wxALIGN_LEFT | wxBORDER_SIMPLE );


        input1 = new wxTextCtrl(this,TEXT_CTL_INPUT1,"  ", wxPoint(310,500), wxSize(40,30), wxALIGN_LEFT | wxBORDER_SIMPLE | wxTE_PROCESS_ENTER);
        wxStaticText *label2 = new wxStaticText(this, wxID_ANY, "Name: ", wxPoint(25, 550), wxSize(300,30), wxALIGN_LEFT);
        input2 = new wxTextCtrl(this,TEXT_CTL_INPUT2,"  ", wxPoint(310,550), wxSize(100,30), wxALIGN_LEFT | wxBORDER_SIMPLE | wxTE_PROCESS_ENTER);
        wxStaticText *label3 = new wxStaticText(this, wxID_ANY, "Logo: ", wxPoint(25, 600), wxSize(300,30), wxALIGN_LEFT);
        ReadLogos("./Pictures/RadioChannels/");
    };

    file.close();
}*/

#endif // MEDIAITEM_H
