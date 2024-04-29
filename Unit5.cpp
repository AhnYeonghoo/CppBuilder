//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmBoolean *frmBoolean;
//---------------------------------------------------------------------------
__fastcall TfrmBoolean::TfrmBoolean(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TfrmBoolean::sbtOperand1Click(TObject *Sender)
{
	if (sbtOperand1->Down == true)
	{
		sbtOperand1->Caption = L"True";
	}
	else
	{
		sbtOperand1->Caption = L"False";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBoolean::sbtOperand2Click(TObject *Sender)
{
	if (sbtOperand2->Down == true)
	{
		sbtOperand2->Caption = L"True";
	}
	else
	{
		sbtOperand2->Caption = L"False";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBoolean::sbtResultClick(TObject *Sender)
{
	if (sbtResult->Down == true)
	{
		sbtResult->Caption = L"True";
	}
	else
	{
		sbtResult->Caption = L"False";
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBoolean::btnNewOperationClick(TObject *Sender)
{
	UnicodeString strBooleanValues[] = {"True", "False"};
	UnicodeString strOperations[] = {"A ^ B", "A V B"};

	sbtOperand1->Caption = strBooleanValues[Random(2)];
	sbtOperand2->Caption = strBooleanValues[Random(2)];

	if (sbtOperand1->Caption == L"True")
	{
		sbtOperand1->Down = true;
	}
	else
	{
		sbtOperand1->Down = false;
	}

	if (sbtOperand2->Caption == L"True")
	{
		sbtOperand2->Down = true;
	}
	else
	{
		sbtOperand2->Down = false;
	}

	sttOperation->Caption = strOperations[Random(2)];
}
//---------------------------------------------------------------------------
void __fastcall TfrmBoolean::btnCheckClick(TObject *Sender)
{
	// Logical Conjuction
	if (sttOperation->Caption == "A ^ B")
	{
		if (sbtOperand1->Down == true)
		{
			if (sbtOperand2->Down == true)
			{
				if (sbtResult->Down == true)
				{
					ShowMessage(L"Bravo - Good Answer");
                }
			}
			else if (sbtOperand2->Down == false)
			{
				if (sbtResult->Down == false)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == true)
				{
					ShowMessage(L"Wrong - Get it right next time!");
				}
			}
		}
		else if (sbtOperand1->Down == false)
		{
			if (sbtOperand2->Down == true)
			{
				if (sbtResult->Down == false)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == true)
				{
					ShowMessage(L"Wrong - Get it right next time!");
				}
			}
			else if (sbtOperand2->Down == false)
			{
				if (sbtResult->Down == false)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == true)
				{
					ShowMessage(L"Wrong - Get it right next time!");
				}
			}
		}
	}

	else if (sttOperation->Caption == "A V B")
	{
		if (sbtOperand1->Down == true)
		{
			if (sbtOperand2->Down == true)
			{
				if (sbtResult->Down == true)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == false)
				{
					ShowMessage(L"Wrong - Get it right next time!");
				}
			}
			else if (sbtOperand2->Down == false)
			{
				if (sbtResult->Down == true)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == false)
				{
					ShowMessage(L"Wrong - Get it right next time!");
				}
			}
		}
		else if (sbtOperand1->Down == false)
		{
			if (sbtOperand2->Down == true)
			{
				if (sbtResult->Down == true)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == false)
				{
					ShowMessage(L"Wrong -  Get it right next time!");
				}
			}
			else if (sbtOperand2->Down == false)
			{
				if (sbtResult->Down == false)
				{
					ShowMessage(L"Bravo - Good Answer");
				}
				else if (sbtResult->Down == true)
				{
					ShowMessage(L"Wrong - Get it right next time!");
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TfrmBoolean::btnCloseClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
