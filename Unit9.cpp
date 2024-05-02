//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit9.h"
#include "DEVICE\AXT\AxtLIB.h"
#include "DEVICE\AXT\AxtDio.h"
#include "DEVICE\AXT\AxtAIO.h"
#include "DEVICE\uAxtIoCtrl.h"
#include "DEVICE\uIoCtrl.h"
#include "DEVICE\uAxtMotorCtrl.h"

//---------------------------------------------------------------------------
#pragma package(smart_init, weak)
#pragma link "VrControls"
#pragma link "VrThreads"
#pragma link "VrArrow"
#pragma link "VrSwitch"
#pragma resource "*.dfm"

TForm9 *Form9;

UINT16 uModuleNo;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
	: TForm(Owner)
{

	VrSwitch0->OnChange = VrSwitch1Change;
	VrSwitch1->OnChange = VrSwitch1Change;
	VrSwitch2->OnChange = VrSwitch1Change;
	VrSwitch33->OnChange = VrSwitch1Change;
	VrSwitch4->OnChange = VrSwitch1Change;
	VrSwitch5->OnChange = VrSwitch1Change;
	VrSwitch6->OnChange = VrSwitch1Change;
	VrSwitch7->OnChange = VrSwitch1Change;
	VrSwitch8->OnChange = VrSwitch1Change;
	VrSwitch9->OnChange = VrSwitch1Change;
	VrSwitchA->OnChange = VrSwitch1Change;
	VrSwitchB->OnChange = VrSwitch1Change;
	VrSwitchC->OnChange = VrSwitch1Change;
	VrSwitchD->OnChange = VrSwitch1Change;
	VrSwitchE->OnChange = VrSwitch1Change;
	VrSwitchF->OnChange = VrSwitch1Change;

	EditControls[0] = Edit0;   EditControls[8] = Edit8;
	EditControls[1] = Edit1;   EditControls[9] = Edit9;
	EditControls[2] = Edit2;   EditControls[10] = Edit10;
	EditControls[3] = Edit3;   EditControls[11] = Edit11;
	EditControls[4] = Edit4;   EditControls[12] = Edit12;
	EditControls[5] = Edit5;   EditControls[13] = Edit13;
	EditControls[6] = Edit6;   EditControls[14] = Edit14;
	EditControls[7] = Edit7;   EditControls[15] = Edit15;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TForm9::FormCreate(TObject *Sender)
{
	if(!AxtIsInitialized())						        // 통합 라이브러리가 사용 가능하지 (초기화가 되었는지) 확인
	{
		if(!AxtInitialize(Form9->WindowHandle , 0))		// 통합 라이브러리 초기화
		{
			ShowMessage("Can not Library Initialize!!");
		}
	}

    if(!DIOIsInitialized())			                    // DIO모듈을 사용할 수 있도록 라이브러리가 초기화되었는지 확인
	{
		if(!InitializeDIO())		                    // DIO모듈을 초기화(열려있는 모든베이스보드에서 AIO모듈을 검색하여 초기화)
		{
			ShowMessage("Can not DIO Module Initialize!!");
		}
		else
		{
            ShowMessage("입출력 초기화 성공");
        }
	}

    if(!AxtIsInitializedBus(BUSTYPE_PCI))               // 지정한 버스(PCI)가 초기화 되었는지 확인
	{									                // 버스가 ISA 일경우 BUSTYPE_PCI -> BUSTYPE_ISA 변경
		if(!AxtOpenDeviceAuto(BUSTYPE_PCI))		        // 새로운 베이스보드를 자동으로 통합라이브러리에 추가
		{
			ShowMessage("Can not Baseboard Initialize!!");
		}
		else
		{
			ShowMessage("PCI 버스 초기화 성공");
        }
	}


	SearchModule();
}
//---------------------------------------------------------------------------
void TForm9::SearchModule() {

	WORD nCount;
	nCount = DIOget_module_count(); // 캐리어 보드에 장착할 수 있는 모듈 수 반환
	INT16 nBoardNo; // 캐리어보드 번호
	INT16 nModulePos;


	if(nCount > 0) {

		// nCount = 4
		for(int i=0; i<nCount; i++) {

			// i는 캐리어보드 OffSet Ex. i = 0 일 때 캐리어보드 0번에 장착된 모듈
			// DIOget_module_id(i) 에 장착된 모듈의 ID 값에 따라서 Case 처리
			switch(DIOget_module_id(i)) {
				case AXT_SIO_DI32:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DI32"); // ComboBox에 추가
					break;
				case AXT_SIO_DO32P:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DO32P"); // ComboBox에 추가
					break;
				case AXT_SIO_DB32P:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DB32P"); // ComboBox에 추가
//					uModuleNo = DIOget_module_number(nBoardNo,nModulePos);
					break;
				case AXT_SIO_DO32T:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DO32T"); // ComboBox에 추가
					break;
				case AXT_SIO_DB32T:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DB32T"); // ComboBox에 추가
					break;

			}
		}
	}
}

//---------------------------------------------------------------------------


void __fastcall TForm9::WriteModule(TVrSwitch *VrSwitch, int Offset)
{
	if(VrSwitch->Offset == 3)
	{
	  // DIOwrite_outport_bit (모듈번호, offset, 비트) offset == 접점번호
	  DIOwrite_outport_bit(uModuleNo, Offset, 1);
	}
	else
	{
	   DIOwrite_outport_bit(uModuleNo, Offset, 0);
	}

}

void __fastcall TForm9::ReadModule(TObject *Sender)
{
	int OffSet[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int arrSize = sizeof(OffSet)/sizeof(OffSet[0]);
	int status;
	for(int i=0; i< arrSize; i++)
	{
		/* 각 Offset의 Read값 업데이트*/
	   status = DIOread_inport_bit(uModuleNo,i);
	   EditControls[i]->Text = IntToStr(status);
	}
}



void __fastcall TForm9::VrSwitch1Change(TObject *Sender)
{
	TVrSwitch *VrSwitch = dynamic_cast<TVrSwitch *>(Sender);

	int SwitchId = VrSwitch->Tag;

	WriteModule(VrSwitch, SwitchId);
}
//---------------------------------------------------------------------------

