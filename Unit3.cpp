//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
	Level = 1;
    Operation = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm3::btnAdditionClick(TObject *Sender)
{
	int Operand1 = 0;
	int Operand2 = 0;
	Operation = 1;

	if ( Level == 1 )
	{
		Operand1 = Random(10);
		Operand2 = Random(10);
	}
	else if ( Level == 2 )
	{
		Operand1 = Random(30);
		Operand2 = Random(30);
	}
	else if ( Level == 3 )
	{
		Operand1 = Random(60);
		Operand2 = Random(60);
	}
	else
	{
		Operand1 = Random(80);
		Operand2 = Random(80);
	}

	lblOperand1->Caption = IntToStr(Operand1);
	lblOperation->Caption = L"+";
	lblOperand2->Caption = IntToStr(Operand2);
	edtResult->Text = L"0";

}
//---------------------------------------------------------------------------
