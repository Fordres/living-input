#ifndef SCREEN2_H
#define SCREEN2_H

#include <wxFrame.h>


class Screen2 : public wxFrame
{
public:
    Screen2(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    void OnPaint(wxPaintEvent& WXUNUSED(event));
    const wxBitmap myBitmap2 = wxBitmap("Living_2048.gif", wxBITMAP_TYPE_GIF);
    private:
};

Screen2::Screen2(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
    this->Bind(wxEVT_PAINT, &GraphFrame::OnPaint, this);
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

#endif // SCREEN2_H
