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


void __fastcall TForm9::InputButton0Click(TObject *Sender)
{
	// � ������� Ȯ���ϰ� ���� ��� ��ȣ �ִ� ������ �����ϱ�

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
	// �����̾� ��Ʈ �������� �̵��ϴ� �� ����
	// � ������� Ȯ���ؾ� ��
	ShowMessage(L"�����̾� ��Ʈ �������� �̵�!");
}
//---------------------------------------------------------------------------

void __fastcall TForm9::ArrowRightClick(TObject *Sender)
{
	// �����̾� ��Ʈ ���������� �̵��ϴ� �� ����
	// � ������� Ȯ���ؾ� ��
	ShowMessage(L"�����̾� ��Ʈ ���������� �̵�!");
}
//---------------------------------------------------------------------------

