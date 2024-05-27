//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm5 *Form5;
//---------------------------------------------------------------------------
__fastcall TForm5::TForm5(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm5::edtCustomerNameExit(TObject *Sender)
{
	edtFileSave->Text = edtCustomerName->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm5::Calculate()
{
	double Part1UnitPrice = 0.00,
		   Part2UnitPrice = 0.00,
		   Part3UnitPrice = 0.00,
		   Part4UnitPrice = 0.00,
		   Part5UnitPrice = 0.00;

	double Part1SubTotal, Part2SubTotal, Part3SubTotal, Part4SubTotal,
			Part5SubTotal, TotalParts;

	int Part1Quantity = 0,
		Part2Quantity = 0,
		Part3Quantity = 0,
		Part4Quantity = 0,
		Part5Quantity = 0;

	double Job1Price = 0.00,
		   Job2Price = 0.00,
		   Job3Price = 0.00,
		   Job4Price = 0.00,
		   Job5Price = 0.00;

	double TotalLabor;
	double TaxRate = 0.00;
	double TaxAmount, TotalOrder;

	if (edtPartName1->Text == L"")
	{
		edtUnitPrice1->Text = L"0.00";
		edtQty1->Text = L"0";
		edtSubTotal1->Text = L"0.00";
		Part1UnitPrice = 0.00;
	}
	else
	{
		try
		{
			Part1UnitPrice = edtUnitPrice1->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Unit Price");
			edtUnitPrice1->Text = L"0.00";
		}

		try
		{
			Part1Quantity = edtQty1->Text.ToInt();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Quantity");
			edtQty1->Text = L"0";
        }
	}

	if (edtPartName2->Text == L"")
	{
		edtUnitPrice2->Text = L"0.00";
		edtQty2->Text = L"0";
		edtSubTotal2->Text = L"0.00";
		Part2UnitPrice = 0.00;
	}
	else
	{
		try
		{
			Part2UnitPrice = edtUnitPrice2->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Unit Price");
			edtUnitPrice2->Text = L"0.00";
		}

		try
		{
			Part2Quantity =  edtQty2->Text.ToInt();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Quantity");
            edtQty2->Text = L"0";
		}
	}

	if (edtPartName3->Text == L"")
	{
		edtUnitPrice3->Text = L"0.00";
		edtQty3->Text = L"0";
		edtSubTotal3->Text = L"0.00";
		Part3UnitPrice = 0.00;
	}
	else
	{
		try
		{
			Part3UnitPrice = edtUnitPrice3->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Unit Price");
			edtUnitPrice3->Text = L"0.00";
		}

		try
		{
			Part3Quantity = edtQty3->Text.ToInt();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Quantity");
			edtQty3->Text = L"0";
        }
    }

	if (edtPartName4->Text == L"")
	{
		edtUnitPrice4->Text = L"0.00";
		edtQty4->Text = L"0";
		edtSubTotal4->Text = L"0.00";
		Part4UnitPrice = 0.00;
	}
	else
	{
		try
		{
			Part4UnitPrice = edtUnitPrice4->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Unit Price");
			edtUnitPrice4->Text = L"0.00";
		}

		try
		{
			Part4Quantity = edtQty4->Text.ToInt();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Quantity");
			edtQty4->Text = L"0";
		}
	}

	if (edtPartName5->Text == L"")
	{
		edtUnitPrice5->Text = L"0.00";
		edtQty5->Text = L"0";
		edtSubTotal5->Text = L"0.00";
		Part5UnitPrice = 0.00;
	}
	else
	{
		try
		{
			Part5UnitPrice = edtUnitPrice5->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Unit Price");
			edtUnitPrice5->Text = L"0.00";
		}

		try
		{
			Part5Quantity = edtQty5->Text.ToInt();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Unit Price");
			edtQty5->Text = L"0";
		}
	}

	if (edtJobDescription1->Text == L"")
	{
		edtJobCost1->Text = L"0.00";
		Job1Price = 0.00;
	}
	else
	{
		try
		{
			Job1Price = edtJobCost1->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Job Price");
			edtJobCost1->Text = L"0.00";
		}
	}


	if (edtJobDescription2->Text == L"")
	{
		edtJobCost2->Text = L"0.00";
		Job2Price = 0.00;
	}
	else
	{
		try
		{
			Job2Price = edtJobCost2->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Job Price");
			edtJobCost2->Text = L"0.00";
		}
	}


	if (edtJobDescription3->Text == L"")
	{
		edtJobCost3->Text = L"0.00";
		Job3Price = 0.00;
	}
	else
	{
		try
		{
			Job3Price = edtJobCost3->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Job Price");
			edtJobCost3->Text = L"0.00";
		}
	}

	if (edtJobDescription4->Text == L"")
	{
		edtJobCost4->Text = L"0.00";
		Job4Price = 0.00;
	}
	else
	{
		try
		{
			Job4Price = edtJobCost4->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Job Price");
			edtJobCost4->Text = L"0.00";
		}
	}


	if (edtJobDescription5->Text == L"")
	{
		edtJobCost5->Text = L"0.00";
		Job5Price = 0.00;
	}
	else
	{
		try
		{
			Job5Price = edtJobCost5->Text.ToDouble();
		}
		catch (EConvertError *)
		{
			ShowMessage(L"Invalid Job Price");
			edtJobCost5->Text = L"0.00";
		}
	}

	Part1SubTotal = Part1UnitPrice * Part1Quantity;
	Part2SubTotal = Part2UnitPrice * Part2Quantity;
	Part3SubTotal = Part3UnitPrice * Part3Quantity;
	Part4SubTotal = Part4UnitPrice * Part4Quantity;
	Part5SubTotal = Part5UnitPrice * Part5Quantity;

	edtSubTotal1->Text = FloatToStrF(Part1SubTotal, ffFixed, 8, 2);
	edtSubTotal2->Text = FloatToStrF(Part2SubTotal, ffFixed, 8, 2);
	edtSubTotal3->Text = FloatToStrF(Part3SubTotal, ffFixed, 8, 2);
	edtSubTotal4->Text = FloatToStrF(Part4SubTotal, ffFixed, 8, 2);
	edtSubTotal5->Text = FloatToStrF(Part5SubTotal, ffFixed, 8, 2);

	TotalParts = Part1SubTotal + Part2SubTotal + Part3SubTotal + Part4SubTotal
				+ Part5SubTotal;

	TotalLabor = Job1Price + Job2Price + Job3Price + Job4Price + Job5Price;

	try
	{
		TaxRate = edtTaxRate->Text.ToDouble();
	}
	catch (EConvertError *)
	{
		ShowMessage(L"Invalid Tax Rate");
		edtTaxRate->Text = L"5.75";
	}

	double TotalPartsAndLabor = TotalParts + TotalLabor;
	TaxAmount = TotalPartsAndLabor * TaxRate / 100;
	TotalOrder = TotalPartsAndLabor + TaxAmount;

	edtTotalParts->Text = FloatToStrF(TotalParts, ffFixed, 8, 2);
	edtTotalLabor->Text = FloatToStrF(TotalLabor, ffFixed, 8, 2);
	edtTotalAmount->Text = FloatToStrF(TaxAmount, ffFixed, 8, 2);
    edtTotalOrder->Text = FloatToStrF(TotalOrder, ffFixed, 8, 2);

}

void __fastcall TForm5::edtTaxRateExit(TObject *Sender)
{
	Calculate();
}
//---------------------------------------------------------------------------

void __fastcall TForm5::btnResetClick(TObject *Sender)
{
	edtCustomerName->Text = L"";
	edtAddress->Text = L"";
	edtCity->Text = L"";
	edtState->Text = L"";
	edtZIPCode->Text = L"";
	edtMakeModel->Text = L"";
	edtYear->Text = L"";
	mmoProblemDescription->Lines->Clear();

	edtTotalParts->Text = L"0.00";
	edtTotalLabor->Text = L"0.00";
	edtTaxRate->Text = L"5.75";
	edtTotalAmount->Text = L"0.00";
	edtTotalOrder->Text = L"0.00";

	edtPartName1->Text = L"";
	edtUnitPrice1->Text = L"0.00";
	edtQty1->Text = L"0";
	edtSubTotal1->Text = L"0.00";

	edtPartName2->Text = L"";
	edtUnitPrice2->Text = L"0.00";
	edtQty2->Text = L"0";
	edtSubTotal2->Text = L"0.00";

	edtPartName3->Text = L"";
	edtUnitPrice3->Text = L"0.00";
	edtQty3->Text = L"0";
	edtSubTotal3->Text = L"0.00";

	edtPartName4->Text = L"";
	edtUnitPrice4->Text = L"0.00";
	edtQty4->Text = L"0";
	edtSubTotal4->Text = L"0.00";

	edtPartName5->Text = L"";
	edtUnitPrice5->Text = L"0.00";
	edtQty5->Text = L"0";
	edtSubTotal5->Text = L"0.00";

	edtJobDescription1->Text = L"";
	edtJobCost1->Text = L"0.00";

	edtJobDescription2->Text = L"";
	edtJobCost2->Text = L"0.00";

	edtJobDescription3->Text = L"";
	edtJobCost3->Text = L"0.00";

	edtJobDescription4->Text = L"";
	edtJobCost4->Text = L"0.00";

	edtJobDescription5->Text = L"";
	edtJobCost5->Text = L"0.00";

	mmoRecommendations->Lines->Clear();
	edtFileOpen->Text = L"";
    edtFileSave->Text = L"";
}
//---------------------------------------------------------------------------

void __fastcall TForm5::FormCreate(TObject *Sender)
{
    btnResetClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm5::edtSaveClick(TObject *Sender)
{
	if (edtFileSave->Text == L"")
	{
		ShowMessage(L"You must enter the name of the file to save");
		return;
	}
	else
	{
		TFileStream *fstRepairOrder;

		try
		{
			fstRepairOrder = new TFileStream(edtFileSave->Text + L".cpar", fmCreate);

			fstRepairOrder->WriteComponent(edtCustomerName);
			fstRepairOrder->WriteComponent(edtAddress);
			fstRepairOrder->WriteComponent(edtCity);
			fstRepairOrder->WriteComponent(edtState);
			fstRepairOrder->WriteComponent(edtZIPCode);
			fstRepairOrder->WriteComponent(edtMakeModel);
			fstRepairOrder->WriteComponent(edtYear);
			fstRepairOrder->WriteComponent(edtmmoProblemDescription);
			fstRepairOrder->WriteComponent(edtTotalParts);
			fstRepairOrder->WriteComponent(edtTotalLabor);
			fstRepairOrder->WriteComponent(edtTaxRate);
			fstRepairOrder->WriteComponent(edtTotalAmount);
			fstRepairOrder->WriteComponent(edtTotalOrder);

			fstRepairOrder->WriteComponent(edtPartName1);
			fstRepairOrder->WriteComponent(edtUnitPrice1);
			fstRepairOrder->WriteComponent(edtQty1);
			fstRepairOrder->WriteComponent(edtSubTotal1);

			fstRepairOrder->WriteComponent(edtPartName2);
			fstRepairOrder->WriteComponent(edtUnitPrice2);
			fstRepairOrder->WriteComponent(edtQty2);
			fstRepairOrder->WriteComponent(edtSubTotal2);

			fstRepairOrder->WriteComponent(edtPartName3);
			fstRepairOrder->WriteComponent(edtUnitPrice3);
			fstRepairOrder->WriteComponent(edtQty3);
			fstRepairOrder->WriteComponent(edtSubTotal3);

			fstRepairOrder->WriteComponent(edtPartName4);
			fstRepairOrder->WriteComponent(edtUnitPrice4);
			fstRepairOrder->WriteComponent(edtQty4);
			fstRepairOrder->WriteComponent(edtSubTotal4);

			fstRepairOrder->WriteComponent(edtPartName5);
			fstRepairOrder->WriteComponent(edtUnitPrice5);
			fstRepairOrder->WriteComponent(edtQty5);
			fstRepairOrder->WriteComponent(edtSubTotal5);

			fstRepairOrder->WriteComponent(edtJobDescription1);
			fstRepairOrder->WriteComponent(edtJobCost1);
			fstRepairOrder->WriteComponent(edtJobDescription2);
			fstRepairOrder->WriteComponent(edtJobCost2);
			fstRepairOrder->WriteComponent(edtJobDescription3);
			fstRepairOrder->WriteComponent(edtJobCost3);
			fstRepairOrder->WriteComponent(edtJobDescription4);
			fstRepairOrder->WriteComponent(edtJobCost4);
			fstRepairOrder->WriteComponent(edtJobDescription5);
			fstRepairOrder->WriteComponent(edtJobCost5);

			fstRepairOrder->WriteComponent(mmoRecommendations);

			ShowMessage(L"The repair order has been saved");
			btnResetClick(Sender);
		}
		__finally
		{
            delete fstRepairOrder;
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm5::btnOpenClick(TObject *Sender)
{
	if (edtFileOpen->Text == L"")
	{
		ShowMessage(L"You must enter the name of the file to open");
		return;
	}
	else
	{
		TFileStream *fstRepairOrder = NULL;

		try
		{
			fstRepairOrder = new TFileStream(edtFileOpen->Text + L".cpar",
											fmOpenRead | fmShareExclusive);

			fstRepairOrder->ReadComponent(edtCustomerName);
			fstRepairOrder->ReadComponent(edtAddress);
			fstRepairOrder->ReadComponent(edtCity);
			fstRepairOrder->ReadComponent(edtState);
			fstRepairOrder->ReadComponent(edtZIPCode);
			fstRepairOrder->ReadComponent(edtMakeModel);
			fstRepairOrder->ReadComponent(edtYear);
			fstRepairOrder->ReadComponent(mmoProblemDescription);
			fstRepairOrder->ReadComponent(edtTotalParts);
			fstRepairOrder->ReadComponent(edtTotalLabor);
			fstRepairOrder->ReadComponent(edtTaxRate);
			fstRepairOrder->ReadComponent(edtTotalAmount);
			fstRepairOrder->ReadComponent(edtTotalOrder);

			fstRepairOrder->ReadComponent(edtPartName1);
			fstRepairOrder->ReadComponent(edtUnitPrice1);
			fstRepairOrder->ReadComponent(edtQty1);
			fstRepairOrder->ReadComponent(edtSubTotal1);

			fstRepairOrder->ReadComponent(edtPartName2);
			fstRepairOrder->ReadComponent(edtUnitPrice2);
			fstRepairOrder->ReadComponent(edtQty2);
			fstRepairOrder->ReadComponent(edtSubTotal2);

			fstRepairOrder->ReadComponent(edtPartName3);
			fstRepairOrder->ReadComponent(edtUnitPrice3);
			fstRepairOrder->ReadComponent(edtQty3);
			fstRepairOrder->ReadComponent(edtSubTotal3);

			fstRepairOrder->ReadComponent(edtPartName4);
			fstRepairOrder->ReadComponent(edtUnitPrice4);
			fstRepairOrder->ReadComponent(edtQty4);
			fstRepairOrder->ReadComponent(edtSubTotal4);

			fstRepairOrder->ReadComponent(edtPartName5);
			fstRepairOrder->ReadComponent(edtUnitPrice5);
			fstRepairOrder->ReadComponent(edtQty5);
			fstRepairOrder->ReadComponent(edtSubTotal5);

			fstRepairOrder->ReadComponent(edtJobDescription1);
			fstRepairOrder->ReadComponent(edtJobCost1);
			fstRepairOrder->ReadComponent(edtJobDescription2);
			fstRepairOrder->ReadComponent(edtJobCost2);
			fstRepairOrder->ReadComponent(edtJobDescription3);
			fstRepairOrder->ReadComponent(edtJobCost3);
			fstRepairOrder->ReadComponent(edtJobDescription4);
			fstRepairOrder->ReadComponent(edtJobCost4);
			fstRepairOrder->ReadComponent(edtJobDescription5);
			fstRepairOrder->ReadComponent(edtJobCost5);

			fstRepairOrder->ReadComponent(mmoRecommendations);
		}
		__finally
		{
			delete fstRepairOrder;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm5::btnCloseClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

