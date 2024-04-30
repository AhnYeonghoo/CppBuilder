//---------------------------------------------------------------------------
#include <vcl.h>
#include "System.Math.hpp"
#include "AXL\AXL.h"
#include "AXL\AXD.h"
#include "AXL\AXA.h"

#pragma hdrstop

#include "uAxlIoCtrl.h"
#include "VsLogLib.h"
#include "uIoCtrl.h"
#include "VS_UTILS.H"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace VSP;

bool OpenAxlLib(void)
{
    DWORD Code = AxlOpenNoReset(7);
    if (Code == AXT_RT_SUCCESS)
    {
        return true;//AxlLibInit = true;
#ifdef _DEBUG
        AxlSetLogLevel(LEVEL_FUNCTION);
#endif
    }
    else
    {
        ShowMsg(L"AxlOpen() fail");
        return false;
    }
}
//---------------------------------------------------------------------------

void CloseAxlLib(void)
{
    AxlClose();
}
//---------------------------------------------------------------------------

/* ==========================================================================
	CAxlDioCtrl Class
========================================================================== */
bool CAxlDioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::OpenDevice()
{
	InitBuffer();

	TModuleInfo ModInfo;

    DWORD dwStatus;
    DWORD dwCode = AxdInfoIsDIOModule(&dwStatus);

	if(dwCode != AXT_RT_SUCCESS)
	{
		ShowMsg(L"AxdInfoIsDIOModule() Fail");
		return;
	}

	long lModuleCnt;
	dwCode = AxdInfoGetModuleCount(&lModuleCnt);
	if(dwCode != AXT_RT_SUCCESS)
	{
		ShowMsg(L"AxdInfoGetModuleCount() Fail");
		return;
	}

	for(long i = 0; i < lModuleCnt; i++)
	{
		long lBoardNo, lModulePos;
		DWORD dwModuleID;

		dwCode = AxdInfoGetModule(i, &lBoardNo, &lModulePos, &dwModuleID);
		if(dwCode != AXT_RT_SUCCESS)
		{
			ShowMsg(L"AxdInfoGetModule() Fail");
            return;
        }

        ModInfo.sModuleNo = (short)i;
        if(dwModuleID == AXT_SIO_DO32P || dwModuleID == AXT_SIO_DO32T)
        {
            ModInfo.sByteCnt = 4;
			m_vDoModule.push_back(ModInfo);
			LOG_PRINTF(m_strLogHead, L"vDo push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DO32P", ModInfo.sModuleNo, ModInfo.sByteCnt);
		}
		else if(dwModuleID == AXT_SIO_DB32P || dwModuleID == AXT_SIO_DB32T)
		{
			ModInfo.sByteCnt = 2;
			m_vDiModule.push_back(ModInfo);
			LOG_PRINTF(m_strLogHead, L"vDi push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DB32P", ModInfo.sModuleNo, ModInfo.sByteCnt);
			m_vDoModule.push_back(ModInfo);
			LOG_PRINTF(m_strLogHead, L"vDo push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DB32P", ModInfo.sModuleNo, ModInfo.sByteCnt);
		}
		else if(dwModuleID == AXT_SIO_DI32)
		{
			ModInfo.sByteCnt = 4;
			m_vDiModule.push_back(ModInfo);
			LOG_PRINTF(m_strLogHead, L"vDi push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DI32", ModInfo.sModuleNo, ModInfo.sByteCnt);
        }
    }

    m_bConnected = true;
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::CloseDevice()
{

}
//---------------------------------------------------------------------------

void CAxlDioCtrl::InitBuffer()
{
	m_vDiModule.clear();
	m_vDoModule.clear();
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::ReadDiModule(void)
{
	int BufIdx = 0;
    DWORD dwVal;
	for(size_t i = 0; i < m_vDiModule.size(); i++)
	{
		for(int nOffset = 0; nOffset < m_vDiModule.at(i).sByteCnt; nOffset++, BufIdx++)
		{
			if(m_bConnected)
            {
				AxdiReadInportByte(m_vDiModule.at(i).sModuleNo, nOffset, &dwVal);
                rdCifData[BufIdx] = dwVal & 0xFF;
            }
			else
            {
				rdMachineData[BufIdx] = rdCifData[BufIdx];
            }
//			#ifdef _DEBUG
//			LOG_PRINTF(m_strLogHead, L"rdDiData[%d] Val:%d = [Mod.ID:%d, Offset.:%d]", BufIdx, rdDiData[BufIdx], m_vDiModule.at(i).sModuleNo, nOffset);
//			#endif
		}
	}
	memcpy(rdMachineData, rdCifData, m_vDiModule.size() );
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::ReadDoModule(void)
{
	int BufIdx = 0;
    DWORD dwVal;
	for(size_t i = 0; i < m_vDoModule.size(); i++)
	{
		for(int nOffset = 0; nOffset < m_vDoModule.at(i).sByteCnt; nOffset++, BufIdx++)
		{
			if(m_bConnected)
            {
				AxdoReadOutportByte(m_vDoModule.at(i).sModuleNo, nOffset, &dwVal);
                wrCifData[BufIdx] = dwVal & 0xFF;
            }
			else
            {
				wrCifData[BufIdx] = wrMachineData[BufIdx];
            }
//			#ifdef _DEBUG
//			LOG_PRINTF(m_strLogHead, L"rdDoData[%d] Val:%d = [Mod.ID:%d, Offset.:%d]", BufIdx, rdDoData[BufIdx], m_vDoModule.at(i).sModuleNo, nOffset);
//			#endif
		}
	}
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::WriteDoModule(void)
{
	int BufIdx = 0;
	for(size_t i = 0; i < m_vDoModule.size(); i++)
	{
		for(int nOffset = 0; nOffset < m_vDoModule.at(i).sByteCnt; nOffset++, BufIdx++)
		{
			if(wrCifData[BufIdx] != wrMachineData[BufIdx])
				AxdoWriteOutportByte(m_vDoModule.at(i).sModuleNo, nOffset, (DWORD)wrMachineData[BufIdx]);
//			#ifdef _DEBUG
//			LOG_PRINTF(m_strLogHead, L"rdDoData[%d] Val:%d = [Mod.ID:%d, Offset.:%d]", BufIdx, rdDoData[BufIdx], m_vDoModule.at(i).sModuleNo, nOffset);
//			#endif
		}
	}

}
//---------------------------------------------------------------------------


bool CAxlDioCtrl::IsOn(const int nIdx, const bool IsOut /*= false*/)
{
	DWORD dwVal;

    if(IsOut)
        AxdoReadOutport(nIdx, &dwVal);
    else
        AxdiReadInport(nIdx, &dwVal);

	return (bool)dwVal;
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::SetBit(const int nIdx, const bool bOn, const bool IsOut /*= true*/)
{
	if(IsOut)
		AxdoWriteOutport(nIdx, (DWORD)bOn);

}
//---------------------------------------------------------------------------

BYTE CAxlDioCtrl::GetByte(const int nIdx, const bool IsOut /*= false*/)
{
	if(IsOut)
	{
		ReadDoModule();
		return wrCifData[nIdx];
	}
	else
	{
		ReadDiModule();
		return rdCifData[nIdx];
	}
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut /*= true*/)
{
	if(InRange(nIdx, 0, AO_START-1) && IsOut)
	{
		wrMachineData[nIdx] = byVal;
		WriteDoModule();
	}
	else
	{
		LOG_PRINTF(m_strLogHead, L"SetByteVal Index Range Over uIdx = %d", nIdx);
	}
}
//---------------------------------------------------------------------------

WORD CAxlDioCtrl::GetWord(const int nIdx, const WORD wRange /*= 0x00*/, const bool IsOut /*= false*/)
{
	WORD wRet = 0x00;
	UINT nWordIdx = nIdx * 2;

//short s = 0x3210;
//char c1 = s >> 8;
//char c2 = s & 0x00ff;
	if(IsOut)
	{
		ReadDoModule();
		wRet = MAKEWORD(wrCifData[nWordIdx], wrCifData[nWordIdx+1]);
	#ifdef _DEGUG
		 LOG_PRINTF(m_strLogHead, L"[%02X, %02X -> %d]", wrCifData[nWordIdx], wrCifData[nWordIdx+1], wRet);
	#endif
	}
	else
	{
		ReadDiModule();
		wRet = MAKEWORD(rdCifData[nWordIdx], rdCifData[nWordIdx+1]);
	#ifdef _DEGUG
		 LOG_PRINTF(m_strLogHead, L"[%02X, %02X -> %d]", rdCifData[nWordIdx], rdCifData[nWordIdx+1], wRet);
	#endif
	}

	return wRet;
}
//---------------------------------------------------------------------------

void CAxlDioCtrl::SetWordVal(const int nIdx, const WORD wVal, const bool IsOut /*= true*/)
{
	if(InRange(nIdx, 0, AO_START - 2) && IsOut)
	{
		UINT nWordIdx = nIdx * 2;
		BYTE byShift[2];
		byShift[0] = wVal & 0x00FF;
		byShift[1] = (wVal >> 8) & 0x00FF;

		memcpy(&wrMachineData[nWordIdx], &byShift, sizeof(WORD) );
		WriteDoModule();
	}
	else
	{
		LOG_PRINTF(m_strLogHead, L"SetWordVal Index Range Over uIdx = %d", nIdx);
	}
}
//---------------------------------------------------------------------------

/* ==========================================================================
	CAxlAioCtrl Class
========================================================================== */
CAxlAioCtrl::CAxlAioCtrl()
	: m_bConnected(false), m_lChCount(4)
{
	OpenDevice();
}
//---------------------------------------------------------------------------

bool CAxlAioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------

void CAxlAioCtrl::OpenDevice()
{
    DWORD dwStatus;
    AxaInfoIsAIOModule(&dwStatus);

	if(dwStatus != STATUS_EXIST)
	{
		ShowMsg(L"AxaInfoIsAIOModule() Fail");
		return;
	}

	DWORD dwCode = AxaInfoGetOutputCount(0, &m_lChCount);
	if(dwCode != AXT_RT_SUCCESS)
	{
		ShowMsg(L"AxaInfoGetOutputCount() Fail");
        return;
	}

	m_bConnected = true;
}
//---------------------------------------------------------------------------

void CAxlAioCtrl::CloseDevice()
{

}
//---------------------------------------------------------------------------

void CAxlAioCtrl::SetDaConfig(const int nIdx, const double dMax)
{
	if(InRange(nIdx, 0, m_lChCount - 1) )
	{
		AxaoSetRange(nIdx, 0.0, dMax);
	}
}
//---------------------------------------------------------------------------

bool CAxlAioCtrl::WriteAnalogVal(const int nIdx, const double dVal)
{
	if(InRange(nIdx, 0, m_lChCount - 1) )
	{
		DWORD dwRet = AxaoWriteVoltage(nIdx, dVal);

		return (dwRet == AXT_RT_SUCCESS);
	}

	return false;
}
//---------------------------------------------------------------------------
double CAxlAioCtrl::GetMaxRange(const int nIdx)
{
	double dMin = 0.0;
	double dMax = 0.0;

	AxaoGetRange(nIdx, &dMin, &dMax);

	return dMax;
}

double CAxlAioCtrl::GetWriteAnalogVal(const int nIdx)
{
	double dVolt = 0.0;

	AxaoReadVoltage(nIdx, &dVolt);

	return dVolt;
}
