//---------------------------------------------------------------------------

#pragma hdrstop

#include"AxtDIO.h"
#include "AjinIOManager.h"
#include "AjinIODevice.h"
#include "IODefines.h"
#include "SystemManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

AjinIOManager::AjinIOManager()
{
	int ioDeviceCount = IO_COUNT / MAX_IO_COUNT_PER_MODULE;
	for (int i = 0; i < ioDeviceCount; i++)
	{
		AjinIOModuleType.push_back(AXT_SIO_DB32P);
	}

	for (int i = 0; i < ioDeviceCount; i++)
	{
		AjinIODevice * device = new AjinIODevice(i, AjinIOModuleType[i]);
		device->Initialized = GetManager()->IsAjinInitialized;
		AddIODevice(i, device);
	}
}

AjinIOManager::~AjinIOManager()
{
	int ioDeviceCount = IO_COUNT / MAX_IO_COUNT_PER_MODULE;
	for (int i = 0; i < ioDeviceCount; i++)
	{
		if (IODevices[i])
		{
			delete IODevices[i];
        }
	}
}

bool __fastcall AjinIOManager::GetValue(unsigned int addr)
{
	bool ret = false;
	CriticalSection->Acquire();
	{
		int moduleNo = AjinIODevice::GetModuleNo(addr);
		int offset = AjinIODevice::GetOffset(addr);
		if (IODevices[moduleNo])
		{
			ret = IODevices[moduleNo]->GetValue(offset);
		}
	}
    CriticalSection->Release();
	return ret;
}

void __fastcall AjinIOManager::SetOutputValue(unsigned int addr, bool value)
{
	CriticalSection->Acquire();
	{
		int moduleNo = AjinIODevice::GetModuleNo(addr);
		int offset = AjinIODevice::GetOffset(addr);
		if (IODevices[moduleNo])
		{
			IODevices[moduleNo]->SetOutputValue(offset, value);
		}
	}
	CriticalSection->Release();
}

bool __fastcall AjinIOManager::GetIsOutput(unsigned int addr)
{
	int moduleNo = AjinIODevice::GetModuleNo(addr);
	int offset = AjinIODevice::GetOffset(addr);

	bool ret = false;
	if (IODevices[moduleNo])
	{
		ret = IODevices[moduleNo]->IsOutput(offset);
	}
	return ret;
}
