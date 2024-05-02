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
	if(!AxtIsInitialized())						        // ���� ���̺귯���� ��� �������� (�ʱ�ȭ�� �Ǿ�����) Ȯ��
	{
		if(!AxtInitialize(Form9->WindowHandle , 0))		// ���� ���̺귯�� �ʱ�ȭ
		{
			ShowMessage("Can not Library Initialize!!");
		}
	}

    if(!DIOIsInitialized())			                    // DIO����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ����� Ȯ��
	{
		if(!InitializeDIO())		                    // DIO����� �ʱ�ȭ(�����ִ� ��纣�̽����忡�� AIO����� �˻��Ͽ� �ʱ�ȭ)
		{
			ShowMessage("Can not DIO Module Initialize!!");
		}
		else
		{
            ShowMessage("����� �ʱ�ȭ ����");
        }
	}

    if(!AxtIsInitializedBus(BUSTYPE_PCI))               // ������ ����(PCI)�� �ʱ�ȭ �Ǿ����� Ȯ��
	{									                // ������ ISA �ϰ�� BUSTYPE_PCI -> BUSTYPE_ISA ����
		if(!AxtOpenDeviceAuto(BUSTYPE_PCI))		        // ���ο� ���̽����带 �ڵ����� ���ն��̺귯���� �߰�
		{
			ShowMessage("Can not Baseboard Initialize!!");
		}
		else
		{
			ShowMessage("PCI ���� �ʱ�ȭ ����");
        }
	}


	SearchModule();
}
//---------------------------------------------------------------------------
void TForm9::SearchModule() {

	WORD nCount;
	nCount = DIOget_module_count(); // ĳ���� ���忡 ������ �� �ִ� ��� �� ��ȯ
	INT16 nBoardNo; // ĳ����� ��ȣ
	INT16 nModulePos;


	if(nCount > 0) {

		// nCount = 4
		for(int i=0; i<nCount; i++) {

			// i�� ĳ����� OffSet Ex. i = 0 �� �� ĳ����� 0���� ������ ���
			// DIOget_module_id(i) �� ������ ����� ID ���� ���� Case ó��
			switch(DIOget_module_id(i)) {
				case AXT_SIO_DI32:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DI32"); // ComboBox�� �߰�
					break;
				case AXT_SIO_DO32P:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DO32P"); // ComboBox�� �߰�
					break;
				case AXT_SIO_DB32P:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DB32P"); // ComboBox�� �߰�
//					uModuleNo = DIOget_module_number(nBoardNo,nModulePos);
					break;
				case AXT_SIO_DO32T:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DO32T"); // ComboBox�� �߰�
					break;
				case AXT_SIO_DB32T:
					DIOget_module_info(i, &nBoardNo, &nModulePos);
					ModuleList->Items->Add("SIO-DB32T"); // ComboBox�� �߰�
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
	  // DIOwrite_outport_bit (����ȣ, offset, ��Ʈ) offset == ������ȣ
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
		/* �� Offset�� Read�� ������Ʈ*/
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

