//---------------------------------------------------------------------------

#include <memory>
#include <System.IniFiles.hpp>
#include <System.Math.hpp>
#pragma hdrstop

#include "TowerLampControl.h"
#include "HelperFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/* 생성자 정의 */
TowerLampControl::TowerLampControl()
{
}

/* 소멸자 정의 */
TowerLampControl::~TowerLampControl()
{
}

/* 비교 연산자 오버로딩 */
bool TowerLampControl::operator==(const TowerLampControl& arg)
{
	auto bRet = true;

	for (int i = 0; i < TWR_COUNT; i++)
	{
		for (int j = 0; j < TWR_MODE_COUNT; j++)
		{
			auto nSetVal = arg.GetTwrVal(i, j);
			if (nSetVal != nTowerVal[i][j])
			{
				bRet = false;
				break;
			}
		}
	}
	return bRet;
}

/* 복사 대입 연산자 정의 */
TowerLampControl& TowerLampControl::operator=(const TowerLampControl& arg)
{
	for (int i = 0; i < TWR_COUNT; i++)
	{
		for (int j = 0; j < TWR_MODE_COUNT; j++)
		{
			int nSetVal = arg.GetTwrVal(i, j);
			SetTwrVal(i, j, nSetVal);
		}
	}
	return *this;
}

/* 램프 값을 초기화 해주는 함수 */
void TowerLampControl::LoadValue(const auto sPath)
{
	std::shared_ptr<TIniFile> TowerLampFile(new TIniFile(sPath));
	const auto sSection = "TOWER_LAMP";

	if (TowerLampFile->SectionExists(sSection) == false)         // TOWER_LAMP 파일이 없으면
	{
		nTowerVal[TWR_RED][TWR_AUTORUN] = LAMP_OFF;
		nTowerVal[TWR_RED][TWR_STOP] = LAMP_OFF;
		nTowrVal[TWR_RED][TWR_LOTEND] = LAMP_OFF;
		nTowrVal[TWR_RED][TWR_ERR] = LAMP_ON;

		nTowerVal[TWR_YEL][TWR_AUTORUN] = LAMP_OFF;
		nTowerVal[TWR_YEL][TWR_STOP] = LAMP_ON;
		nTowerVal[TWR_YEL][TWR_LOTEND] = LAMP_OFF;
		nTowerVal[TWR_YEL][TWR_ERR] = LAMP_OFF;

		nTowerVal[TWR_GRN][TWR_AUTORUN] = LAMP_ON;
		nTowerVal[TWR_GRN][TWR_STOP] = LAMP_OFF;
		nTowerVal[TWR_GRN][TWR_LOTEND] = LAMP_BLINK;
		nTowerVal[TWR_GRN][TWR_ERR] = LAMP_OFF;

		nTowerVal[TWR_BUZ][TWR_AUTORUN] = BUZZ_OFF;
		nTowerVal[TWR_BUZ][TWR_STOP] = BUZZ_OFF;
		nTowerVal[TWR_BUZ][TWR_LOTEND] = BUZZ_ALARM;
		nTowerVal[TWR_BUZ][TWR_ERR] = BUZZ_ALARM;

		SaveValue(sPath);
	}
	else                  // Ini 파일이 존재하면!
	{
		try
		{
			// 파일에서 값을 읽어와 int 값을 할당한다.
			nTowerVal[TWR_RED][TWR_AUTORUN] = TowerLampFile->ReadInteger(sSection, "RED[AUTO_RUN]", nTowerVal[TWR_RED][TWR_AUTORUN]);
			nTowerVal[TWR_RED][TWR_STOP] = TowerLampFile->ReadInteger(sSection, "RED[STOP]", nTowerVal[TWR_RED][TWR_STOP]);
			nTowerVal[TWR_RED][TWR_LOTEND] = TowerLampFile->ReadInteger(sSection, "RED[LOTEND]", nTowerVal[TWR_RED][TWR_LOTEND]);
			nTowerVal[TWR_RED][TWR_ERR] = TowerLampFile->ReadInteger(sSection, "RED[ERR]", nTowerVal[TWR_RED][TWR_ERR]);

			nTowerVal[TWR_YEL][TWR_AUTORUN] = TowerLampFile->ReadInteger(sSection, "YELLOW[AUTO_RUN]", nTowerVal[TWR_YEL][TWR_AUTORUN]);
			nTowerVal[TWR_YEL][TWR_STOP] = TowerLampFile->ReadInteger(sSection, "YELLOW[STOP]", nTowerVal[TWR_YEL][TWR_STOP]);
			nTowerVal[TWR_YEL][TWR_LOTEND] = TowerLampFile->ReadInteger(sSection, "YELLOW[LOTEND]", nTowerVal[TWR_YEL][TWR_LOTEND]);
			nTowerVal[TWR_YEL][TWR_ERR] = TowerLampFile->ReadInteger(sSection, "YELLOW[ERR]", nTowerVal[TWR_YEL][TWR_ERR]);

			nTowerVal[TWR_GRN][[TWR_AUTORUN] = TowerLampFile->ReadInteger(sSection, "GREEN[AUTO_RUN]", nTowerVal[TWR_GRN][TWR_AUTORUN]);
			nTowerVal[TWR_GRN][TWR_STOP] = TowerLampFile->ReadInteger(sSection, "GREEN[STOP]", nTowerVal[TWR_GRN][TWR_STOP]);
			nTowerVal[TWR_GRN][TWR_LOTEND] = TowerLampFile->ReadInteger(sSection, "GREEN[LOTEND]", nTowerVal[TWR_GRN][TWR_LOTEND]);
			nTowerVal[TWR_GRN][TWR_ERR] = TowerLampFile->ReadInteger(sSection, "GREEN[ERR]", nTowerVal[TWR_GRN][TWR_ERR]);

			nTowerVal[TWR_BUZ][TWR_AUTORUN] = TowerLampFile->ReadInteger(sSection, "BUZZER[AUTO_RUN]", nTowerVal[TWR_BUZ][TWR_AUTORUN]);
			nTowerVal[TWR_BUZ][TWR_STOP] = TowerLampFile->ReadInteger(sSection, "BUZZER[STOP]", nTowerVal[TWR_BUZ][TWR_STOP]);
			nTowerVal[TWR_BUZ][TWR_LOTEND] = TowerLampFile->ReadInteger(sSection, "BUZZER[LOTEND]", nTowerVal[TWR_BUZ][TWR_LOTEND]);
			nTowerVal[TWR_BUZ][TWR_ERR] = TowerLampFile->ReadInteger(sSection, "BUZZER[ERR]", nTowerVal[TWR_BUZ][TWR_ERR]);
		}
		catch (Exception* e)
		{
			SetMessageStr(e->Message);
			ShowMessageDlg();
        }
	}
}

/* 파일에 값을 작성하는 함수 */
void TowerLampControl::SaveValue(const auto sPath)
{
	std::shared_ptr<TIniFile> TowerLampFile(new TIniFile(sPath));
	const auto sSection = "TOWER_LAMP";

	// 파일을 읽고 쓸 때는 항상 try catch 문으로 예외 처리를 해주어야 한다.
	try
	{
		TowerLampFile->WriteInteger(sSection, "RED[AUTO_RUN]", nTowerVal[TWR_RED][TWR_AUTORUN]);
		TowerLampFile->WriteInteger(sSection, "RED[STOP]", nTowerVal[TWR_RED][TWR_STOP]);
		TowerLampFile->WriteInteger(sSection, "RED[LOTEND]", nTowerVal[TWR_RED][TWR_LOTEND]);
		TowerLampFile->WriteInteger(sSection, "RED[ERR]", nTowerVal[TWR_RED][TWR_ERR]);

		TowerLampFile->WriteInteger(sSection, "YELLOW[AUTO_RUN]", nTowerVal[TWR_YEL][TWR_AUTORUN]);
		TowerLampFile->WriteInteger(sSection, "YELLOW[STOP]", nTowerVal[TWR_YEL][TWR_STOP]);
		TowerLampFile->WriteInteger(sSection, "YELLOW[LOTEND]", nTowerVal[TWR_YEL][TWR_LOTEND]);
		TowerLampFile->WriteInteger(sSection, "YELLOW[ERR]", nTowerVal[TWR_YEL][TWR_ERR]);

		TowerLampFile->WriteInteger(sSection, "GREEN[AUTO_RUN]", nTowerVal[TWR_GRN][TWR_AUTORUN]);
		TowerLampFile->WriteInteger(sSection, "GREEN[STOP]", nTowerVal[TWR_GRN][TWR_STOP]);
		TowerLampFile->WriteInteger(sSection, "GREEN[LOTEND]", nTowerVal[TWR_GRN][TWR_LOTEND]);
		TowerLampFile->WriteInteger(sSection, "GREEN[ERR]", nTowerVal[TWR_GRN][TWR_ERR]);

		TowerLampFile->WriteInteger(sSection, "BUZZER[AUTO_RUN]", nTowerVal[TWR_BUZ][TWR_AUTORUN]);
		TowerLampFile->WriteInteger(sSection, "BUZZER[STOP]", nTowerVal[TWR_BUZ][TWR_STOP]);
		TowerLampFile->WriteInteger(sSection, "BUZZER[LOTEND]", nTowerVal[TWR_BUZ][TWR_LOTEND]);
		TowerLampFile->WriteInteger(sSection, "BUZZER[ERR]", nTowerVal[TWR_BUZ][TWR_ERR]);
	}
	catch (Exception* e)
	{
		SetMessageStr(e->Message);
		ShowMessageDlg();
    }

}

/* 현재 Tower Lamp 값을 가져온다 */
int TowerLampControl::GetTwrVal(const auto nKind, const auto nMode, const auto nVal) const
{
	if (!InRange(nKind, TWR_RED, TWR_COUNT - 1))
		return -1;

	if (!InRange(nMode, TWR_AUTORUN, TWR_MODE_COUNT - 1))
		return -1;

	auto nRet = nTowerVal[nKind][nMode];
	return nRet;
}

/* Tower Lamp 값을 설정한다 */
void TowerLampControl::SetTwrVal(const auto nKind, const auto nMode, const auto nVal)
{
	if (!InRange(nKind, TWR_RED, TWR_COUNT - 1))
	{
		return;
	}

	if (!InRange(nKind, TWR_AUTORUN, TWR_MODE_COUNT - 1))
	{
		return;
	}
	nTowrVal[nKind][nMode] = nVal;
}

/* Tower Lamp의 Mode 종류를 [] String 안에 넣고 반환한다 */
auto TowerLampControl::GetTwrValStr(const auto nKind) const
{
	auto sVal = "[";
	for (auto i = 0; i < TWR_MODE_COUNT; i++)
	{
		sVal += nTowerVal[nKind][i];
	}
	sVal += "]";
	return sVal;
}