#ifndef SCREEN2_H
#define SCREEN2_H

#include <wx/dragimag.h>
#include <wx/mousestate.h>
#include <string>

struct Item {
    char type[10];
    char typePicture[15];
    int x;
    int y;
};

enum
  {
    MENU_ITEM_TV = wxID_HIGHEST + 1, // declares an id which will be used to call our button
    MENU_ITEM_AUDIO,
    MENU_ITEM_SENSOR,
    MENU_ITEM_LAMP,
    MENU_ITEM_TERMO,
    MENU_MOVE,
    MENU_DELETE
  };

class Screen2 : public wxFrame
{
public:
    Screen2(const wxString& title, const wxPoint& pos, const wxSize& size);
    void AdditemIcon(wxCommandEvent& WXUNUSED(event));
    void AddAudioIcon(wxCommandEvent& WXUNUSED(event));
    void AddSensorIcon(wxCommandEvent& WXUNUSED(event));
    void AddLampIcon(wxCommandEvent& WXUNUSED(event));
    void AddThermoIcon(wxCommandEvent& WXUNUSED(event));
    void MoveItem(wxCommandEvent& WXUNUSED(event));
    void DeleteItem(wxCommandEvent& WXUNUSED(event));
    void OnMouseEvent(wxMouseEvent& event);
private:
    void OnPaint(wxPaintEvent& WXUNUSED(event));
    void WriteDeviceItem(wxPoint dragPos);
    vector<Item> ReadDeviceItems();
    void render(wxDC&  dc, wxBitmap myBitmap, int x, int y);
    void paintNow(wxBitmap myBitmap, int x, int y);
    const wxBitmap myBitmap2 = wxBitmap("Living_2048.gif", wxBITMAP_TYPE_GIF);
    wxDragImage *itemIcon;
    wxFrame * graphWindow;
    //bool boolMove;
    int itemSort;
    vector<Item> items;
    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE (Screen2, wxFrame)
  EVT_MENU(MENU_ITEM_TV, Screen2::AdditemIcon)
  EVT_MENU(MENU_ITEM_AUDIO, Screen2::AddAudioIcon)
  EVT_MENU(MENU_ITEM_SENSOR, Screen2::AddSensorIcon)
  EVT_MENU(MENU_ITEM_LAMP, Screen2::AddLampIcon)
  EVT_MENU(MENU_ITEM_TERMO, Screen2::AddThermoIcon)
  EVT_MENU(MENU_MOVE, Screen2::MoveItem)
  EVT_MENU(MENU_DELETE, Screen2::DeleteItem)
  EVT_MOUSE_EVENTS(Screen2::OnMouseEvent)
END_EVENT_TABLE()

Screen2::Screen2(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    graphWindow = this;
    wxMenuBar *graphMenu = new wxMenuBar(0);
    wxMenu *menuItem = new wxMenu();
    wxMenu *menuMove = new wxMenu();
    wxMenu *menuDelete = new wxMenu();

    menuItem->Append(MENU_ITEM_TV, wxT("TV"));
    menuItem->Append(MENU_ITEM_AUDIO, wxT("Audio"));
    menuItem->Append(MENU_ITEM_SENSOR, wxT("Sensor"));
    menuItem->Append(MENU_ITEM_LAMP, wxT("Lamp"));
    menuItem->Append(MENU_ITEM_TERMO, wxT("Thermostat"));

    menuMove->Append(MENU_MOVE, wxT("Move Item"));

    menuDelete->Append(MENU_DELETE, wxT("Delete Item" ));

    graphMenu->Append(menuItem, wxT("Item"));
    graphMenu->Append(menuMove, wxT("Move Item") );
    graphMenu->Append(menuDelete, wxT("Delete Item"));
    SetMenuBar(graphMenu);

    this->Bind(wxEVT_PAINT, &Screen2::OnPaint, this);
    this->Maximize();
    items = ReadDeviceItems();
    int vecSize = items.size();
    for (auto & element : items)
    {
        string itemPath = "./Pictures/" + std::string(element.typePicture);
        wxBitmap myBitmap = wxBitmap(itemPath, wxBITMAP_TYPE_PNG);
        paintNow(myBitmap, element.x, element.y);
    };


}

/*void Screen2::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	PrepareDC(dc);

	wxPen mijnPen = wxPen(wxColour(200,200,200), 10, wxPENSTYLE_SOLID);
	dc.SetPen( mijnPen);
	dc.SetBrush( *wxBLUE_BRUSH );
    dc.DrawBitmap(myBitmap2, 0, 20, true);
};*/

void Screen2::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	render(dc, myBitmap2, 0, 20);
}

void Screen2::paintNow(wxBitmap myBitmap, int x, int y)
{
	wxClientDC dc(this);
	render(dc, myBitmap, x, y);
}

void Screen2::render(wxDC&  dc, wxBitmap myBitmap, int x, int y)
{
	wxPen mijnPen = wxPen(wxColour(200,200,200), 10, wxPENSTYLE_SOLID);
	dc.SetPen( mijnPen);
	dc.SetBrush( *wxBLUE_BRUSH );
    dc.DrawBitmap(myBitmap, x, y, true);
}

void Screen2::AdditemIcon(wxCommandEvent& WXUNUSED(event)){
    itemSort = 1;
    wxBitmap tvBitmap = wxBitmap("./Pictures/tv.png", wxBITMAP_TYPE_PNG);
    itemIcon = new wxDragImage( tvBitmap, 6);
}

void Screen2::AddAudioIcon(wxCommandEvent& WXUNUSED(event)){
    itemSort = 2;
    wxBitmap tvBitmap = wxBitmap("./Pictures/streaming.png", wxBITMAP_TYPE_PNG);
    itemIcon = new wxDragImage( tvBitmap, 6);
}

void Screen2::AddSensorIcon(wxCommandEvent& WXUNUSED(event)){
    itemSort = 3;
    wxBitmap tvBitmap = wxBitmap("./Pictures/Door_Closed.png", wxBITMAP_TYPE_PNG);
    itemIcon = new wxDragImage( tvBitmap, 6);
}

void Screen2::AddLampIcon(wxCommandEvent& WXUNUSED(event)){
    itemSort = 4;
    wxBitmap tvBitmap = wxBitmap("./Pictures/lamp_aan.png", wxBITMAP_TYPE_PNG);
    itemIcon = new wxDragImage( tvBitmap, 6);
}

void Screen2::AddThermoIcon(wxCommandEvent& WXUNUSED(event)){
    itemSort = 5;
    wxBitmap tvBitmap = wxBitmap("./Pictures/Thermostat.png", wxBITMAP_TYPE_PNG);
    itemIcon = new wxDragImage( tvBitmap, 6);
}

void Screen2::MoveItem(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::DeleteItem(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::OnMouseEvent(wxMouseEvent& event)
{
    if (event.LeftDown())
    {
        wxPoint dragPos = event.GetPosition();
        wxPoint mousePos = GetPosition();
        itemIcon->BeginDrag(mousePos, this, false, NULL);
        itemIcon->Show();
        itemIcon->Move(dragPos);

    }
    else if (event.LeftUp())
    {
        wxPoint dragPos = event.GetPosition();
        itemIcon->EndDrag();
        WriteDeviceItem(dragPos);

    }
    else if (event.Dragging())
    {
        wxPoint dragPos = event.GetPosition();
        itemIcon->Move(dragPos);

    }
}

void Screen2::WriteDeviceItem(wxPoint dragPos) {
    fstream file("./Data/DeviceItems.txt", ios_base::app);
    if (itemSort == 1) file << "TV "<< "tv.png " << dragPos.x << " " << dragPos.y << endl;
    else if (itemSort == 2 ) file << "Audio " << "streaming.png " << dragPos.x << " " << dragPos.y << endl;
    else if (itemSort == 3 ) file << "Sensor " << "Door_Closed.png " << dragPos.x << " " << dragPos.y << endl;
    else if (itemSort == 4 ) file << "Lamp " << "lamp_aan.png " << dragPos.x << " " << dragPos.y << endl;
    else if (itemSort == 5 ) file << "Thermostat " << "Thermostat.png " << dragPos.x << " " << dragPos.y << endl;
    file.close();
}

vector<Item> Screen2::ReadDeviceItems() {
    fstream file("./Data/DeviceItems.txt", ios_base::app);
    if (file.is_open()) {
        string type, typePicture;
        file.clear();
        file.seekg(0);

        int counter, i;
        int x, y;

        i = 1;
        while (file >> type >> typePicture >> x >> y) {
            Item item1;
            strcpy(item1.type, type.c_str());
            strcpy(item1.typePicture, typePicture.c_str());
            item1.x = x;
            item1.y = y;
            items.push_back(item1);
            i++;
        }
        file.close();
    }
    return items;
}

#endif // SCREEN2_H
