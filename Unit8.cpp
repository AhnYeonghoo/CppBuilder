//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "Unit8.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm8 *Form8;
//---------------------------------------------------------------------------
__fastcall TForm8::TForm8(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm8::FormCreate(TObject *Sender)
{
	hWndIPAddress = CreateWindowEx(0,
	WC_IPADDRESS,
	NULL,
	WS_CHILD | WS_VISIBLE | WS_TABSTOP,
	90, 14, 120, 20,
	Handle,
	NULL,
	HInstance,
	NULL);   C
}
//---------------------------------------------------------------------------
