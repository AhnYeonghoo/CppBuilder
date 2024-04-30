//---------------------------------------------------------------------------

#ifndef uAxlIoCtrlH
#define uAxlIoCtrlH
//---------------------------------------------------------------------------
#include "uIoCtrl.h"

extern bool OpenAxlLib(void);
extern void CloseAxlLib(void);
/* ==========================================================================
	CAxlDioCtrl Class
========================================================================== */
class CAxlDioCtrl : public CIoCtrl
{
	bool m_bConnected;

	struct TModuleInfo
	{
		short sModuleNo;
		short sByteCnt;
	};

	std::vector<TModuleInfo> m_vDiModule;
	std::vector<TModuleInfo> m_vDoModule;

public:
	CAxlDioCtrl() : m_bConnected(false)			{ m_strLogHead = L"AXL"; OpenDevice(); }
	virtual ~CAxlDioCtrl()						{ CloseDevice(); }

	bool IsConnected();
	void OpenDevice();
	void CloseDevice();

	void InitBuffer();
	void ReadDiModule(void);
	void ReadDoModule(void);
	void WriteDoModule(void);

	bool IsOn(const int nIdx, const bool IsOut = false);
	void SetBit(const int nIdx, const bool bOn, const bool IsOut = true);
	BYTE GetByte(const int nIdx, const bool IsOut = false);
	void SetByteVal(const int nIdx, const BYTE byVal, const bool IsOut = true);
	WORD GetWord(const int nIdx, const WORD wRange = 0x00, const bool IsOut = false);
	void SetWordVal(const int nIdx, const WORD wVal, const bool IsOut = true);
};

/* ==========================================================================
	CAxlAioCtrl Class
========================================================================== */
class CAxlAioCtrl : public CIoCtrl
{
	bool m_bConnected;
	long m_lChCount;

public:
	CAxlAioCtrl();
	virtual ~CAxlAioCtrl()						{ CloseDevice(); }

	bool IsConnected();
	long GetChCount() { return m_lChCount; }
	void OpenDevice();
	void CloseDevice();

	void SetDaConfig(const int nIdx, const double dMax);
	bool WriteAnalogVal(const int nIdx, const double dVal);
	double GetMaxRange(const int nIdx); // shlee 20201101
	double GetWriteAnalogVal(const int nIdx);  // shlee 20201101
};
//---------------------------------------------------------------------------
#endif
