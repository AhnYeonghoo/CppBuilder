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
	TGroupBox *GroupBox1;
	TCheckBox *btnInput0;
	TCheckBox *btnInput5;
	TCheckBox *btnInput1;
	TCheckBox *btnInput2;
	TCheckBox *btnInput3;
	TCheckBox *btnInput4;
	TCheckBox *btnInput6;
	TCheckBox *btnInput7;
	TCheckBox *btnInput8;
	TCheckBox *btnInput9;
	TCheckBox *btnInput10;
	TCheckBox *btnInput11;
	TCheckBox *btnInput12;
	TCheckBox *btnInput13;
	TCheckBox *btnInput14;
	TCheckBox *btnInput15;
	TGroupBox *GroupBox2;
	TCheckBox *btnOutput0;
	TCheckBox *btnOutput5;
	TCheckBox *btnOutput1;
	TCheckBox *btnOutput2;
	TCheckBox *btnOutput3;
	TCheckBox *btnOutput4;
	TCheckBox *btnOutput6;
	TCheckBox *btnOutput7;
	TCheckBox *btnOutput8;
	TCheckBox *btnOutput9;
	TCheckBox *btnOutput10;
	TCheckBox *btnOutput11;
	TCheckBox *btnOutput12;
	TCheckBox *btnOutput13;
	TCheckBox *btnOutput14;
	TCheckBox *btnOutput15;
	TComboBox *selectModule;
	TTimer *Timer1;
	TGroupBox *GroupBox3;
	TGroupBox *GroupBox4;
	TCheckBox *chkEndLimitPlus;
	TCheckBox *chkEndLimitMinus;
	TCheckBox *chkSlowLimitPlus;
	TCheckBox *chkSlowLimitMinus;
	TCheckBox *chkInposition;
	TCheckBox *chkAlarm;
	TButton *btnRotate;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *edtPosition;
	TEdit *edtSpeed;
	TEdit *edtAccel;
	TCheckBox *chkServoOn;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnInput0Click(TObject *Sender);
	void __fastcall btnInput1Click(TObject *Sender);
	void __fastcall btnInput2Click(TObject *Sender);
	void __fastcall btnInput3Click(TObject *Sender);
	void __fastcall btnInput4Click(TObject *Sender);
	void __fastcall btnInput5Click(TObject *Sender);
	void __fastcall btnInput6Click(TObject *Sender);
	void __fastcall btnInput7Click(TObject *Sender);
	void __fastcall btnInput8Click(TObject *Sender);
	void __fastcall btnInput9Click(TObject *Sender);
	void __fastcall btnInput10Click(TObject *Sender);
	void __fastcall btnInput11Click(TObject *Sender);
	void __fastcall btnInput12Click(TObject *Sender);
	void __fastcall btnInput13Click(TObject *Sender);
	void __fastcall btnInput14Click(TObject *Sender);
	void __fastcall btnInput15Click(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall chkServoOnClick(TObject *Sender);
	void __fastcall btnRotateClick(TObject *Sender);
	void __fastcall chkEndLimitPlusClick(TObject *Sender);
	void __fastcall chkEndLimitMinusClick(TObject *Sender);
	void __fastcall chkSlowLimitPlusClick(TObject *Sender);
	void __fastcall chkSlowLimitMinusClick(TObject *Sender);
	void __fastcall chkInpositionClick(TObject *Sender);
	void __fastcall chkAlarmClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	void SearchModule(void);
    void InitializeSetting();
	__fastcall TForm2(TComponent* Owner);
	int nDIOBoardNo;
	int nDIOModuleNo;
	int nDIOModulePos[9];
	int nTempBoardNo[9];


	TCheckBox **input;
	TCheckBox **output;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
