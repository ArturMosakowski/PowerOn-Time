//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Wid3.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
        int xM3, xR3, yM3, yR3; //wsoolrzedne pozycji [M-myszy, R-roznica pozycji myszy i okna]
        int UpDwn3;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormCreate(TObject *Sender)
{
        Form4->Left = Form1->Opt.x[3];
        Form4->Top = Form1->Opt.y[3];
        Form4->Image3->Picture->LoadFromFile("gfx//MainBgrD.bmp");
        Form4->Image3->Canvas->Pen->Color=clSilver;
        Form4->Image3->Canvas->Pen->Width=1;
        Form4->Image3->Canvas->MoveTo(12,128);Form4->Image3->Canvas->LineTo(360,128);
        Form4->Image3->Canvas->MoveTo(12,129);Form4->Image3->Canvas->LineTo(360,129);
}
//---------------------------------------------------------------------------

void __fastcall TForm4::FormClose(TObject *Sender, TCloseAction &Action)
{
        Form4->Visible = False;
        Form1->AlphaBlend = False;
        Form1->Enabled = True;        
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Image4Click(TObject *Sender)
{
        Form4->Visible = False;
        Form1->AlphaBlend = False;
        Form1->Enabled = True;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        UpDwn3 = 1;
        POINT poz;
        GetCursorPos(&poz);
        xM3 = poz.x; yM3 = poz.y;
        xR3 = xM3 - Form4->Left;
        yR3 = yM3 - Form4->Top;
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image2MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if (UpDwn3 == 1)
        {
                POINT poz;
                GetCursorPos(&poz);
                xM3 = poz.x; yM3 = poz.y;
                Form4->Left = xM3 - xR3;
                Form4->Top = yM3 - yR3;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm4::Image2MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        UpDwn3 = 0;
        Form1->Opt.x[3] = Form4->Left;
        Form1->Opt.y[3] = Form4->Top;
        Form1->Opt.SaveFileOpt();
}
//---------------------------------------------------------------------------

