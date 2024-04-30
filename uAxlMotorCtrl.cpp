//---------------------------------------------------------------------------
#include <vcl.h>
#include "AXL\AXL.h"
#include "AXL\AXM.h"
#include "AXL\AXDev.h"
#include "AXL\AXHS.h"
#include "AXL\AXHD.h"
#pragma hdrstop

#include "uAxlMotorCtrl.h"

#define AXIS_QUR(AXIS)				((AXIS) % 2)
#define SCR_CMD(AXIS, CMD)			(((CMD) << (AXIS_QUR(AXIS) * 8)) | (0xCFCFCFCF & ~(0x000000FF << (AXIS_QUR(AXIS) * 8))))

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace VS_MTR;

/* ==========================================================================
CAxlMotorCtrl Class
========================================================================== */
CAxlMotorCtrl::CAxlMotorCtrl(const int nCard)
	: CMotorCtrl(nCard)
{
	OpenDevice();
}
//---------------------------------------------------------------------------
CAxlMotorCtrl::~CAxlMotorCtrl()
{
	CloseDevice();
}
//---------------------------------------------------------------------------

bool CAxlMotorCtrl::OpenDevice()
{
	DWORD Code = AxlOpenNoReset(7);
	if (Code == AXT_RT_SUCCESS || Code == AXT_RT_OPEN_ALREADY)
	{
#ifdef _DEBUG
		AxlSetLogLevel(LEVEL_RUNSTOP);
#endif
		DWORD dwStatus;
		Code = AxmInfoIsMotionModule(&dwStatus);
		if (Code == AXT_RT_SUCCESS)
		{
			MotorCtrlInit = (dwStatus == STATUS_EXIST);
            return true;
		}
		else
		{
			ShowMsg(L"AxmInfoIsMotionModule() fail");
			return false;
		}
	}
	else
	{
		ShowMsg(L"AxlOpen() fail");
		return false;
	}
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::CloseDevice()
{
	AxlClose();
}
//---------------------------------------------------------------------------

// Description	: Initial Setting -----------------------------------------
bool CAxlMotorCtrl::SetDecelPulseMode(const int nAxis, const DWORD decelstart, const DWORD pulseout, const DWORD detectsignal)
{
	DWORD dwRet = AxmMotSetDecelMode(nAxis, decelstart);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMotSetPulseOutMethod(nAxis, pulseout);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetDriveMode(const int nAxis, const DWORD enc_method, const DWORD dwStopMode)
{
	//	if(AXT_RT_SUCCESS != ::AxmMotSetEncInputMethod(FlAxis, enc_method) )
	//		return false;

	//	if(AXT_RT_SUCCESS != ::AxmSignalSetStop(FlAxis, dwStopMode, 0) )	// 보드타입 제어기(PCI-N804/404) 및 PCI-R1604-MLII에 한정된 기능
	//		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetInSignals(const int nAxis, const DWORD enc_method, const DWORD dwInpos, const DWORD dwAlarm, \
	const DWORD dwNSLmt, const DWORD dwPSLmt, const DWORD dwNLmt, const DWORD dwPLmt, const bool bEncReverse)
{
	m_dwInposLevel = dwInpos;
	m_dwAlarmLevel = dwAlarm;
	m_dwNLimitLevel = dwNLmt;
	m_dwPLimitLevel = dwPLmt;

	// LOW(0x00): N.C, HIGH(0x01): N.O, UNUSED(0x02), USED(0x03): 현 상태 유지
    DWORD enc_new = (bEncReverse) ? (enc_method + 0x04) : enc_method;

	DWORD dwRet = AxmMotSetEncInputMethod(nAxis, enc_new);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmSignalSetInpos(nAxis, dwInpos);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	//	네트워크 타입 모션 제어기에서는 Use 값에 ‘LOW’, ‘HIGH’가 ‘USED’ 의 의미를 가진다.
	//	예외) RTEX-PM은 보드 타입 제어기(PCI-N804/404)와 동일하게 사용한다
	dwRet = AxmSignalSetServoAlarm(nAxis, dwAlarm);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmSignalSetSoftLimit(nAxis, DISABLE, SLOWDOWN_STOP, COMMAND, 0.0, 0.0);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmSignalSetLimit(nAxis, EMERGENCY_STOP, dwPLmt, dwNLmt);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmSignalSetInpos(nAxis, dwInpos);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetServoOnLevel(const int nAxis, const DWORD dwLevel)
{
	DWORD dwRet = AxmSignalSetServoOnLevel(nAxis, dwLevel);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetAlarmOnLevel(const int nAxis, const DWORD dwLevel)
{
	DWORD dwRet = AxmSignalSetServoAlarm(nAxis, dwLevel);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetAlarmResetLevel(const int nAxis, const DWORD dwLevel)
{
	DWORD dwRet = AxmSignalSetServoAlarmResetLevel(nAxis, dwLevel);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetInPosLevel(const int nAxis, const DWORD dwLevel)
{
	DWORD dwRet = AxmSignalSetInpos(nAxis, dwLevel);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetEmgInputLevel(const int nAxis, const DWORD dwLevel)
{
	DWORD dwRet = AxmSignalSetStop(nAxis, EMERGENCY_STOP, dwLevel);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

// [00h] B 접점(Normal Close) LOW
// [01h] A 접점(Normal Open)  HIGH
//bool CAxlMotorCtrl::SetOutSignals(const int nAxis, const DWORD dwSvrOn, const DWORD dwAlmRst)
//{
//	//	Servo-On 신호를 직접 출력하는 PCI-N804/404 및 RTEX-PM에서만 유효한 함수
//	//	네트워크 타입의 서보 드라이브는(A4N, SGDV[MLII])는 AxmSignalSetServoOnLevel로 설정할 필요가 없다.
//	//	if(AXT_RT_SUCCESS != ::AxmSignalSetServoOnLevel(FlAxis, dwSvrOn ) )
//	//		return false;
//	// Alarm reset(Clear) 신호를 직접 출력하는 PCI-N804/404 및 RTEX-PM에서만 유효한 함수
//	//	if(AXT_RT_SUCCESS != ::AxmSignalSetServoAlarmResetLevel(FlAxis, dwAlmRst) )
//	//		return false;
//
//	return true;
//}
bool CAxlMotorCtrl::SetMovePulsePerUnit(const int nAxis, const double dbPulse)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetMoveUnitPerPulse(nAxis, 1.0, (long)dbPulse);
	return (AXT_RT_SUCCESS == dwRet);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetStartStopSpeed(const int nAxis, const double dSpeed /*= 10.0*/) // Unit/Pulse의 배수
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetMinVel(nAxis, dSpeed);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetMaxSpeed(const int nAxis, const double dbMax)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetMaxVel(nAxis, dbMax);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------


// Description	: I/O 관련 함수 -----------------------------------------
void CAxlMotorCtrl::OutOnOff(const int nAxis, const UINT8 bitNo, const UINT8 bStatus)
{
	// bitNo -> 0x00: SVON, 0x01: ALARCLEAR, 0x02: COM_OUT2, 0x03: COM_OUT3, 0x04: COM_OUT4
	// bStatus -> 0x00: Off, 0x01: On
	if (MotorCtrlInit)
		AxmSignalWriteOutputBit(nAxis, bitNo, bStatus);
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::ServoEnable(const int nAxis, const bool bStatus)
{
	if (MotorCtrlInit)
		DWORD dwRet = AxmSignalServoOn(nAxis, (DWORD)bStatus);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::IsServoEnabled(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = INACTIVE;
	DWORD dwRet = AxmSignalIsServoOn(nAxis, &dwVal);

	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal == ACTIVE);
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::AlarmReset(const int nAxis)
{
	if (MotorCtrlInit)
	{
		AxmSignalServoAlarmReset(nAxis, true);
		Sleep(200);
		AxmSignalServoAlarmReset(nAxis, false);
	}
}
//---------------------------------------------------------------------------

bool CAxlMotorCtrl::IsReady(const int nAxis)
{
	return false;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::IsEmergencyOn(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = INACTIVE;
	DWORD dwRet = AxmSignalReadStop(nAxis, &dwVal);

	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal == ACTIVE);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::IsAlarmOn(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;

	DWORD dwVal = INACTIVE;
	DWORD dwRet = AxmSignalReadServoAlarm(nAxis, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal == ACTIVE);
}
//---------------------------------------------------------------------------

bool CAxlMotorCtrl::IsInpos(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = INACTIVE;
	DWORD dwRet = AxmSignalReadInpos(nAxis, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal == ACTIVE);
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::SetInposWait(const int nAxis, const BYTE bWait /*= ENABLE*/)
{
	if (!MotorCtrlInit)
		return;

	AxmSignalSetInpos(nAxis, (DWORD)bWait);
}
//---------------------------------------------------------------------------

bool CAxlMotorCtrl::IsPELM(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;


	DWORD dwPELM, dwNELM;
	DWORD dwRet = AxmSignalReadLimit(nAxis, &dwPELM, &dwNELM);
	if (AXT_RT_SUCCESS != dwRet)
		return true;

	return (dwPELM == ACTIVE);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::IsNELM(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;

	DWORD dwPELM, dwNELM;
	DWORD dwRet = AxmSignalReadLimit(nAxis, &dwPELM, &dwNELM);
	if (AXT_RT_SUCCESS != dwRet)
		return true;

	return (dwNELM == ACTIVE);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::IsORG(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = INACTIVE;
	DWORD dwRet = AxmSignalReadInputBit(nAxis, 0x00, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal == ACTIVE);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::IsEdgeOn(const int nAxis, const DWORD dwInPort)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = INACTIVE;
	DWORD dwRet = AxmSignalReadInputBit(nAxis, dwInPort, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal == ACTIVE);
}
//---------------------------------------------------------------------------

void CAxlMotorCtrl::TogglIO(const int nAxis, const BYTE byOutputBit)
{
	if (!MotorCtrlInit)
		return;

	DWORD dwVal = INACTIVE;

	DWORD dwRet = AxmSignalReadOutputBit(nAxis, byOutputBit, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return;

	dwRet = AxmSignalWriteOutputBit(nAxis, byOutputBit, !dwVal);
}
//---------------------------------------------------------------------------
DWORD CAxlMotorCtrl::GetMechSignal(const int nAxis)
{
	if (!MotorCtrlInit)
		return 0x00;

	DWORD dwVal = INACTIVE;

	DWORD dwRet = AxmStatusReadMechanical(nAxis, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return 0x00;

	return dwVal;
}
//---------------------------------------------------------------------------

// Description	: Motion 관련 함수 -----------------------------------------
bool CAxlMotorCtrl::InMotion(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = INACTIVE;

	DWORD dwRet = AxmStatusReadInMotion(nAxis, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return (dwVal != INACTIVE);
}
//---------------------------------------------------------------------------
DWORD CAxlMotorCtrl::GetEndStatus(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwVal = 0xFFFFFFFF;

	DWORD dwRet = AxmStatusReadStop(nAxis, &dwVal);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

    std::bitset<32> bsEndSt((unsigned long)dwVal);

	if (bsEndSt.test(0))		// Bit 0, 정방향 리미트 신호(PELM)에 의한 종료
		dwVal = 0x00;
	else if (bsEndSt.test(1))	// Bit 1, 역방향 리미트 신호(NELM)에 의한 종료
		dwVal = 0x00;
	else if (bsEndSt.test(10))	// Bit 10, 급정지 명령에 의한 구동 종료
		dwVal = 0x00;
	else if (bsEndSt.test(11))	// Bit 11, 감속 정지 명령에 의한 구동 종료
		dwVal = 0x00;
	else if (bsEndSt.test(17))	// Bit 17, 원점 검색 성공 종료
		dwVal = 0x00;
	else if (bsEndSt.test(18))	// Bit 18, 신호 검색 성공 종료
		dwVal = 0x00;
	else if (bsEndSt.test(20))	// Bit 20, 비정상 구동 정지 발생
		dwVal = 0x00;

	return dwVal;
}
//---------------------------------------------------------------------------

//========== AXT 신호 검출 구동 ========================================================================
// 지정 신호의 상향/하향 에지를 검색하여 급정지 또는 감속정지를 할 수 있다.
// detect_signal : 검색 신호 설정(typedef : DETECT_DESTINATION_SIGNAL)
//    PElmNegativeEdge    = 0x0,        // +Elm(End limit) 하강 edge
//    NElmNegativeEdge    = 0x1,        // -Elm(End limit) 하강 edge
//    PSlmNegativeEdge    = 0x2,        // +Slm(Slowdown limit) 하강 edge
//    NSlmNegativeEdge    = 0x3,        // -Slm(Slowdown limit) 하강 edge
//    In0DownEdge         = 0x4,        // IN0(ORG) 하강 edge
//    In1DownEdge         = 0x5,        // IN1(Z상) 하강 edge
//    In2DownEdge         = 0x6,        // IN2(범용) 하강 edge
//    In3DownEdge         = 0x7,        // IN3(범용) 하강 edge
//    PElmPositiveEdge    = 0x8,        // +Elm(End limit) 상승 edge
//    NElmPositiveEdge    = 0x9,        // -Elm(End limit) 상승 edge
//    PSlmPositiveEdge    = 0xa,        // +Slm(Slowdown limit) 상승 edge
//    NSlmPositiveEdge    = 0xb,        // -Slm(Slowdown limit) 상승 edge
//    In0UpEdge           = 0xc,        // IN0(ORG) 상승 edge
//    In1UpEdge           = 0xd,        // IN1(Z상) 상승 edge
//    In2UpEdge           = 0xe,        // IN2(범용) 상승 edge
//    In3UpEdge           = 0xf         // IN3(범용) 상승 edge
// Signal Search1 : 구동 시작후 입력 속도까지 가속하여, 신호 검출후 감속 정지.
// Signal Search2 : 구동 시작후 가속없이 입력 속도가 되고, 신호 검출후 급정지.
// 주의 : Signal Search2는 가감속이 없으므로 속도가 높을경우 탈조및 기구부의 무리가 갈수 있으므로 주의한다.
// *s*_*    : 구동중 속도 프로파일을 "S curve"를 이용한다. "*s_*"가 없다면 사다리꼴 가감속을 이용한다.
// *_ex     : 구동중 가감속도를 가속 또는 감속 시간으로 입력 받는다. "*_ex"가 없다면 가감속률로 입력 받는다.

long CAxlMotorCtrl::GetSearchSignalValue(const BYTE signal)
{
	long lRet = 0x00;

	switch (signal)
	{
	case P_LIMIT:
		lRet = PosEndLimit;
		break;
	case N_LIMIT:
		lRet = NegEndLimit;
		break;
	case COM_ORG:
		lRet = HomeSensor;
		break;
	case COM_ZPHASE:
		lRet = EncodZPhase;
		break;
	case COM_IN2:
		lRet = UniInput02;
		break;
	case COM_IN3:
		lRet = UniInput03;
		break;
	default:
		break;
	}

	return lRet;
}
//---------------------------------------------------------------------------
long CAxlMotorCtrl::GetSearchSignalEdge(const BYTE byEdge)
{
	long lRet = SIGNAL_DOWN_EDGE;

	switch (byEdge)
	{
	case VS_MTR::DOWN_EDGE:
		lRet = SIGNAL_DOWN_EDGE;
		break;
	case VS_MTR::UP_EDGE:
		lRet = SIGNAL_UP_EDGE;
		break;
	default:
		break;
	}

	return lRet;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SetHomeSensorLevel(const int nAxis, const BYTE Level)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmHomeSetSignalLevel(nAxis, Level);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::SignalSearch1(const int nAxis, const double dVel, const double dAccel, const BYTE detect_signal, const BYTE byEdge)
{
	if (!MotorCtrlInit)
		return false;

	long lSignal = GetSearchSignalValue(detect_signal);
	long lEdge = GetSearchSignalEdge(byEdge);

	//DWORD AxmMoveSignalSearch(long lAxisNo, double dVel, double dAccel,
	//	long lDetectSignal, long lSignalEdge, long lSignalMethod);

	DWORD dwRet = AxmMoveSignalSearch(nAxis, dVel, dAccel, lSignal, lEdge, SLOWDOWN_STOP);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

/* 설정된 속도로 가감속 구동 없이 설정된 신호
가 검출될 때까지 사다리꼴로 구동되며, 신호
검출 시 급 정지 */
bool CAxlMotorCtrl::SignalSearch2(const int nAxis, const double dVel, const BYTE detect_signal, const BYTE byEdge)
{
	if (!MotorCtrlInit)
		return false;

	long lSignal = GetSearchSignalValue(detect_signal);
	long lEdge = GetSearchSignalEdge(byEdge);

	DWORD dwRet = AxmMoveSignalSearch(nAxis, dVel, 0, lSignal, lEdge, EMERGENCY_STOP);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

//========= 위치 구동함수 ===============================================================================================================
// 주의사항: 위치를 설정할경우 반드시 UNIT/PULSE의 맞추어서 설정한다.
//           위치를 UNIT/PULSE 보다 작게할 경우 최소단위가 UNIT/PULSE로 맞추어지기때문에 그위치까지 구동이 될수없다.

// 설정 속도 단위가 RPM(Revolution Per Minute)으로 맞추고 싶다면.
// ex>    rpm 계산:
// 4500 rpm ?
// unit/ pulse = 1 : 1이면      pulse/ sec 초당 펄스수가 되는데
// 4500 rpm에 맞추고 싶다면     4500 / 60 초 : 75회전/ 1초
// 모터가 1회전에 몇 펄스인지 알아야 된다. 이것은 Encoder에 Z상을 검색해보면 알수있다.
// 1회전:1800 펄스라면 75 x 1800 = 135000 펄스가 필요하게 된다.
// AxmMotSetMoveUnitPerPulse에 Unit = 1, Pulse = 1800 넣어 동작시킨다.

// 설정한 거리만큼 또는 위치까지 이동한다.
// 지정 축의 절대 좌표/ 상대좌표 로 설정된 위치까지 설정된 속도와 가속율로 구동을 한다.
// 속도 프로파일은 AxmMotSetProfileMode 함수에서 설정한다.
// 펄스가 출력되는 시점에서 함수를 벗어난다.
// AxmMotSetAccelUnit(lAxisNo, 1) 일경우 dAccel -> dAccelTime , dDecel -> dDecelTime 으로 바뀐다.
bool CAxlMotorCtrl::StartMotor(const int nAxis, const double dPos, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMotSetProfileMode(nAxis, SYM_TRAPEZOIDE_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMoveStartPos(nAxis, dPos, dVel, dAcc, dAcc);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

// 설정한 거리만큼 또는 위치까지 이동한다.
// 지정 축의 절대 좌표/상대좌표로 설정된 위치까지 설정된 속도와 가속율로 구동을 한다.
// 속도 프로파일은 AxmMotSetProfileMode 함수에서 설정한다.
// 펄스 출력이 종료되는 시점에서 함수를 벗어난다
bool CAxlMotorCtrl::StartMove(const int nAxis, const double dPos, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetAbsRelMode(nAxis, POS_ABS_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMotSetProfileMode(nAxis, SYM_TRAPEZOIDE_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMovePos(nAxis, dPos, dVel, dAcc, dAcc);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

// 상대 좌표 Non Blocking함수 (구동중일 경우 무시됨) => JOG에 사용
bool CAxlMotorCtrl::StartRMove(const int nAxis, const double dDistance, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetAbsRelMode(nAxis, POS_REL_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMotSetProfileMode(nAxis, SYM_TRAPEZOIDE_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMovePos(nAxis, dDistance, dVel, dAcc, dAcc);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

/* 지정 축에 대하여 설정된 속도와 가속율로 지
속적으로 사다리꼴형 구동
펄스 출력이 시작되는 시점에서 함수 탈출 */
bool CAxlMotorCtrl::JogMove(const int nAxis, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	DWORD dwRet = AxmMotSetProfileMode(nAxis, SYM_TRAPEZOIDE_MODE);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	dwRet = AxmMoveVel(nAxis, dVel, dAcc, dAcc);
	if (AXT_RT_SUCCESS != dwRet)
		return false;

	return true;
}
//---------------------------------------------------------------------------

void CAxlMotorCtrl::SetStop(const int nAxis)
{
	AxmMoveSStop(nAxis);
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::SetEStop(const int nAxis)
{
	AxmMoveEStop(nAxis);
}
//---------------------------------------------------------------------------

bool CAxlMotorCtrl::StartRepeat(const int nAxis, const double dDistance, const double dVel, const double dAcc, const DWORD dWait)
{
	if (InMotion(nAxis))
		return false;

	//m_dbRepeatDist = dDistance;
	//m_dbRepeatVel = fabs(dVel);
	//m_dbRepeatAcc = fabs(dAcc);
	//m_dwRepeatWait = dWait;

	//// ORG 검색 Sequence
	//m_bRepeatAbort = false;
	//m_bRepeatDone = false;

	//m_nRunMode = RUN_REPEAT;

	//m_nRepeatStepNo = 0;

	//SetTimerLoop(m_uLoopScanTime);

	return true;
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::StopRepeat(const int nAxis)
{
	//if (!m_bRepeatAbort)
	//	m_bRepeatAbort = true;
}
//---------------------------------------------------------------------------


// Description	: Position -----------------------------------------
void	CAxlMotorCtrl::SetActPos(const int nAxis, const double pos)
{
	AxmStatusSetActPos(nAxis, pos);
}
//---------------------------------------------------------------------------
void	CAxlMotorCtrl::SetCmdPos(const int nAxis, const double pos)
{
	AxmStatusSetCmdPos(nAxis, pos);
}
//---------------------------------------------------------------------------
double	CAxlMotorCtrl::GetActPos(const int nAxis)
{
	double dbRet = -10.0;

	if (!MotorCtrlInit)
		return dbRet;

	DWORD dwRet = AxmStatusGetActPos(nAxis, &dbRet);
	if (AXT_RT_SUCCESS != dwRet)
		return -10.0;

	return dbRet;
}
//---------------------------------------------------------------------------
double	CAxlMotorCtrl::GetCmdPos(const int nAxis)
{
	double dbRet = -10.0;

	if (!MotorCtrlInit)
		return dbRet;

	DWORD dwRet = AxmStatusGetCmdPos(nAxis, &dbRet);
	if (AXT_RT_SUCCESS != dwRet)
		return -10.0;

	return dbRet;
}
//---------------------------------------------------------------------------

// Description	: Scan Edge -----------------------------------------
void CAxlMotorCtrl::InitScanQ(const int nAxis)
{
	DWORD dwReturn = 0;
	dwReturn = AxmSetCommandData16Qi(nAxis, QiINITSQWrite, 0x01);
}
//---------------------------------------------------------------------------
void CAxlMotorCtrl::SetScriptScan(const int nAxis, const int nServoType)
{
	// Script Event Active.
	DWORD	dwSCRCON, dwSCRCMD;
	WORD	wEventCmd,wCmd;;

	switch (nServoType) {
	case AC_SERVO:
		wEventCmd = EVENT_QIUIO8FALLING;
		break;
	case EZI_SERVO:
		wEventCmd = EVENT_QIUIO7FALLING;
		break;
	default:
		break;
	}

	dwSCRCON = QI_OPERATION_ONCE_RUN |
		QI_INTERRUPT_GEN_DISABLE |
		QI_OPERATION_EVENT_NONE |
		QI_SND_EVENT_AXIS(nAxis) |
		QI_FST_EVENT_AXIS(nAxis) |
		QI_OPERATION_EVENT_2(EVENT_QINOOP) |
		QI_OPERATION_EVENT_1(wEventCmd);

	wCmd = QiCNT1Read;
	dwSCRCMD = SCR_CMD(nAxis, wCmd);
	AxmSetScriptCaptionQi(nAxis, QI_SCR_REG1, dwSCRCON, dwSCRCMD, 0x00000000);
}
//---------------------------------------------------------------------------
bool CAxlMotorCtrl::GetScriptScanResult(const int nAxis, DWORD *dwRet)
{
	DWORD dwReturn = 0;
	dwReturn = AxmGetCommandData32Qi(nAxis, QiCQ1Read, dwRet);

	return (dwReturn == AXT_RT_SUCCESS);
}
//---------------------------------------------------------------------------

