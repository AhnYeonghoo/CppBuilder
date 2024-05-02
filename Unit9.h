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
#include "VrSwitch.hpp"

#pragma comment(lib, "DEVICE/AxtLib.lib")

//---------------------------------------------------------------------------
class TForm9 : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox1;
	TVrArrow *ArrowDown;
	TVrArrow *ArrowRight;
	TVrArrow *ArrowUp;
	TVrArrow *ArrowLeft;
	TVrSwitch *VrSwitch0;
	TVrSwitch *VrSwitch1;
	TVrSwitch *VrSwitch2;
	TVrSwitch *VrSwitch33;
	TVrSwitch *VrSwitch4;
	TVrSwitch *VrSwitch5;
	TVrSwitch *VrSwitch6;
	TVrSwitch *VrSwitch7;
	TVrSwitch *VrSwitch8;
	TVrSwitch *VrSwitch9;
	TVrSwitch *VrSwitchA;
	TVrSwitch *VrSwitchB;
	TVrSwitch *VrSwitchC;
	TVrSwitch *VrSwitchD;
	TVrSwitch *VrSwitchE;
	TVrSwitch *VrSwitchF;
	TEdit *Edit0;
	TEdit *Edit2;
	TEdit *Edit1;
	TEdit *Edit4;
	TEdit *Edit3;
	TEdit *Edit6;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TEdit *Edit10;
	TEdit *Edit11;
	TEdit *Edit12;
	TEdit *Edit13;
	TEdit *Edit15;
	TEdit *Edit14;
	TEdit *Edit5;
	TComboBox *ModuleList;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall VrSwitch1Change(TObject *Sender);



	protected:
	TEdit *EditControls[16];


private:

	void SearchModule();// User declarations
	void __fastcall ReadModule(TObject *Sender);
	void __fastcall WriteModule(TVrSwitch *VrSwitch, int Offset);
public:		// User declarations
	__fastcall TForm9(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm9 *Form9;
//---------------------------------------------------------------------------
#endif
