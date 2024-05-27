//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TPanel *pnlLevel;
	TPanel *pnlOperation;
	TSpeedButton *btnLevel1;
	TSpeedButton *btnLevel2;
	TSpeedButton *btnLevel3;
	TSpeedButton *btnLevel4;
	TSpeedButton *btnAddition;
	TSpeedButton *btnSubtraction;
	TSpeedButton *btnMultiplication;
	TSpeedButton *btnDivision;
	TLabel *lblOperand1;
	TLabel *lblOperand2;
	TLabel *lblOperation;
	TLabel *Label1;
	TEdit *edtResult;
	TButton *btnClose;
	TButton *btnCheckResult;
	void __fastcall btnAdditionClick(TObject *Sender);
	void __fastcall btnSubtractionClick(TObject *Sender);
	void __fastcall btnMultiplicationClick(TObject *Sender);
	void __fastcall btnDivisionClick(TObject *Sender);
	void __fastcall btnLevel1Click(TObject *Sender);
	void __fastcall btnLevel2Click(TObject *Sender);
	void __fastcall btnLevel3Click(TObject *Sender);
	void __fastcall btnLevel4Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnCheckResultClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
private:
	int Level;
	int Operation; // User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
