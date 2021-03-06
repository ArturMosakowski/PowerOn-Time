//---------------------------------------------------------------------------
#include <vcl.h>
#include<Registry.hpp>
#include <tchar.h>
#include <time.h>
#include <string>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <Shlobj.h>
#include <fstream>
#include<conio.h>
#pragma hdrstop

#include "Main.h"
#include "Wid1.h"
#include "Wid2.h"
#include "Wid3.h"
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"

TForm1 *Form1;

typedef struct DayStr
{
        int Day, Month, Year, Seconds;
        vector<int> Left; //przechowuje lewe granice przedzialow danego dnia
        vector<int> Right; //przechowuje prawe granice przedzialow danego dnia
        vector<int> Sum; //przechowuje czas danego przedzialu
} DayStr;


        int tmpUpdate = 0;
        int Y, M, D;
        int Hour, Min, Sec, aHour, aMin, aSec;
        int SessStart, SessEnd, SessDur; //poczatek, koniec i czas trwania aktualnej sesji
        int SessTime; //czas calej sesji
        int PrevSess;  //czas poprzedniej sesji
        int pozP[1]; //pozycje lewej i prawej granicy danego przedzialu przy rysowaniu
        int xM, xR, yM, yR; //wsoolrzedne pozycji [M-myszy, R-roznica pozycji myszy i okna]
        int UpDwn;


typedef struct Options
{
        int x[4];
        int y[4];
        int Check[2];
        int Watt;
        int Reg; //czy dodano do rejestru czy nie

        void LoadFileOpt();
        void SaveFileOpt();
} Options;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//------------------------------------------------------------------------------
void GetDate() //Funckja pobiera aktualna date
{
        //Pobieranie aktualnej daty
        SYSTEMTIME st;
        GetLocalTime(&st);
        Y = st.wYear;
        M = st.wMonth;
        D = st.wDay;
        int DoW = st.wDayOfWeek;

        String Dtmp = D;
        String Mtmp = M;
        String Ytmp = Y;
        String DoWtmp;
        if (DoW == 6) DoWtmp = "Sobota";
        if (DoW == 0) DoWtmp = "Niedziela";
        if (DoW == 1) DoWtmp = "Poniedzia�ek";
        if (DoW == 2) DoWtmp = "Wtorek";
        if (DoW == 3) DoWtmp = "�roda";
        if (DoW == 4) DoWtmp = "Czwartek";
        if (DoW == 5) DoWtmp = "Pi�tek";
        if (D <= 9)
                Form1->Label2->Caption = "0" + Dtmp + ".";
        else
                Form1->Label2->Caption = Dtmp + ".";
        if (M <= 9)
                Form1->Label2->Caption = Form1->Label2->Caption + "0" + Mtmp + ".";
        else
                Form1->Label2->Caption = Form1->Label2->Caption + Mtmp + ".";
        Form1->Label2->Caption = Form1->Label2->Caption + Ytmp + "   " + DoWtmp;
}

//------------------------------------------------------------------------------
void SessionON()  //Funkcja pokazujaca czas aktualnej sesji
{
        //Pobieranie aktualnej godziny
        SYSTEMTIME st;
        GetLocalTime(&st);
        aHour = st.wHour;
        aMin = st.wMinute;
        aSec = st.wSecond;
        //czas calego dnia
        SessTime = ((aHour*3600) + (aMin*60) + aSec) - ((Hour*3600) + (Min*60) + Sec);
        int sHour = SessTime/3600;
        int sMin = SessTime/60 - (sHour*60);
        int sSec = SessTime - (sHour*3600) - (sMin*60);

        Form1->Label1->Caption = "";
        if (sHour <=9)
                Form1->Label1->Caption = Form1->Label1->Caption + "0" + sHour + ":";
        else Form1->Label1->Caption = Form1->Label1->Caption + sHour + ":";
        if (sMin <=9)
                Form1->Label1->Caption = Form1->Label1->Caption + "0" + sMin + ":";
        else Form1->Label1->Caption = Form1->Label1->Caption + sMin + ":";
        if (sSec <= 9)
                Form1->Label1->Caption = Form1->Label1->Caption + "0" + sSec;
        else Form1->Label1->Caption = Form1->Label1->Caption + sSec;
        int tmpw=(sHour*3600 + sMin*60 + sSec)*(Form1->Opt.Watt/3600.0);
        Form1->Label10->Caption="";
        Form1->Label10->Caption=Form1->Label10->Caption + tmpw + " W";
        //ustalanie poczatka, konca i czasu trwania aktualnej sesji (w sekundach)
        SessStart = (Hour * 3600) + (Min * 60) + Sec;
        SessEnd = (aHour * 3600) + (aMin * 60) + aSec;
        SessDur = SessEnd - SessStart;
}
//------------------------------------------------------------------------------
void PowerONDay() //Funckja pokazujaca czas calego dnia
{
        int DayTime = SessTime + PrevSess - 1;
        int hrD = DayTime / 3600;
        int minD = DayTime / 60 - (hrD * 60);
        int secD = (DayTime + 1) - ((DayTime / 60) * 60);
        String tmp = "";
        if (hrD <= 9) tmp = tmp + "0" + hrD + ":";
        else tmp = tmp + hrD + ":";
        if (minD <= 9) tmp = tmp + "0" + minD + ":";
        else tmp = tmp + minD + ":";
        if (secD <= 9) tmp = tmp + "0" + secD;
        else tmp = tmp + secD;
        Form1->Label3->Caption = tmp;
        int tmpw=(hrD*3600 + minD*60 + secD)*(Form1->Opt.Watt/3600.0);
        Form1->Label11->Caption="";
        Form1->Label11->Caption=Form1->Label11->Caption + tmpw + " W";
}

//------------------------------------------------------------------------------
void LoadFile()  //Funkcja wczytujaca dane z pliku Data.cpp
{
        string tmpStr;
        int rows = 0;
        fstream File;
        File.open("Data.cpp");  //otwieranie pliku do odczytu
        while (! File.eof()) //sprawdzanie ile wierszy ma plik
        {
                getline(File, tmpStr);
                rows++;
        }
        File.close(); //zamykanie pliku
        fstream File2;
        File2.open("Data.cpp");  //otwieranie pliku do odczytu
        int main = 0;
        int sub = 0;
        int poz[1];  //pozycje znaku "*" w dacie
        int poz1[1]; //pozycje znaku "*" w danym przedziale
        string tmp;
        for (int i = 0; i < rows; i++)  //wczytywanie danych do struktury DS
        {
                getline(File2, tmpStr);
                if (tmpStr[0] == 'd')
                {
                        if (i > 0) main++;
                        Form1->DS.push_back(); //dodawanie elementu do wektora DS
                        poz[0] = 0; poz[1] = 0; //zerowanie pozycji "*"
                        for (unsigned int k = 1; k <= tmpStr.length(); k++) //ustalanie nowych pozycji dla "*"
                        {
                                if (tmpStr[k] == '*' && poz[0] == 0) poz[0] = k;
                                if (tmpStr[k] == '*' && poz[0] != 0) poz[1] = k;
                        }
                        for (int k = 1; k < poz[0]; k++) //przypisywanie dnia w dacie
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Day = atoi(tmp.c_str());
                        tmp = "";
                        for (int k = poz[0]+1; k < poz[1]; k++) //przypisywanie miesiaca w dacie
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Month = atoi(tmp.c_str());
                        tmp = "";
                        for (unsigned int k = poz[1]+1; k <= tmpStr.length(); k++) //przypisywanie roku w dacie
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Year = atoi(tmp.c_str());
                        tmp = "";
                        sub = 0; //zerowanie poziomu wektorow w strukturze(wektorze) DS
                }
                if (tmpStr[0] == 'o') //przypisywanie ogolnego czasu
                {
                        for (unsigned int k = 1; k <= tmpStr.length(); k++)
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Seconds = atoi(tmp.c_str());
                        tmp = "";;
                }
                if (tmpStr[0] == 'p') //przypisywanie poszczegolnych przedzialow czasu
                {
                        Form1->DS[main].Left.push_back(); //tworzenie nowego elementu wektora Left
                        Form1->DS[main].Right.push_back(); //tworzenie nowego elementu wektora Right
                        Form1->DS[main].Sum.push_back(); //tworzenie nowego elementu wektora Sum
                        poz1[0] = 0; poz1[1] = 0; //zerowanie pozycji znaku "*"
                        for (unsigned int k = 1; k <= tmpStr.length(); k++)
                        {
                                if (tmpStr[k] == '*' && poz1[0] == 0) poz1[0] = k;
                                if (tmpStr[k] == '*' && poz1[0] != 0) poz1[1] = k;
                        }
                        for (int k = 1; k < poz1[0]; k++) //przypisanie lewej granicy przedzialu
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Left[sub] = atoi(tmp.c_str());
                        tmp = "";
                        for (int k = poz1[0]+1; k < poz1[1]; k++) //przypisywanie prawej granicy przedzialu
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Right[sub] = atoi(tmp.c_str());
                        tmp = "";
                        for (unsigned int k = poz1[1]+1; k <= tmpStr.length(); k++) //przypisywanie czasu danego przedzialu
                                tmp = tmp + tmpStr[k];
                        Form1->DS[main].Sum[sub] = atoi(tmp.c_str());
                        tmp = "";
                        sub++; //zwiekszanie o 1 poziomu wielkosci wwektorow w strukturze(wektorze) DS
                }
                if (tmpStr[0] == 'e')
                sub = 0; //zerowanie poziomu wektorow w strukturze(wektorze) DS
        }
        File2.close(); //zamykanie pliku
}

//------------------------------------------------------------------------------
void SaveFile() //Funkcja zapisujaca dane do pliku Data.cpp
{
        fstream File("Data.cpp");
        fopen("Data.cpp","w");
        File.close(); //zamykanie pliku

        fstream File2("Data.cpp");
        int vSize = Form1->DS.size(); //rozmiar wektora DS

        for (int i = 0; i < vSize; i++) //zapisywanie danych ze struktury DS do pliku "Data.cpp"
        {
                File2 << "d" << Form1->DS[i].Day << "*" << Form1->DS[i].Month << "*" << Form1->DS[i].Year << endl;
                File2 << "o" << Form1->DS[i].Seconds << endl;
                int j1 = Form1->DS[i].Left.size(); //ustalanie wielkosci wektora Left w biezaceje strukturze DS
                for (int j = 0; j < j1; j++)
                {
                        File2 << "p" << Form1->DS[i].Left[j] << "*" << Form1->DS[i].Right[j] << "*" << Form1->DS[i].Sum[j] << endl;
                }
                File2 << "e" << endl; //dopisywanie na koncu kazdej sekcji separatora "e"
        }
        File2.close(); //zamykanie pliku
}

//------------------------------------------------------------------------------
void UpdateData() //Funkcja aktualizujaca dane w wektorach
{
        int vSize = Form1->DS.size() - 1; //ustalanie wielkosci wektora
        int sSize;
        if (Form1->DS[vSize].Day != D || Form1->DS[vSize].Month != M || Form1->DS[vSize].Year != Y)
        {
                Form1->DS.push_back();
                Form1->DS[vSize+1].Day = D;
                Form1->DS[vSize+1].Month = M;
                Form1->DS[vSize+1].Year = Y;
                Form1->DS[vSize+1].Seconds = SessTime;

                sSize = Form1->DS[vSize].Left.size() - 1;
                Form1->DS[vSize+1].Left.push_back(0);
                Form1->DS[vSize+1].Right.push_back(0);
                Form1->DS[vSize+1].Sum.push_back(0);
                PrevSess = 0;

                Hour = aHour;
                Min = aMin;
                Sec = aSec;
                tmpUpdate = 1;
                Form1->Image1->Picture->LoadFromFile("gfx//MainBar.bmp");
        }
        if (Form1->DS[vSize].Day == D && Form1->DS[vSize].Month == M && Form1->DS[vSize].Year == Y)
        {
                if (tmpUpdate != 1)
                {
                        Form1->DS[vSize].Left.push_back(0);
                        Form1->DS[vSize].Right.push_back(0);
                        Form1->DS[vSize].Sum.push_back(0);
                        tmpUpdate = 1;
                }
                sSize = Form1->DS[vSize].Left.size() - 1;
                Form1->DS[vSize].Seconds = SessTime + PrevSess;
                Form1->DS[vSize].Left[sSize] = SessStart;
                Form1->DS[vSize].Right[sSize] = SessEnd;
                Form1->DS[vSize].Sum[sSize] = SessDur;
        }
}

//------------------------------------------------------------------------------
void DrawBar() //Funkcja rysuje basek post�pu [ilosc godzin przy kompie]
{
        int vSize = Form1->DS.size() - 1 ;
        int sSize = Form1->DS[vSize].Left.size() - 1;

        for (int i = 0; i <= sSize; i++)
        {
                pozP[0] = Form1->DS[vSize].Left[i] / 360 +2;
                pozP[1] = Form1->DS[vSize].Right[i] / 360 +2;
                Form1->Image1->Canvas->Brush->Color = 0x00BFFF;
                Form1->Image1->Canvas->FillRect(Rect(pozP[0], 2, pozP[1], 28));
        }
        Form1->Image1->Canvas->Pen->Color = clGray;
        Form1->Image1->Canvas->MoveTo(30, 2); Form1->Image1->Canvas->LineTo(30, 28);
        Form1->Image1->Canvas->MoveTo(60, 2); Form1->Image1->Canvas->LineTo(60, 28);
        Form1->Image1->Canvas->MoveTo(90, 2); Form1->Image1->Canvas->LineTo(90, 28);
        Form1->Image1->Canvas->MoveTo(120, 2); Form1->Image1->Canvas->LineTo(120, 28);
        Form1->Image1->Canvas->MoveTo(150, 2); Form1->Image1->Canvas->LineTo(150, 28);
        Form1->Image1->Canvas->MoveTo(180, 2); Form1->Image1->Canvas->LineTo(180, 28);
        Form1->Image1->Canvas->MoveTo(210, 2); Form1->Image1->Canvas->LineTo(210, 28);
}
//---------------------------------------------------------------------------
void TForm1::Options::SaveFileOpt() //Funkcja zapisujaca dane do pliku Opt.cpp
{
        fstream File("Opt.cpp");
        fopen("Opt.cpp","w");
        File.close(); //zamykanie pliku

        fstream File2("Opt.cpp");
        //pozycje poszczegolnych okien
        File2 << Form1->Opt.x[0] << endl;
        File2 << Form1->Opt.y[0] << endl;
        File2 << Form1->Opt.x[1] << endl;
        File2 << Form1->Opt.y[1] << endl;
        File2 << Form1->Opt.x[2] << endl;
        File2 << Form1->Opt.y[2] << endl;
        File2 << Form1->Opt.x[3] << endl;
        File2 << Form1->Opt.y[3] << endl;
        //ustawienia checkbox'ow
        File2 << Form1->Opt.Check[0] << endl;
        File2 << Form1->Opt.Check[1] << endl;
        File2 << Form1->Opt.Check[2] << endl;
        //wartosc Watt
        File2 << Form1->Opt.Watt << endl;
        //reg
        File2 << Form1->Opt.Reg << endl;
        File2.close(); //zamykanie pliku
}
//---------------------------------------------------------------------------
void TForm1::Options::LoadFileOpt()  //Funkcja wczytujaca dane z pliku Opt.cpp
{
        string tmp;
        fstream File3;
        File3.open("Opt.cpp");  //otwieranie pliku do odczytu
        //wczytywanie pozycji poszczegolnych okien
        getline(File3, tmp);
        Form1->Opt.x[0]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.y[0]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.x[1]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.y[1]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.x[2]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.y[2]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.x[3]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.y[3]= atoi(tmp.c_str());
        //wczytywanie pozycji checkbox'ow
        getline(File3, tmp);
        Form1->Opt.Check[0]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.Check[1]= atoi(tmp.c_str());
        getline(File3, tmp);
        Form1->Opt.Check[2]= atoi(tmp.c_str());
        //wczytywanie wartosci Watt
        getline(File3, tmp);
        Form1->Opt.Watt= atoi(tmp.c_str());
        //wczytywanie wartosci Reg
        getline(File3, tmp);
        Form1->Opt.Reg= atoi(tmp.c_str());
        File3.close(); //zamykanie pliku
}
//---------------------------------------------------------------------------
void RegAdd(char * fileAndPath, char * registryName)
{
        if(Form1->Opt.Reg == 0)
        {
                char path[MAX_PATH];
                HRESULT hr = SHGetFolderPath(
                        0,                   // hwndOwner
                        CSIDL_COMMON_STARTUP, // nFolder
                        0,                   // hToken
                        SHGFP_TYPE_CURRENT,  // dwFlags
                        path);               // pszPath
              /*  if (hr == S_OK)
                {
                        Form1->Label1->Caption=path;
                        Form1->Edit1->Text=path;
                }  */
                String s=path;
                s=s+ + "\\POTs.lnk";
                CopyFileA("C:\\POT\\POTs.lnk", s.c_str(), true);

                Form1->Opt.Reg=1;
                Form1->Opt.SaveFileOpt();
        }
}
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        GetDate();
        SessionON();
        PowerONDay();
        UpdateData();
        SaveFile();
        DrawBar();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
        //Pobieranie daty i godziny rozpoczecia pracy aplikacji
        SYSTEMTIME st;
        GetLocalTime(&st);
        Hour = st.wHour;
        Min = st.wMinute;
        Sec = st.wSecond;
        Y = st.wYear;
        M = st.wMonth;
        D = st.wDay;
        LoadFile();
        Form1->Opt.LoadFileOpt();
        Form1->Left = Form1->Opt.x[0];
        Form1->Top = Form1->Opt.y[0];
        int vSize = DS.size(); //ustalanie wielkosci wektora
        PrevSess = DS[vSize-1].Seconds; //pobieranie wartosci z poprzedniej sesji
        UpDwn = 0;
        RegAdd("C:\\POT\\POT.exe", "POTfinal");
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image7MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image7->Picture->LoadFromFile("gfx//StatDwn.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image7MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        Form1->Image7->Picture->LoadFromFile("gfx//StatUp.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image10MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image10->Picture->LoadFromFile("gfx//OptUp.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image10MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image10->Picture->LoadFromFile("gfx//OptDwn.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image11MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image11->Picture->LoadFromFile("gfx//QMarkDwn.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image11MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image11->Picture->LoadFromFile("gfx//QMarkUp.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image12MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image12->Picture->LoadFromFile("gfx//MiniDwn.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image12MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image12->Picture->LoadFromFile("gfx//MiniUp.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image13MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image13->Picture->LoadFromFile("gfx//TrayDwn.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image13MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image13->Picture->LoadFromFile("gfx//TrayUp.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image14MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image14->Picture->LoadFromFile("gfx//PwrDwn.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image14MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form1->Image14->Picture->LoadFromFile("gfx//PwrUp.bmp");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image14Click(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image7Click(TObject *Sender)
{
        Form2->Visible = True;
        Form1->AlphaBlend = True;
        Form1->Enabled = False;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image6MouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if (UpDwn == 1)
        {
                POINT poz;
                GetCursorPos(&poz);
                xM = poz.x; yM = poz.y;
                Form1->Left = xM - xR;
                Form1->Top = yM - yR;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image6MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        UpDwn = 1;
        POINT poz;
        GetCursorPos(&poz);
        xM = poz.x; yM = poz.y;
        xR = xM - Form1->Left;
        yR = yM - Form1->Top;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image6MouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        UpDwn = 0;
        Form1->Opt.x[0] = Form1->Left;
        Form1->Opt.y[0] = Form1->Top;
        Form1->Opt.SaveFileOpt();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image12Click(TObject *Sender)
{
        Application->Minimize();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Image13Click(TObject *Sender)
{
	Form1->TrayIcon1->Visible=True;
	Form1->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrayIcon1Click(TObject *Sender)
{
	Form1->TrayIcon1->Visible=False;
	Form1->Show();
}


void __fastcall TForm1::Image10Click(TObject *Sender)
{
        Form3->Visible = True;
        Form1->AlphaBlend = True;
        Form1->Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Image11Click(TObject *Sender)
{
        Form4->Visible = True;
        Form1->AlphaBlend = True;
        Form1->Enabled = False;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
        if (Form1->Opt.Check[1]==1)
        {
	        Form1->TrayIcon1->Visible=True;
	        Form1->Hide();
        }
        if (Form1->Opt.Check[2]==1)
                Application->Minimize();
        Form1->Timer2->Enabled=False;
}
//---------------------------------------------------------------------------


