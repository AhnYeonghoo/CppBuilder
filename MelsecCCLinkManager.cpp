//---------------------------------------------------------------------------

#pragma hdrstop

#include "MelsecCCLinkManager.h"
#include "uMelsecCCLinkIoCtrl.h"
#include "EQDefines.h"
#include "IODefines.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

MelsecCCLinkManager::MelsecCCLinkManager()
	: IOControlManager()
{
	CriticalSection = new TCriticalSection;
	IODevices.push_back(nullptr);
}

MelsecCCLinkManager::~MelsecCCLinkManager()
{
	if (CriticalSection)
	{
		delete CriticalSection;
	}
}

bool __fastcall MelsecCCLinkManager::GetValue(unsigned int addr)
{
	bool ret = false;
	CriticalSection->Acquire();
	{
		int moduleNo = addr / MAX_IO_COUNT;
		int offset = addr;
		if (IODevices[moduleNo] != nullptr)
		{
			ret = IODevices[moduleNo]->GetValue(offset);
		}
	}
    CriticalSection->Release();
	return ret;
}

void __fastcall MelsecCCLinkManager::SetOutputValue(unsigned int addr, bool value)
{
	CriticalSection->Acquire();
	{
		int moduleNo = 1;//CMelsecCCLinkIoCtrl::GetShiftVal(addr);
		int offset = addr;
		if (IODevices[moduleNo] != nullptr)
		{
			IODevices[moduleNo]->SetOutputValue(offset, value);
		}
	}
	CriticalSection->Release();
}

bool __fastcall MelsecCCLinkManager::GetIsOutput(unsigned int addr)
{
	int moduleNo = addr / MAX_INPUT_COUNT;
	int offset = addr;

	bool ret = false;
	if (IODevices[moduleNo] != nullptr)
	{
        ret = IODevices[moduleNo]->IsOutput(offset);
	}
	return ret;
}
