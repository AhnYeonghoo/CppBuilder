//---------------------------------------------------------------------------

#ifndef uAdlinkIoCtrlH
#define uAdlinkIoCtrlH
//---------------------------------------------------------------------------
#include "uIoCtrl.h"

/* ==========================================================================
Description	: CAdlinkIoCtrl class
========================================================================== */
class CAdlinkIoCtrl : public CIoCtrl
{
	bool m_bConnected;
	short Pci9112;

public:
	CAdlinkIoCtrl() : m_bConnected(false), Pci9112(-1)		{ m_strLogHead = L"ADLINK"; OpenDevice(); }
	virtual ~CAdlinkIoCtrl()						        { CloseDevice(); }

	bool IsConnected();
	void OpenDevice();
	void CloseDevice();

	bool IsOn(const int nIdx, const bool IsOut = false);
	void SetBit(const int nIdx, const bool bOn, const bool IsOut = true);
	BYTE GetByte(const int nIdx, const bool IsOut = false);
	void SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut = true);
	WORD GetWord(const int nIdx, const WORD wRange = 0x00, const bool IsOut = false);
	void SetWordVal(const int nIdx, const WORD wVal, const bool IsOut = true);
	void SetDaConfig(const int nIdx, const double dMax);
	bool WriteAnalogVal(const int nIdx, const double dVal);
	double GetMaxRange(const int nIdx); // 20201101
    double GetWriteAnalogVal(const int nIdx);   // 20201101
};
//---------------------------------------------------------------------------
#endif
