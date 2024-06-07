//---------------------------------------------------------------------------

#ifndef DoorTestFormH
#define DoorTestFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "AdvGlassButton.hpp"
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFmDoorTest : public TForm
{
__published:	// IDE-managed Components
	TAdvGlassButton *BtnSlidingOpen;
	TAdvGlassButton *BtnSlidingClose;
	TAdvGlassButton *BtnCylinderOpen;
	TAdvGlassButton *BtnCylinderClose;
	TAdvGlassButton *BtnClampOpen;
	TAdvGlassButton *BtnClampClose;
	TAdvGlassButton *BtnOpenDoor;
	TAdvGlassButton *BtnCloseDoor;
	TAdvGlassButton *BtnDoorTest;
	TTimer *Timer1;
	TPanel *Panel1;
	TAdvGlassButton *SetLogger;
	TAdvGlassButton *BtnSwingDoorInit;
	TAdvGlassButton *BtnPushPullDoorInit;
	TAdvGlassButton *BtnO2PumpOn;
	TPanel *pnlO2PumpStatus;
	TPanel *pnlO2Flowrate;
	TAdvGlassButton *BtnO2PumpOff;
	void __fastcall BtnClampOpenClick(TObject *Sender);
	void __fastcall BtnClampCloseClick(TObject *Sender);
	void __fastcall BtnSlidingOpenClick(TObject *Sender);
	void __fastcall BtnSlidingCloseClick(TObject *Sender);
	void __fastcall BtnCylinderOpenClick(TObject *Sender);
	void __fastcall BtnCylinderCloseClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnOpenDoorClick(TObject *Sender);
	void __fastcall BtnCloseDoorClick(TObject *Sender);
	void __fastcall BtnDoorTestClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall SetLoggerClick(TObject *Sender);
	void __fastcall BtnSwingDoorInitClick(TObject *Sender);
	void __fastcall BtnPushPullDoorInitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnO2PumpOnClick(TObject *Sender);
	void __fastcall BtnO2PumpOffClick(TObject *Sender);
private:	// User declarations
	bool DoorTest;
	unsigned int Count;
public:		// User declarations
	__fastcall TFmDoorTest(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFmDoorTest *FmDoorTest;
//---------------------------------------------------------------------------
#endif
