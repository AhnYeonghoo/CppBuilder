//---------------------------------------------------------------------------
#include <vcl.h>
#include "Math.hpp"
#include "ADLINK\DASK.h"

#pragma hdrstop

#include "uAdlinkIoCtrl.h"
#include "uIoDefine.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/* ==========================================================================
Description	: CAdlinkIoCtrl class
========================================================================== */
bool CAdlinkIoCtrl::IsConnected()
{
	return m_bConnected;
}
//---------------------------------------------------------------------------
void CAdlinkIoCtrl::OpenDevice()
{
	Pci9112 = Register_Card(PCI_9112, 0);

	if(Pci9112 < 0)
	{
		ShowMsg(L"Analog Input Initialization Fail ");
	}
	else
	{
		AI_9112_Config(Pci9112, TRIG_INT_PACER);
		LOG_PRINTF(m_strLogHead, L"PCI-9112 Register_Card, %d", Pci9112);
		m_bConnected = true;
	}
}
//---------------------------------------------------------------------------
void CAdlinkIoCtrl::CloseDevice()
{
	if(m_bConnected)
	{
		Release_Card(Pci9112);
		m_bConnected = false;
	}
}
//---------------------------------------------------------------------------

bool CAdlinkIoCtrl::IsOn(const int nIdx, const bool IsOut /*= false*/)
{
	return false;
}
//---------------------------------------------------------------------------
void CAdlinkIoCtrl::SetBit(const int nIdx, const bool bOn, const bool IsOut /*= true*/)
{

}
//---------------------------------------------------------------------------
BYTE CAdlinkIoCtrl::GetByte(const int nIdx, const bool IsOut /*= false*/)
{
	return 0x00;
}
//---------------------------------------------------------------------------
void CAdlinkIoCtrl::SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut /*= true*/)
{

}
//---------------------------------------------------------------------------
WORD CAdlinkIoCtrl::GetWord(const int nIdx, const WORD wRange /*= 0x00*/, const bool IsOut /*= false*/)
{
	USHORT wVal = 0x00;

	AI_ReadChannel(Pci9112, nIdx, wRange, &wVal);
	wVal = (wVal >> 4) + 1;

	return wVal;
}
//---------------------------------------------------------------------------
void CAdlinkIoCtrl::SetWordVal(const int nIdx, const WORD wVal, const bool IsOut /*= true*/)
{

}
//---------------------------------------------------------------------------
void CAdlinkIoCtrl::SetDaConfig(const int nIdx, const double dMax)
{
	if(InRange(nIdx, 0, MAX_AI - 1) )
	{
		AO_9112_Config(Pci9112, nIdx, -5);
	}
}
//---------------------------------------------------------------------------
bool CAdlinkIoCtrl::WriteAnalogVal(const int nIdx, const double dVal)
{
	short sRet = ErrorInvalidIoChannel;

	if(m_bConnected)
		sRet = AO_VWriteChannel(Pci9112, nIdx , dVal);

	return (sRet == NoError);
}
//---------------------------------------------------------------------------
double CAdlinkIoCtrl::GetMaxRange(const int nIdx)
{
	return 0.0;
}

double CAdlinkIoCtrl::GetWriteAnalogVal(const int nIdx)
{
	return 0.0;
}

