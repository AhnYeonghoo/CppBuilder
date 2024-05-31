//---------------------------------------------------------------------------
#ifndef ChamberOptionDefinesH
#define ChamberOptionDefinesH
//---------------------------------------------------------------------------
#include "OptionBase.h"

class OPTION_TEMP_PROFILE_CHANNEL : public OPTION_BASE
{
protected:
	int FChannel;

	// 옵션 항목
	OptionItem<bool> FUse;
	OptionItem<double> FOffset;
//	OptionItem<int> FColor;     // 그래프 그릴 때 사용

protected:
    void __fastcall Init();
	void __fastcall RegisterListValues() {}
	void __fastcall RegisterItemList();
	String __fastcall GetRefName()
	{
		String str;
		str.sprintf(L"%s %d", FName.c_str(), Channel + 1);
        return str;
    }

public:
	__property OptionItem<bool> Channel = { read = FChannel, write = FChannel };
	__property OptionItem<bool> Use = { read = FUse, write = FUse };
	__property OptionItem<double> Offset = { read = FOffset, write = FOffset };
//	__property OptionItem<int> Color = { read = FColor, write = FColor };

public:
	OPTION_TEMP_PROFILE_CHANNEL();
	OPTION_TEMP_PROFILE_CHANNEL(const OPTION_TEMP_PROFILE_CHANNEL &other);
	OPTION_TEMP_PROFILE_CHANNEL(int ch);//, TColor color);
	~OPTION_TEMP_PROFILE_CHANNEL();

	OPTION_TEMP_PROFILE_CHANNEL __fastcall operator=(const OPTION_TEMP_PROFILE_CHANNEL &other);
    String __fastcall GetSubIndex() const;
};

class OPTION_TEMP_PROFILE_DEVIATION_ALARM : public OPTION_BASE
{
protected:
	// 옵션 항목
	OptionItem<bool> FUse; 				// 온도로거 TC별 편차 알람 사용 여부
	OptionItem<int> FAlarmEnableTime;    // 온도로거 모니터링 지연시간(분)
	// 변수들
	std::vector<bool> FIsDeviationHighStarted;
	std::vector<bool> FIsDeviationLowStarted;
	std::vector<TDateTime> FDeviationHighStartTime;
	std::vector<TDateTime> FDeviationLowStartTime;

protected:
	void __fastcall RegisterListValues() {}
	void __fastcall RegisterItemList();

public:
	__property OptionItem<bool> Use = { read = FUse, write = FUse };
	__property OptionItem<int> AlarmEnableTime = { read = FAlarmEnableTime, write = FAlarmEnableTime };

public:
	OPTION_TEMP_PROFILE_DEVIATION_ALARM();
	OPTION_TEMP_PROFILE_DEVIATION_ALARM(const OPTION_TEMP_PROFILE_DEVIATION_ALARM &other);
	~OPTION_TEMP_PROFILE_DEVIATION_ALARM();

	OPTION_TEMP_PROFILE_DEVIATION_ALARM __fastcall operator=(const OPTION_TEMP_PROFILE_DEVIATION_ALARM &other);

	void __fastcall Reset();
	bool __fastcall GetDeviationHighStarted(int idx);
	void __fastcall SetDeviationHighStarted(int idx, bool value);
	bool __fastcall GetDeviationLowStarted(int idx);
	void __fastcall SetDeviationLowStarted(int idx, bool value);
	TDateTime __fastcall  GetDeviationHighStartTime(int idx);
	void __fastcall SetDeviationHighStartTime(int idx, TDateTime time);
	TDateTime __fastcall  GetDeviationLowStartTime(int idx);
	void __fastcall SetDeviationLowStartTime(int idx, TDateTime time);
};

class OPTION_GENERAL : public OPTION_BASE
{
protected:
	// 옵션 항목
//	OptionItem<int> FCoolingWaterVentTime;
	OptionItem<int> FDoorOpenTempCondition;   // 도어열기 가능한 챔버온도

protected:
	void __fastcall RegisterListValues() {}
	void __fastcall RegisterItemList();

public:
//	__property OptionItem<int> CoolingWaterVentTime = { read = FCoolingWaterVentTime, write = FCoolingWaterVentTime };
	__property OptionItem<int> DoorOpenTempCondition = { read = FDoorOpenTempCondition, write = FDoorOpenTempCondition };

public:
	OPTION_GENERAL();
	OPTION_GENERAL(const OPTION_GENERAL &other);
	~OPTION_GENERAL();

	OPTION_GENERAL __fastcall operator=(const OPTION_GENERAL &other);
};

class OPTION_SERIAL_SETTING : public OPTION_BASE
{
protected:
	// 옵션 항목
	OptionItem<bool> FUse;
	OptionItem<int> FAddr;
	OptionItem<int> FBaudRate;
	OptionItem<int> FParity;
	OptionItem<int> FDataBit;
	OptionItem<int> FStopBit;
	OptionItem<int> FPortNo;

protected:
	void __fastcall RegisterListValues();
	void __fastcall RegisterItemList();

public:
	__property OptionItem<bool> Use = { read = FUse, write = FUse };
	__property OptionItem<int> Addr = { read = FAddr, write = FAddr };
	__property OptionItem<int> BaudRate = { read = FBaudRate, write = FBaudRate };
	__property OptionItem<int> Parity = { read = FParity, write = FParity };
	__property OptionItem<int> DataBit = { read = FDataBit, write = FDataBit };
	__property OptionItem<int> StopBit = { read = FStopBit, write = FStopBit };
	__property OptionItem<int> PortNo = { read = FPortNo, write = FPortNo };

public:
	OPTION_SERIAL_SETTING();
	OPTION_SERIAL_SETTING(const OPTION_SERIAL_SETTING &other);
	~OPTION_SERIAL_SETTING();

	OPTION_SERIAL_SETTING __fastcall operator=(const OPTION_SERIAL_SETTING &other);
	DWORD __fastcall GetBaudRate();
	BYTE __fastcall GetParity();
	unsigned char __fastcall GetDataBit();
	unsigned char __fastcall GetStopBit();
};

class OPTION_TEMP_PROFILE : public OPTION_BASE
{
protected:
	OPTION_TEMP_PROFILE_DEVIATION_ALARM	FTempProfileDeviationAlarm;
	OPTION_TEMP_PROFILE_CHANNEL			FTempChannel[MAX_LOGGER_POINT_COUNT];

protected:
    void __fastcall RegisterListValues() {}
	void __fastcall InitTempProfile();

	OPTION_TEMP_PROFILE_CHANNEL __fastcall GetTempChannel(int ch) const
	{
		OPTION_TEMP_PROFILE_CHANNEL profile = FTempChannel[ch];
		return profile;
	}
	void __fastcall SetTempChannel(int ch, OPTION_TEMP_PROFILE_CHANNEL value)
	{
		FTempChannel[ch] = value;
	}
	void __fastcall RegisterItemList();

public:
	__property OPTION_TEMP_PROFILE_DEVIATION_ALARM	TempProfileDeviationAlarm = { read = FTempProfileDeviationAlarm, write = FTempProfileDeviationAlarm };
	__property OPTION_TEMP_PROFILE_CHANNEL 			TempChannel[int ch] = { read = GetTempChannel, write = SetTempChannel };

public:
	OPTION_TEMP_PROFILE();
	OPTION_TEMP_PROFILE(const OPTION_TEMP_PROFILE &other);
	~OPTION_TEMP_PROFILE();

	OPTION_TEMP_PROFILE __fastcall operator=(const OPTION_TEMP_PROFILE &other);
	int __fastcall GetTempChannelCount();
};

class OPTION_COMM_SETTING : public OPTION_BASE
{
protected:
	OPTION_SERIAL_SETTING FMainTempCtrl;
	OPTION_SERIAL_SETTING FTempLogger;

protected:
	void __fastcall RegisterListValues() {}
	void __fastcall RegisterItemList();

public:
	__property OPTION_SERIAL_SETTING MainTempCtrl = { read = FMainTempCtrl, write = FMainTempCtrl };
	__property OPTION_SERIAL_SETTING TempLogger = { read = FTempLogger, write = FTempLogger };

public:
	OPTION_COMM_SETTING();
	OPTION_COMM_SETTING(const OPTION_COMM_SETTING &other);
	~OPTION_COMM_SETTING();

	OPTION_COMM_SETTING __fastcall operator=(const OPTION_COMM_SETTING &other);
};

class CHAMBER_OPTIONS : public OPTION_CONTAINER_BASE
{
protected:
	int FChamberID;

	OPTION_GENERAL                      FGeneral;
	OPTION_COMM_SETTING               	FCommSetting;
	OPTION_TEMP_PROFILE					FTempProfile;

protected:
	void __fastcall RegisterOptionList();
    void __fastcall SetDependency();

public:
	__property int	 					ChamberID = { read = FChamberID, write = FChamberID };
	__property OPTION_GENERAL			General = { read = FGeneral, write = FGeneral };
	__property OPTION_COMM_SETTING		CommSetting = { read = FCommSetting, write = FCommSetting };
	__property OPTION_TEMP_PROFILE		TempProfile = { read = FTempProfile, write = FTempProfile };

public:
	CHAMBER_OPTIONS();
	CHAMBER_OPTIONS(const CHAMBER_OPTIONS &other);
	CHAMBER_OPTIONS(int id);
	~CHAMBER_OPTIONS();

	CHAMBER_OPTIONS __fastcall operator=(const CHAMBER_OPTIONS &other);
};


#endif
