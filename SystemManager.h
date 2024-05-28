//---------------------------------------------------------------------------

#ifndef SystemManagerH
#define SystemManagerH
#include <vector>

#include "Defines.h"
//---------------------------------------------------------------------------


class BaseChamber;
class SystemManagerBase : public Singleton<SystemManagerBase>
{
protected:
	String FProgramName;
	int FLoginLevel;
	String FUserID;
	String FOperatorID;
	BaseChamber* FChamber[MAX_CHAMBER_COUNT];

	int FLanguage;
	int FChamberCount;
	bool FUseAutomation;
	int FAutoMationKind;
	bool FUseRemoteCheck;
	bool FUseScreenSaver;
	int FScreenSaverTIme;
	int FDVFModeLoggerOffset;
	bool FIsShowLoginForm;

	int GetLanguage() { return FLanguage; }
	void SetLanguage(int language);
	BaseChamber* GetAChamber(int chamberId);

public:
	SystemManagerBase();
	~SystemManagerBase();

	__property String ProgramName { read = FProgramName };
	__property int LoginLevel = { read = FLoginLevel, write = FLoginLevel };
	__property String UserID = { read = FUserID, write = FUserID };
	__property String OperatorID = { read = FOperatorID, write = FOperatorID };
	__property int Language = { read = FLanguage, write = SetLanguage };
	__property int ChamberCount = { read = FChamberCount, write = FChamberCount };
	__property bool UseAutomation = { read = FUseAutomation, write = FUseAutomation };
	__property int AutomationKind = { read = FAutomationKind, write = FAutomationKind };
	__property bool UseRemoteCheck = { read = FUseRemoteCheck, write = FUseRemoteCheck };
	__property bool UseScreenSaver = { read = FUseScreenSaver, write = FUseScreenSaver };
	__property int ScreenSaverTime = { read = FScreenSaverTime, write = FScreenSaverTime};
	__property int DVFModeLoggerOffset = { read = FDVFModeLoggerOffset, write = FDVFModeLoggerOffset };
	__property bool IsShowLoginForm = { read = FIsShowLoginForm, write = FIsShowLoginForm };

	static SystemManagerBase* GetSystemManager() { return Singleton<SystemManagerBase>:;GetInstance(); }

	virtual bool LoadSystemParameters() { return false; }
	virtual bool SaveSystemParameters() { return false; }
	virtual bool CreateSerialDevices() { return false; }
	virtual void DestroySerialDevices() {}
	virtual void InitDirectory(String PrgName) { }
};

class OvenChamber;
class DevMainTempController;
class DevLimitController;
class OvenSystemManagerBase : public SystemManagerBase
{
protected:
	int FLoggerCount;
	int FLoggerPointCount;
	int FMainTempCtrlPort;
	int FChamberTempCtrlPort;
	int FChamberTempLimitCtrlPort;
	int FLoggerPort;
	int FEmoOption;
	int FGasType;
	int FInverter008IG5APort;
	int FHeaterPort;

	int FMainTempCtrlTimeout;
	int FChamberTempCtrlTimeout;
	int FLimitCtrlTimeout;
	int FLoggerTimeout;
	int FInverter008IG5ATimeout;
	int FHeaterTimeout;

	double FMaxTemp;

	DevMainTempController* CreateMainTempController(OvenChamber *chamber, PORTINFO portInfo);
	DevLimitController* CreateLimitController(OvenChamber *chamber, PORTINFO portInfo, int limitType);

public:
	OvenSystemManagerBase();
	~OvenSystemManagerBase();

	__property double MaxTemp = { read = FMaxTemp };
	__property OvenChamber* AChamber[int idx] = { read = GetAChamber };

	__property int MainTempCtrlTimeout = { read = FMainTempCtrlTimeout, write = FMainTempCtrlTimeout };
	__property int ChamberTempCtrlTimeout = { read = FChamberTempCtrlTimeout, write = FChamberTempCtrlTimeout };
	__property int LimitCtrlTimeout = { read = FLimitCtrlTimeout, write = FLimitCtrlTimeout };
	__property int LoggerTimeout = { read = FLoggerTimeout, write = FLoggerTimeout };

	__property int LoggerCount = { read = FLoggerCount, write = FLoggerCount };
	__property int LoggerPointCount = { read = FLoggerPointCount, write = FLoggerPointCount };
	__property int MainTempCtrlPort = { read = FMainTempCtrlPort, wrtie = FMainTempCtrlPort };
	__property int ChamberTempCtrlPort = { read = FChamberTempCtrlPort, write = FChamberTempCtrlPort };
	__property int ChamberTempLimitCtrlPort = { read = FChamberTempLimitCtrlPort, write = FChamberTempLimitCtrlPort };
	__property int LoggerPort = { read = FLoggerPort, write = FLoggerPort };
	__property int EmoOption = { read = FEmoOption, write = FEmoOption };
	__property int GasType = { read = FGasType, write = FGasType};

	virtual void CreateChamber() = 0;
	virtual void DestroyChamber() = 0;
	virtual bool CreateSerialDevices();
	virtual void DestroySerialDevices();
	virtual void InitDirectory(String PrgName);

};


extern PORTSETTING MainTempPortSetting;
extern PORTSETTING SP540PortSetting;
extern PORTSETTING ST340PortSetting;
extern PORTSETTING LoggerPortSetting;
extern PORTSETTING KVC3300PortSetting;
extern PORTSETTING MotorBoardPortSetting;
extern PORTSETTING DIOBoardPortSetting;
extern PORTSETTING DPPortSetting;
extern PORTSETTING O2AnalyzerPortSetting;
extern PORTSETTING ZR502AnalyzerPortSetting;
extern PORTSETTING PlasourceRFGenPortSetting;
extern PORTSETTING DamperMotorPortSetting;
extern PORTSETTING DIOPortSetting;
extern PORTSETTING RF400PortSetting;
extern PORTSETTING GT600PortSetting;
extern PORTSETTING Inverter008IGAPortSetting;
extern PORTSETTING InverterVFDBPortSetting;
extern PORTSETTING VSDIOPortSetting;
extern PORTSETTING REXP250PortSetting;


#endif
