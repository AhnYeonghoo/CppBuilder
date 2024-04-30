//---------------------------------------------------------------------------

#ifndef uAxtMotorCtrlH
#define uAxtMotorCtrlH
//---------------------------------------------------------------------------
#include "uMotorCtrl.h"

/* ==========================================================================
CAxtMotorCtrl Class
========================================================================== */
class CAxtMotorCtrl : public CMotorCtrl
{
	BYTE GetSearchSignalValue(const BYTE signal, const BYTE edge);

public:
	CAxtMotorCtrl(const int nCard);
	virtual ~CAxtMotorCtrl();

	static CMotorCtrl *__stdcall Create(const int nCard) { return new CAxtMotorCtrl(nCard); }

	virtual bool OpenDevice();
	virtual void CloseDevice();

	// Description	: Initial Setting -----------------------------------------
	virtual bool SetDecelPulseMode(const int nAxis, const DWORD decelstart, const DWORD pulseout, const DWORD detectsignal);
	virtual bool SetDriveMode(const int nAxis, const DWORD enc_method, const DWORD dwStopMode);
	virtual bool SetInSignals(const int nAxis, const DWORD enc_method, const DWORD dwInpos, const DWORD dwAlarm, \
		const DWORD dwNSLmt, const DWORD dwPSLmt, const DWORD dwNLmt, const DWORD dwPLmt, const bool bEncReverse);

	virtual bool SetServoOnLevel(const int nAxis, const DWORD dwLevel);
    virtual bool SetAlarmOnLevel(const int nAxis, const DWORD dwLevel);
	virtual bool SetAlarmResetLevel(const int nAxis, const DWORD dwLevel);
	virtual bool SetInPosLevel(const int nAxis, const DWORD dwLevel);
    virtual bool SetEmgInputLevel(const int nAxis, const DWORD dwLevel);

	virtual bool SetMovePulsePerUnit(const int nAxis, const double dbPulse);
	virtual bool SetStartStopSpeed(const int nAxis, const double dSpeed /*= 10.0*/); // Unit/Pulse의 배수
	virtual bool SetMaxSpeed(const int nAxis, const double dbMax);

	// Description	: I/O 관련 함수 -----------------------------------------
	virtual void OutOnOff(const int nAxis, const UINT8 bitNo, const UINT8 bStatus);
	virtual void ServoEnable(const int nAxis, const bool bStatus);
	virtual bool IsServoEnabled(const int nAxis);
	virtual void AlarmReset(const int nAxis);

	virtual bool IsReady(const int nAxis);
	virtual bool IsEmergencyOn(const int nAxis);
	virtual bool IsAlarmOn(const int nAxis);
	virtual bool IsInpos(const int nAxis);
	virtual void SetInposWait(const int nAxis, const BYTE bWait /*= ENABLE*/);

	virtual bool IsPELM(const int nAxis);
	virtual bool IsNELM(const int nAxis);
	virtual bool IsORG(const int nAxis);
	virtual bool IsEdgeOn(const int nAxis, const DWORD dwInPort);

	virtual void TogglIO(const int nAxis, const BYTE byOutputBit);
	virtual DWORD GetMechSignal(const int nAxis);

	// Description	: Motion 관련 함수 -----------------------------------------
	virtual bool InMotion(const int nAxis);
	virtual DWORD GetEndStatus(const int nAxis);

    virtual bool SetHomeSensorLevel(const int nAxis, const BYTE Level);
	virtual bool SignalSearch1(const int nAxis, const double dVel, const double dAccel, const BYTE detect_signal, const BYTE byEdge);
	virtual bool SignalSearch2(const int nAxis, const double dVel, const BYTE detect_signal, const BYTE byEdge);
	virtual bool StartMotor(const int nAxis, const double dPos, const double dVel, const double dAcc);
	virtual bool StartMove(const int nAxis, const double dPos, const double dVel, const double dAcc);
	virtual bool StartRMove(const int nAxis, const double dDistance, const double dVel, const double dAcc);
	virtual bool MoveMotor(const int nAxis, const double dPos, const double dVel, const double dAcc);
	virtual bool JogMove(const int nAxis, const double dVel, const double dAcc);
	virtual bool VMove(const int nAxis, const double dVel, const double dAcc);
	virtual void SetStop(const int nAxis);
	virtual void SetEStop(const int nAxis);
	virtual bool StartRepeat(const int nAxis, const double dDistance, const double dVel, const double dAcc, const DWORD dWait);
	virtual void StopRepeat(const int nAxis);

	// Description	: Position -----------------------------------------
	virtual void	SetActPos(const int nAxis, const double pos);
	virtual void	SetCmdPos(const int nAxis, const double pos);
	virtual double	GetActPos(const int nAxis);
	virtual double	GetCmdPos(const int nAxis);

	// Description	: Scan Edge -----------------------------------------
	virtual void InitScanQ(const int nAxis);
	virtual void SetScriptScan(const int nAxis, const int nServoType);
	virtual bool GetScriptScanResult(const int nAxis, DWORD *dwRet);
//    virtual bool StartCaptureMove(const int nAxis, const double dbPos, const double dbVel, const double dbAcc, const int nServoType = VS_MTR::AC_SERVO);

	// Description	: Universal DIO -----------------------------------------
	static bool GetAxtMotionLibInit(void);
	static INT16 GetTotalAxisCount(void);

	static BYTE GetOutputByte(const int nAxis);
	static bool GetOutputBit(const int nAxis, const int nOffset);
	static bool SetOutputBit(const int nAxis, const int nOffset);
	static bool ResetOutputBit(const int nAxis, const int nOffset);

	static BYTE GetInputputByte(const int nAxis);
	static bool GetInputBit(const int nAxis, const int nOffset);
};
//---------------------------------------------------------------------------
#endif
