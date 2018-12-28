//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Wid2.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;

        int pozP2[1];
        int xM2, xR2, yM2, yR2; //wsoolrzedne pozycji [M-myszy, R-roznica pozycji myszy i okna]
        int UpDwn2;
  
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TForm3::Image8Click(TObject *Sender)
{
        Form3->Visible = False;
        Form1->AlphaBlend = False;
        Form1->Enabled = True;
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Image6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        UpDwn2 = 1;
        POINT poz;
        GetCursorPos(&poz);
        xM2 = poz.x; yM2 = poz.y;
        xR2 = xM2 - Form3->Left;
        yR2 = yM2 - Form3->Top;
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image6MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if (UpDwn2 == 1)
        {
                POINT poz;
                GetCursorPos(&poz);
                xM2 = poz.x; yM2 = poz.y;
                Form3->Left = xM2 - xR2;
                Form3->Top = yM2 - yR2;
        }        
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image6MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        UpDwn2 = 0;
        Form1->Opt.x[2] = Form3->Left;
        Form1->Opt.y[2] = Form3->Top;
        Form1->Opt.SaveFileOpt();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image1Click(TObject *Sender)
{
        if (Form1->Opt.Check[0]==0)
        {
                Form1->Opt.Check[0]=1;
                Form1->Opt.Check[1]=0;
                Form1->Opt.Check[2]=0;
                Form3->Image1->Picture->LoadFromFile("gfx//Check1.bmp");
                Form3->Image2->Picture->LoadFromFile("gfx//Check0.bmp");
                Form3->Image3->Picture->LoadFromFile("gfx//Check0.bmp");
                Form1->Opt.SaveFileOpt();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image2Click(TObject *Sender)
{
        if (Form1->Opt.Check[1]==0)
        {
                Form1->Opt.Check[0]=0;
                Form1->Opt.Check[1]=1;
                Form1->Opt.Check[2]=0;
                Form3->Image1->Picture->LoadFromFile("gfx//Check0.bmp");
                Form3->Image2->Picture->LoadFromFile("gfx//Check1.bmp");
                Form3->Image3->Picture->LoadFromFile("gfx//Check0.bmp");
                Form1->Opt.SaveFileOpt();
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Image3Click(TObject *Sender)
{
        if (Form1->Opt.Check[2]==0)
        {
                Form1->Opt.Check[0]=0;
                Form1->Opt.Check[1]=0;
                Form1->Opt.Check[2]=1;
                Form3->Image1->Picture->LoadFromFile("gfx//Check0.bmp");
                Form3->Image2->Picture->LoadFromFile("gfx//Check0.bmp");
                Form3->Image3->Picture->LoadFromFile("gfx//Check1.bmp");
                Form1->Opt.SaveFileOpt();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm3::FormCreate(TObject *Sender)
{
        Form3->Left = Form1->Opt.x[2];
        Form3->Top = Form1->Opt.y[2];
        if (Form1->Opt.Check[0]==0)
                Form3->Image1->Picture->LoadFromFile("gfx//Check0.bmp");
        else
                Form3->Image1->Picture->LoadFromFile("gfx//Check1.bmp");
        if (Form1->Opt.Check[1]==0)
                Form3->Image2->Picture->LoadFromFile("gfx//Check0.bmp");
        else
                Form3->Image2->Picture->LoadFromFile("gfx//Check1.bmp");
        if (Form1->Opt.Check[2]==0)
                Form3->Image3->Picture->LoadFromFile("gfx//Check0.bmp");
        else
                Form3->Image3->Picture->LoadFromFile("gfx//Check1.bmp");
        Form3->Edit1->Text=Form1->Opt.Watt;
}
//---------------------------------------------------------------------------


void __fastcall TForm3::Edit1Change(TObject *Sender)
{
        Form1->Opt.Watt=Form3->Edit1->Text.ToInt();
        Form1->Opt.SaveFileOpt();       
}
//---------------------------------------------------------------------------

