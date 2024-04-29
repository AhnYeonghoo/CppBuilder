//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmMain *frmMain;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormCreate(TObject *Sender)
{
	CreateWindowEx(0, PROGRESS_CLASS, NULL,
					WS_CHILD | WS_VISIBLE | PBS_VERTICAL,
					20, 20, 18, 170,
					Handle, NULL, HInstance, NULL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::Timer1Timer(TObject *Sender)
{
	TDateTime CurTime = TDateTime::CurrentTime();
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
