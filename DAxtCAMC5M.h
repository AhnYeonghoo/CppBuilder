#ifndef __AXT_DAXTCAMC5M_H__
#define __AXT_DAXTCAMC5M_H__

#include "AxtLIBDef.h"
#include "CAMC5MDef.h"

/*------------------------------------------------------------------------------------------------*
	AXTCAMC5M Library - CAMC-5M Motion module
	적용제품
		SMC-1V01 - CAMC-5M 1축
		SMC-2V01 - CAMC-5M 2축
 *------------------------------------------------------------------------------------------------*/

/// 초기화 함수군
// CAMC-5M이 장착된 모듈(SMC-1V01, SMC-2V01)을 검색하여 초기화한다. CAMC-5M 1.0만 검출한다
typedef BOOL    PASCAL EXPORT funcInitializeCAMC5M(BOOL reset);
// reset	: 1(TRUE) = 레지스터(카운터 등)를 초기화한다
//  reset(TRUE)일때 초기 설정값.
//  1) 인터럽트 사용하지 않음.
//  2) 인포지션 기능 사용하지 않음.
//  3) 알람정지 기능 사용하지 않음.
//  4) 급정지 리미트 기능 사용 함.
//  5) 감속정지 리미트 기능 사용 함.            
//  6) 펄스 출력 모드 : OneLowHighLow(Pulse : Active LOW, Direction : CW{High};CCW{LOW}).
//  7) 검색 신호 : +급정지 리미트 신호 하강 에지.
//  8) 입력 인코더 설정 : 2상, 4 체배.
//  9) 알람, 인포지션, +-감속 정지 리미트, +-급정지 리미트 Active level : HIGH
// 10) 내부/외부 카운터 : 0.
// CAMC-5M 모듈의 사용이 가능한지를 혹인한다
typedef BOOL    PASCAL EXPORT funcC5MIsInitialized(void);
// 리턴값 :  1(TRUE) = CAMC-5M 모듈을 사용 가능하다
// CAMC-5M이 장착된 모듈의 사용을 종료한다
typedef void    PASCAL EXPORT funcC5MStopService();

/// 보드 정보 관련 함수군        -===================================================================================
// 지정한 주소에 장착된 베이스보드의 번호를 리턴한다. 없으면 -1을 리턴한다
typedef INT16	PASCAL EXPORT funcC5Mget_boardno(UINT32 address);
// 베이스보드의 갯수를 리턴한다
typedef INT16	PASCAL EXPORT funcC5Mget_numof_boards();
// 지정한 베이스보드에 장착된 축의 갯수를 리턴한다
typedef INT16	PASCAL EXPORT funcC5Mget_numof_axes(INT16 nBoardNo);
// 축의 갯수를 리턴한다
typedef INT16	PASCAL EXPORT funcC5Mget_total_numof_axis();
// 지정한 베이스보드번호와 모듈번호에 해당하는 축번호를 리턴한다
typedef INT16	PASCAL EXPORT funcC5Mget_axisno(INT16 nBoardNo, INT16 nModuleNo);
// 지정한 축의 정보를 리턴한다
// nBoardNo : 해당 축이 장착된 베이스보드의 번호.
// nModuleNo: 해당 축이 장착된 모듈의 베이스 모드내 모듈 위치(0~3)
// bModuleID: 해당 축이 장착된 모듈의 ID : SMC-2V01(0x01)
// nAxisPos : 해당 축이 장착된 모듈의 첫번째인지 두번째 축인지 정보.(0 : 첫번째, 1 : 두번째)
typedef BOOL	PASCAL EXPORT funcC5Mget_axis_info(INT16 nAxisNo, INT16 *nBoardNo, INT16 *nModuleNo, UINT8 *bModuleID, INT16 *nAxisPos);

// 파일 관련 함수군        -========================================================================================
// 지정 축의 초기값을 지정한 파일에서 읽어서 설정한다
// Loading parameters.
//	1) 1Pulse당 이동거리(Move Unit / Pulse)
//	2) 최대 이동 속도, 시작/정지 속도
//	3) 엔코더 입력방식, 펄스 출력방식 
//	4) +급정지 리미트레벨, -급정지 리미트레벨, 급정지 리미트 사용유무
//  5) +감속정지 리미트레벨,-감속정지 리미트레벨, 감속정지 리미트 사용유무
//  6) 알람레벨, 알람 사용유무
//  7) 인포지션(위치결정완료 신호)레벨, 인포지션 사용유무
//  8) 비상정지 사용유무
//  9) 내부/외부 카운터 : 0. 	
typedef BOOL	PASCAL EXPORT funcC5Mload_parameter(INT16 axis, char *nfilename);
// 지정 축의 초기값을 지정한 파일에 저장한다.
// Saving parameters.
//	1) 1Pulse당 이동거리(Move Unit / Pulse)
//	2) 최대 이동 속도, 시작/정지 속도
//	3) 엔코더 입력방식, 펄스 출력방식 
//	4) +급정지 리미트레벨, -급정지 리미트레벨, 급정지 리미트 사용유무
//  5) +감속정지 리미트레벨,-감속정지 리미트레벨, 감속정지 리미트 사용유무
//  6) 알람레벨, 알람 사용유무
//  7) 인포지션(위치결정완료 신호)레벨, 인포지션 사용유무
//  8) 비상정지 사용유무
typedef BOOL	PASCAL EXPORT funcC5Msave_parameter(INT16 axis, char *nfilename);
// 모든 축의 초기값을 지정한 파일에서 읽어서 설정한다
typedef BOOL	PASCAL EXPORT funcC5Mload_parameter_all(char *nfilename);
// 모든 축의 초기값을 지정한 파일에 저장한다
typedef BOOL	PASCAL EXPORT funcC5Msave_parameter_all(char *nfilename);

// 인터럽트 함수군   -================================================================================================
//(인터럽트를 사용하기 위해서는 
//Window message & procedure
//    hWnd    : 윈도우 핸들, 윈도우 메세지를 받을때 사용. 사용하지 않으면 NULL을 입력.
//    wMsg    : 윈도우 핸들의 메세지, 사용하지 않거나 디폴트값을 사용하려면 0을 입력.
//    proc    : 인터럽트 발생시 호출될 함수의 포인터, 사용하지 않으면 NULL을 입력.
typedef void	PASCAL EXPORT funcC5MSetWindowMessage(HANDLE hWnd, UINT16 wMsg, AXT_CAMC5M_INTERRUPT_PROC proc);

// 구동 설정 초기화 함수군        -==================================================================================
// 메인클럭 설정( 모듈에 장착된 Oscillator가 변경될 경우에만 설정)
typedef void	PASCAL EXPORT funcC5MKeSetMainClk(INT32 nMainClk);
// Drive mode 1의 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_drive_mode1(INT16 axis, 
				UINT8 decelstartpoint,
				UINT8 pulseoutmethod,
				UINT8 detectsignal);
typedef UINT8	PASCAL EXPORT funcC5Mget_drive_mode1(INT16 axis);
// decelstartpoint : 지정거리 구동 기능 사용중 감속 위치 지정 방식 설정(0 : 자동 가감속, 1 : 수동 가감속)
// pulseoutmethod : 출력 펄스 방식 설정(typedef : PULSE_OUTPUT)
// detecsignal : 신호 검색-1/2 구동 기능 사용중 검색 할 신호 설정(typedef : DETECT_DESTINATION_SIGNAL)
// Drive mode 2의 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_drive_mode2(INT16 axis, 
				UINT8 encmethod,
				UINT8 inpactivelevel,
				UINT8 alarmactivelevel,
				UINT8 nslmactivelevel,
				UINT8 pslmactivelevel,
				UINT8 nelmactivelevel,
				UINT8 pelmactivelevel);
typedef UINT8	PASCAL EXPORT funcC5Mget_drive_mode2(INT16 axis);
// Unit/Pulse 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_moveunit_perpulse(INT16 axis, double unitperpulse);
typedef double	PASCAL EXPORT funcC5Mget_moveunit_perpulse(INT16 axis);
// Unit/Pulse : 1 pulse에 대한 system의 이동거리를 말하며, 이때 Unit의 기준은 사용자가 임의로 생각할 수 있다.
// Ex) Ball screw pitch : 10mm, 모터 1회전당 펄스수 : 10000 ==> Unit을 mm로 생각할 경우 : Unit/Pulse = 10/10000.
// 따라서 unitperpulse에 0.001을 입력하면 모든 제어단위가 mm로 설정됨. 
// Ex) Linear motor의 분해능이 1 pulse당 2 uM. ==> Unit을 mm로 생각할 경우 : Unit/Pulse = 0.002/1.
// Unit/Pulse와 역수관계
// pulse/Unit 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_movepulse_perunit(INT16 axis, INT32 pulseperunit);
typedef INT32	PASCAL EXPORT funcC5Mget_movepulse_perunit(INT16 axis);
// 시작 속도 설정/확인한다.(Unit/Sec)
typedef void	PASCAL EXPORT funcC5Mset_startstop_speed(INT16 axis, double velocity);
typedef double	PASCAL EXPORT funcC5Mget_startstop_speed(INT16 axis);
// 최고 속도 설정 Unit/Sec. 제어 system의 최고 속도를 설정한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_max_speed(INT16 axis, double max_velocity);
typedef double	PASCAL EXPORT funcC5Mget_max_speed(INT16 axis);
// Unit/Pulse 설정과 시작속도 설정 이후에 설정한다.
// 설정된 최고 속도 이상으로는 구동을 할수 없으므로 주의한다.
// SW에 관계된 값을 설정/확인한다. 이값으로 Quasi S-Curve 구간을 percentage로 설정 가능하다.
typedef void	PASCAL EXPORT funcC5Mset_qs_rate(INT16 axis, double a_percent, double b_percent);
typedef void	PASCAL EXPORT funcC5Mget_qs_rate(INT16 axis, double *a_percent, double *b_percent);
// 수동 가감속 모드에서 잔량 펄스를 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_slowdown_rear_pulse(INT16 axis, UINT32 ulData);
typedef UINT32	PASCAL EXPORT funcC5Mget_slowdown_rear_pulse(INT16 axis);
// 지정 축의 감속 시작 포인터 검출 방식을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_decel_point(INT16 axis, UINT8 method);
typedef UINT8	PASCAL EXPORT funcC5Mget_decel_point(INT16 axis);
// 0x0 : 자동 가감속.
// 0x1 : 수동 가감속.

// 구동 상태 확인 함수군        -=====================================================================================
// 지정 축의 펄스 출력중인지를 확인한다.
typedef BOOL	PASCAL EXPORT funcC5Min_motion(INT16 axis);
// 지정 축의 펄스 출력이 종료됐는지 확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mmotion_done(INT16 axis);
// 지정 축의 구동시작 이후 출력된 펄스 카운터 값을 확인한다. (Pulse)
typedef INT32	PASCAL EXPORT funcC5Mget_drive_pulse_counts(INT16 axis);
// 지정 축의 DriveStatus 레지스터를 확인한다.
typedef UINT8	PASCAL EXPORT funcC5Mget_drive_status(INT16 axis);
// 지정 축의 EndStatus 레지스터를 확인한다.
typedef UINT8	PASCAL EXPORT funcC5Mget_end_status(INT16 axis);
// End Status Bit별 의미
// 7 bit : 데이타 설정 에러에 의한 종료
// 6 bit : ALARM 신호 입력에 의한 종료
// 5 bit : 급정지 명령에 의한 종료
// 4 bit : 감속정지 명령에 의한 종료
// 3 bit : 급정지 신호 입력에 의한 종료 (EMG Button)
// 2 bit : 감속정지 신호 입력에 의한 종료
// 1 bit : Limit(PELM, NELM, Soft) 급정지에 의한 종료
// 0 bit : Limit(PSLM, NSLM, Soft) 감속정지에 의한 종료
typedef UINT8	PASCAL EXPORT funcC5Mget_mechanical_signal(INT16 axis);
// 7 bit : Encoder Up신호 입력 Level(A상 신호)
// 6 bit : Encoder Down신호 입력 Level(B상 신호)
// 5 bit : INPOSITION 신호 Active 상태
// 4 bit : ALARM 신호 Active 상태
// 3 bit : -Limit 감속정지 신호 Active 상태 (Ver3.0부터 사용되지않음)
// 2 bit : +Limit 감속정지 신호 Active 상태 (Ver3.0부터 사용되지않음)
// 1 bit : -Limit 급정지 신호 Active 상태
// 0 bit : +Limit 급정지 신호 Active 상태
// 지정 축의  현재 속도를 읽어 온다.(Unit/Sec)
typedef double	PASCAL EXPORT funcC5Mget_velocity(INT16 axis);
// 지정 축의 Command position과 Actual position의 차를 확인한다.
typedef double	PASCAL EXPORT funcC5Mget_error(INT16 axis);
// 지정 축의 최후 드라이브의 이동 거리를 확인 한다. (Unit)
typedef double	PASCAL EXPORT funcC5Mget_drivedistance(INT16 axis);

//Encoder 입력 방식 설정 함수군        -=============================================================================
// 지정 축의 Encoder 입력 방식을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_enc_input_method(INT16 axis, UINT8 method);
typedef UINT8	PASCAL EXPORT funcC5Mget_enc_input_method(INT16 axis);
// method : typedef(EXTERNAL_COUNTER_INPUT)
// UpDownMode = 0x0    // Up/Down
// Sqr1Mode   = 0x1    // 1체배
// Sqr2Mode   = 0x2    // 2체배
// Sqr4Mode   = 0x3    // 4체배

// 펄스 출력 방식 함수군        -=====================================================================================
// 펄스 출력 방식을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_pulse_out_method(INT16 axis, UINT8 method);
typedef UINT8	PASCAL EXPORT funcC5Mget_pulse_out_method(INT16 axis);
// method : 출력 펄스 방식 설정(typedef : PULSE_OUTPUT)
// OneHighLowHigh   = 0x0, 1펄스 방식, PULSE(Active High), 정방향(DIR=Low)  / 역방향(DIR=High)
// OneHighHighLow   = 0x1, 1펄스 방식, PULSE(Active High), 정방향(DIR=High) / 역방향(DIR=Low)
// OneLowLowHigh    = 0x2, 1펄스 방식, PULSE(Active Low),  정방향(DIR=Low)  / 역방향(DIR=High)
// OneLowHighLow    = 0x3, 1펄스 방식, PULSE(Active Low),  정방향(DIR=High) / 역방향(DIR=Low)
// TwoCcwCwHigh     = 0x4, 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active High 
// TwoCcwCwLow      = 0x5, 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active Low 
// TwoCwCcwHigh     = 0x6, 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active High
// TwoCwCcwLow      = 0x7, 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active Low

// 위치 확인 및 위치 비교 설정 함수군 -===============================================================================
// 외부 위치 값을 설정한다. 현재의 상태에서 외부 위치를 특정 값으로 설정/확인한다.(position = Unit)
typedef void	PASCAL EXPORT funcC5Mset_actual_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_actual_position(INT16 axis);
// 내부 위치 값을 설정한다. 현재의 상태에서 내부 위치를 특정 값으로 설정/확인한다.(position = Unit)
typedef void	PASCAL EXPORT funcC5Mset_command_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_command_position(INT16 axis);

// 서보 드라이버 출력 신호 설정 함수군-===============================================================================
// 서보 Enable출력 신호의 Active Level을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_servo_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_servo_level(INT16 axis);
// 서보 Enable(On) / Disable(Off)을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_servo_enable(INT16 axis, UINT8 state);
typedef UINT8	PASCAL EXPORT funcC5Mget_servo_enable(INT16 axis);

// 서보 드라이버 입력 신호 설정 함수군-===============================================================================
// 서보 위치결정완료(inposition)입력 신호의 사용유무를 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_inposition_enable(INT16 axis, UINT8 use);
typedef UINT8	PASCAL EXPORT funcC5Mget_inposition_enable(INT16 axis);
// 서보 위치결정완료(inposition)입력 신호의 Active Level을 설정/확인/상태확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_inposition_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_inposition_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_inposition_switch(INT16 axis);
typedef BOOL	PASCAL EXPORT funcC5Min_position(INT16 axis);
// 서보 알람 입력신호 기능의 사용유무를 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_alarm_enable(INT16 axis, UINT8 use);
typedef UINT8	PASCAL EXPORT funcC5Mget_alarm_enable(INT16 axis);
// 서보 알람 입력 신호의 Active Level을 설정/확인/상태확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_alarm_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_alarm_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_alarm_switch(INT16 axis);

// 리미트 신호 설정 함수군-===========================================================================================
// -급정지 리미트 입력 신호의 Active Level을 설정/확인/상태확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_nend_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_nend_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_nend_limit_switch(INT16 axis);
// +급정지 리미트 입력 신호의 Active Level을 설정/확인/상태확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_pend_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_pend_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_pend_limit_switch(INT16 axis);
// -감속정지 리미트 입력 신호의 Active Level을 설정/확인/상태확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_nslow_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_nslow_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_nslow_limit_switch(INT16 axis);
// +감속정지 리미트 입력 신호의 Active Level을 설정/확인/상태확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_pslow_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_pslow_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_pslow_limit_switch(INT16 axis);
// -LIMIT 센서 감지시 급/감속정지 여부를 설정/확인한다. (Ver 3.0부터 적용)
typedef BOOL	PASCAL EXPORT funcC5Mset_nlimit_sel(INT16 axis, UINT8 stop);
typedef UINT8	PASCAL EXPORT funcC5Mget_nlimit_sel(INT16 axis);
// stop:
// 0 : 급정지, 1 : 감속정지
// +LIMIT 센서 감지시 급/감속정지 여부를 설정/확인한다. (Ver 3.0부터 적용)	
typedef BOOL	PASCAL EXPORT funcC5Mset_plimit_sel(INT16 axis, UINT8 stop);
typedef UINT8	PASCAL EXPORT funcC5Mget_plimit_sel(INT16 axis);

// 비상정지 신호-=====================================================================================================
// 비상정지의 급/감속정지 여부를 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop_sel(INT16 axis, UINT8 stop);
typedef UINT8	PASCAL EXPORT funcC5Mget_stop_sel(INT16 axis);

// 단축 지정 거리 구동-===============================================================================================
// start_** : 지정 축에서 구동 시작후 함수를 return한다. "start_*" 가 없으면 이동 완료후 return한다(Blocking).
// *r*_*    : 지정 축에서 입력된 거리만큼(상대좌표)로 이동한다. "*r_*이 없으면 입력된 위치(절대좌표)로 이동한다.
// *qs*_*   : 구동중 속도 프로파일을 "Quasi S curve"를 이용한다. "*qs_*"가 없다면 사다리꼴 가감속을 이용한다.
// *_ex     : 구동중 가감속도를 가속 또는 감속 시간으로 입력 받는다. "*_ex"가 없다면 가감속률로 입력 받는다.
// 입력 값들: velocity(Unit/Sec), acceleration/deceleration(Unit/Sec^2), acceltime/deceltime(Sec), position(Unit)

// 지정펄스(Pulse Drive), 사다리꼴 구동 함수, 절대/상대좌표(r), 가속율/가속시간(_ex)(시간단위:Sec)
// Blocking함수 (제어권이 펄스 출력이 완료된 후 넘어옴)
typedef UINT8	PASCAL EXPORT funcC5Mmove(INT16 axis, double position, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mmove_ex(INT16 axis, double position, double velocity, double acceltime);
typedef UINT8	PASCAL EXPORT funcC5Mr_move(INT16 axis, double distance, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mr_move_ex(INT16 axis, double distance, double velocity, double acceltime);
// Non Blocking함수 (구동중일 경우 무시됨)
typedef BOOL	PASCAL EXPORT funcC5Mstart_move(INT16 axis, double position, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_ex(INT16 axis, double position, double velocity, double acceltime);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move(INT16 axis, double distance, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move_ex(INT16 axis, double distance, double velocity, double acceltime);
// 지정펄스(Pulse Drive), Quasi S자형 구동, 절대/상대좌표(r), 가속율/가속시간(_ex)(시간단위:Sec)
// Blocking함수 (제어권이 펄스 출력이 완료된 후 넘어옴)
typedef UINT8	PASCAL EXPORT funcC5Mqs_move(INT16 axis, double position, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mqs_move_ex(INT16 axis, double position, double velocity, double acceltime);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move(INT16 axis, double distance, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move_ex(INT16 axis, double distance, double velocity, double acceltime);
// Non Blocking함수 (구동중일 경우 무시됨)
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move(INT16 axis, double position, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move_ex(INT16 axis, double position, double velocity, double acceltime);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move(INT16 axis, double distance, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move_ex(INT16 axis, double distance, double velocity, double acceltime);

// 단축 연속 구동-====================================================================================================
// 지정 가감속도 및 속도로 정지 조건이 발생하지 않으면 지속적으로 구동한다.
// *qs*_*    : 구동중 속도 프로파일을 "S curve"를 이용한다. "*s_*"가 없다면 사다리꼴 가감속을 이용한다.
// *_ex     : 구동중 가감속도를 가속 또는 감속 시간으로 입력 받는다. "*_ex"가 없다면 가감속률로 입력 받는다.

// 정속도 사다리꼴 구동 함수군, 가속율/가속시간(_ex)(시간단위:Sec) - 구동중일 경우에는 속도오버라이드
typedef BOOL	PASCAL EXPORT funcC5Mv_move(INT16 axis, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mv_move_ex(INT16 axis, double velocity, double acceltime);
// 정속도 Quasi S자형 구동 함수군, 가속율/가속시간(_ex)(시간단위:Sec) - 구동중일 경우에는 속도오버라이드
typedef BOOL	PASCAL EXPORT funcC5Mv_qs_move(INT16 axis, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mv_qs_move_ex(INT16 axis, double velocity, double acceltime);

// 신호 검출 구동-====================================================================================================
// 지정 신호의 상향/하향 에지를 검색하여 급정지 또는 감속정지를 할 수 있다.
// detect_signal : 검색 신호 설정(typedef : DETECT_DESTINATION_SIGNAL)
// PElmNegativeEdge    = 0x0,        // +Elm(End limit) 하강 edge
// NElmNegativeEdge    = 0x1,        // -Elm(End limit) 하강 edge
// PSlmNegativeEdge    = 0x2,        // +Slm(Slowdown limit) 하강 edge
// NSlmNegativeEdge    = 0x3,        // -Slm(Slowdown limit) 하강 edge
// In0DownEdge         = 0x4,        // IN0(ORG) 하강 edge
// In1DownEdge         = 0x5,        // IN1(Z상) 하강 edge
// In2DownEdge         = 0x6,        // IN2(범용) 하강 edge
// In3DownEdge         = 0x7,        // IN3(범용) 하강 edge
// PElmPositiveEdge    = 0x8,        // +Elm(End limit) 상승 edge
// NElmPositiveEdge    = 0x9,        // -Elm(End limit) 상승 edge
// PSlmPositiveEdge    = 0xa,        // +Slm(Slowdown limit) 상승 edge
// NSlmPositiveEdge    = 0xb,        // -Slm(Slowdown limit) 상승 edge
// In0UpEdge           = 0xc,        // IN0(ORG) 상승 edge
// In1UpEdge           = 0xd,        // IN1(Z상) 상승 edge
// In2UpEdge           = 0xe,        // IN2(범용) 상승 edge
// In3UpEdge           = 0xf         // IN3(범용) 상승 edge
// Signal Search1 : 구동 시작후 입력 속도까지 가속하여, 신호 검출후 감속 정지.
// Signal Search2 : 구동 시작후 가속없이 입력 속도가 되고, 신호 검출후 급정지. 
// 주의 : Signal Search2는 가감속이 없으므로 속도가 높을경우 탈조및 기구부의 무리가 갈수 있으므로 주의한다.
// *s*_*    : 구동중 속도 프로파일을 "S curve"를 이용한다. "*s_*"가 없다면 사다리꼴 가감속을 이용한다.
// *_ex     : 구동중 가감속도를 가속 또는 감속 시간으로 입력 받는다. "*_ex"가 없다면 가감속률로 입력 받는다.

// 신호검출1(Signal search 1) 사다리꼴 구동, 가속율/가속시간(_ex)(시간단위:Sec)
typedef BOOL	PASCAL EXPORT funcC5Mstart_signal_search1(INT16 axis, double velocity, double acceleration, UINT8 detect_signal);
typedef BOOL	PASCAL EXPORT funcC5Mstart_signal_search1_ex(INT16 axis, double velocity, double acceltime, UINT8 detect_signal);
// 신호검출1(Signal search 1) Quasi S자형 구동, 가속율/가속시간(_ex)(시간단위:Sec)
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_signal_search1(INT16 axis, double velocity, double acceleration, UINT8 detect_signal);
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_signal_search1_ex(INT16 axis, double velocity, double acceltime, UINT8 detect_signal);
// 신호검출2(Signal search 2) 사다리꼴 구동, 가감속 없음
typedef BOOL	PASCAL EXPORT funcC5Mstart_signal_search2(INT16 axis, double velocity, UINT8 detect_signal);

// 오버라이드(구동중)-================================================================================================
// 단축 지정 거리 구동시 구동 시작시점에서 입력한 위치(절대위치)를 구동중 바꾼다.
typedef BOOL	PASCAL EXPORT funcC5Mposition_override(INT16 axis, double overrideposition);
// 단축 지정 거리 구동시 구동 시작시점에서 입력한 거리(상대위치)를 구동중 바꾼다.    
typedef BOOL	PASCAL EXPORT funcC5Mposition_r_override(INT16 axis, double overridedistance);	

// 단축 구동 확인-====================================================================================================
// 지정 축의 구동이 종료될 때까지 기다린 후 함수를 벗어난다.
typedef UINT8	PASCAL EXPORT funcC5Mwait_for_done(INT16 axis);	

// 단축 구동 정지-====================================================================================================
// 지정 축을 급정지한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_e_stop(INT16 axis);
// 지정 축을 구동시 감속율로 정지한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop(INT16 axis);
// 지정 축을 입력된 감속율로 정지한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop_decel(INT16 axis, double deceleration);
// 지정 축을 입력된 감속 시간으로 정지한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop_deceltime(INT16 axis, double deceltime);

// 다축 동기 구동관련 설정-==========================================================================================
// Master/Slave link 또는 좌표계 link 둘중 하나를 사용하여야 한다.
// Master/Slave link 설정. (일반 단축 구동시 master 축 구동시 slave축도 같이 구동된다.)
// Master/Slave link 설정
typedef BOOL	PASCAL EXPORT funcC5Mlink(INT16 master, INT16 slave, double ratio);
// Master/Slave link 해제
typedef BOOL	PASCAL EXPORT funcC5Mendlink(INT16 slave);

// 좌표계 link 설정-================================================================================================
// 지정 좌표계에 축 할당 - n_axes갯수만큼의 축수를 설정/확인한다.(coordinate는 1..8까지 사용 가능)
// n_axes 갯수만큼의 축수를 설정/확인한다. - (n_axes는 1..4까지 사용 가능)
typedef BOOL	PASCAL EXPORT funcC5Mmap_axes(INT16 coordinate, INT16 n_axes, INT16 *map_array);
typedef BOOL	PASCAL EXPORT funcC5Mget_mapped_axes(INT16 coordinate, INT16 n_axes, INT16 *map_array);
// 지정 좌표계의 상대/절대 모드 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_coordinate_mode(INT16 coordinate, INT16 mode);
typedef INT16	PASCAL EXPORT funcC5Mget_coordinate_mode(INT16 coordinate);
// mode:
// 0: 상대좌표구동, 1: 절대좌표 구동
// 지정 좌표계의 속도 프로파일 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_move_profile(INT16 coordinate, INT16 mode);
typedef INT16	PASCAL EXPORT funcC5Mget_move_profile(INT16 coordinate);
// mode:
// 0: 사다리꼴 구동, 1: Quasi S커브 구동
// 지정 좌표계의 초기 속도를 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_move_startstop_velocity(INT16 coordinate, double velocity);
typedef double	PASCAL EXPORT funcC5Mget_move_startstop_velocity(INT16 coordinate);
// 지정 좌표계의 초기 속도를 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_move_velocity(INT16 coordinate, double velocity);
typedef double	PASCAL EXPORT funcC5Mget_move_velocity(INT16 coordinate);
// 특정 좌표계의 가속율을 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_move_acceleration(INT16 coordinate, double acceleration);
typedef double	PASCAL EXPORT funcC5Mget_move_acceleration(INT16 coordinate);
// 특정 좌표계의 가속 시간(Sec)을 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_move_acceltime(INT16 coordinate, double acceltime);
typedef double	PASCAL EXPORT funcC5Mget_move_acceltime(INT16 coordinate);
// 보간 구동중인  좌표계의 현재 속도를 반환한다.
typedef double	PASCAL EXPORT funcC5Mco_get_velocity(INT16 coordinate);

// 소프트웨어 보간 구동(지정 좌표계에 대하여)-========================================================================
// Blocking함수 (제어권이 펄스 출력이 완료된 후 넘어옴)
// 2, 3, 4축이 동시이동한다.
typedef BOOL	PASCAL EXPORT funcC5Mmove_2(INT16 coordinate, double x, double y);
typedef BOOL	PASCAL EXPORT funcC5Mmove_3(INT16 coordinate, double x, double y, double z);
typedef BOOL	PASCAL EXPORT funcC5Mmove_4(INT16 coordinate, double x, double y, double z, double w);
// Non Blocking함수 (구동중일 경우 무시됨)
// 2, 3, 4축이 동시 이동한다.
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_2(INT16 coordinate, double x, double y);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_3(INT16 coordinate, double x, double y, double z);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_4(INT16 coordinate, double x, double y, double z, double w);
// 지정 좌표계의 모든축의 모션 완료 체크    
typedef BOOL	PASCAL EXPORT funcC5Mco_motion_done(INT16 coordinate);
// 지정 좌표계의 구동이 완료될때 까지 기다린다.
typedef BOOL	PASCAL EXPORT funcC5Mco_wait_for_done(INT16 coordinate);

// 다축 구동(동기 구동) : Master/Slave로 link되어 있을 경우 오류가 발생 할 수 있다.-==================================
// 지정 축들을 지정 거리 및 속도 가속도 정보로 동기 시작 구동한다. 구동 시작에 대한 동기화시 사용한다. 
// start_** : 지정 축에서 구동 시작후 함수를 return한다. "start_*" 가 없으면 이동 완료후 return한다.
// *r*_*    : 지정 축에서 입력된 거리만큼(상대좌표)로 이동한다. "*r_*이 없으면 입력된 위치(절대좌표)로 이동한다.
// *qs*_*    : 구동중 속도 프로파일을 "Quasi S curve"를 이용한다. "*qs_*"가 없다면 사다리꼴 가감속을 이용한다.
// *_ex     : 구동중 가감속도를 가속 또는 감속 시간으로 입력 받는다. "*_ex"가 없다면 가감속률로 입력 받는다.

// 다축 지정펄스(Pulse Drive)구동, 사다리꼴 구동, 절대/상대좌표(r), 가속율/가속시간(_ex)(시간단위:Sec)
// Blocking함수 (제어권이 모든 구동축의 펄스 출력이 완료된 후 넘어옴)
typedef UINT8	PASCAL EXPORT funcC5Mmove_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mmove_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef UINT8	PASCAL EXPORT funcC5Mr_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mr_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
// Non Blocking함수 (구동중인 축은 무시됨)
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
// 다축 지정펄스(Pulse Drive)구동, S자형 구동, 절대/상대좌표(r), 가속율/가속시간(_ex)(시간단위:Sec)
// Blocking함수 (제어권이 모든 구동축의 펄스 출력이 완료된 후 넘어옴)
typedef UINT8	PASCAL EXPORT funcC5Mqs_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mqs_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
// Non Blocking함수 (구동중인 축은 무시됨)
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
//지정 축들에 대하여 S자형 구동을 위한 가감속시의 Quasi S커브의 비율을 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_qs_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);
typedef void	PASCAL EXPORT funcC5Mget_qs_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);

// 다축 구동 확인-====================================================================================================
// 입력 해당 축들의 구동 상태를 확인하고 구동이 끝날 때 까지 기다린다.
typedef UINT8	PASCAL EXPORT funcC5Mwait_for_all(INT16 number, INT16 *axes);

// 다축 동기 설정-====================================================================================================
// 지정 축들의 동기를 해제시킨다. - 구동명령이 내려져도 구동되지않고 대기함.
typedef BOOL	PASCAL EXPORT funcC5Mreset_axis_sync(INT16 nLen, INT16 *aAxis);
// 지정 축들의 동기를 해제시킨다. - 구동명령이 내려져도 구동되지않고 대기함.
typedef BOOL	PASCAL EXPORT funcC5Mset_axis_sync(INT16 nLen, INT16 *aAxis);
// 지정한 베이스 보드에 장착된 축들을 동기설정/확인한다. 
typedef BOOL	PASCAL EXPORT funcC5Mset_sync(INT16 nBoardNo, UINT8 byState);
typedef UINT8	PASCAL EXPORT funcC5Mget_sync_info(INT16 nBoardNo);
// byState:
// bit 7 : (SUB4 Axis 1) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 6 : (SUB4 Axis 0) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 5 : (SUB3 Axis 1) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 4 : (SUB3 Axis 0) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 3 : (SUB2 Axis 1) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 2 : (SUB2 Axis 0) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 1 : (SUB1 Axis 1) - 0: 모터 구동하지 않음, 1: 모터 구동함
// bit 0 : (SUB1 Axis 0) - 0: 모터 구동하지 않음, 1: 모터 구동함

// 다축 구동 정지-====================================================================================================
// 홈 서치 쓰레드도 정지
typedef BOOL	PASCAL EXPORT funcC5Memergency_stop();	

// -원점검색 =========================================================================================================
// 라이브러리 상에서 Thread를 사용하여 검색한다. 주의 : 구동후 칩내의 StartStop Speed가 변할 수 있다.
// 원점검색을 종료한다.
/// 원점 검색 함수군
typedef BOOL	PASCAL EXPORT funcC5Mabort_home_search(INT16 axis, UINT8 bStop);
// bStop:
// 0: 감속정지
// 1: 급정지
// 원점검색을 시작한다. 시작하기 전에 원점검색에 필요한 설정이 필요하다.
typedef BOOL	PASCAL EXPORT funcC5Mhome_search(INT16 axis);
// 입력 축들을 동시에 원점검색을 실시한다.
typedef BOOL	PASCAL EXPORT funcC5Mhome_search_all(INT16 number, INT16 *axes);
// 원점검색 진행 중인지를 확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mget_home_done(INT16 axis);
// 반환값: 0: 원점검색 진행중, 1: 원점검색 종료
// 해당 축들의 원점검색 진행 중인지를 확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mget_home_done_all(INT16 number, INT16 *axes);
// 지정 축의 원점 검색 실행후 종료 상태를 확인한다.
typedef UINT8	PASCAL EXPORT funcC5Mget_home_end_status(INT16 axis);
// 반환값: 0: 원점검색 실패, 1: 원점검색 성공
// 지정 축들의 원점 검색 실행후 종료 상태를 확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mget_home_end_status_all(INT16 number, INT16 *axes, UINT8 *endstatus);
//원점 검색시 각 스텝마다 method를 설정/확인한다.
//Method에 대한 설명 
//    0 Bit 스텝 사용여부 설정 (0 : 사용하지 않음, 1: 사용함
//    1 Bit 가감속 방법 설정 (0 : 가속율, 1 : 가속 시간)
//    2 Bit 정지방법 설정 (0 : 감속 정지, 1 : 급 정지)
//    3 Bit 검색방향 설정 (0 : cww(-), 1 : cw(+))
// 7654 Bit detect signal 설정(typedef : DETECT_DESTINATION_SIGNAL)
typedef BOOL	PASCAL EXPORT funcC5Mset_home_method(INT16 axis, INT16 nstep, UINT8 *method);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_method(INT16 axis, INT16 nstep, UINT8 *method);
//원점 검색시 각 스텝마다 offset을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_offset(INT16 axis, INT16 nstep, double *offset);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_offset(INT16 axis, INT16 nstep, double *offset);
// 각 축의 원점 검색 속도를 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_velocity(INT16 axis, INT16 nstep, double *velocity);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_velocity(INT16 axis, INT16 nstep, double *velocity);
//지정 축의 원점 검색 시 각 스텝별 가속율을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_acceleration(INT16 axis, INT16 nstep, double *acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_acceleration(INT16 axis, INT16 nstep, double *acceleration);
// 지정 축의 원점 검색 시 각 스텝별 가속 시간을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_acceltime(INT16 axis, INT16 nstep, double *acceltime);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_acceltime(INT16 axis, INT16 nstep, double *acceltime);
// 지정 축에 원점 검색에서 엔코더 'Z'상 검출 사용 시 구동 한계값를 설정/확인한다.(Pulse) - 범위를 벗어나면 검색 실패
typedef BOOL	PASCAL EXPORT funcC5Mset_zphase_search_range(INT16 axis, INT16 pulses);
typedef INT16	PASCAL EXPORT funcC5Mget_zphase_search_range(INT16 axis);
// 현재 위치를 원점(0 Position)으로 설정한다. - 구동중이면 무시됨.
typedef BOOL	PASCAL EXPORT funcC5Mhome_zero(INT16 axis);
// 설정한 모든 축의 현재 위치를 원점(0 Position)으로 설정한다. - 구동중인 축은 무시됨
typedef BOOL	PASCAL EXPORT funcC5Mhome_zero_all(INT16 number, INT16 *axes);	

// 범용 입출력-=======================================================================================================
// 범용 출력
// 0 bit : 범용 출력 0(Servo-On)
// 1 bit : 범용 출력 1(ALARM Clear)
// 2 bit : 범용 출력 2
// 3 bit : 범용 출력 3
// 범용 입력
// 0 bit : 범용 입력 0(ORiginal Sensor)
// 1 bit : 범용 입력 1(Z phase)
// 2 bit : 범용 입력 2
// 3 bit : 범용 입력 3
// On ==> 단자대 N24V, 'Off' ==> 단자대 Open(float).		

// 현재 범용 출력값을 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_output(INT16 axis, UINT8 value);
typedef UINT8   PASCAL EXPORT funcC5Mget_output(INT16 axis);
// 범용 입력 값을 확인한다.
// '1'('On') <== 단자대 N24V와 연결됨, '0'('Off') <== 단자대 P24V 또는 Float.
typedef UINT8   PASCAL EXPORT funcC5Mget_input(INT16 axis);
// 해당 축의 해당 bit의 출력을 On/Off 시킨다.
// bitNo : 0 ~ 3.
typedef BOOL	PASCAL EXPORT funcC5Mset_output_bit(INT16 axis, UINT8 bitNo);
typedef BOOL	PASCAL EXPORT funcC5Mreset_output_bit(INT16 axis, UINT8 bitNo);
// 해당 축의 해당 범용 출력 bit의 출력 상태를 확인한다.
// bitNo : 0 ~ 3.
typedef BOOL	PASCAL EXPORT funcC5Moutput_bit_on(INT16 axis, UINT8 bitNo);
// 해당 축의 해당 범용 출력 bit의 상태를 입력 state로 바꾼다.
// bitNo : 0 ~ 3. 
typedef BOOL	PASCAL EXPORT funcC5Mchange_output_bit(INT16 axis, UINT8 bitNo, UINT8 state);
// 해당 축의 해당 범용 입력 bit의 상태를 확인 한다.
// bitNo : 0 ~ 3.
typedef BOOL	PASCAL EXPORT funcC5Minput_bit_on(INT16 axis, UINT8 bitNo);

// 잔여 펄스 clear-===================================================================================================
// 해당 축의 서보팩 잔여 펄스 Clear 출력의 사용 여부를 설정/확인한다.
// CLR 신호의 Default 출력 ==> 단자대 Open이다.
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_mask(INT16 axis, INT16 mask);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_mask(INT16 axis);
// 해당 축의 잔여 펄스 Clear 출력의 Active level을 설정/확인한다.
// Default Active level ==> '1' ==> 단자대 N24V
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_level(INT16 axis, INT16 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_level(INT16 axis);
//해당 축의 -Emeregency End limit에 대한 Clear출력 사용 유무를 설정/확인한다.    
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_nelm_mask(INT16 axis, INT16 mask);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_nelm_mask(INT16 axis);
// 해당 축의 -Emeregency End limit의 Active level을 설정/확인한다. set_nend_limit_level과 동일하게 설정한다.    
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_nelm_level(INT16 axis, INT16 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_nelm_level(INT16 axis);
// 해당 축의 +Emeregency End limit에 대한 Clear출력 사용 유무를 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_pelm_mask(INT16 axis, INT16 mask);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_pelm_mask(INT16 axis);
// 해당 축의 +Emeregency End limit의 Active level을 설정/확인한다. set_nend_limit_level과 동일하게 설정한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_pelm_level(INT16 axis, INT16 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_pelm_level(INT16 axis);
// 해당 축의 잔여 펄스 Clear 출력을 입력 값으로 강제 출력/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_programmed_crc(INT16 axis, INT16 data);
typedef UINT8	PASCAL EXPORT funcC5Mget_programmed_crc(INT16 axis);

// 트리거 기능 ======================================================================================================
// 내부/외부 위치에 대하여 주기/절대 위치에서 설정된 Active level의 Trigger pulse를 발생 시킨다.
// 트리거 출력 펄스의 Active level을 설정/확인한다.
// ('0' : 5V 출력(0 V), 24V 터미널 출력(Open); '1'(default) : 5V 출력(5 V), 24V 터미널 출력(N24V).
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_level(INT16 axis, UINT8 trigger_level);
typedef UINT8	PASCAL EXPORT funcC5Mget_trigger_level(INT16 axis);
// 트리거 기능에 사용할 기준 위치를 선택한다.
// 0x0 : 외부 위치 External(Actual)
// 0x1 : 내부 위치 Internal(Command)
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_sel(INT16 axis, UINT8 trigger_sel);
typedef UINT8	PASCAL EXPORT funcC5Mget_trigger_sel(INT16 axis);
// 트리거 펄스폭을 설정/확인한다.
// 0Fh : 64 msec
// 0Eh : 32 msec
// 0Dh : 16 mSec
// ..
// 04h : 0.0625 msec
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_time(INT16 axis, UINT8 time);
typedef UINT8	PASCAL EXPORT funcC5Mget_trigger_time(INT16 axis);
// 지정 축의 트리거 기능의 사용 여부를 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_enable(INT16 axis, UINT8 ena_status);
typedef UINT8	PASCAL EXPORT funcC5Mis_trigger_enabled(INT16 axis);
// 지정 축에 트리거 발생시 인터럽트를 발생하도록 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_interrupt_enable(INT16 axis, UINT8 ena_int);
typedef UINT8	PASCAL EXPORT funcC5Mis_trigger_interrupt_enabled(INT16 axis);

// 위치 비교기 관련 함수군 ==========================================================================================
// Internal(Command) comparator값을 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_internal_comparator_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_internal_comparator_position(INT16 axis);
// External(Encoder) comparator값을 설정/확인한다.
typedef void	PASCAL EXPORT funcC5Mset_external_comparator_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_external_comparator_position(INT16 axis);

// 인터럽트 관련 함수군 ==========================================================================================
// 모션종료시 인터럽트 발생 사용 설정/확인한다.
typedef BOOL	PASCAL EXPORT funcC5Mset_motiondone_interrupt_enable(INT16 axis, UINT8 ena_int);
typedef UINT8	PASCAL EXPORT funcC5Mis_motiondone_interrupt_enabled(INT16 axis);

// 에러코드 읽기 함수군 =============================================================================================
// 마지막 에러코드를 읽는다.
typedef INT16	PASCAL EXPORT funcC5Mget_error_code();
// 에러코드의 원인을 문자로 반환한다.
typedef char*	PASCAL EXPORT funcC5Mget_error_msg(INT16 ErrorCode);	



extern funcInitializeCAMC5M						*InitializeCAMC5M;
extern funcC5MIsInitialized						*C5MIsInitialized;
extern funcC5MStopService						*C5MStopService;

extern funcC5Mget_boardno						*C5Mget_boardno;
extern funcC5Mget_numof_boards					*C5Mget_numof_boards;
extern funcC5Mget_numof_axes					*C5Mget_numof_axes;
extern funcC5Mget_total_numof_axis				*C5Mget_total_numof_axis;
extern funcC5Mget_axisno						*C5Mget_axisno;
extern funcC5Mget_axis_info						*C5Mget_axis_info;

extern funcC5Mload_parameter					*C5Mload_parameter;
extern funcC5Msave_parameter					*C5Msave_parameter;
extern funcC5Mload_parameter_all				*C5Mload_parameter_all;
extern funcC5Msave_parameter_all				*C5Msave_parameter_all;

extern funcC5MSetWindowMessage					*C5MSetWindowMessage;

extern funcC5MKeSetMainClk						*C5MKeSetMainClk;
extern funcC5Mset_drive_mode1					*C5Mset_drive_mode1;
extern funcC5Mget_drive_mode1					*C5Mget_drive_mode1;
extern funcC5Mset_drive_mode2					*C5Mset_drive_mode2;
extern funcC5Mget_drive_mode2					*C5Mget_drive_mode2;
extern funcC5Mset_moveunit_perpulse				*C5Mset_moveunit_perpulse;
extern funcC5Mget_moveunit_perpulse				*C5Mget_moveunit_perpulse;
extern funcC5Mset_movepulse_perunit				*C5Mset_movepulse_perunit;
extern funcC5Mget_movepulse_perunit				*C5Mget_movepulse_perunit;
extern funcC5Mset_startstop_speed				*C5Mset_startstop_speed;
extern funcC5Mget_startstop_speed				*C5Mget_startstop_speed;
extern funcC5Mset_max_speed						*C5Mset_max_speed;
extern funcC5Mget_max_speed						*C5Mget_max_speed;
extern funcC5Mset_qs_rate						*C5Mset_qs_rate;
extern funcC5Mget_qs_rate						*C5Mget_qs_rate;
extern funcC5Mset_slowdown_rear_pulse			*C5Mset_slowdown_rear_pulse;
extern funcC5Mget_slowdown_rear_pulse			*C5Mget_slowdown_rear_pulse;
extern funcC5Mset_decel_point					*C5Mset_decel_point;
extern funcC5Mget_decel_point					*C5Mget_decel_point;

extern funcC5Min_motion							*C5Min_motion;
extern funcC5Mmotion_done						*C5Mmotion_done;
extern funcC5Mget_drive_pulse_counts			*C5Mget_drive_pulse_counts;
extern funcC5Mget_drive_status					*C5Mget_drive_status;
extern funcC5Mget_end_status					*C5Mget_end_status;
extern funcC5Mget_mechanical_signal				*C5Mget_mechanical_signal;
extern funcC5Mget_velocity						*C5Mget_velocity;
extern funcC5Mget_error							*C5Mget_error;
extern funcC5Mget_drivedistance					*C5Mget_drivedistance;

extern funcC5Mset_enc_input_method				*C5Mset_enc_input_method;
extern funcC5Mget_enc_input_method				*C5Mget_enc_input_method;

extern funcC5Mset_pulse_out_method				*C5Mset_pulse_out_method;
extern funcC5Mget_pulse_out_method				*C5Mget_pulse_out_method;

extern funcC5Mset_actual_position				*C5Mset_actual_position;
extern funcC5Mget_actual_position				*C5Mget_actual_position;
extern funcC5Mset_command_position				*C5Mset_command_position;
extern funcC5Mget_command_position				*C5Mget_command_position;

extern funcC5Mset_servo_level					*C5Mset_servo_level;
extern funcC5Mget_servo_level					*C5Mget_servo_level;
extern funcC5Mset_servo_enable					*C5Mset_servo_enable;
extern funcC5Mget_servo_enable					*C5Mget_servo_enable;

extern funcC5Mset_inposition_enable				*C5Mset_inposition_enable;
extern funcC5Mget_inposition_enable				*C5Mget_inposition_enable;
extern funcC5Mset_inposition_level				*C5Mset_inposition_level;
extern funcC5Mget_inposition_level				*C5Mget_inposition_level;
extern funcC5Mget_inposition_switch				*C5Mget_inposition_switch;
extern funcC5Min_position						*C5Min_position;
extern funcC5Mset_alarm_enable					*C5Mset_alarm_enable;
extern funcC5Mget_alarm_enable					*C5Mget_alarm_enable;
extern funcC5Mset_alarm_level					*C5Mset_alarm_level;
extern funcC5Mget_alarm_level					*C5Mget_alarm_level;
extern funcC5Mget_alarm_switch					*C5Mget_alarm_switch;

extern funcC5Mset_nend_limit_level				*C5Mset_nend_limit_level;
extern funcC5Mget_nend_limit_level				*C5Mget_nend_limit_level;
extern funcC5Mget_nend_limit_switch				*C5Mget_nend_limit_switch;
extern funcC5Mset_pend_limit_level				*C5Mset_pend_limit_level;
extern funcC5Mget_pend_limit_level				*C5Mget_pend_limit_level;
extern funcC5Mget_pend_limit_switch				*C5Mget_pend_limit_switch;
extern funcC5Mset_nslow_limit_level				*C5Mset_nslow_limit_level;
extern funcC5Mget_nslow_limit_level				*C5Mget_nslow_limit_level;
extern funcC5Mget_nslow_limit_switch			*C5Mget_nslow_limit_switch;
extern funcC5Mset_pslow_limit_level				*C5Mset_pslow_limit_level;
extern funcC5Mget_pslow_limit_level				*C5Mget_pslow_limit_level;
extern funcC5Mget_pslow_limit_switch			*C5Mget_pslow_limit_switch;
extern funcC5Mset_nlimit_sel					*C5Mset_nlimit_sel;
extern funcC5Mget_nlimit_sel					*C5Mget_nlimit_sel;
extern funcC5Mset_plimit_sel					*C5Mset_plimit_sel;
extern funcC5Mget_plimit_sel					*C5Mget_plimit_sel;

extern funcC5Mset_stop_sel						*C5Mset_stop_sel;
extern funcC5Mget_stop_sel						*C5Mget_stop_sel;


extern funcC5Mmove								*C5Mmove;
extern funcC5Mmove_ex							*C5Mmove_ex;
extern funcC5Mr_move							*C5Mr_move;
extern funcC5Mr_move_ex							*C5Mr_move_ex;
extern funcC5Mstart_move						*C5Mstart_move;
extern funcC5Mstart_move_ex						*C5Mstart_move_ex;
extern funcC5Mstart_r_move						*C5Mstart_r_move;
extern funcC5Mstart_r_move_ex					*C5Mstart_r_move_ex;
extern funcC5Mqs_move							*C5Mqs_move;
extern funcC5Mqs_move_ex						*C5Mqs_move_ex;
extern funcC5Mrqs_move							*C5Mrqs_move;
extern funcC5Mrqs_move_ex						*C5Mrqs_move_ex;
extern funcC5Mstart_qs_move						*C5Mstart_qs_move;
extern funcC5Mstart_qs_move_ex					*C5Mstart_qs_move_ex;
extern funcC5Mstart_rqs_move					*C5Mstart_rqs_move;
extern funcC5Mstart_rqs_move_ex					*C5Mstart_rqs_move_ex;


extern funcC5Mv_move							*C5Mv_move;
extern funcC5Mv_move_ex							*C5Mv_move_ex;
extern funcC5Mv_qs_move							*C5Mv_qs_move;
extern funcC5Mv_qs_move_ex						*C5Mv_qs_move_ex;


extern funcC5Mstart_signal_search1				*C5Mstart_signal_search1;
extern funcC5Mstart_signal_search1_ex			*C5Mstart_signal_search1_ex;
extern funcC5Mstart_qs_signal_search1			*C5Mstart_qs_signal_search1;
extern funcC5Mstart_qs_signal_search1_ex		*C5Mstart_qs_signal_search1_ex;
extern funcC5Mstart_signal_search2				*C5Mstart_signal_search2;

extern funcC5Mposition_override					*C5Mposition_override;
extern funcC5Mposition_r_override				*C5Mposition_r_override;

extern funcC5Mwait_for_done						*C5Mwait_for_done;

extern funcC5Mset_e_stop						*C5Mset_e_stop;
extern funcC5Mset_stop							*C5Mset_stop;
extern funcC5Mset_stop_decel					*C5Mset_stop_decel;
extern funcC5Mset_stop_deceltime				*C5Mset_stop_deceltime;

extern funcC5Mlink								*C5Mlink;
extern funcC5Mendlink							*C5Mendlink;

extern funcC5Mmap_axes							*C5Mmap_axes;
extern funcC5Mget_mapped_axes					*C5Mget_mapped_axes;
extern funcC5Mset_coordinate_mode				*C5Mset_coordinate_mode;
extern funcC5Mget_coordinate_mode				*C5Mget_coordinate_mode;
extern funcC5Mset_move_profile					*C5Mset_move_profile;
extern funcC5Mget_move_profile					*C5Mget_move_profile;
extern funcC5Mset_move_startstop_velocity		*C5Mset_move_startstop_velocity;
extern funcC5Mget_move_startstop_velocity		*C5Mget_move_startstop_velocity;
extern funcC5Mset_move_velocity					*C5Mset_move_velocity;
extern funcC5Mget_move_velocity					*C5Mget_move_velocity;
extern funcC5Mset_move_acceleration				*C5Mset_move_acceleration;
extern funcC5Mget_move_acceleration				*C5Mget_move_acceleration;
extern funcC5Mset_move_acceltime				*C5Mset_move_acceltime;
extern funcC5Mget_move_acceltime				*C5Mget_move_acceltime;
extern funcC5Mco_get_velocity					*C5Mco_get_velocity;

extern funcC5Mmove_2							*C5Mmove_2;
extern funcC5Mmove_3							*C5Mmove_3;
extern funcC5Mmove_4							*C5Mmove_4;
extern funcC5Mstart_move_2						*C5Mstart_move_2;
extern funcC5Mstart_move_3						*C5Mstart_move_3;
extern funcC5Mstart_move_4						*C5Mstart_move_4;
extern funcC5Mco_motion_done					*C5Mco_motion_done;
extern funcC5Mco_wait_for_done					*C5Mco_wait_for_done;


extern funcC5Mmove_all							*C5Mmove_all;
extern funcC5Mmove_all_ex						*C5Mmove_all_ex;
extern funcC5Mr_move_all						*C5Mr_move_all;
extern funcC5Mr_move_all_ex						*C5Mr_move_all_ex;
extern funcC5Mstart_move_all					*C5Mstart_move_all;
extern funcC5Mstart_move_all_ex					*C5Mstart_move_all_ex;
extern funcC5Mstart_r_move_all					*C5Mstart_r_move_all;
extern funcC5Mstart_r_move_all_ex				*C5Mstart_r_move_all_ex;
extern funcC5Mqs_move_all						*C5Mqs_move_all;
extern funcC5Mqs_move_all_ex					*C5Mqs_move_all_ex;
extern funcC5Mrqs_move_all						*C5Mrqs_move_all;
extern funcC5Mrqs_move_all_ex					*C5Mrqs_move_all_ex;
extern funcC5Mstart_qs_move_all					*C5Mstart_qs_move_all;
extern funcC5Mstart_qs_move_all_ex				*C5Mstart_qs_move_all_ex;
extern funcC5Mstart_rqs_move_all				*C5Mstart_rqs_move_all;
extern funcC5Mstart_rqs_move_all_ex				*C5Mstart_rqs_move_all_ex;
extern funcC5Mset_qs_rate_all					*C5Mset_qs_rate_all;
extern funcC5Mget_qs_rate_all					*C5Mget_qs_rate_all;

extern funcC5Mwait_for_all						*C5Mwait_for_all;

extern funcC5Mreset_axis_sync					*C5Mreset_axis_sync;
extern funcC5Mset_axis_sync						*C5Mset_axis_sync;
extern funcC5Mset_sync							*C5Mset_sync;
extern funcC5Mget_sync_info						*C5Mget_sync_info;

extern funcC5Memergency_stop					*C5Memergency_stop;

extern funcC5Mabort_home_search					*C5Mabort_home_search;
extern funcC5Mhome_search						*C5Mhome_search;
extern funcC5Mhome_search_all					*C5Mhome_search_all;
extern funcC5Mget_home_done						*C5Mget_home_done;
extern funcC5Mget_home_done_all					*C5Mget_home_done_all;
extern funcC5Mget_home_end_status				*C5Mget_home_end_status;
extern funcC5Mget_home_end_status_all			*C5Mget_home_end_status_all;
extern funcC5Mset_home_method					*C5Mset_home_method;
extern funcC5Mget_home_method					*C5Mget_home_method;
extern funcC5Mset_home_offset					*C5Mset_home_offset;
extern funcC5Mget_home_offset					*C5Mget_home_offset;
extern funcC5Mset_home_velocity					*C5Mset_home_velocity;
extern funcC5Mget_home_velocity					*C5Mget_home_velocity;
extern funcC5Mset_home_acceleration				*C5Mset_home_acceleration;
extern funcC5Mget_home_acceleration				*C5Mget_home_acceleration;
extern funcC5Mset_home_acceltime				*C5Mset_home_acceltime;
extern funcC5Mget_home_acceltime				*C5Mget_home_acceltime;
extern funcC5Mset_zphase_search_range			*C5Mset_zphase_search_range;
extern funcC5Mget_zphase_search_range			*C5Mget_zphase_search_range;
extern funcC5Mhome_zero							*C5Mhome_zero;
extern funcC5Mhome_zero_all						*C5Mhome_zero_all;


extern funcC5Mset_output						*C5Mset_output;
extern funcC5Mget_output						*C5Mget_output;
extern funcC5Mget_input							*C5Mget_input;
extern funcC5Mset_output_bit					*C5Mset_output_bit;
extern funcC5Mreset_output_bit					*C5Mreset_output_bit;
extern funcC5Moutput_bit_on						*C5Moutput_bit_on;
extern funcC5Mchange_output_bit					*C5Mchange_output_bit;
extern funcC5Minput_bit_on						*C5Minput_bit_on;

extern funcC5Mset_crc_mask						*C5Mset_crc_mask;
extern funcC5Mget_crc_mask						*C5Mget_crc_mask;
extern funcC5Mset_crc_level						*C5Mset_crc_level;
extern funcC5Mget_crc_level						*C5Mget_crc_level;
extern funcC5Mset_crc_nelm_mask					*C5Mset_crc_nelm_mask;
extern funcC5Mget_crc_nelm_mask					*C5Mget_crc_nelm_mask;
extern funcC5Mset_crc_nelm_level				*C5Mset_crc_nelm_level;
extern funcC5Mget_crc_nelm_level				*C5Mget_crc_nelm_level;
extern funcC5Mset_crc_pelm_mask					*C5Mset_crc_pelm_mask;
extern funcC5Mget_crc_pelm_mask					*C5Mget_crc_pelm_mask;
extern funcC5Mset_crc_pelm_level				*C5Mset_crc_pelm_level;
extern funcC5Mget_crc_pelm_level				*C5Mget_crc_pelm_level;
extern funcC5Mset_programmed_crc				*C5Mset_programmed_crc;
extern funcC5Mget_programmed_crc				*C5Mget_programmed_crc;

extern funcC5Mset_trigger_level					*C5Mset_trigger_level;
extern funcC5Mget_trigger_level					*C5Mget_trigger_level;
extern funcC5Mset_trigger_sel					*C5Mset_trigger_sel;
extern funcC5Mget_trigger_sel					*C5Mget_trigger_sel;
extern funcC5Mset_trigger_time					*C5Mset_trigger_time;
extern funcC5Mget_trigger_time					*C5Mget_trigger_time;
extern funcC5Mset_trigger_enable				*C5Mset_trigger_enable;
extern funcC5Mis_trigger_enabled				*C5Mis_trigger_enabled;
extern funcC5Mset_trigger_interrupt_enable		*C5Mset_trigger_interrupt_enable;
extern funcC5Mis_trigger_interrupt_enabled		*C5Mis_trigger_interrupt_enabled;

extern funcC5Mset_internal_comparator_position	*C5Mset_internal_comparator_position;
extern funcC5Mget_internal_comparator_position	*C5Mget_internal_comparator_position;
extern funcC5Mset_external_comparator_position	*C5Mset_external_comparator_position;
extern funcC5Mget_external_comparator_position	*C5Mget_external_comparator_position;

extern funcC5Mset_motiondone_interrupt_enable	*C5Mset_motiondone_interrupt_enable;
extern funcC5Mis_motiondone_interrupt_enabled	*C5Mis_motiondone_interrupt_enabled;

extern funcC5Mget_error_code					*C5Mget_error_code;
extern funcC5Mget_error_msg						*C5Mget_error_msg;



BOOL LoadAxtCAMC5M();
BOOL FreeAxtCAMC5M();

#endif	__AXT_DAXTCAMC5M_H__