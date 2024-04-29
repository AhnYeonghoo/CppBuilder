//---------------------------------------------------------------------------

#ifndef Unit5H
#define Unit5H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmBoolean : public TForm
{
__published:	// IDE-managed Components
	TStaticText *sttOperand1;
	TStaticText *sttOperand2;
	TStaticText *sttOperation;
	TSpeedButton *sbtOperand1;
	TSpeedButton *sbtOperand2;
	TSpeedButton *sbtResult;
	TButton *btnCheck;
	TButton *btnNewOperation;
	TButton *btnClose;
	void __fastcall sbtOperand1Click(TObject *Sender);
	void __fastcall sbtOperand2Click(TObject *Sender);
	void __fastcall sbtResultClick(TObject *Sender);
	void __fastcall btnNewOperationClick(TObject *Sender);
	void __fastcall btnCheckClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TfrmBoolean(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBoolean *frmBoolean;
//---------------------------------------------------------------------------
#endif
