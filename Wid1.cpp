//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Wid1.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
        int xM1, xR1, yM1, yR1; //wsoolrzedne pozycji [M-myszy, R-roznica pozycji myszy i okna]
        int UpDwn1;
        int ii; //ComboBox1->ItemIndex
        int pozP1[1];
        int Year1, Month1, Day1;
        int pozP1a[1]; //pozycje lewej i prawej granicy danego przedzialu przy rysowaniu
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
int Przestepny(int rok) //Sprawdza czy rok jest przestepny (1-tak, 0-nie)
{
  if ( ((rok%4)==0) && ((rok%100)!=0) || ((rok%400)==0) ) return 1;
  else return 0;
}
//----------------------------------------------------------------------------
int DayOfWeek(int Day, int Month, int Year) //Funkcja ustala dzien tygodnia danej daty
{
        int D = Day;
        int M = Month;
        int Y = Year;
        int DoW = (D += M<3 ? Y-- : Y-2, 23*M/9+D+4+Y/4-Y/100+Y/40)%7;
        return DoW;
}
//----------------------------------------------------------------------------
void GetDate2() //Funckja pobiera aktualna date
{
        //Pobieranie aktualnej daty
        SYSTEMTIME st;
        GetLocalTime(&st);
        int Y = st.wYear;
        int M = st.wMonth;
        int D = st.wDay;
        int DoW = st.wDayOfWeek;
        Year1 = Y; Month1 = M; Day1 = D;
        String Dtmp = D;
        String Mtmp = M;
        String Ytmp = Y;
        String DoWtmp;
        if (DoW == 6) DoWtmp = "Sobota";
        if (DoW == 0) DoWtmp = "Niedziela";
        if (DoW == 1) DoWtmp = "Poniedzia³ek";
        if (DoW == 2) DoWtmp = "Wtorek";
        if (DoW == 3) DoWtmp = "Œroda";
        if (DoW == 4) DoWtmp = "Czwartek";
        if (DoW == 5) DoWtmp = "Pi¹tek";
        if (D <= 9)
                Form2->Label15->Caption = "0" + Dtmp + ".";
        else
                Form2->Label15->Caption = Dtmp + ".";
        if (M <= 9)
                Form2->Label15->Caption = Form2->Label15->Caption + "0" + Mtmp + ".";
        else
                Form2->Label15->Caption = Form2->Label15->Caption + Mtmp + ".";
        Form2->Label15->Caption = Form2->Label15->Caption + Ytmp;
}
//---------------------------------------------------------------------------
void UpdateSearch() //Funkcja aktualizuj¹ca szukan¹ datê
{
        switch (Month1) //Zmiana wyswietlanego miesiaca
        {
                case 1: Form2->Label9->Caption =  "  Styczeñ  "; break;
                case 2: Form2->Label9->Caption =  "    Luty   "; break;
                case 3: Form2->Label9->Caption =  "   Marzec  "; break;
                case 4: Form2->Label9->Caption =  "  Kwiecieñ "; break;
                case 5: Form2->Label9->Caption =  "    Maj    "; break;
                case 6: Form2->Label9->Caption =  "  Czerwiec "; break;
                case 7: Form2->Label9->Caption =  "   Lipiec  "; break;
                case 8: Form2->Label9->Caption =  "  Sierpieñ "; break;
                case 9: Form2->Label9->Caption =  "  Wrzesieñ "; break;
                case 10: Form2->Label9->Caption = "PaŸdziernik"; break;
                case 11: Form2->Label9->Caption = "  Listopad "; break;
                case 12: Form2->Label9->Caption = "  Grudzieñ "; break;
        }
        Form2->Label8->Caption = Year1; //Zmiana wyswietlanego roku
}
//---------------------------------------------------------------------------
void SetPositions() //Ustawianie kolorow poszczegolnych dni miesiaca
{
        int DayTmp = DayOfWeek(1, Month1, Year1);
        if (DayTmp==4) //Poniedizalek
        {
                Form2->Image1->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image1->Left=24; Form2->Image1->Top=158;
                Form2->Image2->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image2->Left=56; Form2->Image2->Top=158;
                Form2->Image3->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image3->Left=88; Form2->Image3->Top=158;
                Form2->Image4->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image4->Left=120; Form2->Image4->Top=158;
                Form2->Image5->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image5->Left=152; Form2->Image5->Top=158;
                Form2->Image6->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image6->Left=184; Form2->Image6->Top=158;
                Form2->Image7->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image7->Left=216; Form2->Image7->Top=158;
                Form2->L1->Left=31; Form2->L1->Top=165;
                Form2->L2->Left=63; Form2->L2->Top=165;
                Form2->L3->Left=95; Form2->L3->Top=165;
                Form2->L4->Left=127; Form2->L4->Top=165;
                Form2->L5->Left=159; Form2->L5->Top=165;
                Form2->L6->Left=191; Form2->L6->Top=165;
                Form2->L7->Left=223; Form2->L7->Top=165;

                Form2->Image8->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image8->Left=24; Form2->Image8->Top=190;
                Form2->Image9->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image9->Left=56; Form2->Image9->Top=190;
                Form2->Image10->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image10->Left=88; Form2->Image10->Top=190;
                Form2->Image11->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image11->Left=120; Form2->Image11->Top=190;
                Form2->Image12->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image12->Left=152; Form2->Image12->Top=190;
                Form2->Image13->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image13->Left=184; Form2->Image13->Top=190;
                Form2->Image14->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image14->Left=216; Form2->Image14->Top=190;
                Form2->L8->Left=31; Form2->L8->Top=197;
                Form2->L9->Left=63; Form2->L9->Top=197;
                Form2->L10->Left=95; Form2->L10->Top=197;
                Form2->L11->Left=127; Form2->L11->Top=197;
                Form2->L12->Left=159; Form2->L12->Top=197;
                Form2->L13->Left=191; Form2->L13->Top=197;
                Form2->L14->Left=223; Form2->L14->Top=197;

                Form2->Image15->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image15->Left=24; Form2->Image15->Top=222;
                Form2->Image16->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image16->Left=56; Form2->Image16->Top=222;
                Form2->Image17->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image17->Left=88; Form2->Image17->Top=222;
                Form2->Image18->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image18->Left=120; Form2->Image18->Top=222;
                Form2->Image19->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image19->Left=152; Form2->Image19->Top=222;
                Form2->Image20->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image20->Left=184; Form2->Image20->Top=222;
                Form2->Image21->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image21->Left=216; Form2->Image21->Top=222;
                Form2->L15->Left=31; Form2->L15->Top=229;
                Form2->L16->Left=63; Form2->L16->Top=229;
                Form2->L17->Left=95; Form2->L17->Top=229;
                Form2->L18->Left=127; Form2->L18->Top=229;
                Form2->L19->Left=159; Form2->L19->Top=229;
                Form2->L20->Left=191; Form2->L20->Top=229;
                Form2->L21->Left=223; Form2->L21->Top=229;

                Form2->Image22->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image22->Left=24; Form2->Image22->Top=254;
                Form2->Image23->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image23->Left=56; Form2->Image23->Top=254;
                Form2->Image24->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image24->Left=88; Form2->Image24->Top=254;
                Form2->Image25->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image25->Left=120; Form2->Image25->Top=254;
                Form2->Image26->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image26->Left=152; Form2->Image26->Top=254;
                Form2->Image27->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image27->Left=184; Form2->Image27->Top=254;
                Form2->L22->Left=31; Form2->L22->Top=261;
                Form2->L23->Left=63; Form2->L23->Top=261;
                Form2->L24->Left=95; Form2->L24->Top=261;
                Form2->L25->Left=127; Form2->L25->Top=261;
                Form2->L26->Left=159; Form2->L26->Top=261;
                Form2->L27->Left=191; Form2->L27->Top=261;
                Form2->L28->Left=223; Form2->L28->Top=261;

                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image28->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image28->Left=216; Form2->Image28->Top=254;
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=24; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=56; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image31->Left=88; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=True;
                        Form2->L28->Left=223; Form2->L28->Top=261; Form2->L28->Visible=True;
                        Form2->L29->Left=31; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=63; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=95; Form2->L31->Top=293; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image28->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image28->Left=216; Form2->Image28->Top=254;
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=24; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=56; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=88; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L28->Left=223; Form2->L28->Top=261; Form2->L28->Visible=True;
                        Form2->L29->Left=31; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=63; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=95; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image28->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image28->Left=216; Form2->Image28->Top=254;
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=24; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=56; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=88; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L28->Left=223; Form2->L28->Top=261; Form2->L28->Visible=True;
                        Form2->L29->Left=31; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=63; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=95; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                if (Month1==2 && P==1)
                {
                        Form2->Image28->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image28->Left=216; Form2->Image28->Top=254;
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=24; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=56; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=88; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L28->Left=223; Form2->L28->Top=261; Form2->L28->Visible=True;
                        Form2->L29->Left=31; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=63; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=95; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=120; Form2->Image32->Top=286;
                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=152; Form2->Image33->Top=286;
                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=184; Form2->Image34->Top=286;
                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=216; Form2->Image35->Top=286;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=24; Form2->Image36->Top=318;
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=56; Form2->Image37->Top=318;
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=88; Form2->Image38->Top=318;
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=120; Form2->Image39->Top=318;
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=152; Form2->Image40->Top=318;
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=184; Form2->Image41->Top=318;
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=216; Form2->Image42->Top=318;
        }
        if (DayTmp==5) //Wtorek
        {
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=24; Form2->Image42->Top=158;
                Form2->Image1->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image1->Left=56; Form2->Image1->Top=158;
                Form2->Image2->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image2->Left=88; Form2->Image2->Top=158;
                Form2->Image3->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image3->Left=120; Form2->Image3->Top=158;
                Form2->Image4->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image4->Left=152; Form2->Image4->Top=158;
                Form2->Image5->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image5->Left=184; Form2->Image5->Top=158;
                Form2->Image6->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image6->Left=216; Form2->Image6->Top=158;
                Form2->L1->Left=63; Form2->L1->Top=165;
                Form2->L2->Left=95; Form2->L2->Top=165;
                Form2->L3->Left=127; Form2->L3->Top=165;
                Form2->L4->Left=159; Form2->L4->Top=165;
                Form2->L5->Left=191; Form2->L5->Top=165;
                Form2->L6->Left=223; Form2->L6->Top=165;

                Form2->Image7->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image7->Left=24; Form2->Image7->Top=190;
                Form2->Image8->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image8->Left=56; Form2->Image8->Top=190;
                Form2->Image9->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image9->Left=88; Form2->Image9->Top=190;
                Form2->Image10->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image10->Left=120; Form2->Image10->Top=190;
                Form2->Image11->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image11->Left=152; Form2->Image11->Top=190;
                Form2->Image12->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image12->Left=184; Form2->Image12->Top=190;
                Form2->Image13->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image13->Left=216; Form2->Image13->Top=190;
                Form2->L7->Left=31; Form2->L7->Top=197;
                Form2->L8->Left=63; Form2->L8->Top=197;
                Form2->L9->Left=95; Form2->L9->Top=197;
                Form2->L10->Left=127; Form2->L10->Top=197;
                Form2->L11->Left=159; Form2->L11->Top=197;
                Form2->L12->Left=191; Form2->L12->Top=197;
                Form2->L13->Left=223; Form2->L13->Top=197;

                Form2->Image14->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image14->Left=24; Form2->Image14->Top=222;
                Form2->Image15->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image15->Left=56; Form2->Image15->Top=222;
                Form2->Image16->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image16->Left=88; Form2->Image16->Top=222;
                Form2->Image17->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image17->Left=120; Form2->Image17->Top=222;
                Form2->Image18->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image18->Left=152; Form2->Image18->Top=222;
                Form2->Image19->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image19->Left=184; Form2->Image19->Top=222;
                Form2->Image20->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image20->Left=216; Form2->Image20->Top=222;
                Form2->L14->Left=31; Form2->L14->Top=229;
                Form2->L15->Left=63; Form2->L15->Top=229;
                Form2->L16->Left=95; Form2->L16->Top=229;
                Form2->L17->Left=127; Form2->L17->Top=229;
                Form2->L18->Left=159; Form2->L18->Top=229;
                Form2->L19->Left=191; Form2->L19->Top=229;
                Form2->L20->Left=223; Form2->L20->Top=229;

                Form2->Image21->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image21->Left=24; Form2->Image21->Top=254;
                Form2->Image22->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image22->Left=56; Form2->Image22->Top=254;
                Form2->Image23->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image23->Left=88; Form2->Image23->Top=254;
                Form2->Image24->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image24->Left=120; Form2->Image24->Top=254;
                Form2->Image25->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image25->Left=152; Form2->Image25->Top=254;
                Form2->Image26->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image26->Left=184; Form2->Image26->Top=254;
                Form2->Image27->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image27->Left=216; Form2->Image27->Top=254;
                Form2->L21->Left=31; Form2->L21->Top=261;
                Form2->L22->Left=63; Form2->L22->Top=261;
                Form2->L23->Left=95; Form2->L23->Top=261;
                Form2->L24->Left=127; Form2->L24->Top=261;
                Form2->L25->Left=159; Form2->L25->Top=261;
                Form2->L26->Left=191; Form2->L26->Top=261;
                Form2->L27->Left=223; Form2->L27->Top=261;

                Form2->Image28->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image28->Left=24; Form2->Image28->Top=286;
                Form2->L28->Left=31; Form2->L28->Top=293;

                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=56; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=88; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image31->Left=120; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=True;
                        Form2->L29->Left=63; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=95; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=127; Form2->L31->Top=293; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=56; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=88; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=120; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=63; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=95; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=127; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=56; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=88; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=120; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=63; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=95; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=127; Form2->L31->Top=293; Form2->L31->Visible=False;

                }
                if (Month1==2 && P==1)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=56; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=88; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=120; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=63; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=95; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=127; Form2->L31->Top=293; Form2->L31->Visible=False;
                }

                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=152; Form2->Image32->Top=286;
                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=184; Form2->Image33->Top=286;
                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=216; Form2->Image34->Top=286;

                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=24; Form2->Image35->Top=318;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=56; Form2->Image36->Top=318;
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=88; Form2->Image37->Top=318;
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=120; Form2->Image38->Top=318;
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=152; Form2->Image39->Top=318;
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=184; Form2->Image40->Top=318;
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=216; Form2->Image41->Top=318;

        }
        if (DayTmp==6) //Sroda
        {
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=24; Form2->Image41->Top=158;
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=56; Form2->Image42->Top=158;
                Form2->Image1->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image1->Left=88; Form2->Image1->Top=158;
                Form2->Image2->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image2->Left=120; Form2->Image2->Top=158;
                Form2->Image3->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image3->Left=152; Form2->Image3->Top=158;
                Form2->Image4->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image4->Left=184; Form2->Image4->Top=158;
                Form2->Image5->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image5->Left=216; Form2->Image5->Top=158;
                Form2->L1->Left=95; Form2->L1->Top=165;
                Form2->L2->Left=127; Form2->L2->Top=165;
                Form2->L3->Left=159; Form2->L3->Top=165;
                Form2->L4->Left=191; Form2->L4->Top=165;
                Form2->L5->Left=223; Form2->L5->Top=165;

                Form2->Image6->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image6->Left=24; Form2->Image6->Top=190;
                Form2->Image7->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image7->Left=56; Form2->Image7->Top=190;
                Form2->Image8->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image8->Left=88; Form2->Image8->Top=190;
                Form2->Image9->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image9->Left=120; Form2->Image9->Top=190;
                Form2->Image10->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image10->Left=152; Form2->Image10->Top=190;
                Form2->Image11->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image11->Left=184; Form2->Image11->Top=190;
                Form2->Image12->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image12->Left=216; Form2->Image12->Top=190;
                Form2->L6->Left=31; Form2->L6->Top=197;
                Form2->L7->Left=63; Form2->L7->Top=197;
                Form2->L8->Left=95; Form2->L8->Top=197;
                Form2->L9->Left=127; Form2->L9->Top=197;
                Form2->L10->Left=159; Form2->L10->Top=197;
                Form2->L11->Left=191; Form2->L11->Top=197;
                Form2->L12->Left=223; Form2->L12->Top=197;

                Form2->Image13->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image13->Left=24; Form2->Image13->Top=222;
                Form2->Image14->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image14->Left=56; Form2->Image14->Top=222;
                Form2->Image15->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image15->Left=88; Form2->Image15->Top=222;
                Form2->Image16->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image16->Left=120; Form2->Image16->Top=222;
                Form2->Image17->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image17->Left=152; Form2->Image17->Top=222;
                Form2->Image18->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image18->Left=184; Form2->Image18->Top=222;
                Form2->Image19->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image19->Left=216; Form2->Image19->Top=222;
                Form2->L13->Left=31; Form2->L13->Top=229;
                Form2->L14->Left=63; Form2->L14->Top=229;
                Form2->L15->Left=95; Form2->L15->Top=229;
                Form2->L16->Left=127; Form2->L16->Top=229;
                Form2->L17->Left=159; Form2->L17->Top=229;
                Form2->L18->Left=191; Form2->L18->Top=229;
                Form2->L19->Left=223; Form2->L19->Top=229;

                Form2->Image20->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image20->Left=24; Form2->Image20->Top=254;
                Form2->Image21->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image21->Left=56; Form2->Image21->Top=254;
                Form2->Image22->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image22->Left=88; Form2->Image22->Top=254;
                Form2->Image23->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image23->Left=120; Form2->Image23->Top=254;
                Form2->Image24->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image24->Left=152; Form2->Image24->Top=254;
                Form2->Image25->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image25->Left=184; Form2->Image25->Top=254;
                Form2->Image26->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image26->Left=216; Form2->Image26->Top=254;
                Form2->L20->Left=31; Form2->L20->Top=261;
                Form2->L21->Left=63; Form2->L21->Top=261;
                Form2->L22->Left=95; Form2->L22->Top=261;
                Form2->L23->Left=127; Form2->L23->Top=261;
                Form2->L24->Left=159; Form2->L24->Top=261;
                Form2->L25->Left=191; Form2->L25->Top=261;
                Form2->L26->Left=223; Form2->L26->Top=261;

                Form2->Image27->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image27->Left=24; Form2->Image27->Top=286;
                Form2->Image28->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image28->Left=56; Form2->Image28->Top=286;
                Form2->L27->Left=31; Form2->L27->Top=293;
                Form2->L28->Left=63; Form2->L28->Top=293;


                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=88; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=120; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image31->Left=152; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=True;
                        Form2->L29->Left=95; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=127; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=159; Form2->L31->Top=293; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=88; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=120; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=152; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=95; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=127; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=159; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=88; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=120; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=152; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=95; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=127; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=159; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                if (Month1==2 && P==1)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=88; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=120; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=152; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=95; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=127; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=159; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=184; Form2->Image32->Top=286;
                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=216; Form2->Image33->Top=286;

                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=24; Form2->Image34->Top=318;
                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=56; Form2->Image35->Top=318;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=88; Form2->Image36->Top=318;
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=120; Form2->Image37->Top=318;
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=152; Form2->Image38->Top=318;
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=184; Form2->Image39->Top=318;
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=216; Form2->Image40->Top=318;

        }
        if (DayTmp==0) //Czwartek
        {
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=24; Form2->Image40->Top=158;
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=56; Form2->Image41->Top=158;
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=88; Form2->Image42->Top=158;
                Form2->Image1->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image1->Left=120; Form2->Image1->Top=158;
                Form2->Image2->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image2->Left=152; Form2->Image2->Top=158;
                Form2->Image3->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image3->Left=184; Form2->Image3->Top=158;
                Form2->Image4->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image4->Left=216; Form2->Image4->Top=158;
                Form2->L1->Left=127; Form2->L1->Top=165;
                Form2->L2->Left=159; Form2->L2->Top=165;
                Form2->L3->Left=191; Form2->L3->Top=165;
                Form2->L4->Left=223; Form2->L4->Top=165;

                Form2->Image5->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image5->Left=24; Form2->Image5->Top=190;
                Form2->Image6->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image6->Left=56; Form2->Image6->Top=190;
                Form2->Image7->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image7->Left=88; Form2->Image7->Top=190;
                Form2->Image8->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image8->Left=120; Form2->Image8->Top=190;
                Form2->Image9->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image9->Left=152; Form2->Image9->Top=190;
                Form2->Image10->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image10->Left=184; Form2->Image10->Top=190;
                Form2->Image11->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image11->Left=216; Form2->Image11->Top=190;
                Form2->L5->Left=31; Form2->L5->Top=197;
                Form2->L6->Left=63; Form2->L6->Top=197;
                Form2->L7->Left=95; Form2->L7->Top=197;
                Form2->L8->Left=127; Form2->L8->Top=197;
                Form2->L9->Left=159; Form2->L9->Top=197;
                Form2->L10->Left=191; Form2->L10->Top=197;
                Form2->L11->Left=223; Form2->L11->Top=197;

                Form2->Image12->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image12->Left=24; Form2->Image12->Top=222;
                Form2->Image13->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image13->Left=56; Form2->Image13->Top=222;
                Form2->Image14->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image14->Left=88; Form2->Image14->Top=222;
                Form2->Image15->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image15->Left=120; Form2->Image15->Top=222;
                Form2->Image16->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image16->Left=152; Form2->Image16->Top=222;
                Form2->Image17->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image17->Left=184; Form2->Image17->Top=222;
                Form2->Image18->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image18->Left=216; Form2->Image18->Top=222;
                Form2->L12->Left=31; Form2->L12->Top=229;
                Form2->L13->Left=63; Form2->L13->Top=229;
                Form2->L14->Left=95; Form2->L14->Top=229;
                Form2->L15->Left=127; Form2->L15->Top=229;
                Form2->L16->Left=159; Form2->L16->Top=229;
                Form2->L17->Left=191; Form2->L17->Top=229;
                Form2->L18->Left=223; Form2->L18->Top=229;

                Form2->Image19->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image19->Left=24; Form2->Image19->Top=254;
                Form2->Image20->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image20->Left=56; Form2->Image20->Top=254;
                Form2->Image21->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image21->Left=88; Form2->Image21->Top=254;
                Form2->Image22->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image22->Left=120; Form2->Image22->Top=254;
                Form2->Image23->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image23->Left=152; Form2->Image23->Top=254;
                Form2->Image24->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image24->Left=184; Form2->Image24->Top=254;
                Form2->Image25->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image25->Left=216; Form2->Image25->Top=254;
                Form2->L19->Left=31; Form2->L19->Top=261;
                Form2->L20->Left=63; Form2->L20->Top=261;
                Form2->L21->Left=95; Form2->L21->Top=261;
                Form2->L22->Left=127; Form2->L22->Top=261;
                Form2->L23->Left=159; Form2->L23->Top=261;
                Form2->L24->Left=191; Form2->L24->Top=261;
                Form2->L25->Left=223; Form2->L25->Top=261;

                Form2->Image26->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image26->Left=24; Form2->Image26->Top=286;
                Form2->Image27->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image27->Left=56; Form2->Image27->Top=286;
                Form2->Image28->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image28->Left=88; Form2->Image28->Top=286;
                Form2->L26->Left=31; Form2->L26->Top=293;
                Form2->L27->Left=63; Form2->L27->Top=293;
                Form2->L28->Left=95; Form2->L28->Top=293;

                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=120; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=152; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image31->Left=184; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=True;
                        Form2->L29->Left=127; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=159; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=191; Form2->L31->Top=293; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=120; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=152; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=184; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=127; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=159; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=191; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=120; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=152; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=184; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=127; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=159; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=191; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                if (Month1==2 && P==1)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=120; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=152; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=184; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=127; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=159; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=191; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=216; Form2->Image32->Top=286;

                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=24; Form2->Image33->Top=318;
                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=56; Form2->Image34->Top=318;
                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=88; Form2->Image35->Top=318;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=120; Form2->Image36->Top=318;
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=152; Form2->Image37->Top=318;
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=184; Form2->Image38->Top=318;
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=216; Form2->Image39->Top=318;


        }
        if (DayTmp==1) //Piatek
        {
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=24; Form2->Image39->Top=158;
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=56; Form2->Image40->Top=158;
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=88; Form2->Image41->Top=158;
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=120; Form2->Image42->Top=158;
                Form2->Image1->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image1->Left=152; Form2->Image1->Top=158;
                Form2->Image2->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image2->Left=184; Form2->Image2->Top=158;
                Form2->Image3->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image3->Left=216; Form2->Image3->Top=158;
                Form2->L1->Left=159; Form2->L1->Top=165;
                Form2->L2->Left=191; Form2->L2->Top=165;
                Form2->L3->Left=223; Form2->L3->Top=165;

                Form2->Image4->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image4->Left=24; Form2->Image4->Top=190;
                Form2->Image5->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image5->Left=56; Form2->Image5->Top=190;
                Form2->Image6->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image6->Left=88; Form2->Image6->Top=190;
                Form2->Image7->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image7->Left=120; Form2->Image7->Top=190;
                Form2->Image8->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image8->Left=152; Form2->Image8->Top=190;
                Form2->Image9->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image9->Left=184; Form2->Image9->Top=190;
                Form2->Image10->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image10->Left=216; Form2->Image10->Top=190;
                Form2->L4->Left=31; Form2->L4->Top=197;
                Form2->L5->Left=63; Form2->L5->Top=197;
                Form2->L6->Left=95; Form2->L6->Top=197;
                Form2->L7->Left=127; Form2->L7->Top=197;
                Form2->L8->Left=159; Form2->L8->Top=197;
                Form2->L9->Left=191; Form2->L9->Top=197;
                Form2->L10->Left=223; Form2->L10->Top=197;

                Form2->Image11->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image11->Left=24; Form2->Image11->Top=222;
                Form2->Image12->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image12->Left=56; Form2->Image12->Top=222;
                Form2->Image13->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image13->Left=88; Form2->Image13->Top=222;
                Form2->Image14->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image14->Left=120; Form2->Image14->Top=222;
                Form2->Image15->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image15->Left=152; Form2->Image15->Top=222;
                Form2->Image16->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image16->Left=184; Form2->Image16->Top=222;
                Form2->Image17->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image17->Left=216; Form2->Image17->Top=222;
                Form2->L11->Left=31; Form2->L11->Top=229;
                Form2->L12->Left=63; Form2->L12->Top=229;
                Form2->L13->Left=95; Form2->L13->Top=229;
                Form2->L14->Left=127; Form2->L14->Top=229;
                Form2->L15->Left=159; Form2->L15->Top=229;
                Form2->L16->Left=191; Form2->L16->Top=229;
                Form2->L17->Left=223; Form2->L17->Top=229;

                Form2->Image18->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image18->Left=24; Form2->Image18->Top=254;
                Form2->Image19->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image19->Left=56; Form2->Image19->Top=254;
                Form2->Image20->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image20->Left=88; Form2->Image20->Top=254;
                Form2->Image21->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image21->Left=120; Form2->Image21->Top=254;
                Form2->Image22->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image22->Left=152; Form2->Image22->Top=254;
                Form2->Image23->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image23->Left=184; Form2->Image23->Top=254;
                Form2->Image24->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image24->Left=216; Form2->Image24->Top=254;
                Form2->L18->Left=31; Form2->L18->Top=261;
                Form2->L19->Left=63; Form2->L19->Top=261;
                Form2->L20->Left=95; Form2->L20->Top=261;
                Form2->L21->Left=127; Form2->L21->Top=261;
                Form2->L22->Left=159; Form2->L22->Top=261;
                Form2->L23->Left=191; Form2->L23->Top=261;
                Form2->L24->Left=223; Form2->L24->Top=261;

                Form2->Image25->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image25->Left=24; Form2->Image25->Top=286;
                Form2->Image26->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image26->Left=56; Form2->Image26->Top=286;
                Form2->Image27->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image27->Left=88; Form2->Image27->Top=286;
                Form2->Image28->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image28->Left=120; Form2->Image28->Top=286;
                Form2->L25->Left=31; Form2->L25->Top=293;
                Form2->L26->Left=63; Form2->L26->Top=293;
                Form2->L27->Left=95; Form2->L27->Top=293;
                Form2->L28->Left=127; Form2->L28->Top=293;

                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=152; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=184; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image31->Left=216; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=True;
                        Form2->L29->Left=159; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=191; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=223; Form2->L31->Top=293; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=152; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=184; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=216; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=159; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=191; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=223; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=152; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=184; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=216; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=159; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=191; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=223; Form2->L31->Top=293; Form2->L31->Visible=False;
                }
                if (Month1==2 && P==1)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=152; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=184; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image31->Left=216; Form2->Image31->Top=286;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=159; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=191; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=223; Form2->L31->Top=293; Form2->L31->Visible=False;
                }

                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=24; Form2->Image32->Top=318;
                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=56; Form2->Image33->Top=318;
                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=88; Form2->Image34->Top=318;
                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=120; Form2->Image35->Top=318;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=152; Form2->Image36->Top=318;
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=184; Form2->Image37->Top=318;
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=216; Form2->Image38->Top=318;

        }
        if (DayTmp==2) //Sobota
        {
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=24; Form2->Image38->Top=158;
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=56; Form2->Image39->Top=158;
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=88; Form2->Image40->Top=158;
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=120; Form2->Image41->Top=158;
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=152; Form2->Image42->Top=158;
                Form2->Image1->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image1->Left=184; Form2->Image1->Top=158;
                Form2->Image2->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image2->Left=216; Form2->Image2->Top=158;
                Form2->L1->Left=191; Form2->L1->Top=165;
                Form2->L2->Left=223; Form2->L2->Top=165;

                Form2->Image3->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image3->Left=24; Form2->Image3->Top=190;
                Form2->Image4->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image4->Left=56; Form2->Image4->Top=190;
                Form2->Image5->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image5->Left=88; Form2->Image5->Top=190;
                Form2->Image6->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image6->Left=120; Form2->Image6->Top=190;
                Form2->Image7->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image7->Left=152; Form2->Image7->Top=190;
                Form2->Image8->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image8->Left=184; Form2->Image8->Top=190;
                Form2->Image9->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image9->Left=216; Form2->Image9->Top=190;
                Form2->L3->Left=31; Form2->L3->Top=197;
                Form2->L4->Left=63; Form2->L4->Top=197;
                Form2->L5->Left=95; Form2->L5->Top=197;
                Form2->L6->Left=127; Form2->L6->Top=197;
                Form2->L7->Left=159; Form2->L7->Top=197;
                Form2->L8->Left=191; Form2->L8->Top=197;
                Form2->L9->Left=223; Form2->L9->Top=197;

                Form2->Image10->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image10->Left=24; Form2->Image10->Top=222;
                Form2->Image11->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image11->Left=56; Form2->Image11->Top=222;
                Form2->Image12->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image12->Left=88; Form2->Image12->Top=222;
                Form2->Image13->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image13->Left=120; Form2->Image13->Top=222;
                Form2->Image14->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image14->Left=152; Form2->Image14->Top=222;
                Form2->Image15->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image15->Left=184; Form2->Image15->Top=222;
                Form2->Image16->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image16->Left=216; Form2->Image16->Top=222;
                Form2->L10->Left=31; Form2->L10->Top=229;
                Form2->L11->Left=63; Form2->L11->Top=229;
                Form2->L12->Left=95; Form2->L12->Top=229;
                Form2->L13->Left=127; Form2->L13->Top=229;
                Form2->L14->Left=159; Form2->L14->Top=229;
                Form2->L15->Left=191; Form2->L15->Top=229;
                Form2->L16->Left=223; Form2->L16->Top=229;

                Form2->Image17->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image17->Left=24; Form2->Image17->Top=254;
                Form2->Image18->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image18->Left=56; Form2->Image18->Top=254;
                Form2->Image19->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image19->Left=88; Form2->Image19->Top=254;
                Form2->Image20->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image20->Left=120; Form2->Image20->Top=254;
                Form2->Image21->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image21->Left=152; Form2->Image21->Top=254;
                Form2->Image22->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image22->Left=184; Form2->Image22->Top=254;
                Form2->Image23->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image23->Left=216; Form2->Image23->Top=254;
                Form2->L17->Left=31; Form2->L17->Top=261;
                Form2->L18->Left=63; Form2->L18->Top=261;
                Form2->L19->Left=95; Form2->L19->Top=261;
                Form2->L20->Left=127; Form2->L20->Top=261;
                Form2->L21->Left=159; Form2->L21->Top=261;
                Form2->L22->Left=191; Form2->L22->Top=261;
                Form2->L23->Left=223; Form2->L23->Top=261;

                Form2->Image24->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image24->Left=24; Form2->Image24->Top=286;
                Form2->Image25->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image25->Left=56; Form2->Image25->Top=286;
                Form2->Image26->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image26->Left=88; Form2->Image26->Top=286;
                Form2->Image27->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image27->Left=120; Form2->Image27->Top=286;
                Form2->Image28->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image28->Left=152; Form2->Image28->Top=286;
                Form2->L24->Left=31; Form2->L24->Top=293;
                Form2->L25->Left=63; Form2->L25->Top=293;
                Form2->L26->Left=95; Form2->L26->Top=293;
                Form2->L27->Left=127; Form2->L27->Top=293;
                Form2->L28->Left=159; Form2->L28->Top=293;


                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=184; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image30->Left=216; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image31->Left=24; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=True;
                        Form2->L29->Left=191; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=223; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=31; Form2->L31->Top=325; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=184; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image30->Left=216; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=24; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=191; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=223; Form2->L30->Top=293; Form2->L30->Visible=True;
                        Form2->L31->Left=31; Form2->L31->Top=325; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=184; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=216; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=24; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=191; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=223; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=31; Form2->L31->Top=325; Form2->L31->Visible=False;
                }
                if (Month1==2 && P==1)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image29->Left=184; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=216; Form2->Image30->Top=286;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=24; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=191; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=223; Form2->L30->Top=293; Form2->L30->Visible=False;
                        Form2->L31->Left=31; Form2->L31->Top=325; Form2->L31->Visible=False;
                }
                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=56; Form2->Image32->Top=318;
                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=88; Form2->Image33->Top=318;
                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=120; Form2->Image34->Top=318;
                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=152; Form2->Image35->Top=318;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=184; Form2->Image36->Top=318;
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=216; Form2->Image37->Top=318;
        }
        if (DayTmp==3) //Niedziela
        {
                Form2->Image37->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image37->Left=24; Form2->Image37->Top=158;
                Form2->Image38->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image38->Left=56; Form2->Image38->Top=158;
                Form2->Image39->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image39->Left=88; Form2->Image39->Top=158;
                Form2->Image40->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image40->Left=120; Form2->Image40->Top=158;
                Form2->Image41->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image41->Left=152; Form2->Image41->Top=158;
                Form2->Image42->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image42->Left=184; Form2->Image42->Top=158;
                Form2->Image1->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image1->Left=216; Form2->Image1->Top=158;
                Form2->L1->Left=223; Form2->L1->Top=165;

                Form2->Image2->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image2->Left=24; Form2->Image2->Top=190;
                Form2->Image3->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image3->Left=56; Form2->Image3->Top=190;
                Form2->Image4->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image4->Left=88; Form2->Image4->Top=190;
                Form2->Image5->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image5->Left=120; Form2->Image5->Top=190;
                Form2->Image6->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image6->Left=152; Form2->Image6->Top=190;
                Form2->Image7->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image7->Left=184; Form2->Image7->Top=190;
                Form2->Image8->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image8->Left=216; Form2->Image8->Top=190;
                Form2->L2->Left=31; Form2->L2->Top=197;
                Form2->L3->Left=63; Form2->L3->Top=197;
                Form2->L4->Left=95; Form2->L4->Top=197;
                Form2->L5->Left=127; Form2->L5->Top=197;
                Form2->L6->Left=159; Form2->L6->Top=197;
                Form2->L7->Left=191; Form2->L7->Top=197;
                Form2->L8->Left=223; Form2->L8->Top=197;

                Form2->Image9->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image9->Left=24; Form2->Image9->Top=222;
                Form2->Image10->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image10->Left=56; Form2->Image10->Top=222;
                Form2->Image11->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image11->Left=88; Form2->Image11->Top=222;
                Form2->Image12->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image12->Left=120; Form2->Image12->Top=222;
                Form2->Image13->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image13->Left=152; Form2->Image13->Top=222;
                Form2->Image14->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image14->Left=184; Form2->Image14->Top=222;
                Form2->Image15->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image15->Left=216; Form2->Image15->Top=222;
                Form2->L9->Left=31; Form2->L9->Top=229;
                Form2->L10->Left=63; Form2->L10->Top=229;
                Form2->L11->Left=95; Form2->L11->Top=229;
                Form2->L12->Left=127; Form2->L12->Top=229;
                Form2->L13->Left=159; Form2->L13->Top=229;
                Form2->L14->Left=191; Form2->L14->Top=229;
                Form2->L15->Left=223; Form2->L15->Top=229;

                Form2->Image16->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image16->Left=24; Form2->Image16->Top=254;
                Form2->Image17->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image17->Left=56; Form2->Image17->Top=254;
                Form2->Image18->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image18->Left=88; Form2->Image18->Top=254;
                Form2->Image19->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image19->Left=120; Form2->Image19->Top=254;
                Form2->Image20->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image20->Left=152; Form2->Image20->Top=254;
                Form2->Image21->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image21->Left=184; Form2->Image21->Top=254;
                Form2->Image22->Picture->LoadFromFile("gfx//CalRed.bmp");
                Form2->Image22->Left=216; Form2->Image22->Top=254;
                Form2->L16->Left=31; Form2->L16->Top=261;
                Form2->L17->Left=63; Form2->L17->Top=261;
                Form2->L18->Left=95; Form2->L18->Top=261;
                Form2->L19->Left=127; Form2->L19->Top=261;
                Form2->L20->Left=159; Form2->L20->Top=261;
                Form2->L21->Left=191; Form2->L21->Top=261;
                Form2->L22->Left=223; Form2->L22->Top=261;

                Form2->Image23->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image23->Left=24; Form2->Image23->Top=286;
                Form2->Image24->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image24->Left=56; Form2->Image24->Top=286;
                Form2->Image25->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image25->Left=88; Form2->Image25->Top=286;
                Form2->Image26->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image26->Left=120; Form2->Image26->Top=286;
                Form2->Image27->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image27->Left=152; Form2->Image27->Top=286;
                Form2->Image28->Picture->LoadFromFile("gfx//CalYellow.bmp");
                Form2->Image28->Left=184; Form2->Image28->Top=286;
                Form2->L23->Left=31; Form2->L23->Top=293;
                Form2->L24->Left=63; Form2->L24->Top=293;
                Form2->L25->Left=95; Form2->L25->Top=293;
                Form2->L26->Left=127; Form2->L26->Top=293;
                Form2->L27->Left=159; Form2->L27->Top=293;
                Form2->L28->Left=191; Form2->L28->Top=293;

                if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image29->Left=216; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=24; Form2->Image30->Top=318;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image31->Left=56; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=True;
                        Form2->L29->Left=223; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=31; Form2->L30->Top=325; Form2->L30->Visible=True;
                        Form2->L31->Left=63; Form2->L31->Top=325; Form2->L31->Visible=True;
                }
                if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image29->Left=216; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalYellow.bmp");
                        Form2->Image30->Left=24; Form2->Image30->Top=318;
                        Form2->Image30->Enabled=True;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=56; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=223; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=31; Form2->L30->Top=325; Form2->L30->Visible=True;
                        Form2->L31->Left=63; Form2->L31->Top=325; Form2->L31->Visible=False;
                }
                int P = Przestepny(Year1);
                if (Month1==2 && P==0)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image29->Left=216; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=False;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=24; Form2->Image30->Top=318;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=56; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=223; Form2->L29->Top=293; Form2->L29->Visible=False;
                        Form2->L30->Left=31; Form2->L30->Top=325; Form2->L30->Visible=False;
                        Form2->L31->Left=63; Form2->L31->Top=325; Form2->L31->Visible=False;
                }
                if (Month1==2 && P==1)
                {
                        Form2->Image29->Picture->LoadFromFile("gfx//CalRed.bmp");
                        Form2->Image29->Left=216; Form2->Image29->Top=286;
                        Form2->Image29->Enabled=True;
                        Form2->Image30->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image30->Left=24; Form2->Image30->Top=318;
                        Form2->Image30->Enabled=False;
                        Form2->Image31->Picture->LoadFromFile("gfx//CalGrey.bmp");
                        Form2->Image31->Left=56; Form2->Image31->Top=318;
                        Form2->Image31->Enabled=False;
                        Form2->L29->Left=223; Form2->L29->Top=293; Form2->L29->Visible=True;
                        Form2->L30->Left=31; Form2->L30->Top=325; Form2->L30->Visible=False;
                        Form2->L31->Left=63; Form2->L31->Top=325; Form2->L31->Visible=False;
                }
                Form2->Image32->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image32->Left=88; Form2->Image32->Top=318;
                Form2->Image33->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image33->Left=120; Form2->Image33->Top=318;
                Form2->Image34->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image34->Left=152; Form2->Image34->Top=318;
                Form2->Image35->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image35->Left=184; Form2->Image35->Top=318;
                Form2->Image36->Picture->LoadFromFile("gfx//CalGrey.bmp");
                Form2->Image36->Left=216; Form2->Image36->Top=318;
        }
}
//---------------------------------------------------------------------------
void NextYear() //Funkcja zwiêkszaj¹ca rok o 1
{
        Year1 = Year1 + 1;
        UpdateSearch();
}
//---------------------------------------------------------------------------
void PrevYear() //Funkcja zmniejszaj¹ca rok o 1
{
        Year1 = Year1 - 1;
        UpdateSearch();
}
//---------------------------------------------------------------------------
void NextMonth() //Funkcja zwiêkszaj¹ca miesi¹c o 1
{
        if (Month1 < 12)
        {
                Month1 = Month1 + 1;
        }
        UpdateSearch();
}
//---------------------------------------------------------------------------
void PrevMonth() //Funkcja zmniejszaj¹ca rok o 1
{
        if (Month1 > 1)
        {
                Month1 = Month1 - 1;
        }
        UpdateSearch();
}
//----------------------------------------------------------------------------
void ShowDate()
{
        Form2->Label18->Caption="Przedzia³y czasowe w danym dniu";
        Form2->Label15->Caption="";
        if (Day1 <= 9)
                Form2->Label15->Caption=Form2->Label15->Caption + "0" + Day1 + ".";
        else
                Form2->Label15->Caption=Form2->Label15->Caption + Day1 + ".";
        if (Month1 <= 9)
                Form2->Label15->Caption=Form2->Label15->Caption + "0" + Month1 + ".";
        else
                Form2->Label15->Caption=Form2->Label15->Caption + Month1 + ".";
        Form2->Label15->Caption=Form2->Label15->Caption + Year1;
}
//---------------------------------------------------------------------------
void FindAndShowDay() //Funkcja znajduj¹ca i wyswietlajaca statystyki danego dnia
{
        ShowDate();
        //czyszczenie okan danych
        Form2->Image58->Picture->LoadFromFile("gfx//MainBar.bmp");
        Form2->ListBox1->Clear();
        Form2->Label16->Caption = "00:00:00";

        int vSize = Form1->DS.size() - 1;
        int tmp=-1;
        for (int i=0; i<=vSize; i++)
        {
                if (Form1->DS[i].Day==Day1 && Form1->DS[i].Month==Month1 && Form1->DS[i].Year==Year1)
                        tmp=i;
        }
        if (tmp>=0)
        {
                //rysowanie przedzialow na pasku glownym
                int sSize = Form1->DS[tmp].Left.size() - 1;
                for (int i = 0; i <= sSize; i++)
                {
                        pozP1a[0] = Form1->DS[tmp].Left[i] / 360 +2;
                        pozP1a[1] = Form1->DS[tmp].Right[i] / 360 +2;
                        Form2->Image58->Canvas->Brush->Color = 0x00BFFF;
                        Form2->Image58->Canvas->FillRect(Rect(pozP1a[0], 2, pozP1a[1], 28));
                }
                //wypisanie przedzialow i czasu w ListBox1
                String tmpStr, tmpStr2;
                int tmpLH, tmpLM, tmpLS;
                int tmpRH, tmpRM, tmpRS;
                int tmpSH, tmpSM, tmpSS;
                int nr, h, m, s;
                for (int i = 0; i <= sSize; i++)
                {
                        tmpLH = Form1->DS[tmp].Left[i] / 3600;
                        tmpLM = Form1->DS[tmp].Left[i] / 60 - (tmpLH * 60);
                        tmpLS = Form1->DS[tmp].Left[i] - (tmpLH * 3600) - (tmpLM * 60);
                        tmpRH = Form1->DS[tmp].Right[i] / 3600;
                        tmpRM = Form1->DS[tmp].Right[i] / 60 - (tmpRH * 60);
                        tmpRS = Form1->DS[tmp].Right[i] - (tmpRH * 3600) - (tmpRM * 60);
                        tmpSH = Form1->DS[tmp].Sum[i] / 3600;
                        tmpSM = Form1->DS[tmp].Sum[i] / 60 - (tmpSH * 60);
                        tmpSS = Form1->DS[tmp].Sum[i] - (tmpSH * 3600) - (tmpSM * 60);
                        nr = i + 1;
                        tmpStr = "";
                        if (nr <= 9) tmpStr = tmpStr + "0" + nr + ".     ";
                        else tmpStr = tmpStr + nr + ".     ";
                        if (tmpLH <= 9) tmpStr = tmpStr + "0" + tmpLH + ":";
                        else tmpStr = tmpStr + tmpLH + ":";
                        if (tmpLM <= 9) tmpStr = tmpStr + "0" + tmpLM + ":";
                        else tmpStr = tmpStr + tmpLM + ":";
                        if (tmpLS <= 9) tmpStr = tmpStr + "0" + tmpLS + " - ";
                        else tmpStr = tmpStr + tmpLS + " - ";
                        if (tmpRH <= 9) tmpStr = tmpStr + "0" + tmpRH + ":";
                        else tmpStr = tmpStr + tmpRH + ":";
                        if (tmpRM <= 9) tmpStr = tmpStr + "0" + tmpRM + ":";
                        else tmpStr = tmpStr + tmpRM + ":";
                        if (tmpRS <= 9) tmpStr = tmpStr + "0" + tmpRS + "     | d³ugoœæ  ";
                        else tmpStr = tmpStr + tmpRS + "     | d³ugoœæ  ";
                        if (tmpSH <= 9) tmpStr = tmpStr + "0" + tmpSH + ":";
                        else tmpStr = tmpStr + tmpSH + ":";
                        if (tmpSM <= 9) tmpStr = tmpStr + "0" + tmpSM + ":";
                        else tmpStr = tmpStr + tmpSM + ":";
                        if (tmpSS <= 9) tmpStr = tmpStr + "0" + tmpSS;
                        else tmpStr = tmpStr + tmpSS;
                        Form2->ListBox1->Items->Add(tmpStr);
                }
                //Dlugosc calego dnia
                tmpStr2 = "";
                h = Form1->DS[tmp].Seconds / 3600;
                m = Form1->DS[tmp].Seconds / 60 - (h * 60);
                s = Form1->DS[tmp].Seconds - (h * 3600) - (m * 60);
                if (h <= 9) tmpStr2 = tmpStr2 + "0" + h + ":";
                else tmpStr2 = tmpStr2 + h + ":";
                if (m <= 9) tmpStr2 = tmpStr2 + "0" + m + ":";
                else tmpStr2 = tmpStr2 + m + ":";
                if (s <= 9) tmpStr2 = tmpStr2 + "0" + s;
                else tmpStr2 = tmpStr2 + s;
                Form2->Label16->Caption = tmpStr2;
                int tmpw=(h*3600 + m*60 + s)*(Form1->Opt.Watt/3600.0);
                Form2->Label17->Caption="";
                Form2->Label17->Caption=Form2->Label17->Caption+tmpw+" W";
        }
        Form2->Image58->Canvas->Pen->Color = clGray;
        Form2->Image58->Canvas->MoveTo(30, 2); Form2->Image58->Canvas->LineTo(30, 28);
        Form2->Image58->Canvas->MoveTo(60, 2); Form2->Image58->Canvas->LineTo(60, 28);
        Form2->Image58->Canvas->MoveTo(90, 2); Form2->Image58->Canvas->LineTo(90, 28);
        Form2->Image58->Canvas->MoveTo(120, 2); Form2->Image58->Canvas->LineTo(120, 28);
        Form2->Image58->Canvas->MoveTo(150, 2); Form2->Image58->Canvas->LineTo(150, 28);
        Form2->Image58->Canvas->MoveTo(180, 2); Form2->Image58->Canvas->LineTo(180, 28);
        Form2->Image58->Canvas->MoveTo(210, 2); Form2->Image58->Canvas->LineTo(210, 28);
}
//---------------------------------------------------------------------------
void FindAndShowMonth() //Wyswietlanie danych calego miesiaca
{
        Form2->Label18->Caption="Data, czas oraz pobór energii";
        //wypisanie daty
        Form2->Label15->Caption="";
        if (Month1==1 || Month1==3 || Month1==5 || Month1==7 || Month1==8 || Month1==10 || Month1==12)
        {
                Form2->Label15->Caption=Form2->Label15->Caption + "1-31. ";
        }
        if (Month1==4 || Month1==6 || Month1==9 || Month1==11)
        {
                Form2->Label15->Caption=Form2->Label15->Caption + "1-30. ";
        }
        int P = Przestepny(Year1);
        if (Month1==2 && P==0)
        {
                Form2->Label15->Caption=Form2->Label15->Caption + "1-28. ";
        }
        if (Month1==2 && P==1)
        {
                Form2->Label15->Caption=Form2->Label15->Caption + "1-29. ";
        }
        if (Month1 <= 9)
                Form2->Label15->Caption=Form2->Label15->Caption + "0" + Month1 + ".";
        else
                Form2->Label15->Caption=Form2->Label15->Caption + Month1 + ".";
        Form2->Label15->Caption=Form2->Label15->Caption + Year1;

        //czyszczenie okna danych
        Form2->Image58->Picture->LoadFromFile("gfx//MainBar.bmp");
        Form2->ListBox1->Clear();
        Form2->Label16->Caption = "00:00:00";

        //wypisanie czasu calego miesiaca
        int vSize = Form1->DS.size() - 1;
        int tab[30];
        int sum=0;
        for (int i=0; i<=30; i++)
                tab[i]=0;
        int j=0;
        for (int i=0; i<=vSize; i++)
        {
                if (Form1->DS[i].Month==Month1 && Form1->DS[i].Year==Year1)
                {
                        tab[j]=Form1->DS[i].Seconds;
                        j++;
                }
        }
        for (int i=0; i<=30; i++)
        {
                sum=sum+tab[i];
        }
        String tmpStr2 = "";
        int h = sum / 3600;
        int m = sum / 60 - (h * 60);
        int s = sum - (h * 3600) - (m * 60);
        if (h <= 9) tmpStr2 = tmpStr2 + "0" + h + ":";
        else tmpStr2 = tmpStr2 + h + ":";
        if (m <= 9) tmpStr2 = tmpStr2 + "0" + m + ":";
        else tmpStr2 = tmpStr2 + m + ":";
        if (s <= 9) tmpStr2 = tmpStr2 + "0" + s;
        else tmpStr2 = tmpStr2 + s;

        Form2->Label16->Caption=tmpStr2;

        int tmpw=(h*3600 + m*60 + s)*(Form1->Opt.Watt/3600.0);
        Form2->Label17->Caption="";
        Form2->Label17->Caption=Form2->Label17->Caption+tmpw+" W";

        //wypisywanie czasow i poboru mocy w poszczegolnych dniach
        int vSize1 = Form1->DS.size() - 1;
        String tmp1;
        String tmp2;
        for (int i=0; i<=vSize1; i++)
        {
                if (Form1->DS[i].Month==Month1 && Form1->DS[i].Year==Year1)
                {
                        tmp1=" ";
                        if (Form1->DS[i].Day<=9)
                                tmp1=tmp1+"0"+Form1->DS[i].Day;
                        else
                                tmp1=tmp1+Form1->DS[i].Day;
                        if (Form1->DS[i].Month<=9)
                                tmp1=tmp1+".0"+Form1->DS[i].Month;
                        else
                                tmp1=tmp1+"."+Form1->DS[i].Month;
                        tmp1=tmp1+"."+Form1->DS[i].Year;

                        tmp2 = "";
                        int h = Form1->DS[i].Seconds / 3600;
                        int m = Form1->DS[i].Seconds / 60 - (h * 60);
                        int s = Form1->DS[i].Seconds - (h * 3600) - (m * 60);
                        if (h <= 9) tmp2=tmp2 + "0" + h + ":";
                        else tmp2=tmp2 + h + ":";
                        if (m <= 9) tmp2=tmp2 + "0" + m + ":";
                        else tmp2=tmp2 + m + ":";
                        if (s <= 9) tmp2=tmp2 + "0" + s;
                        else tmp2=tmp2 + s;

                        int tmp3=(h*3600 + m*60 + s)*(Form1->Opt.Watt/3600.0);
                        if (tmp3<=10)
                                tmp1=tmp1 + "          "+tmp2+"   |   "+tmp3 +"        W";
                        if (tmp3<=100 && tmp3>10)
                                tmp1=tmp1 + "          "+tmp2+"   |   "+tmp3 +"      W";
                        if (tmp3<=1000 && tmp3>100)
                                tmp1=tmp1 + "          "+tmp2+"   |   "+tmp3 +"    W";
                        if (tmp3<=10000 && tmp3>1000)
                                tmp1=tmp1 + "          "+tmp2+"   |   "+tmp3 +"  W";
                        Form2->ListBox1->Items->Add(tmp1);
                }
        }
}
//---------------------------------------------------------------------------
void DrawFrames()
{
        Form2->Image49->Canvas->Pen->Color=clSilver;
        Form2->Image49->Canvas->Pen->Width=1;
        // Rysowanie dwuch ramek glownych
        Form2->Image49->Canvas->MoveTo(12,54);
        Form2->Image49->Canvas->LineTo(259,54);
        Form2->Image49->Canvas->LineTo(259,403);
        Form2->Image49->Canvas->LineTo(12,403);
        Form2->Image49->Canvas->LineTo(12,54);

        Form2->Image49->Canvas->MoveTo(13,55);
        Form2->Image49->Canvas->LineTo(258,55);
        Form2->Image49->Canvas->LineTo(258,402);
        Form2->Image49->Canvas->LineTo(13,402);
        Form2->Image49->Canvas->LineTo(13,55);

        Form2->Image49->Canvas->MoveTo(264,54);
        Form2->Image49->Canvas->LineTo(554,54);
        Form2->Image49->Canvas->LineTo(554,403);
        Form2->Image49->Canvas->LineTo(264,403);
        Form2->Image49->Canvas->LineTo(264,54);

        Form2->Image49->Canvas->MoveTo(265,55);
        Form2->Image49->Canvas->LineTo(553,55);
        Form2->Image49->Canvas->LineTo(553,402);
        Form2->Image49->Canvas->LineTo(265,402);
        Form2->Image49->Canvas->LineTo(265,55);
}
//---------------------------------------------------------------------------
void MarkDay(int x, int y)  //zaznaczenie danego dnia w kalendarzu
{
        Form2->Image49->Canvas->Pen->Color=clWhite;
        Form2->Image49->Canvas->Pen->Width=1;
        Form2->Image49->Canvas->MoveTo(x-1,y-1);
        Form2->Image49->Canvas->LineTo(x+30,y-1);
        Form2->Image49->Canvas->LineTo(x+30,y+30);
        Form2->Image49->Canvas->LineTo(x-1,y+30);
        Form2->Image49->Canvas->LineTo(x-1,y-1);

        Form2->Image49->Canvas->MoveTo(x-2,y-2);
        Form2->Image49->Canvas->LineTo(x+31,y-2);
        Form2->Image49->Canvas->LineTo(x+31,y+31);
        Form2->Image49->Canvas->LineTo(x-2,y+31);
        Form2->Image49->Canvas->LineTo(x-2,y-2);
        // lewy rog gorny
        Form2->Image49->Canvas->MoveTo(x,y); Form2->Image49->Canvas->LineTo(x+2,y);
        Form2->Image49->Canvas->MoveTo(x,y); Form2->Image49->Canvas->LineTo(x,y+2);
        // lewy dolny rog
        Form2->Image49->Canvas->MoveTo(x,y+27); Form2->Image49->Canvas->LineTo(x,y+29);
        Form2->Image49->Canvas->MoveTo(x,y+29); Form2->Image49->Canvas->LineTo(x+2,y+29);
        //prawy gorny rog
        Form2->Image49->Canvas->MoveTo(x+27,y); Form2->Image49->Canvas->LineTo(x+29,y);
        Form2->Image49->Canvas->MoveTo(x+29,y); Form2->Image49->Canvas->LineTo(x+29,y+2);
        //prawy dolny rog
        Form2->Image49->Canvas->MoveTo(x+27,y+29); Form2->Image49->Canvas->LineTo(x+30,y+29);
        Form2->Image49->Canvas->MoveTo(x+29,y+27); Form2->Image49->Canvas->LineTo(x+29,y+29);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Image43MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image43->Picture->LoadFromFile("gfx//MinusDwn.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image43MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image43->Picture->LoadFromFile("gfx//MinusUp.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image45MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image45->Picture->LoadFromFile("gfx//MinusDwn.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image45MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image45->Picture->LoadFromFile("gfx//MinusUp.bmp");        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image44MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image44->Picture->LoadFromFile("gfx//PlusDwn.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image44MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image44->Picture->LoadFromFile("gfx//PlusUp.bmp");        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image46MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image46->Picture->LoadFromFile("gfx//PlusDwn.bmp");        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image46MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image46->Picture->LoadFromFile("gfx//PlusUp.bmp");        
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image51MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image51->Picture->LoadFromFile("gfx//CloseDwn.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image51MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image51->Picture->LoadFromFile("gfx//CloseUp.bmp");        
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Image50MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        UpDwn1 = 0;
        Form1->Opt.x[1] = Form2->Left;
        Form1->Opt.y[1] = Form2->Top;
        Form1->Opt.SaveFileOpt();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image50MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        UpDwn1 = 1;
        POINT poz;
        GetCursorPos(&poz);
        xM1 = poz.x; yM1 = poz.y;
        xR1 = xM1 - Form2->Left;
        yR1 = yM1 - Form2->Top;
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image50MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        if (UpDwn1 == 1)
        {
                POINT poz;
                GetCursorPos(&poz);
                xM1 = poz.x; yM1 = poz.y;
                Form2->Left = xM1 - xR1;
                Form2->Top = yM1 - yR1;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
        UpDwn1 = 0;
        GetDate2();
        UpdateSearch();
        SetPositions();
        FindAndShowDay();
        DrawFrames();
        Form2->Left = Form1->Opt.x[1];
        Form2->Top = Form1->Opt.y[1];
        if (Day1==1) MarkDay(Form2->Image1->Left,Form2->Image1->Top);
        if (Day1==2) MarkDay(Form2->Image2->Left,Form2->Image2->Top);
        if (Day1==3) MarkDay(Form2->Image3->Left,Form2->Image3->Top);
        if (Day1==4) MarkDay(Form2->Image4->Left,Form2->Image4->Top);
        if (Day1==5) MarkDay(Form2->Image5->Left,Form2->Image5->Top);
        if (Day1==6) MarkDay(Form2->Image6->Left,Form2->Image6->Top);
        if (Day1==7) MarkDay(Form2->Image7->Left,Form2->Image7->Top);
        if (Day1==8) MarkDay(Form2->Image8->Left,Form2->Image8->Top);
        if (Day1==9) MarkDay(Form2->Image9->Left,Form2->Image9->Top);
        if (Day1==10) MarkDay(Form2->Image10->Left,Form2->Image10->Top);
        if (Day1==11) MarkDay(Form2->Image11->Left,Form2->Image11->Top);
        if (Day1==12) MarkDay(Form2->Image12->Left,Form2->Image12->Top);
        if (Day1==13) MarkDay(Form2->Image13->Left,Form2->Image13->Top);
        if (Day1==14) MarkDay(Form2->Image14->Left,Form2->Image14->Top);
        if (Day1==15) MarkDay(Form2->Image15->Left,Form2->Image15->Top);
        if (Day1==16) MarkDay(Form2->Image16->Left,Form2->Image16->Top);
        if (Day1==17) MarkDay(Form2->Image17->Left,Form2->Image17->Top);
        if (Day1==18) MarkDay(Form2->Image18->Left,Form2->Image18->Top);
        if (Day1==19) MarkDay(Form2->Image19->Left,Form2->Image19->Top);
        if (Day1==20) MarkDay(Form2->Image20->Left,Form2->Image20->Top);
        if (Day1==21) MarkDay(Form2->Image21->Left,Form2->Image21->Top);
        if (Day1==22) MarkDay(Form2->Image22->Left,Form2->Image22->Top);
        if (Day1==23) MarkDay(Form2->Image23->Left,Form2->Image23->Top);
        if (Day1==24) MarkDay(Form2->Image24->Left,Form2->Image24->Top);
        if (Day1==25) MarkDay(Form2->Image25->Left,Form2->Image25->Top);
        if (Day1==26) MarkDay(Form2->Image26->Left,Form2->Image26->Top);
        if (Day1==27) MarkDay(Form2->Image27->Left,Form2->Image27->Top);
        if (Day1==28) MarkDay(Form2->Image28->Left,Form2->Image28->Top);
        if (Day1==29) MarkDay(Form2->Image29->Left,Form2->Image29->Top);
        if (Day1==30) MarkDay(Form2->Image30->Left,Form2->Image30->Top);
        if (Day1==31) MarkDay(Form2->Image31->Left,Form2->Image31->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image51Click(TObject *Sender)
{
        Form2->Visible = False;
        Form1->AlphaBlend = False;
        Form1->Enabled = True;
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Image44Click(TObject *Sender)
{
        NextYear();
        SetPositions();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image43Click(TObject *Sender)
{
        PrevYear();
        SetPositions();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image46Click(TObject *Sender)
{
        NextMonth();
        SetPositions();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image45Click(TObject *Sender)
{
        PrevMonth();
        SetPositions();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image1Click(TObject *Sender)
{
        Day1 = 1;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image1->Left,Form2->Image1->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image2Click(TObject *Sender)
{
        Day1 = 2;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image2->Left,Form2->Image2->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image52MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image52->Picture->LoadFromFile("gfx//MonthDwn.bmp");
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image52MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        Form2->Image52->Picture->LoadFromFile("gfx//MonthUp.bmp");          
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Image3Click(TObject *Sender)
{
        Day1 = 3;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image3->Left,Form2->Image3->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image4Click(TObject *Sender)
{
        Day1 = 4;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image4->Left,Form2->Image4->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image5Click(TObject *Sender)
{
        Day1 = 5;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image5->Left,Form2->Image5->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image6Click(TObject *Sender)
{
        Day1 = 6;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image6->Left,Form2->Image6->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image7Click(TObject *Sender)
{
        Day1 = 7;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image7->Left,Form2->Image7->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image8Click(TObject *Sender)
{
        Day1 = 8;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image8->Left,Form2->Image8->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image9Click(TObject *Sender)
{
        Day1 = 9;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image9->Left,Form2->Image9->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image10Click(TObject *Sender)
{
        Day1 = 10;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image10->Left,Form2->Image10->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image11Click(TObject *Sender)
{
        Day1 = 11;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image11->Left,Form2->Image11->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image12Click(TObject *Sender)
{
        Day1 = 12;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image12->Left,Form2->Image12->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image13Click(TObject *Sender)
{
        Day1 = 13;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image13->Left,Form2->Image13->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image14Click(TObject *Sender)
{
        Day1 = 14;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image14->Left,Form2->Image14->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image15Click(TObject *Sender)
{
        Day1 = 15;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image15->Left,Form2->Image15->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image16Click(TObject *Sender)
{
        Day1 = 16;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image16->Left,Form2->Image16->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image17Click(TObject *Sender)
{
        Day1 = 17;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image17->Left,Form2->Image17->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image18Click(TObject *Sender)
{
        Day1 = 18;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image18->Left,Form2->Image18->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image19Click(TObject *Sender)
{
        Day1 = 19;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image19->Left,Form2->Image19->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image20Click(TObject *Sender)
{
        Day1 = 20;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image20->Left,Form2->Image20->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image21Click(TObject *Sender)
{
        Day1 = 21;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image21->Left,Form2->Image21->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image22Click(TObject *Sender)
{
        Day1 = 22;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image22->Left,Form2->Image22->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image23Click(TObject *Sender)
{
        Day1 = 23;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image23->Left,Form2->Image23->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image24Click(TObject *Sender)
{
        Day1 = 24;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image24->Left,Form2->Image24->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image25Click(TObject *Sender)
{
        Day1 = 25;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image25->Left,Form2->Image25->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image26Click(TObject *Sender)
{
        Day1 = 26;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image26->Left,Form2->Image26->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image27Click(TObject *Sender)
{
        Day1 = 27;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image27->Left,Form2->Image27->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image28Click(TObject *Sender)
{
        Day1 = 28;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image28->Left,Form2->Image28->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image29Click(TObject *Sender)
{
        Day1 = 29;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image29->Left,Form2->Image29->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image30Click(TObject *Sender)
{
        Day1 = 30;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image30->Left,Form2->Image30->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image31Click(TObject *Sender)
{
        Day1 = 31;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image31->Left,Form2->Image31->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L1Click(TObject *Sender)
{
        Day1 = 1;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image1->Left,Form2->Image1->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L2Click(TObject *Sender)
{
        Day1 = 2;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image2->Left,Form2->Image2->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L3Click(TObject *Sender)
{
        Day1 = 3;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image3->Left,Form2->Image3->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L4Click(TObject *Sender)
{
        Day1 = 4;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image4->Left,Form2->Image4->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L5Click(TObject *Sender)
{
        Day1 = 5;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image5->Left,Form2->Image5->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L6Click(TObject *Sender)
{
        Day1 = 6;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image6->Left,Form2->Image6->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L7Click(TObject *Sender)
{
        Day1 = 7;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image7->Left,Form2->Image7->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L8Click(TObject *Sender)
{
        Day1 = 8;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image8->Left,Form2->Image8->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L9Click(TObject *Sender)
{
        Day1 = 9;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image9->Left,Form2->Image9->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L10Click(TObject *Sender)
{
        Day1 = 10;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image10->Left,Form2->Image10->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L11Click(TObject *Sender)
{
        Day1 = 11;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image11->Left,Form2->Image11->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L12Click(TObject *Sender)
{
        Day1 = 12;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image12->Left,Form2->Image12->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L13Click(TObject *Sender)
{
        Day1 = 13;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image13->Left,Form2->Image13->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L14Click(TObject *Sender)
{
        Day1 = 14;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image14->Left,Form2->Image14->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L15Click(TObject *Sender)
{
        Day1 = 15;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image15->Left,Form2->Image15->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L16Click(TObject *Sender)
{
        Day1 = 16;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image16->Left,Form2->Image16->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L17Click(TObject *Sender)
{
        Day1 = 17;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image17->Left,Form2->Image17->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L18Click(TObject *Sender)
{
        Day1 = 18;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image18->Left,Form2->Image18->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L19Click(TObject *Sender)
{
        Day1 = 19;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image19->Left,Form2->Image19->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L20Click(TObject *Sender)
{
        Day1 = 20;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image20->Left,Form2->Image20->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L21Click(TObject *Sender)
{
        Day1 = 21;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image21->Left,Form2->Image21->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L22Click(TObject *Sender)
{
        Day1 = 22;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image22->Left,Form2->Image22->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L23Click(TObject *Sender)
{
        Day1 = 23;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image23->Left,Form2->Image23->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L24Click(TObject *Sender)
{
        Day1 = 24;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image24->Left,Form2->Image24->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L25Click(TObject *Sender)
{
        Day1 = 25;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image25->Left,Form2->Image25->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L26Click(TObject *Sender)
{
        Day1 = 26;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image26->Left,Form2->Image26->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L27Click(TObject *Sender)
{
        Day1 = 27;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image27->Left,Form2->Image27->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L28Click(TObject *Sender)
{
        Day1 = 28;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image28->Left,Form2->Image28->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L29Click(TObject *Sender)
{
        Day1 = 29;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image29->Left,Form2->Image29->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L30Click(TObject *Sender)
{
        Day1 = 30;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image30->Left,Form2->Image30->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::L31Click(TObject *Sender)
{
        Day1 = 31;
        UpdateSearch();
        FindAndShowDay();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
        MarkDay(Form2->Image30->Left,Form2->Image30->Top);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Image52Click(TObject *Sender)
{
        FindAndShowMonth();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Label12Click(TObject *Sender)
{
        FindAndShowMonth();
        Form2->Image49->Picture->LoadFromFile("gfx//MainBgrA.bmp");
        DrawFrames();
}
//---------------------------------------------------------------------------







