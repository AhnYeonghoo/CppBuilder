//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TBevel *Bevel1;
	TLabel *Label1;
	TEdit *edtEmployeeName;
	TLabel *Label2;
	TEdit *edtHourlySalary;
	TBevel *Bevel2;
	TLabel *Monday;
	TLabel *Tuesday;
	TLabel *Wednesday;
	TLabel *Thursday;
	TLabel *Friday;
	TLabel *Saturday;
	TLabel *Sunday;
	TLabel *Label3;
	TLabel *Label4;
	TEdit *edtWeek1Monday;
	TEdit *edtWeek2Monday;
	TEdit *edtWeek1Tuesday;
	TEdit *edtWeek2Tuesday;
	TEdit *edtWeek2Wednesday;
	TEdit *edtWeek1Wednesday;
	TEdit *edtWeek2Thursday;
	TEdit *edtWeek1Thursday;
	TEdit *edtWeek2Friday;
	TEdit *edtWeek1Friday;
	TEdit *edtWeek2Saturday;
	TEdit *edtWeek1Saturday;
	TEdit *Edit13;
	TEdit *edtWeek1Sunday;
	TBevel *Bevel3;
	TButton *btnCalculate;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *edtRegularTime;
	TEdit *edtRegularPay;
	TEdit *edtOvertime;
	TEdit *edtOvertimePay;
	TLabel *Label9;
	TEdit *edtNetPay;
	TStaticText *StaticText1;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *edtTotaltime;
	TEdit *edtTotalpay;
	TButton *btnClose;
	TCheckBox *chkApplyOvertimeRules;
	void __fastcall edtEmployeeNameChange(TObject *Sender);
	void __fastcall btnCalculateClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
