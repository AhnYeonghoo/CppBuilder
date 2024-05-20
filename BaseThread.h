//---------------------------------------------------------------------------

#ifndef BaseThreadH
#define BaseThreadH

#include <System.Classes.hpp>
#include <map>
#include <string>
#include <vector>
//---------------------------------------------------------------------------

enum INIT_STATUS
{
	IS_NOT_INIT = 0,
	IS_INITIALIZING,
	IS_INIT_DONE,
	IS_COUNT
};

class TComponentBaseFrm;

class BaseThread : public TThread
{
	protected:
	bool FEnabled;
	unsigned int FModuleType;
	int FStep;
	bool StepChanged;
	int FInitStatus;
	int FRunStatus;
	int FPrevRunStatus;

	std::map<int, string> FStepString;
	std::vector<int> AlarmList;
	String ModuleName;

	protected:
	virtual void __fastcall Execute();
	virtual void __fastcall DoWorkSequence() = 0;
	virtual void __fastcall LogStepChanged() = 0;
	virtual void __fastcall SetStep(int step);
	virtual void __fastcall DelayTime(unsigned int milliSeconds, bool workInThread = true);
	virtual int __fastcall GetRunStatus();
	virtual void __fastcall SetRunStatus(int status);

	public:
	__property bool Enable { read = FEnabled, write = FEnabled };
	__property int InitStatus = { read = FInitStatus, write = FInitStatus };
	__property int RunStatus { read = FRunStatus, write = FRunStatus };
	__property int PrevRunStatus { read = FPrevRunStatus, write = FPrevRunStatus };
	__property int Step = { read = FStep, write = FStep };
	__property unsigned int ModuleType = { read = FModuleType, write = FModuleType };
	__property int StepString = { read = GetStepString };

	public:
	__fastcall BaseThread(unsigned int moduleType = 0);
	__fastcall ~BaseThread();

	virtual String __fastcall GetModuleName() { return ModuleName; }
	virtual String __fastcall GetStepString();
	virtual void __fastcall RaiseAlarm(int errorCode, bool setPaused = false);

	virtual void __fastcall ResumeRunStatus();

	virtual void __fastcall AddAlarm(int alarmCode);
	virtual void __fastcall RemoveAlarm(int alarmCode);
	virtual void __fastcall RemoveAlarmAll();
    virtual void __fastcall FindAlarm(int alarmCode);
};
#endif
