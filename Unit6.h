//---------------------------------------------------------------------------

#ifndef Unit6H
#define Unit6H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TfrmRepairOrders : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TEdit *edtCustomerName;
	TLabel *Label2;
	TEdit *edtAddress;
	TLabel *Label3;
	TEdit *edtCity;
	TLabel *Label4;
	TEdit *edtState;
	TLabel *Label5;
	TEdit *edtZIPCode;
	TLabel *Label6;
	TEdit *edtMakeModel;
	TLabel *Label7;
	TEdit *edtYear;
	TLabel *Label8;
	TMemo *mmoProblemDescription;
	TGroupBox *GroupBox2;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *edtTotalParts;
	TEdit *edtTotalLabor;
	TEdit *edtTaxRate;
	TEdit *edtTaxAmount;
	TEdit *edtTotalOrder;
	TGroupBox *GroupBox3;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *edtPartName1;
	TEdit *edtPartName2;
	TEdit *edtPartName3;
	TEdit *edtPartName4;
	TEdit *edtPartName5;
	TEdit *edtUnitPrice1;
	TEdit *edtUnitPrice2;
	TEdit *edtUnitPrice3;
	TEdit *edtUnitPrice4;
	TEdit *edtUnitPrice5;
	TEdit *edtQuantity1;
	TEdit *edtQuantity2;
	TEdit *edtQuantity3;
	TEdit *edtQuantity4;
	TEdit *edtQuantity5;
	TEdit *edtSubTotal1;
	TEdit *edtSubTotal2;
	TEdit *edtSubTotal3;
	TEdit *edtSubTotal4;
	TEdit *edtSubTotal5;
	TGroupBox *GroupBox4;
	TLabel *Label19;
	TEdit *edtJobDescription2;
	TEdit *edtJobDescription3;
	TEdit *edtJobDescription4;
	TEdit *edtJobDescription5;
	TEdit *edtJobDescription1;
	TLabel *Label20;
	TEdit *edtJobCost1;
	TEdit *edtJobCost2;
	TEdit *edtJobCost3;
	TEdit *edtJobCost4;
	TEdit *edtJobCost5;
	TGroupBox *GroupBox5;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmRepairOrders(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmRepairOrders *frmRepairOrders;
//---------------------------------------------------------------------------
#endif
