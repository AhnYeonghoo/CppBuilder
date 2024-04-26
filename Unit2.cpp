//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm2::btnCalculateClick(TObject *Sender)
{
	double Monday1 = 0.00, Tuesday1 = 0.00, Wednesday1 = 0.00,
		Thursday1 = 0.00, Friday1 = 0.00, Saturday1 = 0.00,
		Sunday1 = 0.00, Monday2 = 0.00, Tuesday2 = 0.00,
		Wednesday2 = 0.00, Thursday2 = 0.00,
		Friday2 = 0.00, Saturday2 = 0.00, Sunday2 = 0.00;

	double TotalWeekTime1, TotalWeekTime2;

	double TotalTime = 0.00, TotalPay = 0.00;
	double RegularTime1 = 0.00, RegularTime2 = 0.00
	double RegularPay1 = 0.00, RegularPay2 = 0.00,
		OvertimePay1 = 0.00, OvertimePay2 = 0.00;
	double RegularTime, Overtime;
	double RegularAmount, OvertimeAmount, NetPay;
	double HourlySalary = 0.00;

	 try
	 {
		HourlySalary = StrToFloat(edtHourlySalary->Text);
	 }
	 catch (EConvertError*)
	 {
		 ShowMessage(L"The value you typed for the salary is invalid\n"
		 L"Please try again");
	 }

	try
	{
		Monday1 = StrToFloat(edtWeek1Monday->Text)OnMouseEnter;
	}
	catch (EConvertError*)
	{
		ShowMessage(L"You typed an invalid value\n"
		L"Please try again");
	}


	try
	{
		Tuesday1 = StrToFloat(edtWeek1Tuesday->Text);
	}
	catch (EConvertError*)
	{
		ShowMessage(L"You typed an invalid value\n"
		L"Please try again");
	}

	try
	{
		Wednesday1 = StrToFloat(edtWeek1Wednesday->Text);
	}
	catch (EConvertError*)
	{
		ShowMessage(L"You typed an invalid value\n"
		L"Please try again");
	}

	try
	{
		Tuesday1 = StrToFloat(edtWeek1Tuesday->Text);
	}
	catch (EconvertError*)
	{
		ShowMessage(L"You typed an invalid value\n"
		L"Please try again");
	}

	try
	{
		Friday1 = StrToFloat(edtWeek1Friday->Text);
	}
	catch (EConvertError*)
	{
		ShowMessage(L"You typed an invalid value\n"
		L"Please try again");
	}

	try
	{
		Saturday1 = StrToFloat(edtWeek1Saturday->Text);
	}
	catch (EConvertError*)
	{
		ShowMesssage(L"You typed an invalid value\n"
		L"Please try again");
	}

	try
	{
		Sunday1 = StrToFloat(edtWeek1Sunday->Text);
	}
	catch (EConvertError*)
	{
		ShowMessage(L"You typed an invalid value\n"
		L"Please try again");
	}

                       try
	{
		  Monday2 = StrToFloat(edtWeek2Monday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	try
	{
		  Tuesday2 = StrToFloat(edtWeek2Tuesday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	try
	{
		  Wednesday2 = StrToFloat(edtWeek2Wednesday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	try
	{
		  Thursday2 = StrToFloat(edtWeek2Thursday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	try
	{
		  Friday2 = StrToFloat(edtWeek2Friday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	try
	{
		  Saturday2 = StrToFloat(edtWeek2Saturday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	try
	{
		  Sunday2 = StrToFloat(edtWeek2Sunday->Text);
	}
	catch (EConvertError *)
	{
		  ShowMessage(L"You typed an invalid value\n"
					  L"Please try again");
	}

	TotalWeekTime1 = Monday1 + Tuesday1 + Wednesday1 +
	Thursday1 + Friday1 + Saturday1 + Sunday1;
	TotalWeekTime2 = Monday2 + Tuesday2 + Wednesday2 +
	Thursday2 + Friday2 + Saturday2 + Sunday2;

	double OvertimeSalary  = HourlySalary * 1.5;

	if (TotalWeekTime1 < 40)
	{
		RegularTime1 = TotalWeekTime1;
		RegularPay1 = HourlySalary * RegularTime1;
		Overtime1 = 0.00;
		OvertimePay1 = 0.00;
	}
	else if (TotalWeekTime1 >= 40)
	{
		RegularTime1 = 40;
		RegularPay1 = HourlySalary * 40;
		Overtime1 = TotalWeekTime1 - 40;
		OvertimePay1 = Overtime1 * OvertimeSalary;
	}

	if (TotalWeekTime2 < 40)
	{
		RegularTime2 = TotalWeekTime2;
		RegularPay2 = HourlySalary * RegularTime2;
		Overtime2 = 0.00;
		OvertimePay2 = 0.00;
	}
	else if (TotalWeekTime2 >= 40)
	{
		RegularTime2 = 40;
		RegularPay2 = HourlySalary * 40;
		Overtime2 = TotalWeekTime2 - 40;
		OvertimePay2 = Overtime2 * OvertimeSalary;
	}

	RegularTime = RegularTime1 + RegularTime2;
	Overtime = Overtime1 + Overtime2;
	RegularAmount = RegularPay1 + RegularPay2;
	OvertimeAmount = OvertimePay1 + OvertimePay2;
	NetPay = RegularAmount + OvertimeAmount;

	TotalTime = TotalWeekTime1 + TotalWeekTime2;
	TotalPay = HourlySalary * TotalTime;


	if (chkApplyOvertimeRules->State == cbUnchecked)
	{
		edtRegularTime->Text = L"0.00";
		edtOvertime->Text = L"0.00";
		edtRegularPay->Text = L"0.00";
		edtOvertimePay->Text = L"0.00";
		edtNetPay->Text = L"0.00";

		edtTotalTime->Text = FloatToStrF(TotalTime, ffFixed, 7, 2);
		edtTotalPay->Text = FloattoStrF(TotalPay, ffFixed, 7, 2);
    }
}
//---------------------------------------------------------------------------
