//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm5 : public TForm
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
	TEdit *edtMakeModel;
	TLabel *Label6;
	TEdit *edtYear;
	TMemo *mmoProblemDescription;
	TGroupBox *GroupBox2;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TEdit *edtTotalParts;
	TEdit *edtTaxRate;
	TLabel *Label12;
	TEdit *edtTotalLabor;
	TEdit *edtTotalAmount;
	TEdit *edtTotalOrder;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TLabel *Label13;
	TEdit *edtPartName1;
	TEdit *edtPartName2;
	TEdit *edtPartName3;
	TEdit *edtPartName4;
	TEdit *edtPartName5;
	TLabel *Label14;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *edtUnitPrice1;
	TEdit *edtUnitPrice2;
	TEdit *edtUnitPrice3;
	TEdit *edtUnitPrice4;
	TEdit *edtUnitPrice5;
	TEdit *edtQty1;
	TEdit *edtQty2;
	TEdit *edtQty3;
	TEdit *edtQty4;
	TEdit *edtQty5;
	TEdit *edtSubTotal1;
	TEdit *edtSubTotal3;
	TEdit *edtSubTotal4;
	TEdit *edtSubTotal5;
	TEdit *edtSubTotal2;
	TLabel *Label17;
	TEdit *edtJobDescription1;
	TEdit *edtJobDescription2;
	TEdit *edtJobDescription3;
	TEdit *edtJobDescription4;
	TEdit *edtJobDescription5;
	TLabel *Label18;
	TEdit *edtJobCost1;
	TEdit *edtJobCost2;
	TEdit *edtJobCost3;
	TEdit *edtJobCost4;
	TEdit *edtJobCost5;
	TGroupBox *GroupBox5;
	TMemo *mmoRecommendations;
	TLabel *Label19;
	TEdit *edtFileOpen;
	TButton *btnOpen;
	TLabel *Label20;
	TEdit *edtFileSave;
	TButton *edtSave;
	TButton *btnReset;
	TButton *btnClose;
	void __fastcall edtCustomerNameExit(TObject *Sender);
	void __fastcall edtTaxRateExit(TObject *Sender);
	void __fastcall btnResetClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall edtSaveClick(TObject *Sender);
	void __fastcall btnOpenClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm5(TComponent* Owner);
    void __fastcall Calculate();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm5 *Form5;
//---------------------------------------------------------------------------
#endif
