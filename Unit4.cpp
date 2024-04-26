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
void __fastcall TForm4::FormCreate(TObject *Sender)
{
	TGroupBox *gbxHolder = new TGroupBox(this);
	gbxHolder->Parent = this;

	gbxHolder->Top = 20;
	gbxHolder->Left = 20;
	gbxHolder->Width = 250;
	gbxHolder->Height = 100;

	gbxHolder->Caption = L"MemberShip";
}
//---------------------------------------------------------------------------
