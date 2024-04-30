//---------------------------------------------------------------------------
#include <vcl.h>
#include "AXT\AxtCamcFs.h"
#include "AXT\AxtCAMC5M.h"
#include "AXT\AxtCAMCFS20.h"
#include "AXT\AxtKeCAMCFS20.h"
#pragma hdrstop

#include "uAxtMotorCtrl.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace VS_MTR;
/* ==========================================================================
CAxtMotorCtrl Class
========================================================================== */
CAxtMotorCtrl::CAxtMotorCtrl(const int nCard)
	: CMotorCtrl(nCard)
{
	m_strLogHead = L"AXT_M";
	OpenDevice();
}
//---------------------------------------------------------------------------
CAxtMotorCtrl::~CAxtMotorCtrl()
{
	CloseDevice();
}
//---------------------------------------------------------------------------

bool CAxtMotorCtrl::OpenDevice()
{
	if(!CFS20IsInitialized() )
	{
		if(!InitializeCAMCFS20(true))
		{
			MotorCtrlInit = false;
			ShowMsg(L"InitializeCAMCFS20() fail");
			return false;
		}
		else
		{
			CFSKeSetMainClk(16384000); // 16.384 MHz 로 초기화
			MotorCtrlInit = true;
            return true;
		}
	}

    return true;
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::CloseDevice()
{
	CFS20StopService();
}
//---------------------------------------------------------------------------

// Description	: Initial Setting -----------------------------------------
bool CAxtMotorCtrl::SetDecelPulseMode(const int nAxis, const DWORD decelstart, const DWORD pulseout, const DWORD detectsignal)
{
	// Description =====================================================
	//	: 지정 축의 Mode1 Write 레지스터에 축 구동에 필요한 데이터를 설정(D0 ~ D7)
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_drive_mode1((INT16)nAxis, (UINT8)decelstart, (UINT8)pulseout, (UINT8)detectsignal);
			break;
		case CFS:
			CFSset_drive_mode1((INT16)nAxis, (UINT8)decelstart, (UINT8)pulseout, (UINT8)detectsignal);
			break;
		case CFS2:
			CFS20set_drive_mode1((INT16)nAxis, (UINT8)decelstart, (UINT8)pulseout, (UINT8)detectsignal);
			break;
		default:
			break;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetDriveMode(const int nAxis, const DWORD enc_method, const DWORD dwStopMode)
{
	return false;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetInSignals(const int nAxis, const DWORD enc_method, const DWORD dwInpos, const DWORD dwAlarm, \
	const DWORD dwNSLmt, const DWORD dwPSLmt, const DWORD dwNLmt, const DWORD dwPLmt, const bool bEncReverse)
{
	// Description =====================================================
	//		: Mode2 데이터는 보드의 입장에서의 입력인 엔코더, 센서 신호등의 입력사항을 조합하여 8 비트로
	//		만들어 놓은 것으로 엔코더 입력 방식, 리미트 센서의 입력 신호레벨, Inposition 신호와 Alarm
	//		신호의 입력 레벨을 결정

	m_dwInposLevel = dwInpos;
	m_dwAlarmLevel = dwAlarm;
	m_dwNLimitLevel = dwNLmt;
	m_dwPLimitLevel = dwPLmt;

	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_drive_mode2((INT16)nAxis, (UINT8)enc_method, (UINT8)dwInpos, (UINT8)dwAlarm,\
				(UINT8)dwNSLmt, (UINT8)dwPSLmt, (UINT8)dwNLmt, (UINT8)dwPLmt);
			//C5Mset_nlimit_sel((INT16)nAxis, (UINT8)dwEmg); // 0: 급정지, 1: 감속 정지
			//C5Mset_plimit_sel((INT16)nAxis, (UINT8)dwEmg); // 0: 급정지, 1: 감속 정지
			break;
		case CFS:
			CFSset_drive_mode2((INT16)nAxis, (UINT8)enc_method, (UINT8)dwInpos, (UINT8)dwAlarm, \
				(UINT8)dwNSLmt, (UINT8)dwPSLmt, (UINT8)dwNLmt, (UINT8)dwPLmt);
			//CFSset_nlimit_sel((INT16)nAxis, (UINT8)dwEmg); // 0: 급정지, 1: 감속 정지
			//CFSset_plimit_sel((INT16)nAxis, (UINT8)dwEmg); // 0: 급정지, 1: 감속 정지
			break;
		case CFS2:
			CFS20set_drive_mode2((INT16)nAxis, (UINT8)enc_method, (UINT8)dwInpos, (UINT8)dwAlarm, \
				(UINT8)dwNSLmt, (UINT8)dwPSLmt, (UINT8)dwNLmt, (UINT8)dwPLmt);
			//CFS20set_nlimit_sel((INT16)nAxis, (UINT8)dwEmg); // 0: 급정지, 1: 감속 정지
			//CFS20set_plimit_sel((INT16)nAxis, (UINT8)dwEmg); // 0: 급정지, 1: 감속 정지
            CFS20set_enc_reverse(nAxis, bEncReverse);
			break;
		default: break;
		}
	}

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetServoOnLevel(const int nAxis, const DWORD dwLevel)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		C5Mset_servo_level(nAxis, (UINT8)dwLevel);
	else if (m_nCardType == CFS)
		CFSset_servo_level(nAxis, (UINT8)dwLevel);
	else if (m_nCardType == CFS2)
		CFS20set_servo_level(nAxis, (UINT8)dwLevel);
	else
		CFS20set_servo_level(nAxis, (UINT8)dwLevel);

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetAlarmOnLevel(const int nAxis, const DWORD dwLevel)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		C5Mset_alarm_level(nAxis, (UINT8)dwLevel);
	else if (m_nCardType == CFS)
		CFSset_alarm_level(nAxis, (UINT8)dwLevel);
	else if (m_nCardType == CFS2)
		CFS20set_alarm_level(nAxis, (UINT8)dwLevel);
	else
		CFS20set_alarm_level(nAxis, (UINT8)dwLevel);

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetAlarmResetLevel(const int nAxis, const DWORD dwLevel)
{
// shlee 20200609 remove remark.
	if (MotorCtrlInit)
	{
		if (m_nCardType == CAM5)
			C5Mset_alarm_level(nAxis, (UINT8)dwLevel);
		else if (m_nCardType == CFS)
			CFSset_alarm_level(nAxis, (UINT8)dwLevel);
		else if (m_nCardType == CFS2)
			CFS20set_alarm_level(nAxis, (UINT8)dwLevel);
		else
			CFS20set_alarm_level(nAxis, (UINT8)dwLevel);
	}

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetInPosLevel(const int nAxis, const DWORD dwLevel)
{
	if (MotorCtrlInit)
	{
		if (m_nCardType == CAM5)
			C5Mset_inposition_level(nAxis, (UINT8)dwLevel);
		else if (m_nCardType == CFS)
			CFSset_inposition_level(nAxis, (UINT8)dwLevel);
		else if (m_nCardType == CFS2)
			CFS20set_inposition_level(nAxis, (UINT8)dwLevel);
		else
			CFS20set_inposition_level(nAxis, (UINT8)dwLevel);
	}

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetEmgInputLevel(const int nAxis, const DWORD dwLevel)
{
	if (MotorCtrlInit)
	{
		if (m_nCardType == CAM5)
			CFSset_emg_signal_enable(nAxis, (UINT8)dwLevel);
		else if (m_nCardType == CFS)
			CFSset_emg_signal_enable(nAxis, (UINT8)dwLevel);
		else if (m_nCardType == CFS2)
			CFS20set_emg_signal_enable(nAxis, (UINT8)dwLevel);
		else
			CFS20set_emg_signal_enable(nAxis, (UINT8)dwLevel);
	}

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetMovePulsePerUnit(const int nAxis, const double dbPulse)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		C5Mset_movepulse_perunit(nAxis, (INT32)dbPulse);
	else if (m_nCardType == CFS)
		CFSset_movepulse_perunit(nAxis, dbPulse);
	else if (m_nCardType == CFS2)
		CFS20set_movepulse_perunit(nAxis, dbPulse);
	else
		CFS20set_movepulse_perunit(nAxis, dbPulse);

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetStartStopSpeed(const int nAxis, const double dSpeed /*= 10.0*/) // Unit/Pulse의 배수
{
	if (!MotorCtrlInit)
		return false;

	switch (m_nCardType)
	{
	case CAM5:
		C5Mset_startstop_speed(nAxis, dSpeed);
		break;
	case CFS:
		CFSset_startstop_speed(nAxis, dSpeed);
		break;
	case CFS2:
		CFS20set_startstop_speed(nAxis, dSpeed);
		break;
	default:   break;
	}
	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetMaxSpeed(const int nAxis, const double dbMax)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		C5Mset_max_speed(nAxis, dbMax);
	else if (m_nCardType == CFS)
		CFSset_max_speed(nAxis, dbMax);
	else if (m_nCardType == CFS2)
		CFS20set_max_speed(nAxis, dbMax);
	else
		CFS20set_max_speed(nAxis, dbMax);

	return true;
}
//---------------------------------------------------------------------------

// Description	: I/O 관련 함수 -----------------------------------------
void CAxtMotorCtrl::OutOnOff(const int nAxis, const UINT8 bitNo, const UINT8 bStatus)
{
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
//			if(bStatus)
//				C5Mchange_output_bit(nAxis, bitNo);
//			else
//				C5Mreset_output_bit(nAxis, bitNo);
			break;
		case CFS:
//			if(bStatus)
//				CFSset_output_bit(nAxis, bitNo);
//			else
//				CFSreset_output_bit(nAxis, bitNo);
			break;
		case CFS2:
			if(bStatus)
				CFS20change_output_bit(nAxis, bitNo, 1);
			else
				CFS20change_output_bit(nAxis, bitNo, 0);
			break;
		default:   break;
		}
	}
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::ServoEnable(const int nAxis, const bool bStatus)
{
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_servo_enable(nAxis, bStatus);
			break;
		case CFS:
			CFSset_servo_enable(nAxis, bStatus);
			break;
		case CFS2:
			CFS20set_servo_enable(nAxis, bStatus);
			break;
		default:  break;
		}
	}
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsServoEnabled(const int nAxis)
{
	if (MotorCtrlInit)
	{
		if (m_nCardType == CAM5)
			return C5Mget_servo_enable(nAxis);
		else if (m_nCardType == CFS)
			return CFSget_servo_enable(nAxis);
		else if (m_nCardType == CFS2)
			return CFS20get_servo_enable(nAxis);
		else
			return CFSget_servo_enable(nAxis);
	}

	return false;
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::AlarmReset(const int nAxis)
{
	OutOnOff(nAxis, COM_ALMCLR, true);
	Sleep(200);
	OutOnOff(nAxis, COM_ALMCLR, false);
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsReady(const int nAxis)
{
	//	if(MotorCtrlInit)
	//	{
	//		if(m_nCardType == CAM5)
	//			return C5Minput_bit_on(nAxis, COM_IN2);
	//		else if(m_nCardType == CFS)
	//			return CFSinput_bit_on(nAxis, COM_IN2);
	//		else if(m_nCardType == CFS2)
	//			return CFS20input_bit_on(nAxis, COM_IN2);
	//		else
	//			return CFS20input_bit_on(nAxis, COM_IN2);
	//	}

	return false;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsEmergencyOn(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;

	bool bRet = true;

	if (m_nCardType == CAM5)
		bRet = (C5Mget_stop_sel(nAxis) == LOW);
//	else if (m_nCardType == CFS)
//		bRet = (CFSget_stop_sel(nAxis) == LOW);
	else if (m_nCardType == CFS2)
		bRet = (CFS20get_stop_sel(nAxis) == LOW);
	else
		bRet = (CFS20get_stop_sel(nAxis) == LOW);

	return bRet;

}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsAlarmOn(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;

	UINT8 level, state;

	if (m_nCardType == CAM5)
	{
		state = C5Mget_alarm_switch(nAxis);
		level = C5Mget_alarm_level(nAxis);
	}
	else if (m_nCardType == CFS)
	{
		state = CFSget_alarm_switch(nAxis);
		level = CFSget_alarm_level(nAxis);
	}
	else if (m_nCardType == CFS2)
	{
		state = CFS20get_alarm_switch(nAxis);
		level = CFS20get_alarm_level(nAxis);
	}
	else
	{
		state = CFS20get_alarm_switch(nAxis);
		level = CFS20get_alarm_level(nAxis);
	}

//	bool bRet = (state == HIGH);//level);
	bool bRet = (state != level); //  shlee 20200609 mdoified.
	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsInpos(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	bool bRet = true;

	//if (m_nCardType == CAM5)
	//	bRet = (C5Min_position(nAxis) );
	//else if (m_nCardType == CFS)
	//	bRet = (CFSin_position(nAxis));
	//else if (m_nCardType == CFS2)
	//	bRet = (CFS20in_position(nAxis) );
	//else
	//	bRet = (CFS20in_position(nAxis) );

	if (m_nCardType == CAM5)
		bRet = (C5Mget_inposition_switch(nAxis) == HIGH);
	else if (m_nCardType == CFS)
		bRet = (CFSget_inposition_switch(nAxis) == HIGH);
	else if (m_nCardType == CFS2)
		bRet = (CFS20get_inposition_switch(nAxis) == HIGH);
	else
		bRet = (CFS20get_inposition_switch(nAxis) == HIGH);

	return bRet;
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::SetInposWait(const int nAxis, const BYTE bWait /*= ENABLE*/)
{
	if (!MotorCtrlInit)
		return;

	switch (m_nCardType)
	{
	case CAM5:
		C5Mset_inposition_enable(nAxis, bWait);
		break;
	case CFS:
		CFSset_inposition_enable(nAxis, bWait);
		break;
	case CFS2:
		CFS20set_inposition_enable(nAxis, bWait);
		break;
	default:
		CFS20set_inposition_enable(nAxis, bWait);
		break;
	}
}
//---------------------------------------------------------------------------

bool CAxtMotorCtrl::IsPELM(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;

	bool bRet = true;

	if (m_nCardType == CAM5)
		bRet = (C5Mget_pend_limit_switch(nAxis) == HIGH);
	else if (m_nCardType == CFS)
		bRet = (CFSget_pend_limit_switch(nAxis) == HIGH);
	else if (m_nCardType == CFS2)
		bRet = (CFS20get_pend_limit_switch(nAxis) == HIGH);
	else
		bRet = (CFS20get_pend_limit_switch(nAxis) == HIGH);

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsNELM(const int nAxis)
{
	if (!MotorCtrlInit)
		return true;

	bool bRet = true;

	if (m_nCardType == CAM5)
		bRet = (C5Mget_nend_limit_switch(nAxis) == HIGH);
	else if (m_nCardType == CFS)
		bRet = (CFSget_nend_limit_switch(nAxis) == HIGH);
	else if (m_nCardType == CFS2)
		bRet = (CFS20get_nend_limit_switch(nAxis) == HIGH);
	else
		bRet = (CFS20get_nend_limit_switch(nAxis) == HIGH);

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsORG(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	bool bRet = GetInputBit(nAxis, COM_ORG);

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::IsEdgeOn(const int nAxis, const DWORD dwInPort)
{
	if (!MotorCtrlInit)
		return false;

	bool bRet = GetInputBit(nAxis, (UINT8)dwInPort);

	return bRet;
}
//---------------------------------------------------------------------------

void CAxtMotorCtrl::TogglIO(const int nAxis, const BYTE byOutputBit)
{
	if (!MotorCtrlInit)
		return;

	BYTE bRead = (GetOutputBit(nAxis, byOutputBit) == true);

	switch (m_nCardType)
	{
	case CAM5:
		C5Mchange_output_bit(nAxis, byOutputBit, !bRead);
		break;
	case CFS:
		CFSchange_output_bit(nAxis, byOutputBit, !bRead);
		break;
	case CFS2:
		CFS20change_output_bit(nAxis, byOutputBit, !bRead);
		break;
	default:
		CFS20change_output_bit(nAxis, byOutputBit, !bRead);
		break;
	}
}
//---------------------------------------------------------------------------
DWORD CAxtMotorCtrl::GetMechSignal(const int nAxis)
{
	if (MotorCtrlInit)
	{
		if (m_nCardType == CAM5)
			return C5Mget_mechanical_signal(nAxis);
		else if (m_nCardType == CFS)
			return CFSget_mechanical_signal(nAxis);
		else if (m_nCardType == CFS2)
			return CFS20get_mechanical_signal(nAxis);
		else
			return CFS20get_mechanical_signal(nAxis);
	}

	return PElmNegativeEdge;
}
//---------------------------------------------------------------------------

// Description	: Motion 관련 함수 -----------------------------------------
bool CAxtMotorCtrl::InMotion(const int nAxis)
{
	if (!MotorCtrlInit)
		return false;

	bool bRet = false;

	if (m_nCardType == CAM5)
		bRet = C5Min_motion(nAxis);
	else if (m_nCardType == CFS)
		bRet = CFSin_motion(nAxis);
	else if (m_nCardType == CFS2)
		bRet = CFS20in_motion(nAxis);
	else
		bRet = CFS20in_motion(nAxis);

	return bRet;
}
//---------------------------------------------------------------------------
DWORD CAxtMotorCtrl::GetEndStatus(const int nAxis)
{
	DWORD byRet = 0xFFFFFFFF;

	if (MotorCtrlInit)
	{
		if (m_nCardType == CAM5)
			byRet = C5Mget_end_status(nAxis);
		else if (m_nCardType == CFS)
			byRet = CFSget_end_status(nAxis);
		else if (m_nCardType == CFS2)
			byRet = CFS20get_end_status(nAxis);
		else
			byRet = CFS20get_end_status(nAxis);
	}

	if (byRet == 0x4400)	// 14bit: Limit(PELM, NELM, PSLM, NSLM, Soft)에 의한 종료
		byRet = 0x00;		// 10bit: 신호 검출에 의한 종료(Signal Search-1/2 drive종료)
	else if (byRet == 0x0800)
		byRet = 0x00;		// 11bit: Preset pulse drive에 의한 종료(지정한 위치/거리만큼 움직이는 함수군)

	return byRet;
}
//---------------------------------------------------------------------------
BYTE CAxtMotorCtrl::GetSearchSignalValue(const BYTE signal, const BYTE edge)
{
	BYTE byRet = PElmNegativeEdge;

	switch (signal)
	{
	case P_LIMIT:
		byRet = (edge == UP_EDGE) ? PElmPositiveEdge : PElmNegativeEdge;
		break;
	case N_LIMIT:
		byRet = (edge == UP_EDGE) ? NElmPositiveEdge : NElmNegativeEdge;
		break;
	case COM_ORG:
		byRet = (edge == UP_EDGE) ? In0UpEdge : In0DownEdge;
		break;
	case COM_ZPHASE:
		byRet = (edge == UP_EDGE) ? In1UpEdge : In1DownEdge;
		break;
	case COM_IN2:
		byRet = (edge == UP_EDGE) ? In2UpEdge : In2DownEdge;
		break;
	case COM_IN3:
		byRet = (edge == UP_EDGE) ? In3UpEdge : In3DownEdge;
		break;
	default:
		break;
	}

	return byRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetHomeSensorLevel(const int nAxis, const BYTE Level)
{
	if (!MotorCtrlInit)
		return false;

	return true;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SignalSearch1(const int nAxis, const double dVel, const double dAccel, const BYTE detect_signal, const BYTE byEdge)
{
	if (!MotorCtrlInit)
		return false;

	BYTE signal = GetSearchSignalValue(detect_signal, byEdge);

	if (m_nCardType == CAM5)
		return C5Mstart_signal_search1(nAxis, dVel, dAccel, signal);
	else if (m_nCardType == CFS)
		return CFSstart_signal_search1(nAxis, dVel, dAccel, signal);
	else if (m_nCardType == CFS2)
		return CFS20start_signal_search1(nAxis, dVel, dAccel, signal);
	else
		return CFS20start_signal_search1(nAxis, dVel, dAccel, signal);
}
//---------------------------------------------------------------------------

/* 설정된 속도로 가감속 구동 없이 설정된 신호
가 검출될 때까지 사다리꼴로 구동되며, 신호
검출 시 급 정지 */
bool CAxtMotorCtrl::SignalSearch2(const int nAxis, const double dVel, const BYTE detect_signal, const BYTE byEdge)
{
	if (!MotorCtrlInit)
		return false;

	BYTE signal = GetSearchSignalValue(detect_signal, byEdge);

	if (m_nCardType == CAM5)
		return C5Mstart_signal_search2(nAxis, dVel, signal);
	else if (m_nCardType == CFS)
		return CFSstart_signal_search2(nAxis, dVel, signal);
	else if (m_nCardType == CFS2)
		return CFS20start_signal_search2(nAxis, dVel, signal);
	else
		return CFS20start_signal_search2(nAxis, dVel, signal);
}
//---------------------------------------------------------------------------

//========== 단축 지정 거리 구동 ===================================================================
// start_** : 지정 축에서 구동 시작후 함수를 return한다. "start_*" 가 없으면 이동 완료후 return한다(Blocking).
// *r*_*    : 지정 축에서 입력된 거리만큼(상대좌표)로 이동한다. "*r_*이 없으면 입력된 위치(절대좌표)로 이동한다.
// *s*_*    : 구동중 속도 프로파일을 "S curve"를 이용한다. "*s_*"가 없다면 사다리꼴 가감속을 이용한다.
// *a*_*    : 구동중 속도 가감속도를 비대칭으로 사용한다. 가속률 또는 가속 시간과  감속률 또는 감속 시간을 각각 입력받는다.
// *_ex     : 구동중 가감속도를 가속 또는 감속 시간으로 입력 받는다. "*_ex"가 없다면 가감속률로 입력 받는다.
// 입력 값들: velocity(Unit/Sec), acceleration/deceleration(Unit/Sec^2), acceltime/deceltime(Sec), position(Unit)
//==================================================================================================
bool CAxtMotorCtrl::StartMotor(const int nAxis, const double dPos, const double dVel, const double dAcc)
{
	bool bRet = false;

	if (!MotorCtrlInit)
		return bRet;

	// ==========================================================
	if (m_nCardType == CAM5)
		bRet = C5Mstart_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);
	else if (m_nCardType == CFS)
		bRet = CFSstart_s_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);
	else if (m_nCardType == CFS2)
		bRet = CFS20start_s_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);
	else
		bRet = CFS20start_s_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::StartMove(const int nAxis, const double dPos, const double dVel, const double dAcc)
{
	//	Description ==========================================================
	//		: 지정 축의 절대 좌표로 설정된 위치까지 설정된 속도와 가속율로 사다리꼴 구동
	//		  Non Blocking함수 (구동중일 경우 무시됨)
	bool bRet = false;

	if (!MotorCtrlInit)
		return bRet;

	if (m_nCardType == CAM5)
		bRet = C5Mstart_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);
	else if (m_nCardType == CFS)
		bRet = CFSstart_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);
	else if (m_nCardType == CFS2)
		bRet = CFS20start_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);
	else
		bRet = CFS20start_move(nAxis, dPos, dVel/**m_RpmVel */, dAcc/**m_RpmVel */);

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::StartRMove(const int nAxis, const double dDistance, const double dVel, const double dAcc)
{
	bool bRet = false;

	if (!MotorCtrlInit)
		return bRet;

	if (m_nCardType == CAM5)
		bRet = C5Mstart_r_move(nAxis, dDistance, dVel, dAcc);
	else if (m_nCardType == CFS)
		bRet = CFSstart_r_move(nAxis, dDistance, dVel, dAcc);
	else if (m_nCardType == CFS2)
		bRet = CFS20start_r_move(nAxis, dDistance, dVel, dAcc);
	else
		bRet = CFS20start_r_move(nAxis, dDistance, dVel, dAcc);

	return bRet;
}
//---------------------------------------------------------------------------

/* 지정 축의 절대 좌표로 설정된 위치까지 설정
된 속도와 가속율로 S자형 구동
펄스 출력이 종료되는 시점에서 함수 탈출 */
bool CAxtMotorCtrl::MoveMotor(const int nAxis, const double dPos, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		return C5Mmove(nAxis, dPos, dVel, dAcc);
	else if (m_nCardType == CFS)
		return CFSs_move(nAxis, dPos, dVel, dAcc);
	else if (m_nCardType == CFS2)
		return CFS20s_move(nAxis, dPos, dVel, dAcc);
	else
		return CFS20s_move(nAxis, dPos, dVel, dAcc);
}
//---------------------------------------------------------------------------

/* 지정 축에 대하여 설정된 속도와 가속율로 지
속적으로 사다리꼴형 구동
펄스 출력이 시작되는 시점에서 함수 탈출 */
bool CAxtMotorCtrl::JogMove(const int nAxis, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		return C5Mv_move(nAxis, dVel, dAcc);
	else if (m_nCardType == CFS)
		return CFSv_move(nAxis, dVel, dAcc);
	else if (m_nCardType == CFS2)
		return CFS20v_move(nAxis, dVel, dAcc);
	else
		return CFS20v_move(nAxis, dVel, dAcc);
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::VMove(const int nAxis, const double dVel, const double dAcc)
{
	if (!MotorCtrlInit)
		return false;

	if (m_nCardType == CAM5)
		return C5Mv_move(nAxis, dVel, dAcc);
	else if (m_nCardType == CFS)
		return CFSv_s_move(nAxis, dVel, dAcc);
	else if (m_nCardType == CFS2)
		return CFS20v_s_move(nAxis, dVel, dAcc);
	else
		return CFS20v_s_move(nAxis, dVel, dAcc);
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::SetStop(const int nAxis)
{
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_stop(nAxis);
			break;
		case CFS:
			CFSset_stop(nAxis);
			break;
		case CFS2:
			CFS20set_stop(nAxis);
			break;
		default:
			CFS20set_stop(nAxis);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::SetEStop(const int nAxis)
{
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_e_stop(nAxis);
			break;
		case CFS:
			CFSset_e_stop(nAxis);
			break;
		case CFS2:
			CFS20set_e_stop(nAxis);
			break;
		default:
			CFS20set_e_stop(nAxis);
			break;
		}
	}
}
//---------------------------------------------------------------------------

bool CAxtMotorCtrl::StartRepeat(const int nAxis, const double dDistance, const double dVel, const double dAcc, const DWORD dWait)
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
void CAxtMotorCtrl::StopRepeat(const int nAxis)
{
	//if (!m_bRepeatAbort)
	//	m_bRepeatAbort = true;
}
//---------------------------------------------------------------------------

// Description	: Position -----------------------------------------
void	CAxtMotorCtrl::SetActPos(const int nAxis, const double pos)
{
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_actual_position(nAxis, pos);
			break;
		case CFS:
			CFSset_actual_position(nAxis, pos);
			break;
		case CFS2:
			CFS20set_actual_position(nAxis, pos);
			break;
		default:
			CFS20set_actual_position(nAxis, pos);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void	CAxtMotorCtrl::SetCmdPos(const int nAxis, const double pos)
{
	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			C5Mset_command_position(nAxis, pos);
			break;
		case CFS:
			CFSset_command_position(nAxis, pos);
			break;
		case CFS2:
			CFS20set_command_position(nAxis, pos);
			break;
		default:
			CFS20set_command_position(nAxis, pos);
			break;
		}
	}
}
//---------------------------------------------------------------------------
double	CAxtMotorCtrl::GetActPos(const int nAxis)
{
	double pos = -10.0f;

	if (MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			pos = C5Mget_actual_position(nAxis);
			break;
		case CFS:
			pos = CFSget_actual_position(nAxis);
			break;
		case CFS2:
			pos = CFS20get_actual_position(nAxis);
			break;
		default:
			pos = CFS20get_actual_position(nAxis);
			break;
		}
	}

	return pos;
}
//---------------------------------------------------------------------------
double	CAxtMotorCtrl::GetCmdPos(const int nAxis)
{
	double pos = -10.0f;

	if(MotorCtrlInit)
	{
		switch (m_nCardType)
		{
		case CAM5:
			pos = C5Mget_command_position(nAxis);
			break;
		case CFS:
			pos = CFSget_command_position(nAxis);
			break;
		case CFS2:
			pos = CFS20get_command_position(nAxis);
			break;
		default:
			pos = CFS20get_command_position(nAxis);
			break;
		}
	}

	return pos;
}
//---------------------------------------------------------------------------

// Description	: Scan Edge -----------------------------------------
void CAxtMotorCtrl::InitScanQ(const int nAxis)
{
	CFS20KeScriptQueueClear(nAxis);
	CFS20KeCaptionQueueClear(nAxis);
	LOG_PRINTF(m_strLogHead, L"InitScanQ FsExternalCounterRead Axis:%d [%d]", nAxis, FsExternalCounterRead);
}
//---------------------------------------------------------------------------
void CAxtMotorCtrl::SetScriptScan(const int nAxis, const int nServoType)
{
	FSEVENT nVal = nServoType ? EVENT_IN2_LOW : EVENT_IN3_LOW;

	CFS20KeSetScriptCaption(nAxis,
		CAPTION_REG1,				// Capture Reg(저장용 Script 1번을 사용, )
		OPERATION_CONTINUE_RUN |	// OPERATION_ONCE_RUN |		// 1 회만 동작.
		OPERATION_EVENT_NONE |		// 이벤트 비교는 없음.
		OPERATION_EVENT_2(0) |		// 2번째 이벤트 없음
		OPERATION_EVENT_1(nVal) |	//OPERATION_EVENT_1(EVENT_IN2_HIGH) |	// 1번째 이벤트 : Motion Universal Input 2번이 Active
		FsExternalCounterRead,		// 외부 위치 카운터 (Encoder) 값 확인 ( 내부 Command 값 확인 시 FsInternalCounterRead로 변경 )
		0);

	LOG_PRINTF(m_strLogHead, L"FsExternalCounterRead Axis:%d [%d]", nAxis, FsExternalCounterRead);
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::GetScriptScanResult(const int nAxis, DWORD *dwRet)
{
	int nResult = 0x00;
	UINT32 nScanPulse = 0x00;

	nResult = CFS20KeGetCaptionQueueFlag(nAxis);

	if ((nResult & 0x10) == 0x10)
	{
		*dwRet = CFS20KeGetCaption1Data(nAxis);
		LOG_PRINTF(m_strLogHead, L"CFS20KeGetCaption1Data Axis:%d [Val: %d]", nAxis, *dwRet);
		return true;
	}

	return false;
}
//---------------------------------------------------------------------------

// Description	: Universal DIO -----------------------------------------
bool CAxtMotorCtrl::GetAxtMotionLibInit(void)
{
	return MotorCtrlInit;
}
//---------------------------------------------------------------------------
INT16 CAxtMotorCtrl::GetTotalAxisCount(void)
{
	INT16 nTotAxis = 0;

	if (MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			nTotAxis = C5Mget_total_numof_axis();
//			break;
//		case CFS:
//			nTotAxis = CFSget_total_numof_axis();
//			break;
//		case CFS2:
//			nTotAxis = CFS20get_total_numof_axis();
//			break;
//		default:
			nTotAxis = CFS20get_total_numof_axis();
//			break;
//		}
	}

	return nTotAxis;
}
//---------------------------------------------------------------------------

BYTE CAxtMotorCtrl::GetOutputByte(const int nAxis)
{
	BYTE byRet = 0x00;

	if(MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			byRet = C5Mget_output(nAxis);
//			break;
//		case CFS:
//			byRet = CFSget_output(nAxis);
//			break;
//		case CFS2:
//			byRet = CFS20get_output(nAxis);
//			break;
//		default:
			byRet = CFS20get_output(nAxis);
//			break;
//		}
	}

	return byRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::GetOutputBit(const int nAxis, const int nOffset)
{
	bool bRet = false;

	if(MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			bRet = C5Moutput_bit_on(nAxis, nOffset);
//			break;
//		case CFS:
//			bRet = CFSoutput_bit_on(nAxis, nOffset);
//			break;
//		case CFS2:
//			bRet = CFS20output_bit_on(nAxis, nOffset);
//			break;
//		default:
			bRet = CFS20output_bit_on(nAxis, nOffset);
//			break;
//		}
	}

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::SetOutputBit(const int nAxis, const int nOffset)
{
	bool bRet = false;

	if(MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			bRet = C5Mset_output_bit(nAxis, nOffset);
//			break;
//		case CFS:
//			bRet = CFSset_output_bit(nAxis, nOffset);
//			break;
//		case CFS2:
//			bRet = CFS20set_output_bit(nAxis, nOffset);
//			break;
//		default:
			bRet = CFS20set_output_bit(nAxis, nOffset);
//			break;
//		}
	}

	return bRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::ResetOutputBit(const int nAxis, const int nOffset)
{
	bool bRet = false;

	if(MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			bRet = C5Mreset_output_bit(nAxis, nOffset);
//			break;
//		case CFS:
//			bRet = CFSreset_output_bit(nAxis, nOffset);
//			break;
//		case CFS2:
//			bRet = CFS20reset_output_bit(nAxis, nOffset);
//			break;
//		default:
			bRet = CFS20reset_output_bit(nAxis, nOffset);
//			break;
//		}
	}

	return bRet;
}
//---------------------------------------------------------------------------

BYTE CAxtMotorCtrl::GetInputputByte(const int nAxis)
{
	BYTE byRet = 0x00;

	if(MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			byRet = C5Mget_input(nAxis);
//			break;
//		case CFS:
//			byRet = CFSget_input(nAxis);
//			break;
//		case CFS2:
//			byRet = CFS20get_input(nAxis);
//			break;
//		default:
			byRet = CFS20get_input(nAxis);
//			break;
//		}
	}

	return byRet;
}
//---------------------------------------------------------------------------
bool CAxtMotorCtrl::GetInputBit(const int nAxis, const int nOffset)
{
	bool bRet = false;

	if(MotorCtrlInit)
	{
//		switch (m_nCardType)
//		{
//		case CAM5:
//			bRet = C5Minput_bit_on(nAxis, nOffset);
//			break;
//		case CFS:
//			bRet = CFSinput_bit_on(nAxis, nOffset);
//			break;
//		case CFS2:
//			bRet = CFS20input_bit_on(nAxis, nOffset);
//			break;
//		default:
			bRet = CFS20input_bit_on(nAxis, nOffset);
//			break;
//		}
	}

	return bRet;
}
//---------------------------------------------------------------------------
