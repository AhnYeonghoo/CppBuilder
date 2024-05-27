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
void __fastcall TForm3::btnSubtractionClick(TObject *Sender)
{
	int Operand1 = 0;
	int Operand2 = 0;
	Operation = 2;

	if ( Level == 1 )
	{
		Operand1 = Random(10);
		Operand2 = Random(10);
	}
	else if (Level == 2)
	{
		Operand1 = Random(30);
		Operand2 = Random(30);
	}
	else if (Level == 3)
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
	lblOperation->Caption = L"-";
	lblOperand2->Caption = IntToStr(Operand2);
	edtResult->Text = L"0";
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnMultiplicationClick(TObject *Sender)
{
	int Operand1 = 0;
	int Operand2 = 0;
	Operation = 3;

	if (Level == 1)
	{
		Operand1 = Random(5);
		Operand2 = Random(5);
	}
	else if (Level == 2)
	{
		Operand1 = Random(15);
		Operand2 = Random(15);
	}
	else if (Level == 3)
	{
		Operand1 = Random(25);
		Operand2 = Random(25);
	}
	else
	{
		Operand1 = Random(40);
		Operand2 = Random(40);
	}

	lblOperand1->Caption = IntToStr(Operand1);
	lblOperation->Caption = L"*";
	lblOperand1->Caption = IntToStr(Operand2);
	edtResult->Text = L"0";

}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnDivisionClick(TObject *Sender)
{
	int Operand1 = 0;
	int Operand2 = 0;
	int Factor = 1;
	Operation = 4;

	if (Level == 1)
	{
		Factor = Random(3);
		Operand2 = Random(5);
	}
	else if (Level == 2)
	{
		Factor = Random(4);
		Operand2 = Random(10);
	}
	else if (Level == 3)
	{
		Factor = Random(6);
		Operand2 = Random(10);
	}
	else
	{
		Factor = Random(10);
		Operand2 = Random(20);
	}

	Operand1 = Factor * Operand2;
	if (Operand2 == 0)
	{
		Operand2 == 1;
	}

	lblOperand1->Caption = IntToStr(Operand1);
	lblOperation->Caption = L"/";
	lblOperand2->Caption = IntToStr(Operand2);
    edtResult->Text = L"0";
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnLevel1Click(TObject *Sender)
{
	Level = 1;

	if (Operation == 1)
	{
		btnAdditionClick(Sender);
	}
	else if (Operation == 2)
	{
		btnSubtractionClick(Sender);
	}
	else if (Operation == 3)
	{
		btnMultiplicationClick(Sender);
	}
	else
	{
		btnDivisionClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnLevel2Click(TObject *Sender)
{
	Level = 2;
	if (Operation == 1)
	{
		btnAdditionClick(Sender);
	}
	else if (Operation == 2)
	{
		btnSubtractionClick(Sender);
	}
	else if (Operation == 3)
	{
		btnMultiplicationClick(Sender);
	}
	else
	{
		btnDivisionClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnLevel3Click(TObject *Sender)
{
	Level = 3;
	if (Operation == 1)
	{
		btnAdditionClick(Sender);
	}
	else if (Operation == 2)
	{
		btnSubtractionClick(Sender);
	}
	else if (Operation == 3)
	{
		btnMultiplicationClick(Sender);
	}
	else
	{
		btnDivisionClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnLevel4Click(TObject *Sender)
{
    Level = 4;
	if (Operation == 1)
	{
		btnAdditionClick(Sender);
	}
	else if (Operation == 2)
	{
		btnSubtractionClick(Sender);
	}
	else if (Operation == 3)
	{
		btnMultiplicationClick(Sender);
	}
	else
	{
		btnDivisionClick(Sender);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
    btnAdditionClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnCheckResultClick(TObject *Sender)
{
	int Operand1 = StrToInt(lblOperand1->Caption);
	int Operand2 = StrToInt(lblOperand2->Caption);
	int UserResult = StrToInt(edtResult->Text);
	bool RightAnswer = False;

	if ( (btnAddition->Down == True) && (UserResult == (Operand1 + Operand2)))
	{
		RightAnswer = True;
	}
	else if ((btnSubtraction->Down == True) && (UserResult == (Operand1 - Operand2)))
	{
		RightAnswer = True;
	}
	else if ((btnMultiplication->Down == True) && (UserResult == (Operand1 * Operand2)))
	{
		RightAnswer = True;
	}
	else if ((btnDivision->Down == True) && (UserResult == (Operand1 / Operand2)))
	{
		RightAnswer = True;
	}

	if (RightAnswer == True)
	{
		MessageBoxW(Handle, L"WOW - Good Result", L"Elementary Algebra", 0);
	}
	else
	{
		MessageBoxW(Handle,
			   L"PSST - Wrong Answer\n"
			   L"We hope you will get it right next time",
			   L"Elementary Algebra", 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm3::btnCloseClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

