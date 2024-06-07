//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DoorTestForm.h"
#include "JobForm.h"
#include "PressureOvenSystemManager.h"
#include "PressureOvenChamber.h"
#include "HelperFunctions.h"
#include "I7018.h"
#include "ZR5.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvGlassButton"
#pragma resource "*.dfm"
TFmDoorTest *FmDoorTest;
//---------------------------------------------------------------------------
__fastcall TFmDoorTest::TFmDoorTest(TComponent* Owner)
	: TForm(Owner)
{
	Count = 0;
	DoorTest = false;

	if (GetManager()->UseO2Analyzer)
	{
		BtnO2PumpOn->Visible = true;
		BtnO2PumpOff->Visible = true;
		pnlO2PumpStatus->Visible = true;
		pnlO2Flowrate->Visible = true;
	}
	else
	{
		BtnO2PumpOn->Visible = false;
		BtnO2PumpOff->Visible = false;
		pnlO2PumpStatus->Visible = false;
		pnlO2Flowrate->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnClampOpenClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorClampOpen();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnClampCloseClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorClampClose();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnSlidingOpenClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorSwingOpen();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnSlidingCloseClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorSwingClose();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnCylinderOpenClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorPush();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnCylinderCloseClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorPull();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::FormClose(TObject *Sender, TCloseAction &Action)
{
	String str;
	str = "Door Test UI Closed.";
	GetOvenDB()->SaveLog(str, MESSAGES, -1);

	FmJob->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnOpenDoorClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorOpen();
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::BtnCloseDoorClick(TObject *Sender)
{
	GetChamber(CHAMBER_A)->DoorClose();
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::BtnDoorTestClick(TObject *Sender)
{
	DoorTest = !DoorTest;
	if( DoorTest == false )
	{
		Count = 0;
		Timer1->Enabled = false;
	}
	else
	{
		Timer1->Enabled = true;
	}
	BtnDoorTest->Caption = DoorTest ? L"Stop Door Test" : L"Start Door Test";
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::Timer1Timer(TObject *Sender)
{
	if( DoorTest )
	{
		Timer1->Enabled = false;
		int state = GetChamber(CHAMBER_A)->CheckDoorState();
		if( state == DOOR_OPENED )
		{
			GetChamber(CHAMBER_A)->DoorClose();
		}
		else
		if( state == DOOR_CLOSED )
		{
			if( GetChamber(CHAMBER_A)->DoorOpen() )
				Count ++;
		}

		PressureOvenChamber *chamber = GetChamber(CHAMBER_A);
		if( chamber != nullptr )
		{
			if (GetManager()->UseO2Analyzer && chamber->UseO2DensityLimit)
			{
				if ( chamber->O2Analyzer->O2PumpStatus == false )
				{
					pnlO2PumpStatus->Caption = "close";
				}
				else if ( chamber->O2Analyzer->O2PumpStatus == true )
				{
					pnlO2PumpStatus->Caption = "open";
				}

				pnlO2Flowrate->Caption = chamber->O2Analyzer->FlowRate;
			}
		}

		Timer1->Enabled = true;
	}
	Panel1->Caption = Count;
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::SetLoggerClick(TObject *Sender)
{
	if( GetChamber(CHAMBER_A)->LoggerController[0] )
	{
		if( !GetChamber(CHAMBER_A)->LoggerController[0]->WriteCJCSetting() )
		{
			SetMessageStr(L"Failed to CJC Setting.");
			ShowMessageDlg();
		}

		if( !GetChamber(CHAMBER_A)->LoggerController[0]->WriteChannelSetting() )
		{
			SetMessageStr(L"Failed to Channel Setting.");
			ShowMessageDlg();
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TFmDoorTest::BtnSwingDoorInitClick(TObject *Sender)
{
	// 도어 밀기
	GetChamber(CHAMBER_A)->DIO[O_DoorOpenZSol].On();
	GetChamber(CHAMBER_A)->DIO[O_DoorCloseZSol].Off();
	WaitSecond(20);

	// 도어 열림 체크
	if( !(GetChamber(CHAMBER_A)->DIO[I_DoorOpenZSen].IsOn() &&
		GetChamber(CHAMBER_A)->DIO[I_DoorCloseZSen].IsOff()) )
	{
		// 열리지 않으면 솔을 반대로 움직임
		GetChamber(CHAMBER_A)->DIO[O_DoorOpenZSol].Off();
		GetChamber(CHAMBER_A)->DIO[O_DoorCloseZSol].On();
		WaitSecond(10);

		// 다시 한번 열기
		GetChamber(CHAMBER_A)->DIO[O_DoorOpenZSol].On();
		GetChamber(CHAMBER_A)->DIO[O_DoorCloseZSol].Off();
		WaitSecond(20);
	}

	if( GetChamber(CHAMBER_A)->DIO[I_DoorOpenZSen].IsOn() &&
		GetChamber(CHAMBER_A)->DIO[I_DoorCloseZSen].IsOff() )
	{
		SetMessageStr(L"Swing door initializing success.");
		ShowMessageDlg();
	}
	else
	{
		SetMessageStr(L"Swing door initializing failed.");
		ShowMessageDlg();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::BtnPushPullDoorInitClick(TObject *Sender)
{
	// 도어 밀기
	GetChamber(CHAMBER_A)->DIO[O_DoorPushYSol].On();
	GetChamber(CHAMBER_A)->DIO[O_DoorPullYSol].Off();
	WaitSecond(20);

	// 도어 열림 체크
	if( !(GetChamber(CHAMBER_A)->DIO[I_DoorPushYSen].IsOn() &&
		GetChamber(CHAMBER_A)->DIO[I_DoorPullYSen].IsOff()) )
	{
		// 열리지 않으면 솔을 반대로 움직임
		GetChamber(CHAMBER_A)->DIO[O_DoorPushYSol].Off();
		GetChamber(CHAMBER_A)->DIO[O_DoorPullYSol].On();
		WaitSecond(10);

		// 다시 한번 열기
		GetChamber(CHAMBER_A)->DIO[O_DoorPushYSol].On();
		GetChamber(CHAMBER_A)->DIO[O_DoorPullYSol].Off();
		WaitSecond(20);
	}

	if( GetChamber(CHAMBER_A)->DIO[I_DoorPushYSen].IsOn() &&
		GetChamber(CHAMBER_A)->DIO[I_DoorPullYSen].IsOff() )
	{
		SetMessageStr(L"Push-pull door initializing success.");
		ShowMessageDlg();
	}
	else
	{
		SetMessageStr(L"Push-pull door initializing failed.");
		ShowMessageDlg();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::FormShow(TObject *Sender)
{
	String str;
	str = "Door Test UI Executed.";
	GetOvenDB()->SaveLog(str, MESSAGES, -1);
}
//---------------------------------------------------------------------------
void __fastcall TFmDoorTest::BtnO2PumpOnClick(TObject *Sender)
{
	PressureOvenChamber *chamber = GetChamber(CHAMBER_A);
	if( chamber == nullptr )
		return;

	if (GetManager()->UseO2Analyzer && chamber->UseO2DensityLimit)
	{
       	if ( chamber->Step == STEP_IDLE && chamber->O2Analyzer->O2PumpStatus == false )
		{
			chamber->O2Analyzer->SetO2Pump(true);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TFmDoorTest::BtnO2PumpOffClick(TObject *Sender)
{
	PressureOvenChamber *chamber = GetChamber(CHAMBER_A);
	if( chamber == nullptr )
		return;

	if (GetManager()->UseO2Analyzer && chamber->UseO2DensityLimit)
	{
     	if ( chamber->Step == STEP_IDLE && chamber->O2Analyzer->O2PumpStatus == true )
		{
			chamber->O2Analyzer->SetO2Pump(false);
		}
    }
}
//---------------------------------------------------------------------------

