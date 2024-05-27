//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm4::Timer1Timer(TObject *Sender)
{
	TDateTime  CurTime = TDateTime::CurrentTime();
	unsigned short Hours, Minutes, Seconds, Milliseconds;

	CurTime.DecodeTime(&Hours, &Minutes, &Seconds, &Milliseconds);

	pgrHours->Position = Hours;
	pgrMinutes->Position = Minutes;
	pgrSeconds->Position = Seconds;

	lblHours->Caption = UnicodeString(Hours);
	lblMinutes->Caption = UnicodeString(Minutes);
	lblSeconds->Caption = UnicodeString(Seconds);
}
//---------------------------------------------------------------------------
