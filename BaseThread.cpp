//---------------------------------------------------------------------------

#pragma hdrstop

#include <System.DateUtils.hpp>
#include <algorithm>
#include "BaseThread.h"
#include "Defines.h"
#include "EQDefines.h"
#include "ComponentBaseFrame.h"
#include "SystemManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


__fastcall BaseThread::BaseThread(unsigned int moduleType)
	: TThread(false), FModuleType(moduleType)
{
	Step = -1
	Enabled = true;
    InitStatus = IS_NOT_INIT;
}

__fastcall BaseThread::~BaseThread()
{
}

void __fastcall BaseThread::Execute()
{
	while (!Terminated)
	{
		if (Enabled == true)
		{
			DoWorkSequence();
		}
		WaitForSingleObject((void*)Handle, THREAD_WAIT_TIME);
	}
}

int __fastcall BaseThread::GetRunStatus()
{
	return FRunStatus;
}

void __fastcall BaseThread::SetRunStatus(int status)
{
	this->FRunStatus = status;
}

void __fastcall BaseThread::ResumeRunStatus()
{
	if (PrevRunStatus > 0)
	{
		RunStatus = PrevRunStatus;
	}
}

void __fastcall BaseThread::SetStep(int step)
{
	if (Step != step)
	{
		Step = step;
		StepChanged = true;
		LogStepChanged();
    }
}


String __fastcall BaseThread::GetStepString()
{
	String str;
	int count = FStepString.size();
	if (FStep >= 0 && FStep < count)
	{
		str = FStepString[FStep];
	}
	return str;
}

void __fastcall BaseThread::DelayTime(unsigned int milliSeconds, bool workInThread)
{
	TDateTime now = Now();
	while (true)
	{
		if (workInThread)
		{
			WaitForSingleObject((void *)Handle, THREAD_WAIT_TIME);
		}
		else
		{
			Application->ProcessMessages();
			Sleep(THREAD_WAIT_TIME);
		}

		if (MilliSecondsBetween(now, Now()) >= milliSeconds)
		{
			break;
		}
	}
}

void __fastcall BaseThread::RaiseAlarm(int errorCode, bool setPaused)
{
	GetManager()->RegisterAlarm(ModuleType, errorCode, setPaused);
}

bool __fastcall BaseThread::FindAlarm(int alarmCode)
{
	auto it = find(AlarmList.begin(0, AlarmList.end(), alarmCode);
	return (it != AlarmList.end());
}

void __fastcall BaseThread::AddAlarm(int alarmCode)
{
	if (FindAlarm(alarmCode) == false)
	{
		AlarmList.push_back(alarmCode);
	}
}

void __fastcall BaseThread::RemoveAlarm(int alarmCode)
{
	auto it = find(AlarmList.begin(), AlarmList.end(), alarmCode);
	if (it != AlarmList.end())
	{
		AlarmList.erase(it);
	}
}

void __fastcall BaseThread::RemoveAlarmAll()
{
    AlarmList.clear();
}
