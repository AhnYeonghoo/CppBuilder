//---------------------------------------------------------------------------

#pragma hdrstop

#include "Defines.h"
#include "ChamberOptionDefines.h"
#include "HelperFunctions.h"
#include "SystemManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

OPTION_TEMP_PROFILE_CHANNEL::OPTION_TEMP_PROFILE_CHANNEL()
{
	Init();

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE_CHANNEL::OPTION_TEMP_PROFILE_CHANNEL(const OPTION_TEMP_PROFILE_CHANNEL &other)
{
	Channel = other.Channel;
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	Use = other.Use;
	Offset = other.Offset;
//	Color = other.Color;

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE_CHANNEL::OPTION_TEMP_PROFILE_CHANNEL(int ch)//, TColor color)
	: Channel(ch)
{
	Init();

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE_CHANNEL::~OPTION_TEMP_PROFILE_CHANNEL()
{
}

void __fastcall OPTION_TEMP_PROFILE_CHANNEL::Init()
{
	Name = L"Temp. Profile";
	FIsGroup = false;
	FDependentOption = nullptr;
	FDependentValue = 0;

	Use = OptionItem(GetRefName(), L"Use", false, false, true);
	Offset = OptionItem(GetRefName(), L"Offset", 0.0, -10.0, 10.0);
}

String __fastcall OPTION_TEMP_PROFILE_CHANNEL::GetSubIndex() const
{
	String str;
	str.sprintf(L" %d", Channel + 1);
    return str;
}

void __fastcall OPTION_TEMP_PROFILE_CHANNEL::RegisterItemList()
{
	OptionItemList.clear();
	OptionItemList.push_back(&FUse);
	OptionItemList.push_back(&FOffset);
}

OPTION_TEMP_PROFILE_CHANNEL __fastcall OPTION_TEMP_PROFILE_CHANNEL::operator=(const OPTION_TEMP_PROFILE_CHANNEL &other)
{
	Channel = other.Channel;
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	Use = other.Use;
	Offset = other.Offset;

	RegisterListValues();
	RegisterItemList();

	return *this;
}

OPTION_TEMP_PROFILE_DEVIATION_ALARM::OPTION_TEMP_PROFILE_DEVIATION_ALARM()
{
	Name = L"Temp. Profile Deviation Alarm";
	FIsGroup = false;
	FDependentOption = nullptr;
	FDependentValue = 0;

	for (int i = 0; i < MAX_LOGGER_POINT_COUNT; i++)
	{
		bool value = false;
		TDateTime time;
		FIsDeviationHighStarted.push_back(value);
		FIsDeviationLowStarted.push_back(value);
		FDeviationHighStartTime.push_back(time);
		FDeviationLowStartTime.push_back(time);
	}

	Use = OptionItem(FName, L"Use", false, false, true);
	AlarmEnableTime = OptionItem(FName, L"AlarmEnableTime", 10, 0, 10000);

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE_DEVIATION_ALARM::OPTION_TEMP_PROFILE_DEVIATION_ALARM(const OPTION_TEMP_PROFILE_DEVIATION_ALARM &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	Use = other.Use;
	AlarmEnableTime = other.AlarmEnableTime;

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE_DEVIATION_ALARM::~OPTION_TEMP_PROFILE_DEVIATION_ALARM()
{
}

void __fastcall OPTION_TEMP_PROFILE_DEVIATION_ALARM::RegisterItemList()
{
	OptionItemList.clear();
	OptionItemList.push_back(&FUse);
	OptionItemList.push_back(&FAlarmEnableTime);
}

OPTION_TEMP_PROFILE_DEVIATION_ALARM __fastcall OPTION_TEMP_PROFILE_DEVIATION_ALARM::operator=(const OPTION_TEMP_PROFILE_DEVIATION_ALARM &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	Use = other.Use;
	AlarmEnableTime = other.AlarmEnableTime;

	RegisterListValues();
	RegisterItemList();

	return *this;
}

void __fastcall OPTION_TEMP_PROFILE_DEVIATION_ALARM::Reset()
{
	OPTION_BASE::Reset();

	FIsDeviationHighStarted.clear();
	FIsDeviationLowStarted.clear();
	FDeviationHighStartTime.clear();
	FDeviationLowStartTime.clear();

}

bool __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::GetDeviationHighStarted(int idx)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		return FIsDeviationHighStarted[idx];
	}
	return false;
}

void __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::SetDeviationHighStarted(int idx, bool status)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		FIsDeviationHighStarted[idx] = status;
	}
}

bool __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::GetDeviationLowStarted(int idx)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		return FIsDeviationLowStarted[idx];
	}
	return false;
}

void __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::SetDeviationLowStarted(int idx, bool status)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		FIsDeviationLowStarted[idx] = status;
	}
}

TDateTime __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::GetDeviationHighStartTime(int idx)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		return FDeviationHighStartTime[idx];
	}
	return false;
}

void __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::SetDeviationHighStartTime(int idx, TDateTime time)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		FDeviationHighStartTime[idx] = time;
	}
}

TDateTime __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::GetDeviationLowStartTime(int idx)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		return FDeviationLowStartTime[idx];
	}
	return false;
}

void __fastcall
OPTION_TEMP_PROFILE_DEVIATION_ALARM::SetDeviationLowStartTime(int idx, TDateTime time)
{
	if( idx >=0 && idx < MAX_LOGGER_POINT_COUNT )
	{
		FDeviationLowStartTime[idx] = time;
	}
}

OPTION_GENERAL::OPTION_GENERAL()
{
	Name = L"General";
	FIsGroup = false;
	FDependentOption = nullptr;
	FDependentValue = 0;

//	CoolingWaterVentTime = OptionItem(FName, L"CoolingWaterVentTime", 10, 0, 10000);
	DoorOpenTempCondition = OptionItem(FName, L"DoorOpenTempCondition", 50, 0, 10000);

	RegisterListValues();
	RegisterItemList();
}

OPTION_GENERAL::OPTION_GENERAL(const OPTION_GENERAL &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

//	CoolingWaterVentTime = other.CoolingWaterVentTime;
	DoorOpenTempCondition = other.DoorOpenTempCondition;

	RegisterListValues();
	RegisterItemList();
}

OPTION_GENERAL::~OPTION_GENERAL()
{
}

void __fastcall OPTION_GENERAL::RegisterItemList()
{
	OptionItemList.clear();
//	OptionItemList.push_back(&FCoolingWaterVentTime);
	OptionItemList.push_back(&FDoorOpenTempCondition);
}

OPTION_GENERAL __fastcall OPTION_GENERAL::operator=(const OPTION_GENERAL &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

//	CoolingWaterVentTime = other.CoolingWaterVentTime;
	DoorOpenTempCondition = other.DoorOpenTempCondition;

    RegisterListValues();
	RegisterItemList();

	return *this;
}

#include "VaComm.hpp"
#define BAUDRATE_COUNT  5
#define PARITY_COUNT    3
#define DATABIT_COUNT   2
#define STOPBIT_COUNT   2
//unsigned char BaudRates[BAUDRATE_COUNT]	= { br9600, br19200, br38400, br57600, br115200 };
DWORD BaudRates[BAUDRATE_COUNT]	= { CBR_9600, CBR_19200, CBR_38400, CBR_57600, CBR_115200 };
BYTE ParityBits[PARITY_COUNT]	= { NOPARITY, ODDPARITY, EVENPARITY };
unsigned char DataBits[DATABIT_COUNT]	= { db7, db8 };
unsigned char StopBits[STOPBIT_COUNT]	= { sb1, sb2 };

OPTION_SERIAL_SETTING::OPTION_SERIAL_SETTING()
{
	Name = L"Serial Setting";
	FIsGroup = true;
	FDependentOption = nullptr;
	FDependentValue = 0;

	FUse		= OptionItem(FName, L"Use",			true, false, true);
	FAddr		= OptionItem(FName, L"Addr",		1, 1, 30);
	FBaudRate	= OptionItem(FName, L"BaudRate",	0, 0, BAUDRATE_COUNT - 1, NORMAL_LIST);
	FParity		= OptionItem(FName, L"Parity",		0, 0, PARITY_COUNT - 1, NORMAL_LIST);
	FDataBit	= OptionItem(FName, L"DataBit",		0, 0, DATABIT_COUNT - 1, NORMAL_LIST);
	FStopBit	= OptionItem(FName, L"StopBit",		0, 0, STOPBIT_COUNT - 1, NORMAL_LIST);
	FPortNo		= OptionItem(FName, L"PortNo",		1, 1, 100, COM_LIST);

	RegisterListValues();
	RegisterItemList();
}

OPTION_SERIAL_SETTING::OPTION_SERIAL_SETTING(const OPTION_SERIAL_SETTING &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	Use = other.Use;
	Addr = other.Addr;
	BaudRate = other.BaudRate;
	Parity = other.Parity;
	DataBit = other.DataBit;
	StopBit = other.StopBit;
	PortNo = other.PortNo;

	RegisterListValues();
	RegisterItemList();
}

OPTION_SERIAL_SETTING::~OPTION_SERIAL_SETTING()
{
}

DWORD __fastcall OPTION_SERIAL_SETTING::GetBaudRate()
{
	return BaudRates[FBaudRate];
}

BYTE __fastcall OPTION_SERIAL_SETTING::GetParity()
{
	return ParityBits[FParity];
}

unsigned char __fastcall OPTION_SERIAL_SETTING::GetDataBit()
{
	return DataBits[FDataBit];
}

unsigned char __fastcall OPTION_SERIAL_SETTING::GetStopBit()
{
	return StopBits[FStopBit];
}

void __fastcall OPTION_SERIAL_SETTING::RegisterItemList()
{
	OptionItemList.clear();
	OptionItemList.push_back(&FUse);
	OptionItemList.push_back(&FAddr);
	OptionItemList.push_back(&FBaudRate);
	OptionItemList.push_back(&FParity);
	OptionItemList.push_back(&FDataBit);
	OptionItemList.push_back(&FStopBit);
	OptionItemList.push_back(&FPortNo);
}

void __fastcall OPTION_SERIAL_SETTING::RegisterListValues()
{
	TStringList *list = new TStringList();
	GetSerialList(list);
	FPortNo.AssignValueList(list);

	list->Clear();
	list->Add(L"9600");
	list->Add(L"19200");
	list->Add(L"38400");
	list->Add(L"57600");
	list->Add(L"115200");
	FBaudRate.AssignValueList(list);

	list->Clear();
	list->Add(L"None");
	list->Add(L"Odd");
	list->Add(L"Even");
	FParity.AssignValueList(list);

	list->Clear();
	list->Add(L"7 Bit");
	list->Add(L"8 Bit");
	FDataBit.AssignValueList(list);

	list->Clear();
	list->Add(L"1 Bit");
	list->Add(L"2 Bit");
	FStopBit.AssignValueList(list);

	delete list;
}

OPTION_SERIAL_SETTING __fastcall OPTION_SERIAL_SETTING::operator=(const OPTION_SERIAL_SETTING &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	Use = other.Use;
	Addr = other.Addr;
	BaudRate = other.BaudRate;
	Parity = other.Parity;
	DataBit = other.DataBit;
	StopBit = other.StopBit;
	PortNo = other.PortNo;

    RegisterListValues();
	RegisterItemList();

	return *this;
}

OPTION_TEMP_PROFILE::OPTION_TEMP_PROFILE() : OPTION_BASE(true)
{
	Name = L"Temp. Profile";

	FTempProfileDeviationAlarm = OPTION_TEMP_PROFILE_DEVIATION_ALARM();
	InitTempProfile();

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE::OPTION_TEMP_PROFILE(const OPTION_TEMP_PROFILE &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FTempProfileDeviationAlarm = other.FTempProfileDeviationAlarm;

	for (int i = 0; i < MAX_LOGGER_POINT_COUNT; i++)
	{
		TempChannel[i] = other.TempChannel[i];
	}

	RegisterListValues();
	RegisterItemList();
}

OPTION_TEMP_PROFILE::~OPTION_TEMP_PROFILE()
{
}

void __fastcall OPTION_TEMP_PROFILE::RegisterItemList()
{
	OptionGroupList.clear();
	OptionGroupList.push_back(&FTempProfileDeviationAlarm);

	int count = MAX_LOGGER_POINT_COUNT;

	for (int i = 0; i < count; i++)
	{
		OptionGroupList.push_back(&FTempChannel[i]);
	}
}

OPTION_TEMP_PROFILE __fastcall OPTION_TEMP_PROFILE::operator=(const OPTION_TEMP_PROFILE &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FTempProfileDeviationAlarm = other.FTempProfileDeviationAlarm;

	for (int i = 0; i < MAX_LOGGER_POINT_COUNT; i++)
	{
		TempChannel[i] = other.TempChannel[i];
	}

	RegisterListValues();
	RegisterItemList();

	return *this;
}

void __fastcall OPTION_TEMP_PROFILE::InitTempProfile()
{
	for (int i = 0; i < MAX_LOGGER_POINT_COUNT; i++)
	{
		String str;
		str.sprintf(L"Temp. Profile %d", i + 1);
		FTempChannel[i] = OPTION_TEMP_PROFILE_CHANNEL(i);//, SeriesColor[i + 2]);
		FTempChannel[i].Name = str;
        FTempChannel[i].Offset = 0.0;
	}
}

int __fastcall OPTION_TEMP_PROFILE::GetTempChannelCount()
{
	int count = 0;
	for (int i = 0; i < MAX_LOGGER_POINT_COUNT; i++)
	{
		if (FTempChannel[i].Use)
		{
			count++;
		}
	}
	return count;
}

OPTION_COMM_SETTING::OPTION_COMM_SETTING() : OPTION_BASE(true)
{
	Name = L"Comm. Settings";
	FDependentOption = nullptr;
	FDependentValue = 0;

	MainTempCtrl = OPTION_SERIAL_SETTING();
	MainTempCtrl.Name = L"MainTempCtrl";
	MainTempCtrl.Addr = 1;
	MainTempCtrl.BaudRate = 0;
	MainTempCtrl.Parity = 2;
	MainTempCtrl.DataBit = 1;
	MainTempCtrl.StopBit = 0;
	MainTempCtrl.PortNo = 3;

	TempLogger = OPTION_SERIAL_SETTING();
	TempLogger.Name = L"TempLogger";
	TempLogger.Addr = 1;
	TempLogger.BaudRate = 1;
	TempLogger.Parity = 0;
	TempLogger.DataBit = 1;
	TempLogger.StopBit = 0;
	TempLogger.PortNo = 4;

	RegisterListValues();
	RegisterItemList();
}

OPTION_COMM_SETTING::OPTION_COMM_SETTING(const OPTION_COMM_SETTING &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	MainTempCtrl = other.MainTempCtrl;
	TempLogger = other.TempLogger;

	RegisterListValues();
	RegisterItemList();
}

OPTION_COMM_SETTING::~OPTION_COMM_SETTING()
{
}

void __fastcall OPTION_COMM_SETTING::RegisterItemList()
{
	OptionGroupList.clear();
	OptionGroupList.push_back(&FMainTempCtrl);
	OptionGroupList.push_back(&FTempLogger);
}

OPTION_COMM_SETTING __fastcall OPTION_COMM_SETTING::operator=(const OPTION_COMM_SETTING &other)
{
	Name = other.Name;
	FIsGroup = other.IsGroup;
	FDependentOption = other.DependentOption;
	FDependentValue = other.DependentValue;

	MainTempCtrl = other.MainTempCtrl;
	TempLogger = other.TempLogger;

	RegisterListValues();
	RegisterItemList();

	return *this;
}

CHAMBER_OPTIONS::CHAMBER_OPTIONS()
{
	ChamberID = 0;
	Filename.sprintf(L"Chamber_%c.ini", 'A' + ChamberID);

	General = OPTION_GENERAL();
	CommSetting = OPTION_COMM_SETTING();
	TempProfile = OPTION_TEMP_PROFILE();

	RegisterOptionList();
	Load();
	SetDependency();
}

CHAMBER_OPTIONS::CHAMBER_OPTIONS(const CHAMBER_OPTIONS &other)
{
	ChamberID = other.ChamberID;
	Filename = other.Filename;

	General = other.General;
	CommSetting = other.CommSetting;
	TempProfile = other.TempProfile;

	RegisterOptionList();
}

CHAMBER_OPTIONS::CHAMBER_OPTIONS(int id) : ChamberID(id)
{
	Filename.sprintf(L"Chamber_%c.ini", 'A' + ChamberID);

	General = OPTION_GENERAL();
	CommSetting = OPTION_COMM_SETTING();
	TempProfile = OPTION_TEMP_PROFILE();

	RegisterOptionList();
	Load();
	SetDependency();
}

CHAMBER_OPTIONS::~CHAMBER_OPTIONS()
{
}

void __fastcall CHAMBER_OPTIONS::SetDependency()
{

}

 void __fastcall CHAMBER_OPTIONS::RegisterOptionList()
{
	OptionList.clear();
	OptionList.push_back(&FGeneral);
	OptionList.push_back(&FCommSetting);
	OptionList.push_back(&FTempProfile);
}

CHAMBER_OPTIONS __fastcall CHAMBER_OPTIONS::operator=(const CHAMBER_OPTIONS &other)
{
	ChamberID = other.ChamberID;
	Filename = other.Filename;

	General = other.General;
	CommSetting = other.CommSetting;
	TempProfile = other.TempProfile;

	RegisterOptionList();
	return *this;
}
