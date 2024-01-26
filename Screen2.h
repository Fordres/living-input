#ifndef SCREEN2_H
#define SCREEN2_H

#include <wx/dragimag.h>

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
    void AddTVIcon(wxCommandEvent& WXUNUSED(event));
    void AddAudioIcon(wxCommandEvent& WXUNUSED(event));
    void AddSensorIcon(wxCommandEvent& WXUNUSED(event));
    void AddLampIcon(wxCommandEvent& WXUNUSED(event));
    void AddThermoIcon(wxCommandEvent& WXUNUSED(event));
    void MoveItem(wxCommandEvent& WXUNUSED(event));
    void DeleteItem(wxCommandEvent& WXUNUSED(event));
    void OnMouseDown(wxMouseEvent & evt);
    void OnMouseUp(wxMouseEvent & evt);
    void ItemMove();
private:
    void OnPaint(wxPaintEvent& WXUNUSED(event));
    const wxBitmap myBitmap2 = wxBitmap("Living_2048.gif", wxBITMAP_TYPE_GIF);
    wxDragImage *tvIcon;
    wxFrame * graphWindow;
    bool boolMove;
    DECLARE_EVENT_TABLE();
};

BEGIN_EVENT_TABLE (Screen2, wxFrame)
  EVT_MENU(MENU_ITEM_TV, Screen2::AddTVIcon)
  EVT_MENU(MENU_ITEM_AUDIO, Screen2::AddAudioIcon)
  EVT_MENU(MENU_ITEM_SENSOR, Screen2::AddSensorIcon)
  EVT_MENU(MENU_ITEM_LAMP, Screen2::AddLampIcon)
  EVT_MENU(MENU_ITEM_TERMO, Screen2::AddThermoIcon)
  EVT_MENU(MENU_MOVE, Screen2::MoveItem)
  EVT_MENU(MENU_DELETE, Screen2::DeleteItem)
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

    this->Bind(wxEVT_RIGHT_DOWN, &Screen2::OnMouseDown, this );
	this->Bind(wxEVT_RIGHT_UP, &Screen2::OnMouseUp, this );
}

void Screen2::OnPaint(wxPaintEvent& WXUNUSED(event))
{
	wxPaintDC dc(this);
	PrepareDC(dc);

	wxPen mijnPen = wxPen(wxColour(200,200,200), 10, wxPENSTYLE_SOLID);
	dc.SetPen( mijnPen);
	dc.SetBrush( *wxBLUE_BRUSH );
    dc.DrawBitmap(myBitmap2, 0, 20, true);
};

void Screen2::AddTVIcon(wxCommandEvent& WXUNUSED(event)){
    wxBitmap tvBitmap = wxBitmap("tv.png", wxBITMAP_TYPE_GIF);
    tvIcon = new wxDragImage( tvBitmap, 6);
    /*tvIcon->BeginDrag(wxPoint(100,100), this, false, NULL);
    tvIcon->Show();
    tvIcon->Move(wxPoint(300,300));*/
}

void Screen2::AddAudioIcon(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::AddSensorIcon(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::AddLampIcon(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::AddThermoIcon(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::MoveItem(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::DeleteItem(wxCommandEvent& WXUNUSED(event)){

}

void Screen2::OnMouseDown(wxMouseEvent & evt)
{
    boolMove = true;

    do  {
        wxPoint screenPt = wxGetMousePosition();
        tvIcon->BeginDrag(screenPt, this, false, NULL);
        tvIcon->Show();
        screenPt = wxGetMousePosition();
        tvIcon->Move(screenPt);
    }while (boolMove = true);
}

void Screen2::OnMouseUp(wxMouseEvent & evt)
{
    boolMove = false;
    tvIcon->EndDrag();
}

void Screen2::ItemMove()
{
    wxPoint screenPt;
    tvIcon->Show();
    while (boolMove = true) {
        screenPt = wxGetMousePosition();
        tvIcon->Move(screenPt);
    }
}

#endif // SCREEN2_H
