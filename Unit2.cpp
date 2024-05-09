//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit2.h"
#include "DEVICE/AXT/AXTDIO.h"
#include "DEVICE/AXT/AXTLIB.h"
#include "DEVICE/AXT/AxtCAMCFS.h"
#include "DEVICE/AXT/AxtCAMCFS20.h"
#include "DEVICE/AXT/AxtKeCAMCFS20.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VrArrow"
#pragma link "VrControls"
#pragma resource "*.dfm"
#pragma comment(lib, "DEVICE/AXT/AxtLib.lib")
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
	if(!AxtIsInitialized())						        // 통합 라이브러리가 사용 가능하지 (초기화가 되었는지) 확인
	{
		if(!AxtInitialize(Form2->WindowHandle , 0))		// 통합 라이브러리 초기화
		{
			ShowMessage("Can not Library Initialize!!");
		}
	}

	if(!AxtIsInitializedBus(BUSTYPE_PCI))               // 지정한 버스(PCI)가 초기화 되었는지 확인
	{									                // 버스가 ISA 일경우 BUSTYPE_PCI -> BUSTYPE_ISA 변경
		if(!AxtOpenDeviceAuto(BUSTYPE_PCI))		        // 새로운 베이스보드를 자동으로 통합라이브러리에 추가
		{
			ShowMessage("Can not Baseboard Initialize!!");
		}
	}

	if (!DIOIsInitialized())
	{
		if (!InitializeDIO())
		{
            ShowMessage("Can not DIO Initialize!!");
        }
    }


	if(!CFS20IsInitialized())                         // CAMC-FS모듈을 사용할 수 있도록 라이브러리가 초기화되었는지 확인.
	{                                               // 단, CAMC-FS v1.0만 검출. v2.0이상은 FS20 함수를 사용하시기 바랍니다.
		if(!InitializeCAMCFS20(TRUE))
           	MessageBoxA(NULL, "Can not CAMC-FS Module Initilaize!!", "Ajinextek", MB_OK);
	}

	input = new TCheckBox*[16];
	output = new TCheckBox*[16];

	input[0] = btnInput0;
	input[1] = btnInput1;
	input[2] = btnInput2;
	input[3] = btnInput3;
	input[4] = btnInput4;
	input[5] = btnInput5;
	input[6] = btnInput6;
	input[7] = btnInput7;
	input[8] = btnInput8;
	input[9] = btnInput9;
	input[10] = btnInput10;
	input[11] = btnInput11;
	input[12] = btnInput12;
	input[13] = btnInput13;
	input[14] = btnInput14;
	input[15] = btnInput15;
	output[0] = btnOutput0;
	output[1] = btnOutput1;
	output[2] = btnOutput2;
	output[3] = btnOutput3;
	output[4] = btnOutput4;
	output[5] = btnOutput5;
	output[6] = btnOutput6;
	output[7] = btnOutput7;
	output[8] = btnOutput8;
	output[9] = btnOutput9;
	output[10] = btnOutput10;
	output[11] = btnOutput11;
	output[12] = btnOutput12;
	output[13] = btnOutput13;
	output[14] = btnOutput14;
	output[15] = btnOutput15;

    SearchModule();
	InitializeSetting();

}
//---------------------------------------------------------------------------

void TForm2::InitializeSetting()
{
	// dd
	 UnicodeString sDriveModeList[8] =  {"OneHighLowHigh", "OneHighHighLow", "OneLowLowHigh",
	"OneLowHighLow", "TwoCcwCwHigh", "TwoCcwCwLow", "TwoCwCCwHigh", "TwoCwCcwLow" };

	UnicodeString sDetectList[16] =  {"PElmNegativeEdge", "NElmNegativeEdge", "PSlmNegativeEdge",
		"NSlmNegativeEdge", "In0DownEdge", "In1DownEdge", "In2DownEdge", "In3DownEdge",
		"PElmPositiveEdge", "NElmPositiveEdge", "PSlmPositiveEdge", "NSlmPositiveEdge",
		"In0UpEdge", "In1UpEdge", "In2UpEdge", "In3UpEdge"};

	// 펄스 출력 방식을 리스트화 한다.
	for(int i = 0; i < 8; i++)
	{
		cbDriveModeList->Items->Add(sDriveModeList[i]);
	}

	SetnTotalAxisCount(CFSget_total_numof_axis());
	edtTotalAxisCount->Text = IntToStr(GetnTotalAxisCount());
	CFS20KeSetMainClk(F_16_384M_CLK);

	for (int i = 0; i < 16; i++)
	{
		cbDetectList->Items->Add(sDetectList[i]);
	}


}




void TForm2::SetnCount(WORD nCount)
{
	this->nCount = nCount;
}

WORD TForm2::GetnCount()
{
	return this->nCount;
}

UINT16 TForm2::GetwModuleID()
{
	return this->wModuleID;
}

void TForm2::SetwModuleID(UINT16 wModuleID)
{
	this->wModuleID = wModuleID;
}

INT16 TForm2::GetnCarrierBoardCount()
{
	return this->nCarrierBoardCount;
}

void TForm2::SetnCarrierBoardCount(INT16 nCarrierBoardCount)
{
    this->nCarrierBoardCount = nCarrierBoardCount;
}



void TForm2::SearchModule()
{
	INT16 nBoardNo, nModulePos;
	INT16 nAxisCount;
	SetnCount(DIOget_module_count());
	int nPosCount;
	int nIndex;



	if (GetnCount() > 0)
	{
		for (int i = 0; i < GetnCount(); i++)
		{
			switch (DIOget_module_id(i))
			{
				case AXT_SIO_DB32P:
				DIOget_module_info(i, &nBoardNo, &nModulePos);
				nDIOModulePos[nPosCount] = i;
				nTempBoardNo[i] = nBoardNo;
				SetnCarrierBoardCount(CFS20get_numof_boards());
				edtCarrierBoardCount->Text = IntToStr(GetnCarrierBoardCount());
				selectModule->Items->Add(IntToStr(nModulePos));
				edtCarrierBoardNo->Text = IntToStr(nBoardNo);
				nAxisCount = CFS20get_numof_axes(nBoardNo);
				edtAxisCount->Text = IntToStr(nAxisCount);
				cbAxisList->Items->Add(CFSget_axisno(nBoardNo, nModulePos));
				nPosCount++;
				break;

				case AXT_SIO_DB32T:
				DIOget_module_info(i, &nBoardNo, &nModulePos);
				nDIOModulePos[nPosCount] = i;
				nTempBoardNo[i] = nBoardNo;
				edtCarrierBoardNo->Text = IntToStr(nBoardNo);
				SetnCarrierBoardCount(CFS20get_numof_boards());
				edtCarrierBoardCount->Text = IntToStr(GetnCarrierBoardCount());
				selectModule->Items->Add(IntToStr(nModulePos));
				nAxisCount = CFS20get_numof_axes(nBoardNo);
				edtAxisCount->Text = IntToStr(nAxisCount);
				cbAxisList->Items->Add(CFSget_axisno(nBoardNo, nModulePos));
				nPosCount++;
				break;

				case AXT_SIO_DO32P:
				DIOget_module_info(i, &nBoardNo, &nModulePos);
				nDIOModulePos[nPosCount] = i;
				nTempBoardNo[i] = nBoardNo;
				edtCarrierBoardNo->Text = IntToStr(nBoardNo);
				SetnCarrierBoardCount(CFS20get_numof_boards());
				edtCarrierBoardCount->Text = IntToStr(GetnCarrierBoardCount());
				selectModule->Items->Add(IntToStr(nModulePos));
				nAxisCount = CFS20get_numof_axes(nBoardNo);
				edtAxisCount->Text = IntToStr(nAxisCount);
				cbAxisList->Items->Add(CFSget_axisno(nBoardNo, nModulePos));
				nPosCount++;
				break;

				case AXT_SIO_DO32T:
				DIOget_module_info(i, &nBoardNo, &nModulePos);
				nDIOModulePos[nPosCount] = i;
				nTempBoardNo[i] = nBoardNo;
				edtCarrierBoardNo->Text = IntToStr(nBoardNo);
				SetnCarrierBoardCount(CFS20get_numof_boards());
				edtCarrierBoardCount->Text = IntToStr(GetnCarrierBoardCount());
				selectModule->Items->Add(IntToStr(nModulePos));
				nAxisCount = CFS20get_numof_axes(nBoardNo);
				edtAxisCount->Text = IntToStr(nAxisCount);
				cbAxisList->Items->Add(CFSget_axisno(nBoardNo, nModulePos));
				nPosCount++;
				break;

				case AXT_SIO_DI32:
				DIOget_module_info(i, &nBoardNo, &nModulePos);
				nDIOModulePos[nPosCount] = i;
				nTempBoardNo[i] = nBoardNo;
				edtCarrierBoardNo->Text = IntToStr(nBoardNo);
				SetnCarrierBoardCount(CFS20get_numof_boards());
				edtCarrierBoardCount->Text = IntToStr(GetnCarrierBoardCount());
				selectModule->Items->Add(IntToStr(nModulePos));
				nAxisCount = CFS20get_numof_axes(nBoardNo);
				edtAxisCount->Text = IntToStr(nAxisCount);
				cbAxisList->Items->Add(CFSget_axisno(nBoardNo, nModulePos));
				nPosCount++;
				break;

			}
		}
		nIndex = selectModule->ItemIndex;
		nDIOModuleNo = nDIOModulePos[nIndex];
		nDIOBoardNo = nTempBoardNo[nIndex];

	}
	if (nPosCount == 0)
        selectModule->Text = "None";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput0Click(TObject *Sender)
{
	if (btnInput0->Checked == True)
		DIOwrite_outport_bit(nDIOModuleNo, 0, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 0, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput1Click(TObject *Sender)
{
	if (btnInput1->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 1, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 1, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput2Click(TObject *Sender)
{
	if (btnInput2->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 2, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 2, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput3Click(TObject *Sender)
{
	if (btnInput3->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 3, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 3, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput4Click(TObject *Sender)
{
	if (btnInput4->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 4, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 4, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput5Click(TObject *Sender)
{
	if (btnInput5->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 5, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 5, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput6Click(TObject *Sender)
{
	if (btnInput6->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 6, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 6, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput7Click(TObject *Sender)
{
	if (btnInput7->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 7, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 7, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput8Click(TObject *Sender)
{
	if (btnInput8->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 8, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 8, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput9Click(TObject *Sender)
{
    if (btnInput9->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 9, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 9, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput10Click(TObject *Sender)
{
	if (btnInput10->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 10, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 10, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::btnInput11Click(TObject *Sender)
{
	if (btnInput11->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 11, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 11, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput12Click(TObject *Sender)
{
	if (btnInput12->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 12, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 12, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput13Click(TObject *Sender)
{
	if (btnInput13->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 13, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 13, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput14Click(TObject *Sender)
{
	if (btnInput14->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 14, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 14, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::btnInput15Click(TObject *Sender)
{
	if (btnInput15->Checked)
		DIOwrite_outport_bit(nDIOModuleNo, 15, 1);
	else
		DIOwrite_outport_bit(nDIOModuleNo, 15, 0);
}
//---------------------------------------------------------------------------
void __fastcall TForm2::Timer1Timer(TObject *Sender)
{
	if (DIOread_inport_bit(nDIOModuleNo, 0))
	{
		output[0]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 1))
	{
		output[1]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 2))
	{
		output[2]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 3))
	{
		output[3]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 4))
	{
		output[4]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 5))
	{
		output[5]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 6))
	{
		output[6]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 7))
	{
		output[7]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 8))
	{
		output[8]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 9))
	{
		output[9]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 10))
	{
		output[10]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 11))
	{
		output[11]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 12))
	{
		output[12]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 13))
	{
		output[13]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 14))
	{
		output[14]->Checked = True;
	}
	else if (DIOread_inport_bit(nDIOModuleNo, 15))
	{
		output[15]->Checked = True;
	}
	else
	{
		for (int i = 0; i <= 15; i++)
		{
            output[i]->Checked = False;
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm2::btnStopModuleClick(TObject *Sender)
{
    CFS20StopService();
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



// Setting에서 읽어온 값 불러오기
void __fastcall TForm2::Timer2Timer(TObject *Sender)
{

	CFS20set_plimit_sel(0, 1);
	CFS20set_moveunit_perpulse(StrToInt(cbAxisList->Text), 100);
	UINT8 servoEnable = CFS20get_servo_enable(StrToInt(cbAxisList->Text));
	edtReadServoOn->Text = servoEnable;
	UINT8 inpositionEnable = CFS20get_inposition_enable(StrToInt(cbAxisList->Text));
	edtReadInposition->Text = inpositionEnable;
	UINT8 alarmEnable = CFS20get_alarm_enable(StrToInt(cbAxisList->Text));
	edtReadAlarm->Text = alarmEnable;
	UINT8 endLimitPlusEnable = CFS20get_end_limit_enable(StrToInt(cbAxisList->Text));
	edtReadEndLimitPlus->Text = endLimitPlusEnable;
	UINT8 endLimitMinusLevel = CFS20get_nend_limit_level(StrToInt(cbAxisList->Text));
	edtReadEndLimitMinus->Text = endLimitMinusLevel;
	UINT8 slowLimitPlusEnable = CFS20get_slow_limit_enable(StrToInt(cbAxisList->Text));
	edtReadSlowLimitPlus->Text = slowLimitPlusEnable;
	CFSset_pulse_out_method(StrToInt(cbAxisList->Text), OneHighLowHigh);
//	UINT8 slowLimitMinusLevel = CFS20get_nslow_limit_level(StrToInt(cbAxisList->Text));
//	edtReadSlowLimitMinus->Text = slowLimitMinusLevel;

}
//---------------------------------------------------------------------------


void __fastcall TForm2::chkEndLimitPlusClick(TObject *Sender)
{
	if (chkEndLimitPlus->Checked)
	{
		CFS20set_end_limit_enable(StrToInt(cbAxisList->Text), ENABLE);
	}
	else
	{
		CFS20set_end_limit_enable(StrToInt(cbAxisList->Text), DISABLE);
	}
}
//---------------------------------------------------------------------------

// Servo-On 신호의 출력 레벨을 설정한다.
void __fastcall TForm2::chkServoOnClick(TObject *Sender)
{
	if (chkServoOn->Checked)
	{
		CFS20set_servo_enable(StrToInt(cbAxisList->Text), ENABLE);
	}
	else
	{
		CFS20set_servo_enable(StrToInt(cbAxisList->Text), DISABLE);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::chkInpositionClick(TObject *Sender)
{
	if (chkInposition->Checked)
	{
		CFS20set_inposition_enable(StrToInt(cbAxisList->Text), ENABLE);
	}
	else
	{
        CFS20set_inposition_enable(StrToInt(cbAxisList->Text), DISABLE);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::chkAlarmClick(TObject *Sender)
{
	if (chkAlarm->Checked)
	{
		CFS20set_alarm_enable(StrToInt(cbAxisList->Text), ENABLE);
	}
	else
	{
		CFS20set_alarm_enable(StrToInt(cbAxisList->Text), DISABLE);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::chkEndLimitMinusClick(TObject *Sender)
{
	if (chkEndLimitMinus->Checked)
	{
		CFS20set_nend_limit_level(StrToInt(cbAxisList->Text), HIGH);
	}
	else
	{
		CFS20set_nend_limit_level(StrToInt(cbAxisList->Text), LOW);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::chkSlowLimitPlusClick(TObject *Sender)
{
	if (chkSlowLimitPlus->Checked)
	{
		CFS20set_slow_limit_enable(StrToInt(cbAxisList->Text), ENABLE);
	}
	else
	{
		CFS20set_slow_limit_enable(StrToInt(cbAxisList->Text), DISABLE);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm2::chkSlowLimitMinusClick(TObject *Sender)
{
	if (chkSlowLimitMinus->Checked)
	{
		CFS20set_nslow_limit_level(StrToInt(cbAxisList->Text), HIGH);
	}
	else
	{
		CFS20set_nslow_limit_level(StrToInt(cbAxisList->Text), LOW);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm2::btnRotateClick(TObject *Sender)
{
	if (btnRotate->OnMouseEnter)
	{
		CFS20v_move(StrToInt(cbAxisList->Text), StrToFloat(edtSpeed->Text), StrToFloat(edtAccel->Text));
	}

}
//---------------------------------------------------------------------------


