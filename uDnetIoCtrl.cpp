//---------------------------------------------------------------------------
#include <vcl.h>
#include <Math.hpp>
#include "CIF\CIFUSER.H"
#include <bitset>

#pragma hdrstop

#include "uDnetIoCtrl.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace VSP;

CCifThread* ReadWriteCifTh;

uint16_t GetOutBytesCnt(void)
{
	if(SysOption->GetGasOverThree() )
		return 20;
	else
		return 16;
}
/* ==========================================================================
	CCifThread Class
========================================================================== */
void __fastcall CCifThread::Execute()
{
	CDnetDioCtrl *pObj = (CDnetDioCtrl *)FdwUser;

	while(!FbExit)
	{
		if(pObj)
			pObj->ReadWriteCif();
		SleepEx(FmilliSeconds, false);
	}
}
//---------------------------------------------------------------------------

/* ==========================================================================
	CDnetDioCtrl Class
========================================================================== */
void CDnetDioCtrl::InitBuffer()
{

}
//---------------------------------------------------------------------------

bool CDnetDioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------
void CDnetDioCtrl::OpenDevice()
{
	short sRet;

	InitializeCriticalSection(&cs);

	ReadWriteCifTh = new CCifThread(false, (DWORD)this, 10);

	if( (sRet = DevOpenDriver(0) ) != DRV_NO_ERROR)
	{
		// 드라이버 열기 에러
		ShowMsg(L"DevOpenDriver() Fail");
		LOG_PRINTF(m_strLogHead, L"DevOpenDriver fail, %02d", sRet);
	}
	else if( (sRet = DevInitBoard(0, (void *)0xCA000000) ) != DRV_NO_ERROR)
	{
		// 보드 초기화 에러
		ShowMsg(L"DevInitBoard() Fail");
		LOG_PRINTF(m_strLogHead, L"DevInitBoard fail, %02d", sRet);
	}
	else if( (sRet = DevSetHostState(0, HOST_READY, 0L) ) != DRV_NO_ERROR)
	{
		ShowMsg(L"DevSetHostState() Fail");
		LOG_PRINTF(m_strLogHead, L"DevSetHostState set ready fail, %02d", sRet);
	}
	else
	{
		LOG_STR(m_strLogHead, L"Devicenet Open success");
		m_bConnected = true;
	}
}
//---------------------------------------------------------------------------
void CDnetDioCtrl::ReadWriteCif()
{
	short sRet;

	if(m_bConnected)
	{
		memcpy(wrCifData, wrMachineData, sizeof(wrMachineData) );

		EnterCriticalSection(&cs);
		sRet = DevExchangeIO(0, 0, /*BYTES_OUT*/GetOutBytesCnt(), wrCifData, 0, BYTES_IN, rdCifData, 50L);
		if(sRet == DRV_NO_ERROR /*&& rdMachineData[0] != 0*/)
		{
			memcpy(rdMachineData, rdCifData, sizeof(rdMachineData) );
		}
//#ifndef _DEBUG
		else
		{
			LOG_PRINTF(m_strLogHead, L"sRet = %d %s", sRet, GetRxLogVal().c_str() );
		}
//#endif
		LeaveCriticalSection(&cs);
	}
}
//---------------------------------------------------------------------------
void CDnetDioCtrl::CloseDevice()
{
	short sRet;

	if( (sRet = DevSetHostState(0, HOST_NOT_READY, 0L) ) != DRV_NO_ERROR)
	{
		ShowMsg(L"DevSetHostState() Fail");
		LOG_PRINTF(m_strLogHead, L"DevSetHostState set not-ready fail, %02d", sRet);
	}
	else if( (sRet = DevExitBoard(0) ) != DRV_NO_ERROR)
	{
		ShowMsg(L"DevExitBoard() Fail");
		LOG_PRINTF(m_strLogHead, L"DevExitBoard fail, %02d", sRet);
	}
	else if( (sRet = DevCloseDriver(0) ) != DRV_NO_ERROR)
	{
		ShowMsg(L"DevCloseDriver() Fail");
		LOG_PRINTF(m_strLogHead, L"DevCloseDriver fail, %02d", sRet);
	}
	else
	{
		LOG_STR(m_strLogHead, L"Devicenet Close success");
//		ReadWriteCifTh->ThreadExit(NULL);
		m_bConnected = false;
	}
}
//---------------------------------------------------------------------------
String CDnetDioCtrl::GetRxLogVal()
{
	String sLog = "";
	String byteVal = "";

	for(int i = 0; i < BYTES_IN; i++)
	{
		byteVal.sprintf(L"%02X, ", rdMachineData[i]);
		sLog += byteVal;
	}

	return sLog;
}
//---------------------------------------------------------------------------

bool CDnetDioCtrl::IsOn(const int nIdx, const bool IsOut /*= false*/)
{
	assert(InRange(nIdx, 0, BYTES_CNT * 8) );

	USHORT uModNo = static_cast<USHORT>(nIdx/8);
	USHORT uOffset = static_cast<USHORT>(nIdx%8);

	std::bitset<8> RxVal = IsOut ? (wrMachineData[uModNo]) : (rdMachineData[uModNo]);

	if(RxVal.test(uOffset) )
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------
void CDnetDioCtrl::SetBit(const int nIdx, const bool bOn, const bool IsOut /*= true*/)
{
	assert(InRange(nIdx, 0, BYTES_CNT * 8) );

	USHORT uModNo = static_cast<USHORT>(nIdx/8);
	USHORT uOffset = static_cast<USHORT>(nIdx%8);

	std::bitset<8> TxVal = wrMachineData[uModNo] & 0xFF;
	if(bOn)
		TxVal.set(uOffset);
	else
		TxVal.reset(uOffset);

	wrMachineData[uModNo] = TxVal.to_ulong() & 0xFF;
}
//---------------------------------------------------------------------------
BYTE CDnetDioCtrl::GetByte(const int nIdx, const bool IsOut /*= false*/)
{
	if(IsOut)
	{
		assert(InRange(nIdx, 0, /*BYTES_OUT*/GetOutBytesCnt() ) );
		return wrMachineData[nIdx];
	}
	else
	{
		assert(InRange(nIdx, 0, BYTES_IN) );
		return rdMachineData[nIdx];
	}
}
//---------------------------------------------------------------------------
void CDnetDioCtrl::SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut /*= true*/)
{
	if(InRange(nIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()) && IsOut)
	{
		wrMachineData[nIdx] = byVal;
	}
	else
	{
		LOG_PRINTF(m_strLogHead, L"SetByteVal Index Range Over uIdx = %d", nIdx);
	}
}
//---------------------------------------------------------------------------
WORD CDnetDioCtrl::GetWord(const int nIdx, const WORD wRange /*= 0x00*/, const bool IsOut /*= false*/)
{
	WORD wRet = 0x00;
	int nByteIdx = nIdx * 2;

//short s = 0x3210;
//char c1 = s >> 8;
//char c2 = s & 0x00ff;
	if(IsOut)
	{
		assert(InRange(nByteIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()-2) );
		wRet = MAKEWORD(wrMachineData[nByteIdx], wrMachineData[nByteIdx+1]);
	#ifdef _DEGUG
		 LOG_PRINTF(m_strLogHead, L"[%02X, %02X -> %d]", wrMachineData[nByteIdx], wrMachineData[nByteIdx+1], wRet);
	#endif
	}
	else
	{
		assert(InRange(nByteIdx, 0, BYTES_IN-2) );
		wRet = MAKEWORD(rdMachineData[nByteIdx], rdMachineData[nByteIdx+1]);
	#ifdef _DEGUG
		 LOG_PRINTF(m_strLogHead, L"[%02X, %02X -> %d]", rdMachineData[nByteIdx], rdMachineData[nByteIdx+1], wRet);
	#endif
	}

	return wRet;
}
//---------------------------------------------------------------------------
void CDnetDioCtrl::SetWordVal(const int nIdx, const WORD wVal, const bool IsOut /*= true*/)
{
	int nByteIdx = nIdx * 2;

	if(InRange(nByteIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()-2) && IsOut)
	{
		BYTE byShift[2];
		byShift[0] = wVal & 0x00FF;
		byShift[1] = (wVal >> 8) & 0x00FF;

		memcpy(&wrMachineData[nByteIdx], &byShift, sizeof(WORD) );
	}
	else
	{
		LOG_PRINTF(m_strLogHead, L"SetWordVal Index Range Over nByteIdx = %d", nByteIdx);
	}
}
//---------------------------------------------------------------------------

/* ==========================================================================
	CDnetAioCtrl Class
========================================================================== */
CDnetAioCtrl::CDnetAioCtrl()
{
	m_strLogHead = L"Dnet";
}
//---------------------------------------------------------------------------

bool CDnetAioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------
void CDnetAioCtrl::OpenDevice()
{

}
//---------------------------------------------------------------------------
void CDnetAioCtrl::CloseDevice()
{

}
//---------------------------------------------------------------------------

BYTE CDnetAioCtrl::GetByte(const int nIdx, const bool IsOut /*= false*/)
{
	if(IsOut)
	{
		assert(InRange(nIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()-1) );
		return wrMachineData[nIdx];
	}
	else
	{
		assert(InRange(nIdx, 0, BYTES_IN-1) );
		return rdMachineData[nIdx];
	}
}
//---------------------------------------------------------------------------
void CDnetAioCtrl::SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut /*= true*/)
{
	if(InRange(nIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()-1) && IsOut)
	{
		wrMachineData[nIdx] = byVal;
	}
	else
	{
		LOG_PRINTF(m_strLogHead, L"SetByteVal Index Range Over uIdx = %d", nIdx);
	}
}
//---------------------------------------------------------------------------
WORD CDnetAioCtrl::GetWord(const int nIdx, const WORD wRange /*= 0x00*/, const bool IsOut /*= false*/)
{
	WORD wRet = 0x00;

//short s = 0x3210;
//char c1 = s >> 8;
//char c2 = s & 0x00ff;
	if(IsOut)
	{
		assert(InRange(nIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()-2) );
		wRet = MAKEWORD(wrMachineData[nIdx], wrMachineData[nIdx+1]);
#ifdef _DEGUG
		 LOG_PRINTF(m_strLogHead, L"[%02X, %02X -> %d]", wrMachineData[nIdx], wrMachineData[nIdx+1], wRet);
#endif
	}
	else
	{
		assert(InRange(nIdx, 0, BYTES_IN-2) );
		wRet = MAKEWORD(rdMachineData[nIdx], rdMachineData[nIdx+1]);
#ifdef _DEGUG
		 LOG_PRINTF(m_strLogHead, L"[%02X, %02X -> %d]", rdMachineData[nIdx], rdMachineData[nIdx+1], wRet);
#endif
	}

	return wRet;
}
//---------------------------------------------------------------------------
void CDnetAioCtrl::SetWordVal(const int nIdx, const WORD wVal, const bool IsOut /*= true*/)
{
	if(InRange(nIdx, 0, /*BYTES_OUT*/GetOutBytesCnt()-2) && IsOut)
	{
		BYTE byShift[2];
		byShift[0] = wVal & 0x00FF;
		byShift[1] = (wVal >> 8) & 0x00FF;

		memcpy(&wrMachineData[nIdx], &byShift, sizeof(WORD) );
	}
	else
	{
		LOG_PRINTF(m_strLogHead, L"SetWordVal Index Range Over uIdx = %d", nIdx);
	}
}
//---------------------------------------------------------------------------
void CDnetAioCtrl::SetDaConfig(const int nIdx, const double dMax)
{

}
//---------------------------------------------------------------------------
bool CDnetAioCtrl::WriteAnalogVal(const int nIdx, const double dVal)
{
	return true;
}
//---------------------------------------------------------------------------
double CDnetAioCtrl::GetMaxRange(const int nIdx)
{
	return 0.0;
}
double CDnetAioCtrl::GetWriteAnalogVal(const int nIdx)
{
	return 0.0;
}

