//---------------------------------------------------------------------------


#include"SystemManager.h"
#include <memory>
#include <System.hpp>
#include <vcl.h>
#include "VaClasses.hpp"
#include "VaComm.hpp"

#pragma hdrstop

#include "HelperFunctions.h"
#include "MainTempController.h"
#include "Chamber.h"
#include "SystemManager.h"
#include "LimitController.h"
#include "ST340.h"
#include "VXSeries.h"
#include "I7018.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

unsigned int Colors[MAX_COLOR_COUNT] =
{
	0x00FF0000,
    0x00003300,
	0x0000CC00,
	0x00CCCC00,
	0x00666600,
	0x00FF6600,
	0x00FF0099,
	0x00330099,
	0x009966FF,
	0x00330066,
	0x009900FF,
	0x009900CC,
	0x009999CC,
	0x003399CC,
	0x00FF00FF,
	0x005577DD,
	0x00000000,
	0x000000FF
};

String ChamberStr[CHAMBER_COUNT] =
{
	"Chamber A",
	"Chamber B",
	"Chamber C",
	"Chamber D"
};


String LevelStr[LV_COUNT] =
{
	"",
	"Operator",
	"Enginner",
	"Supervisor",
	"Developer"
};

String AutomationKindStr[AUTOMATIONKIND_COUNT]
{
	"SECS/GEM",
	"Amkor eCIM",
	"SFA ATK",
	"SCK Traceability",
	"Barun MES",
	"ITM Semicon",
	"O-Film MES",
	"MinebeaMitsumi",
	"SCK MES",
	"T-Card Recipe Loading",
	"HANA CIM",
	"Fujitsu T-Card",
	"SECS/GEM AMD",
	"SECS/GEM COWELL",
	"SECS/GEM SCK"
};

String MotorDirectionStr[DIRECTION_COUNT]
{
  "CCW",
  "CW"
};

FTPConnectInfo ftpConnectInfo;

// 생성자 정의
SystemManagerBase::SystemManagerBase()
{
	FLoginLevel = -1;
	FChamberCount = 1;
	FLanguage = ENG;
	FUseAutomationKind = SECS_GEM;
	FUseRemoteCheck = false;
	FUseScreenSaver = false;
	FScreenSaverTime = 60;
	FIsShowLoginForm = false;
	FOperatorID = "";
}

SystemManagerBase::~SystemManagerBase()
{
}

void SystemManagerBase::SetLanguage(int language)
{
	FLanguage = language;

	switch ( FLanguage )
	{
		case KOR:
			LangTag = KOR_TAG;
			break;
		case ENG:
			LangTag = ENG_TAG;
			break;
		case CHN:
			LangTag = CHN_TAG;
			break;
		default:
			LangTag = KOR_TAG;
			break;
	}
}

BaseChamber* SystemManagerBase::GetAChamber(int chamberId)
{
	// 챔버 종류 안에 들어오고, 챔버 개수에 들어온다면
	// chamberId에 해당하는 Chamber 객체를 반환한다.
	// 아니면 빈 객체 반환
	if (chamberId >= CHAMBER_A &&  chamberId < FChamberCount )
	{
		return (OvenChamber*)FChamber[chamberId];
	}
	return nullptr;
}

OvenSystemManagerBase::OvenSystemManagerBase()
{
	// 챔버 개수만큼 챔버 객체를 초기화한다.
	for (int i = 0; i < MAX_CHAMBER_COUNT; i++)
	{
		FChamber[i] = nullptr;
	}

	SetLanguage(KOR);

	FLoginLevel = LV_NONE;
	FMainTempCtrlTimeout = 2000;
	FLimitCtrlTimeout = 2000;
	FLoggerTimeout = 2000;
	FMaxTemp = 3000;
}

OvenSystemManagerBase::~OvenSystemManagerBase()
{
	DestroySerialDevices();
}

DevMainTempController* OvenSystemManagerBase::CreateMainTempController(OvenChamber* chamber, PORTINFO portInfo)
{
	DevMainTempController *mainCtrl = nullptr;

	// 일단은 두 개의 종류의 메인 컨트롤러만 사용하나 보다.
	if (chmaber->MaintempControllerType == TEMPCTRL_UP550)
	{
		mainCtrl = new UP550(chamber, portInfo);
	}
	else if (chamber->MainTempControllerType == TEMPCTRL_UP55A)
	{
		mainCtrl = new UP55A(chamber, portInfo);
	}
	return mainCtrl;
}

DevLimitController* OvenSystemManagerBase::CreateLimitController(OvenChamber* chamber, PORTINFO portInfo, int limitType)
{
	DevLimitController* limitCtrl = nullptr;

	if (chamber->LimitControllerType == LIMIT_ST)
	{
		limitCtrl = new ST340(chamber, portInfo, limitType);
	}
	else if (chamber->LimitControllerType == LIMIT_VX)
	{
		limitCtrl = new VXSeries(chamber, portInfo, limitType);
	}

	return limitCtrl;
}

bool OvenSystemManagerBase::CreateSerialDevices()
{
	return true;
}

void OvenSystemManagerBase::DestroySerialDevices()
{
	for (int i = 0; i < FChamberCount; i++)
	{
		OvenChamber* chmaber = (OvenChamber*)FChamber[i];
		if (chamber)
		{
			if (chamber->MainTempController)
			{
				delete chamber->MainTempController;
				chamber->MainTempController = nullptr;
			}

			if (chmaber->ChamberTempLimitController)
			{
				delete chamber->ChamberTempLimitController;
				chmaber->ChamberTempLimitController = nullptr;
			}

			for (int j = 0; j < FLoggerCount; j++)
			{
				if (chamber->LoggerController[j])
				{
					delete chamber->LoggerController[j];
					chamber->LoggerController[j] = nullptr;
                }
            }
        }
    }
}

// 처음에 프로그램 실행할 때 로그 폴더 생성해주는 함수
void OvenSystemManagerBase::InitDirectory(String PrgName)
{
	FProgramName = PrgName;

	AnsiString sDrive;
	String root, data, log, report, remote, FTP, product;

	root = GetRootFolder();
	data = GetDataFolder();
	log = GetLogFolder();
	report = GetReportFolder();
	remote = GetRemotPatterneFolder();
	FTP = GetFTPDataFolder();
	product = GetProductFolder();

	// 폴더가 존재하는지 검사
	if (!DirectoryExists(root))
	{
		// 폴더를 생성시켜봄
		if (!CreateDir(root))
		{
			throw (Exception(PrgName+ " folder creation fail."));
		}
	}

	if (!DirectoryExists(data))
	{
		if (!CreateDir(data))
		{
			throw (Exception(PrgName + "folder creation fail."));
        }
	}

    if( !DirectoryExists(log) )
	{
		if( !CreateDir(log) )
			throw (Exception("LOG folder creation fail."));
	}

	if( !DirectoryExists(report) )
	{
		if( !CreateDir(report) )
			throw (Exception("REPORT folder creation fail."));
	}

	if( !DirectoryExists(remote) )
	{
		if( !CreateDir(remote) )
			throw (Exception("REMOTE PATTERN folder creation fail."));
	}

	if( !DirectoryExists(FTP) )
	{
		if( !CreateDir(FTP) )
			throw (Exception("FTP Data File folder creation fail."));
	}

	if( !DirectoryExists(product) )
	{
		if( !CreateDir(product) )
			throw (Exception("PRODUCT folder creation fail."));
	}

	AnsiString sTemp;

	for (int i = 0; i < FChamberCount; i++)
	{
		sTemp.sprintf(PATTERN_FILE, 'A' + i);
		sTemp = root + sTemp;
		if (!DirectoryExists(sTemp))
		{
			if (!CreateDir(sTemp))
			{
				throw (Exception(sTemp + " folder creation fail."));
            }
        }
	}

	String srcFolder = ExtractFilePath(Application->ExeName);
	String dstFile = data + OVENDB;
	String srcFile = srcFolder + OVENDB;
	if (FileExists(dstFile) == false)
	{
		CopyFile(srcFile.c_str(), dstFile.c_str(), true);
	}

	dstFile = data + ERRDEFDB;
	srcFile = srcFolder + ERRDEFDB;
	CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + LANGUAGEINI;
	srcFile = srcFolder + LANGUAGEINI;
	CopyFile(srcFile.c_str(), dstFile.c_str(), false):

	dstFile = data + OVENSYSTEMINI;
	srcFile = srcFolder + OVENSYSTEMINI;
	if (FileExists(dstFile) == false)
	{
		CopyFile(srcFile.c_str(), dstFile.c_str(), true);
	}

    dstFile = data + "ALID.TXT";
	srcFile = srcFolder + "ALID.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "ALID_COWELL.TXT";
	srcFile = srcFolder + "ALID_COWELL.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "CEID.TXT";
	srcFile = srcFolder + "CEID.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "RPTID.TXT";
	srcFile = srcFolder + "RPTID.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "SVID.TXT";
	srcFile = srcFolder + "SVID.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "FORMAT.SML";
	srcFile = srcFolder + "FORMAT.SML";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "CEID_JSCK.TXT";
	srcFile = srcFolder + "CEID_JSCK.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "RPTID_JSCK.TXT";
	srcFile = srcFolder + "RPTID_JSCK.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);

	dstFile = data + "SVID_JSCK.TXT";
	srcFile = srcFolder + "SVID_JSCK.TXT";
//	if( FileExists(dstFile) == false )
		CopyFile(srcFile.c_str(), dstFile.c_str(), false);
}
