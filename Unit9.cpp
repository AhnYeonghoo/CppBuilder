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
#pragma resource "*.dfm"
TForm9 *Form9;
//---------------------------------------------------------------------------
__fastcall TForm9::TForm9(TComponent* Owner)
	: TForm(Owner)
{
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


void __fastcall TForm9::InputButton0Click(TObject *Sender)
{
	// 어떤 모듈인지 확인하고 실제 장비에 신호 주는 것으로 변경하기

	CFSset_servo_enable(0, ENABLE);
	if (OutputButton0->Color == clRed)
	{
		OutputButton0->Color = clBlue;
	}
	else
	{
        OutputButton0->Color = clRed;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton1Click(TObject *Sender)
{
	if (OutputButton1->Color == clRed)
	{
		OutputButton1->Color = clBlue;
	}
	else
	{
        OutputButton1->Color = clRed;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton2Click(TObject *Sender)
{
	if (OutputButton2->Color == clRed)
	{
		OutputButton2->Color = clBlue;
	}
	else
	{
		OutputButton2->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton3Click(TObject *Sender)
{
	if (OutputButton3->Color == clRed)
	{
		OutputButton3->Color = clBlue;
	}
	else
	{
		OutputButton3->Color = clRed;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton4Click(TObject *Sender)
{
	if (OutputButton4->Color == clRed)
	{
		OutputButton4->Color = clBlue;
	}
	else
	{
		OutputButton4->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton5Click(TObject *Sender)
{
	if (OutputButton5->Color == clRed)
	{
		OutputButton5->Color = clBlue;
	}
	else
	{
		OutputButton5->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton6Click(TObject *Sender)
{
	if (OutputButton6->Color == clRed)
	{
		OutputButton6->Color = clBlue;
	}
	else
	{
		OutputButton6->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton7Click(TObject *Sender)
{
	if (OutputButton7->Color == clRed)
	{
		OutputButton7->Color = clBlue;
	}
	else
	{
		OutputButton7->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton8Click(TObject *Sender)
{
   if (OutputButton8->Color == clRed)
	{
		OutputButton8->Color = clBlue;
	}
	else
	{
		OutputButton8->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButton9Click(TObject *Sender)
{
	if (OutputButton9->Color == clRed)
	{
		OutputButton9->Color = clBlue;
	}
	else
	{
		OutputButton9->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButtonAClick(TObject *Sender)
{
	if (OutputButtonA->Color == clRed)
	{
		OutputButtonA->Color = clBlue;
	}
	else
	{
		OutputButtonA->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButtonBClick(TObject *Sender)
{
	if (OutputButtonB->Color == clRed)
	{
		OutputButtonB->Color = clBlue;
	}
	else
	{
		OutputButtonB->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButtonCClick(TObject *Sender)
{
	if (OutputButtonC->Color == clRed)
	{
		OutputButtonC->Color = clBlue;
	}
	else
	{
		OutputButtonC->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButtonDClick(TObject *Sender)
{
	if (OutputButtonD->Color == clRed)
	{
		OutputButtonD->Color = clBlue;
	}
	else
	{
		OutputButtonD->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButtonEClick(TObject *Sender)
{
	if (OutputButtonE->Color == clRed)
	{
		OutputButtonE->Color = clBlue;
	}
	else
	{
		OutputButtonE->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::InputButtonFClick(TObject *Sender)
{
	if (OutputButtonF->Color == clRed)
	{
		OutputButtonF->Color = clBlue;
	}
	else
	{
		OutputButtonF->Color = clRed;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm9::ArrowLeftClick(TObject *Sender)
{
	// 컨베이어 벨트 왼쪽으로 이동하는 것 구현
	// 어떤 모듈인지 확인해야 함
	ShowMessage(L"컨베이어 벨트 왼쪽으로 이동!");
}
//---------------------------------------------------------------------------

void __fastcall TForm9::ArrowRightClick(TObject *Sender)
{
	// 컨베이어 벨트 오른쪽으로 이동하는 것 구현
	// 어떤 모듈인지 확인해야 함
	ShowMessage(L"컨베이어 벨트 오른쪽으로 이동!");
}
//---------------------------------------------------------------------------

