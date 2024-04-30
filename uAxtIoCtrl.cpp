//---------------------------------------------------------------------------
#include <vcl.h>
#include "System.Math.hpp"
#include "AXT\AxtLIB.h"
#include "AXT\AxtDio.h"
#include "AXT\AxtAIO.h"

#pragma hdrstop

#include "uAxtIoCtrl.h"
#include "uIoCtrl.h"
#include "uAxtMotorCtrl.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace VSP;

bool OpenAxtLib(void)
{
    if(!AxtInitialize(nullptr, -1))
    {
		ShowMsg(L"AxtInitialize() Fail");
        return false;
    }
    else
    {
        if(!AxtOpenDeviceAuto(BUSTYPE_PCI) )
        {
			ShowMsg(L"AxtOpenDeviceAuto() Fail");
            return false;
        }
        else
        {
            return true;
        }
    }
}

void CloseAxtLib(void)
{
	AxtCloseDeviceAll();
    AxtClose();
}

/* ==========================================================================
CAxtDioCtrl Class
========================================================================== */
bool CAxtDioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------
void CAxtDioCtrl::OpenDevice()
{
	InitBuffer();

	TModuleInfo ModInfo;

	if(!InitializeDIO() )
	{
		 ShowMsg(L"InitializeDIO() Fail");
	}
	else
	{
		UINT16 nModuleCnt = DIOget_module_count();
		for(UINT16 i = 0; i < nModuleCnt; i++)
		{
			UINT16 nModuleID = DIOget_module_id(i);
			ModInfo.sModuleNo = i;
			if(nModuleID == AXT_SIO_DO32P || nModuleID == AXT_SIO_DO32T)
			{
				ModInfo.sByteCnt = 4;
				m_vDoModule.push_back(ModInfo);
				LOG_PRINTF(m_strLogHead, L"vDo push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DO32P", ModInfo.sModuleNo, ModInfo.sByteCnt);
			}
			else if(nModuleID == AXT_SIO_DB32P || nModuleID == AXT_SIO_DB32T)
			{
				ModInfo.sByteCnt = 2;
				m_vDiModule.push_back(ModInfo);
				LOG_PRINTF(m_strLogHead, L"vDi push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DB32P", ModInfo.sModuleNo, ModInfo.sByteCnt);
				m_vDoModule.push_back(ModInfo);
				LOG_PRINTF(m_strLogHead, L"vDo push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DB32P", ModInfo.sModuleNo, ModInfo.sByteCnt);
			}
			else if(nModuleID == AXT_SIO_DI32)
			{
				ModInfo.sByteCnt = 4;
				m_vDiModule.push_back(ModInfo);
				LOG_PRINTF(m_strLogHead, L"vDi push_back [Mod.ID:%d, Byte Cnt.:%d] AXT_SIO_DI32", ModInfo.sModuleNo, ModInfo.sByteCnt);
			}
		}
		m_bConnected = true;
	}
}
//---------------------------------------------------------------------------
void CAxtDioCtrl::CloseDevice()
{
//	if(m_bConnected)
//	{
//		AxtCloseDeviceAll();
//		AxtClose();
//	}
}
//---------------------------------------------------------------------------

void CAxtDioCtrl::InitBuffer()
{
	m_vDiModule.clear();
	m_vDoModule.clear();
}
//---------------------------------------------------------------------------
void CAxtDioCtrl::ReadDiModule(void)
{
	int BufIdx = 0;
	for(size_t i = 0; i < m_vDiModule.size(); i++)
	{
		for(int nOffset = 0; nOffset < m_vDiModule.at(i).sByteCnt; nOffset++, BufIdx++)
		{
			if(m_bConnected)
				rdCifData[BufIdx] = DIOread_inport_byte(m_vDiModule.at(i).sModuleNo, nOffset);
			else
				rdMachineData[BufIdx] = rdCifData[BufIdx];
//			#ifdef _DEBUG
//			LOG_PRINTF(m_strLogHead, L"rdDiData[%d] Val:%d = [Mod.ID:%d, Offset.:%d]", BufIdx, rdDiData[BufIdx], m_vDiModule.at(i).sModuleNo, nOffset);
//			#endif
		}
	}
	memcpy(rdMachineData, rdCifData, m_vDiModule.size() );
}
//---------------------------------------------------------------------------
void CAxtDioCtrl::ReadDoModule(void)
{
	int BufIdx = 0;
	for(size_t i = 0; i < m_vDoModule.size(); i++)
	{
		for(int nOffset = 0; nOffset < m_vDoModule.at(i).sByteCnt; nOffset++, BufIdx++)
		{
			if(m_bConnected)
				wrCifData[BufIdx] = DIOread_outport_byte(m_vDoModule.at(i).sModuleNo, nOffset);
			else
				wrCifData[BufIdx] = wrMachineData[BufIdx];
//			#ifdef _DEBUG
//			LOG_PRINTF(m_strLogHead, L"rdDoData[%d] Val:%d = [Mod.ID:%d, Offset.:%d]", BufIdx, rdDoData[BufIdx], m_vDoModule.at(i).sModuleNo, nOffset);
//			#endif
		}
	}
}
//---------------------------------------------------------------------------
void CAxtDioCtrl::WriteDoModule(void)
{
	int BufIdx = 0;
	for(size_t i = 0; i < m_vDoModule.size(); i++)
	{
		for(int nOffset = 0; nOffset < m_vDoModule.at(i).sByteCnt; nOffset++, BufIdx++)
		{
			if(wrCifData[BufIdx] != wrMachineData[BufIdx])
				DIOwrite_outport_byte(m_vDoModule.at(i).sModuleNo, nOffset, wrMachineData[BufIdx]);
//			#ifdef _DEBUG
//			LOG_PRINTF(m_strLogHead, L"rdDoData[%d] Val:%d = [Mod.ID:%d, Offset.:%d]", BufIdx, rdDoData[BufIdx], m_vDoModule.at(i).sModuleNo, nOffset);
//			#endif
		}
	}
}
//---------------------------------------------------------------------------

bool CAxtDioCtrl::IsOn(const int nIdx, const bool IsOut /*= false*/)
{
	bool bRet = IsOut ? DIOread_outport(nIdx) : DIOread_inport(nIdx);

	return bRet;
}
//---------------------------------------------------------------------------
void CAxtDioCtrl::SetBit(const int nIdx, const bool bOn, const bool IsOut /*= true*/)
{
	if(IsOut)
		DIOwrite_outport(nIdx, bOn);
}
//---------------------------------------------------------------------------
BYTE CAxtDioCtrl::GetByte(const int nIdx, const bool IsOut /*= false*/)
{/* TODO :  */
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
void CAxtDioCtrl::SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut /*= true*/)
{/* TODO :  */
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
WORD CAxtDioCtrl::GetWord(const int nIdx, const WORD wRange /*= 0x00*/, const bool IsOut /*= false*/)
{/* TODO :  */
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
void CAxtDioCtrl::SetWordVal(const int nIdx, const WORD wVal, const bool IsOut /*= true*/)
{/* TODO :  */
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
CAxtAioCtrl Class
========================================================================== */
CAxtAioCtrl::CAxtAioCtrl()
	: m_bConnected(false), m_lChCount(4)
{
	OpenDevice();
}
//---------------------------------------------------------------------------

bool CAxtAioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------
void CAxtAioCtrl::OpenDevice()
{
	if(InitializeAIO() )
	{
		m_lChCount = AIOget_channel_number_dac();
		m_bConnected = true;
	}
	else
	{
		ShowMsg(L"InitializeAIO() Fail");
	}
}
//---------------------------------------------------------------------------
void CAxtAioCtrl::CloseDevice()
{
//	if(m_bConnected)
//	{
//		AxtCloseDeviceAll();
//		AxtClose();
//	}
}
//---------------------------------------------------------------------------
void CAxtAioCtrl::SetDaConfig(const int nIdx, const double dMax)
{
	if(InRange(nIdx, 0, m_lChCount - 1) )
	{
		AIOset_range_dac(nIdx, 0.0, dMax);
	}
}
//---------------------------------------------------------------------------
bool CAxtAioCtrl::WriteAnalogVal(const int nIdx, const double dVal)
{
	if(InRange(nIdx, 0, m_lChCount - 1) )
	{
		return AIOwrite_dac(nIdx, dVal);
	}

	return false;
}
//---------------------------------------------------------------------------
double CAxtAioCtrl::GetMaxRange(const int nIdx)
{
	double dMax = 0.0;
	double dMin = 0.0;

	AIOget_range_dac(nIdx, &dMin, &dMax);

	return dMax;
}

double CAxtAioCtrl::GetWriteAnalogVal(const int nIdx)
{
	double dValue =  AIOread_dac(nIdx);
	return dValue;
}

/* ==========================================================================
CAxtMotionDioCtrl Class
========================================================================== */
// 생성 순서 CAxtDioCtrl -> CAxtMotorCtrl -> CAxtMotionDioCtrl

bool CAxtMotionDioCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::OpenDevice()
{
	InitBuffer();

	if(CAxtMotorCtrl::GetAxtMotionLibInit() )
	{
		INT16 nTotalAxis = CAxtMotorCtrl::GetTotalAxisCount();
		m_vDiModule.resize(nTotalAxis);
		m_vDoModule.resize(nTotalAxis);
		LOG_PRINTF(m_strLogHead, L"MOTION Axis Count = %d", nTotalAxis);
		m_bConnected = true;
	}
	else
	{
		m_bConnected = false;
	}
}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::CloseDevice()
{

}
//---------------------------------------------------------------------------

void CAxtMotionDioCtrl::InitBuffer()
{
	m_vDiModule.clear();
	m_vDoModule.clear();
}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::ReadDiModule(void)
{

}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::ReadDoModule(void)
{

}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::WriteDoModule(void)
{

}
//---------------------------------------------------------------------------

bool CAxtMotionDioCtrl::IsOn(const int nIdx, const bool IsOut /*= false*/)
{
	int nAxisNo = static_cast<int>(nIdx / 8);
	int nOffset = (nIdx % 8);

	bool bRet = false;

	if(IsOut)
		bRet = CAxtMotorCtrl::GetOutputBit(nAxisNo, nOffset);
	else
		bRet = CAxtMotorCtrl::GetInputBit(nAxisNo, nOffset);

	return bRet;
}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::SetBit(const int nIdx, const bool bOn, const bool IsOut /*= true*/)
{
	int nAxisNo = static_cast<int>(nIdx / 8);
	int nOffset = (nIdx % 8);

	if(IsOut)
	{
		if(bOn)
			CAxtMotorCtrl::SetOutputBit(nAxisNo, nOffset);
		else
			CAxtMotorCtrl::ResetOutputBit(nAxisNo, nOffset);
	}
}
//---------------------------------------------------------------------------
BYTE CAxtMotionDioCtrl::GetByte(const int nIdx, const bool IsOut /*= false*/)
{
	BYTE byRet = 0x00;
	int nAxisNo = static_cast<int>(nIdx / 8);

	if(IsOut)
		byRet = CAxtMotorCtrl::GetOutputByte(nAxisNo);
	else
		byRet = CAxtMotorCtrl::GetInputputByte(nAxisNo);

	return byRet;
}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut /*= true*/)
{
//	int nAxisNo = static_cast<int>(nIdx / 8);
//
//	if(IsOut)
//	{
//		if(bOn)
//			CAxtMotorCtrl::SetOutputBit(nAxisNo, nOffset);
//		else
//			CAxtMotorCtrl::ResetOutputBit(nAxisNo, nOffset);
//	}
}
//---------------------------------------------------------------------------
WORD CAxtMotionDioCtrl::GetWord(const int nIdx, const WORD wRange /*= 0x00*/, const bool IsOut /*= false*/)
{
	// Range Check

}
//---------------------------------------------------------------------------
void CAxtMotionDioCtrl::SetWordVal(const int nIdx, const WORD wVal, const bool IsOut /*= true*/)
{
	// Range Check

}
//---------------------------------------------------------------------------

