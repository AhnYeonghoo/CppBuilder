//---------------------------------------------------------------------------

#ifndef uAxtIoCtrlH
#define uAxtIoCtrlH
//---------------------------------------------------------------------------
#include "uIoCtrl.h"

extern bool OpenAxtLib(void);
extern void CloseAxtLib(void);
/* ==========================================================================
CAxtDioCtrl Class
========================================================================== */
class CAxtDioCtrl : public CIoCtrl
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
	CAxtDioCtrl() : m_bConnected(false)			{ m_strLogHead = L"AXT_IO"; OpenDevice(); }
	virtual ~CAxtDioCtrl()						{ CloseDevice(); }

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
//---------------------------------------------------------------------------

/* ==========================================================================
CAxtAioCtrl Class
========================================================================== */
class CAxtAioCtrl : public CIoCtrl
{
	bool m_bConnected;
	long m_lChCount;

public:
	CAxtAioCtrl();
	virtual ~CAxtAioCtrl()						{ CloseDevice(); }

	bool IsConnected();
	long GetChCount() { return m_lChCount; }
	void OpenDevice();
	void CloseDevice();

	void SetDaConfig(const int nIdx, const double dMax);
	bool WriteAnalogVal(const int nIdx, const double dVal);
	double GetMaxRange(const int nIdx); // shlee 20201101
    double GetWriteAnalogVal(const int nIdx);   // shlee 20201101
};
//---------------------------------------------------------------------------

/* ==========================================================================
CAxtMotionDioCtrl Class
========================================================================== */
class CAxtMotionDioCtrl : public CIoCtrl
{
	bool m_bConnected;

	std::vector<BYTE> m_vDiModule;
	std::vector<BYTE> m_vDoModule;

public:
	CAxtMotionDioCtrl() : m_bConnected(false)			{ m_strLogHead = L"AXT_IO_M"; OpenDevice(); }
	virtual ~CAxtMotionDioCtrl()						{ CloseDevice(); }

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
//---------------------------------------------------------------------------
#endif
