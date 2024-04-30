//---------------------------------------------------------------------------

#ifndef Unit9H
#define Unit9H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VrControls.hpp"
#include "VrThreads.hpp"
#include <Vcl.ExtCtrls.hpp>
#include "VrArrow.hpp"
#include "DEVICE/AXT/AXTLIB.h"
#include "DEVICE/AXT/AxtCamcFs.h"
#include "DEVICE/AXT/AxtCAMCFS20.h"

#pragma comment(lib, "DEVICE/AxtLib.lib")

//---------------------------------------------------------------------------
class TForm9 : public TForm
{
__published:	// IDE-managed Components
	TButton *InputButton0;
	TButton *InputButton1;
	TButton *InputButton6;
	TButton *InputButton7;
	TButton *InputButton8;
	TButton *InputButton2;
	TButton *InputButton5;
	TButton *InputButton3;
	TButton *InputButton4;
	TButton *InputButtonB;
	TButton *InputButtonA;
	TButton *InputButton9;
	TButton *InputButtonD;
	TButton *InputButtonC;
	TButton *InputButtonE;
	TButton *InputButtonF;
	TListBox *ListBox1;
	TPanel *OutputButton1;
	TPanel *OutputButton2;
	TPanel *OutputButton0;
	TPanel *OutputButton3;
	TPanel *OutputButton4;
	TPanel *OutputButton5;
	TPanel *OutputButton6;
	TPanel *OutputButton7;
	TPanel *OutputButton8;
	TPanel *OutputButton9;
	TPanel *OutputButtonA;
	TPanel *OutputButtonB;
	TPanel *OutputButtonC;
	TPanel *OutputButtonD;
	TPanel *OutputButtonE;
	TPanel *OutputButtonF;
	TVrArrow *ArrowDown;
	TVrArrow *ArrowRight;
	TVrArrow *ArrowUp;
	TVrArrow *ArrowLeft;
	TComboBox *ModuleList;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall InputButton0Click(TObject *Sender);
	void __fastcall InputButton1Click(TObject *Sender);
	void __fastcall InputButton2Click(TObject *Sender);
	void __fastcall InputButton3Click(TObject *Sender);
	void __fastcall InputButton4Click(TObject *Sender);
	void __fastcall InputButton5Click(TObject *Sender);
	void __fastcall InputButton6Click(TObject *Sender);
	void __fastcall InputButton7Click(TObject *Sender);
	void __fastcall InputButton8Click(TObject *Sender);
	void __fastcall InputButton9Click(TObject *Sender);
	void __fastcall InputButtonAClick(TObject *Sender);
	void __fastcall InputButtonBClick(TObject *Sender);
	void __fastcall InputButtonCClick(TObject *Sender);
	void __fastcall InputButtonDClick(TObject *Sender);
	void __fastcall InputButtonEClick(TObject *Sender);
	void __fastcall InputButtonFClick(TObject *Sender);
	void __fastcall ArrowLeftClick(TObject *Sender);
	void __fastcall ArrowRightClick(TObject *Sender);


private:
void SearchModule();// User declarations
public:		// User declarations
	__fastcall TForm9(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm9 *Form9;
//---------------------------------------------------------------------------
#endif
