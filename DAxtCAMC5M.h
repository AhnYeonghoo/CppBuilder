#ifndef __AXT_DAXTCAMC5M_H__
#define __AXT_DAXTCAMC5M_H__

#include "AxtLIBDef.h"
#include "CAMC5MDef.h"

/*------------------------------------------------------------------------------------------------*
	AXTCAMC5M Library - CAMC-5M Motion module
	������ǰ
		SMC-1V01 - CAMC-5M 1��
		SMC-2V01 - CAMC-5M 2��
 *------------------------------------------------------------------------------------------------*/

/// �ʱ�ȭ �Լ���
// CAMC-5M�� ������ ���(SMC-1V01, SMC-2V01)�� �˻��Ͽ� �ʱ�ȭ�Ѵ�. CAMC-5M 1.0�� �����Ѵ�
typedef BOOL    PASCAL EXPORT funcInitializeCAMC5M(BOOL reset);
// reset	: 1(TRUE) = ��������(ī���� ��)�� �ʱ�ȭ�Ѵ�
//  reset(TRUE)�϶� �ʱ� ������.
//  1) ���ͷ�Ʈ ������� ����.
//  2) �������� ��� ������� ����.
//  3) �˶����� ��� ������� ����.
//  4) ������ ����Ʈ ��� ��� ��.
//  5) �������� ����Ʈ ��� ��� ��.            
//  6) �޽� ��� ��� : OneLowHighLow(Pulse : Active LOW, Direction : CW{High};CCW{LOW}).
//  7) �˻� ��ȣ : +������ ����Ʈ ��ȣ �ϰ� ����.
//  8) �Է� ���ڴ� ���� : 2��, 4 ü��.
//  9) �˶�, ��������, +-���� ���� ����Ʈ, +-������ ����Ʈ Active level : HIGH
// 10) ����/�ܺ� ī���� : 0.
// CAMC-5M ����� ����� ���������� Ȥ���Ѵ�
typedef BOOL    PASCAL EXPORT funcC5MIsInitialized(void);
// ���ϰ� :  1(TRUE) = CAMC-5M ����� ��� �����ϴ�
// CAMC-5M�� ������ ����� ����� �����Ѵ�
typedef void    PASCAL EXPORT funcC5MStopService();

/// ���� ���� ���� �Լ���        -===================================================================================
// ������ �ּҿ� ������ ���̽������� ��ȣ�� �����Ѵ�. ������ -1�� �����Ѵ�
typedef INT16	PASCAL EXPORT funcC5Mget_boardno(UINT32 address);
// ���̽������� ������ �����Ѵ�
typedef INT16	PASCAL EXPORT funcC5Mget_numof_boards();
// ������ ���̽����忡 ������ ���� ������ �����Ѵ�
typedef INT16	PASCAL EXPORT funcC5Mget_numof_axes(INT16 nBoardNo);
// ���� ������ �����Ѵ�
typedef INT16	PASCAL EXPORT funcC5Mget_total_numof_axis();
// ������ ���̽������ȣ�� ����ȣ�� �ش��ϴ� ���ȣ�� �����Ѵ�
typedef INT16	PASCAL EXPORT funcC5Mget_axisno(INT16 nBoardNo, INT16 nModuleNo);
// ������ ���� ������ �����Ѵ�
// nBoardNo : �ش� ���� ������ ���̽������� ��ȣ.
// nModuleNo: �ش� ���� ������ ����� ���̽� ��峻 ��� ��ġ(0~3)
// bModuleID: �ش� ���� ������ ����� ID : SMC-2V01(0x01)
// nAxisPos : �ش� ���� ������ ����� ù��°���� �ι�° ������ ����.(0 : ù��°, 1 : �ι�°)
typedef BOOL	PASCAL EXPORT funcC5Mget_axis_info(INT16 nAxisNo, INT16 *nBoardNo, INT16 *nModuleNo, UINT8 *bModuleID, INT16 *nAxisPos);

// ���� ���� �Լ���        -========================================================================================
// ���� ���� �ʱⰪ�� ������ ���Ͽ��� �о �����Ѵ�
// Loading parameters.
//	1) 1Pulse�� �̵��Ÿ�(Move Unit / Pulse)
//	2) �ִ� �̵� �ӵ�, ����/���� �ӵ�
//	3) ���ڴ� �Է¹��, �޽� ��¹�� 
//	4) +������ ����Ʈ����, -������ ����Ʈ����, ������ ����Ʈ �������
//  5) +�������� ����Ʈ����,-�������� ����Ʈ����, �������� ����Ʈ �������
//  6) �˶�����, �˶� �������
//  7) ��������(��ġ�����Ϸ� ��ȣ)����, �������� �������
//  8) ������� �������
//  9) ����/�ܺ� ī���� : 0. 	
typedef BOOL	PASCAL EXPORT funcC5Mload_parameter(INT16 axis, char *nfilename);
// ���� ���� �ʱⰪ�� ������ ���Ͽ� �����Ѵ�.
// Saving parameters.
//	1) 1Pulse�� �̵��Ÿ�(Move Unit / Pulse)
//	2) �ִ� �̵� �ӵ�, ����/���� �ӵ�
//	3) ���ڴ� �Է¹��, �޽� ��¹�� 
//	4) +������ ����Ʈ����, -������ ����Ʈ����, ������ ����Ʈ �������
//  5) +�������� ����Ʈ����,-�������� ����Ʈ����, �������� ����Ʈ �������
//  6) �˶�����, �˶� �������
//  7) ��������(��ġ�����Ϸ� ��ȣ)����, �������� �������
//  8) ������� �������
typedef BOOL	PASCAL EXPORT funcC5Msave_parameter(INT16 axis, char *nfilename);
// ��� ���� �ʱⰪ�� ������ ���Ͽ��� �о �����Ѵ�
typedef BOOL	PASCAL EXPORT funcC5Mload_parameter_all(char *nfilename);
// ��� ���� �ʱⰪ�� ������ ���Ͽ� �����Ѵ�
typedef BOOL	PASCAL EXPORT funcC5Msave_parameter_all(char *nfilename);

// ���ͷ�Ʈ �Լ���   -================================================================================================
//(���ͷ�Ʈ�� ����ϱ� ���ؼ��� 
//Window message & procedure
//    hWnd    : ������ �ڵ�, ������ �޼����� ������ ���. ������� ������ NULL�� �Է�.
//    wMsg    : ������ �ڵ��� �޼���, ������� �ʰų� ����Ʈ���� ����Ϸ��� 0�� �Է�.
//    proc    : ���ͷ�Ʈ �߻��� ȣ��� �Լ��� ������, ������� ������ NULL�� �Է�.
typedef void	PASCAL EXPORT funcC5MSetWindowMessage(HANDLE hWnd, UINT16 wMsg, AXT_CAMC5M_INTERRUPT_PROC proc);

// ���� ���� �ʱ�ȭ �Լ���        -==================================================================================
// ����Ŭ�� ����( ��⿡ ������ Oscillator�� ����� ��쿡�� ����)
typedef void	PASCAL EXPORT funcC5MKeSetMainClk(INT32 nMainClk);
// Drive mode 1�� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_drive_mode1(INT16 axis, 
				UINT8 decelstartpoint,
				UINT8 pulseoutmethod,
				UINT8 detectsignal);
typedef UINT8	PASCAL EXPORT funcC5Mget_drive_mode1(INT16 axis);
// decelstartpoint : �����Ÿ� ���� ��� ����� ���� ��ġ ���� ��� ����(0 : �ڵ� ������, 1 : ���� ������)
// pulseoutmethod : ��� �޽� ��� ����(typedef : PULSE_OUTPUT)
// detecsignal : ��ȣ �˻�-1/2 ���� ��� ����� �˻� �� ��ȣ ����(typedef : DETECT_DESTINATION_SIGNAL)
// Drive mode 2�� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_drive_mode2(INT16 axis, 
				UINT8 encmethod,
				UINT8 inpactivelevel,
				UINT8 alarmactivelevel,
				UINT8 nslmactivelevel,
				UINT8 pslmactivelevel,
				UINT8 nelmactivelevel,
				UINT8 pelmactivelevel);
typedef UINT8	PASCAL EXPORT funcC5Mget_drive_mode2(INT16 axis);
// Unit/Pulse ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_moveunit_perpulse(INT16 axis, double unitperpulse);
typedef double	PASCAL EXPORT funcC5Mget_moveunit_perpulse(INT16 axis);
// Unit/Pulse : 1 pulse�� ���� system�� �̵��Ÿ��� ���ϸ�, �̶� Unit�� ������ ����ڰ� ���Ƿ� ������ �� �ִ�.
// Ex) Ball screw pitch : 10mm, ���� 1ȸ���� �޽��� : 10000 ==> Unit�� mm�� ������ ��� : Unit/Pulse = 10/10000.
// ���� unitperpulse�� 0.001�� �Է��ϸ� ��� ��������� mm�� ������. 
// Ex) Linear motor�� ���ش��� 1 pulse�� 2 uM. ==> Unit�� mm�� ������ ��� : Unit/Pulse = 0.002/1.
// Unit/Pulse�� ��������
// pulse/Unit ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_movepulse_perunit(INT16 axis, INT32 pulseperunit);
typedef INT32	PASCAL EXPORT funcC5Mget_movepulse_perunit(INT16 axis);
// ���� �ӵ� ����/Ȯ���Ѵ�.(Unit/Sec)
typedef void	PASCAL EXPORT funcC5Mset_startstop_speed(INT16 axis, double velocity);
typedef double	PASCAL EXPORT funcC5Mget_startstop_speed(INT16 axis);
// �ְ� �ӵ� ���� Unit/Sec. ���� system�� �ְ� �ӵ��� �����Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_max_speed(INT16 axis, double max_velocity);
typedef double	PASCAL EXPORT funcC5Mget_max_speed(INT16 axis);
// Unit/Pulse ������ ���ۼӵ� ���� ���Ŀ� �����Ѵ�.
// ������ �ְ� �ӵ� �̻����δ� ������ �Ҽ� �����Ƿ� �����Ѵ�.
// SW�� ����� ���� ����/Ȯ���Ѵ�. �̰����� Quasi S-Curve ������ percentage�� ���� �����ϴ�.
typedef void	PASCAL EXPORT funcC5Mset_qs_rate(INT16 axis, double a_percent, double b_percent);
typedef void	PASCAL EXPORT funcC5Mget_qs_rate(INT16 axis, double *a_percent, double *b_percent);
// ���� ������ ��忡�� �ܷ� �޽��� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_slowdown_rear_pulse(INT16 axis, UINT32 ulData);
typedef UINT32	PASCAL EXPORT funcC5Mget_slowdown_rear_pulse(INT16 axis);
// ���� ���� ���� ���� ������ ���� ����� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_decel_point(INT16 axis, UINT8 method);
typedef UINT8	PASCAL EXPORT funcC5Mget_decel_point(INT16 axis);
// 0x0 : �ڵ� ������.
// 0x1 : ���� ������.

// ���� ���� Ȯ�� �Լ���        -=====================================================================================
// ���� ���� �޽� ����������� Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Min_motion(INT16 axis);
// ���� ���� �޽� ����� ����ƴ��� Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mmotion_done(INT16 axis);
// ���� ���� �������� ���� ��µ� �޽� ī���� ���� Ȯ���Ѵ�. (Pulse)
typedef INT32	PASCAL EXPORT funcC5Mget_drive_pulse_counts(INT16 axis);
// ���� ���� DriveStatus �������͸� Ȯ���Ѵ�.
typedef UINT8	PASCAL EXPORT funcC5Mget_drive_status(INT16 axis);
// ���� ���� EndStatus �������͸� Ȯ���Ѵ�.
typedef UINT8	PASCAL EXPORT funcC5Mget_end_status(INT16 axis);
// End Status Bit�� �ǹ�
// 7 bit : ����Ÿ ���� ������ ���� ����
// 6 bit : ALARM ��ȣ �Է¿� ���� ����
// 5 bit : ������ ��ɿ� ���� ����
// 4 bit : �������� ��ɿ� ���� ����
// 3 bit : ������ ��ȣ �Է¿� ���� ���� (EMG Button)
// 2 bit : �������� ��ȣ �Է¿� ���� ����
// 1 bit : Limit(PELM, NELM, Soft) �������� ���� ����
// 0 bit : Limit(PSLM, NSLM, Soft) ���������� ���� ����
typedef UINT8	PASCAL EXPORT funcC5Mget_mechanical_signal(INT16 axis);
// 7 bit : Encoder Up��ȣ �Է� Level(A�� ��ȣ)
// 6 bit : Encoder Down��ȣ �Է� Level(B�� ��ȣ)
// 5 bit : INPOSITION ��ȣ Active ����
// 4 bit : ALARM ��ȣ Active ����
// 3 bit : -Limit �������� ��ȣ Active ���� (Ver3.0���� ����������)
// 2 bit : +Limit �������� ��ȣ Active ���� (Ver3.0���� ����������)
// 1 bit : -Limit ������ ��ȣ Active ����
// 0 bit : +Limit ������ ��ȣ Active ����
// ���� ����  ���� �ӵ��� �о� �´�.(Unit/Sec)
typedef double	PASCAL EXPORT funcC5Mget_velocity(INT16 axis);
// ���� ���� Command position�� Actual position�� ���� Ȯ���Ѵ�.
typedef double	PASCAL EXPORT funcC5Mget_error(INT16 axis);
// ���� ���� ���� ����̺��� �̵� �Ÿ��� Ȯ�� �Ѵ�. (Unit)
typedef double	PASCAL EXPORT funcC5Mget_drivedistance(INT16 axis);

//Encoder �Է� ��� ���� �Լ���        -=============================================================================
// ���� ���� Encoder �Է� ����� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_enc_input_method(INT16 axis, UINT8 method);
typedef UINT8	PASCAL EXPORT funcC5Mget_enc_input_method(INT16 axis);
// method : typedef(EXTERNAL_COUNTER_INPUT)
// UpDownMode = 0x0    // Up/Down
// Sqr1Mode   = 0x1    // 1ü��
// Sqr2Mode   = 0x2    // 2ü��
// Sqr4Mode   = 0x3    // 4ü��

// �޽� ��� ��� �Լ���        -=====================================================================================
// �޽� ��� ����� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_pulse_out_method(INT16 axis, UINT8 method);
typedef UINT8	PASCAL EXPORT funcC5Mget_pulse_out_method(INT16 axis);
// method : ��� �޽� ��� ����(typedef : PULSE_OUTPUT)
// OneHighLowHigh   = 0x0, 1�޽� ���, PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)
// OneHighHighLow   = 0x1, 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)
// OneLowLowHigh    = 0x2, 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)
// OneLowHighLow    = 0x3, 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)
// TwoCcwCwHigh     = 0x4, 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High 
// TwoCcwCwLow      = 0x5, 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low 
// TwoCwCcwHigh     = 0x6, 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High
// TwoCwCcwLow      = 0x7, 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low

// ��ġ Ȯ�� �� ��ġ �� ���� �Լ��� -===============================================================================
// �ܺ� ��ġ ���� �����Ѵ�. ������ ���¿��� �ܺ� ��ġ�� Ư�� ������ ����/Ȯ���Ѵ�.(position = Unit)
typedef void	PASCAL EXPORT funcC5Mset_actual_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_actual_position(INT16 axis);
// ���� ��ġ ���� �����Ѵ�. ������ ���¿��� ���� ��ġ�� Ư�� ������ ����/Ȯ���Ѵ�.(position = Unit)
typedef void	PASCAL EXPORT funcC5Mset_command_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_command_position(INT16 axis);

// ���� ����̹� ��� ��ȣ ���� �Լ���-===============================================================================
// ���� Enable��� ��ȣ�� Active Level�� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_servo_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_servo_level(INT16 axis);
// ���� Enable(On) / Disable(Off)�� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_servo_enable(INT16 axis, UINT8 state);
typedef UINT8	PASCAL EXPORT funcC5Mget_servo_enable(INT16 axis);

// ���� ����̹� �Է� ��ȣ ���� �Լ���-===============================================================================
// ���� ��ġ�����Ϸ�(inposition)�Է� ��ȣ�� ��������� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_inposition_enable(INT16 axis, UINT8 use);
typedef UINT8	PASCAL EXPORT funcC5Mget_inposition_enable(INT16 axis);
// ���� ��ġ�����Ϸ�(inposition)�Է� ��ȣ�� Active Level�� ����/Ȯ��/����Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_inposition_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_inposition_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_inposition_switch(INT16 axis);
typedef BOOL	PASCAL EXPORT funcC5Min_position(INT16 axis);
// ���� �˶� �Է½�ȣ ����� ��������� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_alarm_enable(INT16 axis, UINT8 use);
typedef UINT8	PASCAL EXPORT funcC5Mget_alarm_enable(INT16 axis);
// ���� �˶� �Է� ��ȣ�� Active Level�� ����/Ȯ��/����Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_alarm_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_alarm_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_alarm_switch(INT16 axis);

// ����Ʈ ��ȣ ���� �Լ���-===========================================================================================
// -������ ����Ʈ �Է� ��ȣ�� Active Level�� ����/Ȯ��/����Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_nend_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_nend_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_nend_limit_switch(INT16 axis);
// +������ ����Ʈ �Է� ��ȣ�� Active Level�� ����/Ȯ��/����Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_pend_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_pend_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_pend_limit_switch(INT16 axis);
// -�������� ����Ʈ �Է� ��ȣ�� Active Level�� ����/Ȯ��/����Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_nslow_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_nslow_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_nslow_limit_switch(INT16 axis);
// +�������� ����Ʈ �Է� ��ȣ�� Active Level�� ����/Ȯ��/����Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_pslow_limit_level(INT16 axis, UINT8 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_pslow_limit_level(INT16 axis);
typedef UINT8	PASCAL EXPORT funcC5Mget_pslow_limit_switch(INT16 axis);
// -LIMIT ���� ������ ��/�������� ���θ� ����/Ȯ���Ѵ�. (Ver 3.0���� ����)
typedef BOOL	PASCAL EXPORT funcC5Mset_nlimit_sel(INT16 axis, UINT8 stop);
typedef UINT8	PASCAL EXPORT funcC5Mget_nlimit_sel(INT16 axis);
// stop:
// 0 : ������, 1 : ��������
// +LIMIT ���� ������ ��/�������� ���θ� ����/Ȯ���Ѵ�. (Ver 3.0���� ����)	
typedef BOOL	PASCAL EXPORT funcC5Mset_plimit_sel(INT16 axis, UINT8 stop);
typedef UINT8	PASCAL EXPORT funcC5Mget_plimit_sel(INT16 axis);

// ������� ��ȣ-=====================================================================================================
// ��������� ��/�������� ���θ� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop_sel(INT16 axis, UINT8 stop);
typedef UINT8	PASCAL EXPORT funcC5Mget_stop_sel(INT16 axis);

// ���� ���� �Ÿ� ����-===============================================================================================
// start_** : ���� �࿡�� ���� ������ �Լ��� return�Ѵ�. "start_*" �� ������ �̵� �Ϸ��� return�Ѵ�(Blocking).
// *r*_*    : ���� �࿡�� �Էµ� �Ÿ���ŭ(�����ǥ)�� �̵��Ѵ�. "*r_*�� ������ �Էµ� ��ġ(������ǥ)�� �̵��Ѵ�.
// *qs*_*   : ������ �ӵ� ���������� "Quasi S curve"�� �̿��Ѵ�. "*qs_*"�� ���ٸ� ��ٸ��� �������� �̿��Ѵ�.
// *_ex     : ������ �����ӵ��� ���� �Ǵ� ���� �ð����� �Է� �޴´�. "*_ex"�� ���ٸ� �����ӷ��� �Է� �޴´�.
// �Է� ����: velocity(Unit/Sec), acceleration/deceleration(Unit/Sec^2), acceltime/deceltime(Sec), position(Unit)

// �����޽�(Pulse Drive), ��ٸ��� ���� �Լ�, ����/�����ǥ(r), ������/���ӽð�(_ex)(�ð�����:Sec)
// Blocking�Լ� (������� �޽� ����� �Ϸ�� �� �Ѿ��)
typedef UINT8	PASCAL EXPORT funcC5Mmove(INT16 axis, double position, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mmove_ex(INT16 axis, double position, double velocity, double acceltime);
typedef UINT8	PASCAL EXPORT funcC5Mr_move(INT16 axis, double distance, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mr_move_ex(INT16 axis, double distance, double velocity, double acceltime);
// Non Blocking�Լ� (�������� ��� ���õ�)
typedef BOOL	PASCAL EXPORT funcC5Mstart_move(INT16 axis, double position, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_ex(INT16 axis, double position, double velocity, double acceltime);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move(INT16 axis, double distance, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move_ex(INT16 axis, double distance, double velocity, double acceltime);
// �����޽�(Pulse Drive), Quasi S���� ����, ����/�����ǥ(r), ������/���ӽð�(_ex)(�ð�����:Sec)
// Blocking�Լ� (������� �޽� ����� �Ϸ�� �� �Ѿ��)
typedef UINT8	PASCAL EXPORT funcC5Mqs_move(INT16 axis, double position, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mqs_move_ex(INT16 axis, double position, double velocity, double acceltime);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move(INT16 axis, double distance, double velocity, double acceleration);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move_ex(INT16 axis, double distance, double velocity, double acceltime);
// Non Blocking�Լ� (�������� ��� ���õ�)
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move(INT16 axis, double position, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move_ex(INT16 axis, double position, double velocity, double acceltime);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move(INT16 axis, double distance, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move_ex(INT16 axis, double distance, double velocity, double acceltime);

// ���� ���� ����-====================================================================================================
// ���� �����ӵ� �� �ӵ��� ���� ������ �߻����� ������ ���������� �����Ѵ�.
// *qs*_*    : ������ �ӵ� ���������� "S curve"�� �̿��Ѵ�. "*s_*"�� ���ٸ� ��ٸ��� �������� �̿��Ѵ�.
// *_ex     : ������ �����ӵ��� ���� �Ǵ� ���� �ð����� �Է� �޴´�. "*_ex"�� ���ٸ� �����ӷ��� �Է� �޴´�.

// ���ӵ� ��ٸ��� ���� �Լ���, ������/���ӽð�(_ex)(�ð�����:Sec) - �������� ��쿡�� �ӵ��������̵�
typedef BOOL	PASCAL EXPORT funcC5Mv_move(INT16 axis, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mv_move_ex(INT16 axis, double velocity, double acceltime);
// ���ӵ� Quasi S���� ���� �Լ���, ������/���ӽð�(_ex)(�ð�����:Sec) - �������� ��쿡�� �ӵ��������̵�
typedef BOOL	PASCAL EXPORT funcC5Mv_qs_move(INT16 axis, double velocity, double acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mv_qs_move_ex(INT16 axis, double velocity, double acceltime);

// ��ȣ ���� ����-====================================================================================================
// ���� ��ȣ�� ����/���� ������ �˻��Ͽ� ������ �Ǵ� ���������� �� �� �ִ�.
// detect_signal : �˻� ��ȣ ����(typedef : DETECT_DESTINATION_SIGNAL)
// PElmNegativeEdge    = 0x0,        // +Elm(End limit) �ϰ� edge
// NElmNegativeEdge    = 0x1,        // -Elm(End limit) �ϰ� edge
// PSlmNegativeEdge    = 0x2,        // +Slm(Slowdown limit) �ϰ� edge
// NSlmNegativeEdge    = 0x3,        // -Slm(Slowdown limit) �ϰ� edge
// In0DownEdge         = 0x4,        // IN0(ORG) �ϰ� edge
// In1DownEdge         = 0x5,        // IN1(Z��) �ϰ� edge
// In2DownEdge         = 0x6,        // IN2(����) �ϰ� edge
// In3DownEdge         = 0x7,        // IN3(����) �ϰ� edge
// PElmPositiveEdge    = 0x8,        // +Elm(End limit) ��� edge
// NElmPositiveEdge    = 0x9,        // -Elm(End limit) ��� edge
// PSlmPositiveEdge    = 0xa,        // +Slm(Slowdown limit) ��� edge
// NSlmPositiveEdge    = 0xb,        // -Slm(Slowdown limit) ��� edge
// In0UpEdge           = 0xc,        // IN0(ORG) ��� edge
// In1UpEdge           = 0xd,        // IN1(Z��) ��� edge
// In2UpEdge           = 0xe,        // IN2(����) ��� edge
// In3UpEdge           = 0xf         // IN3(����) ��� edge
// Signal Search1 : ���� ������ �Է� �ӵ����� �����Ͽ�, ��ȣ ������ ���� ����.
// Signal Search2 : ���� ������ ���Ӿ��� �Է� �ӵ��� �ǰ�, ��ȣ ������ ������. 
// ���� : Signal Search2�� �������� �����Ƿ� �ӵ��� ������� Ż���� �ⱸ���� ������ ���� �����Ƿ� �����Ѵ�.
// *s*_*    : ������ �ӵ� ���������� "S curve"�� �̿��Ѵ�. "*s_*"�� ���ٸ� ��ٸ��� �������� �̿��Ѵ�.
// *_ex     : ������ �����ӵ��� ���� �Ǵ� ���� �ð����� �Է� �޴´�. "*_ex"�� ���ٸ� �����ӷ��� �Է� �޴´�.

// ��ȣ����1(Signal search 1) ��ٸ��� ����, ������/���ӽð�(_ex)(�ð�����:Sec)
typedef BOOL	PASCAL EXPORT funcC5Mstart_signal_search1(INT16 axis, double velocity, double acceleration, UINT8 detect_signal);
typedef BOOL	PASCAL EXPORT funcC5Mstart_signal_search1_ex(INT16 axis, double velocity, double acceltime, UINT8 detect_signal);
// ��ȣ����1(Signal search 1) Quasi S���� ����, ������/���ӽð�(_ex)(�ð�����:Sec)
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_signal_search1(INT16 axis, double velocity, double acceleration, UINT8 detect_signal);
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_signal_search1_ex(INT16 axis, double velocity, double acceltime, UINT8 detect_signal);
// ��ȣ����2(Signal search 2) ��ٸ��� ����, ������ ����
typedef BOOL	PASCAL EXPORT funcC5Mstart_signal_search2(INT16 axis, double velocity, UINT8 detect_signal);

// �������̵�(������)-================================================================================================
// ���� ���� �Ÿ� ������ ���� ���۽������� �Է��� ��ġ(������ġ)�� ������ �ٲ۴�.
typedef BOOL	PASCAL EXPORT funcC5Mposition_override(INT16 axis, double overrideposition);
// ���� ���� �Ÿ� ������ ���� ���۽������� �Է��� �Ÿ�(�����ġ)�� ������ �ٲ۴�.    
typedef BOOL	PASCAL EXPORT funcC5Mposition_r_override(INT16 axis, double overridedistance);	

// ���� ���� Ȯ��-====================================================================================================
// ���� ���� ������ ����� ������ ��ٸ� �� �Լ��� �����.
typedef UINT8	PASCAL EXPORT funcC5Mwait_for_done(INT16 axis);	

// ���� ���� ����-====================================================================================================
// ���� ���� �������Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_e_stop(INT16 axis);
// ���� ���� ������ �������� �����Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop(INT16 axis);
// ���� ���� �Էµ� �������� �����Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop_decel(INT16 axis, double deceleration);
// ���� ���� �Էµ� ���� �ð����� �����Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_stop_deceltime(INT16 axis, double deceltime);

// ���� ���� �������� ����-==========================================================================================
// Master/Slave link �Ǵ� ��ǥ�� link ���� �ϳ��� ����Ͽ��� �Ѵ�.
// Master/Slave link ����. (�Ϲ� ���� ������ master �� ������ slave�൵ ���� �����ȴ�.)
// Master/Slave link ����
typedef BOOL	PASCAL EXPORT funcC5Mlink(INT16 master, INT16 slave, double ratio);
// Master/Slave link ����
typedef BOOL	PASCAL EXPORT funcC5Mendlink(INT16 slave);

// ��ǥ�� link ����-================================================================================================
// ���� ��ǥ�迡 �� �Ҵ� - n_axes������ŭ�� ����� ����/Ȯ���Ѵ�.(coordinate�� 1..8���� ��� ����)
// n_axes ������ŭ�� ����� ����/Ȯ���Ѵ�. - (n_axes�� 1..4���� ��� ����)
typedef BOOL	PASCAL EXPORT funcC5Mmap_axes(INT16 coordinate, INT16 n_axes, INT16 *map_array);
typedef BOOL	PASCAL EXPORT funcC5Mget_mapped_axes(INT16 coordinate, INT16 n_axes, INT16 *map_array);
// ���� ��ǥ���� ���/���� ��� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_coordinate_mode(INT16 coordinate, INT16 mode);
typedef INT16	PASCAL EXPORT funcC5Mget_coordinate_mode(INT16 coordinate);
// mode:
// 0: �����ǥ����, 1: ������ǥ ����
// ���� ��ǥ���� �ӵ� �������� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_move_profile(INT16 coordinate, INT16 mode);
typedef INT16	PASCAL EXPORT funcC5Mget_move_profile(INT16 coordinate);
// mode:
// 0: ��ٸ��� ����, 1: Quasi SĿ�� ����
// ���� ��ǥ���� �ʱ� �ӵ��� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_move_startstop_velocity(INT16 coordinate, double velocity);
typedef double	PASCAL EXPORT funcC5Mget_move_startstop_velocity(INT16 coordinate);
// ���� ��ǥ���� �ʱ� �ӵ��� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_move_velocity(INT16 coordinate, double velocity);
typedef double	PASCAL EXPORT funcC5Mget_move_velocity(INT16 coordinate);
// Ư�� ��ǥ���� �������� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_move_acceleration(INT16 coordinate, double acceleration);
typedef double	PASCAL EXPORT funcC5Mget_move_acceleration(INT16 coordinate);
// Ư�� ��ǥ���� ���� �ð�(Sec)�� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_move_acceltime(INT16 coordinate, double acceltime);
typedef double	PASCAL EXPORT funcC5Mget_move_acceltime(INT16 coordinate);
// ���� ��������  ��ǥ���� ���� �ӵ��� ��ȯ�Ѵ�.
typedef double	PASCAL EXPORT funcC5Mco_get_velocity(INT16 coordinate);

// ����Ʈ���� ���� ����(���� ��ǥ�迡 ���Ͽ�)-========================================================================
// Blocking�Լ� (������� �޽� ����� �Ϸ�� �� �Ѿ��)
// 2, 3, 4���� �����̵��Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mmove_2(INT16 coordinate, double x, double y);
typedef BOOL	PASCAL EXPORT funcC5Mmove_3(INT16 coordinate, double x, double y, double z);
typedef BOOL	PASCAL EXPORT funcC5Mmove_4(INT16 coordinate, double x, double y, double z, double w);
// Non Blocking�Լ� (�������� ��� ���õ�)
// 2, 3, 4���� ���� �̵��Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_2(INT16 coordinate, double x, double y);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_3(INT16 coordinate, double x, double y, double z);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_4(INT16 coordinate, double x, double y, double z, double w);
// ���� ��ǥ���� ������� ��� �Ϸ� üũ    
typedef BOOL	PASCAL EXPORT funcC5Mco_motion_done(INT16 coordinate);
// ���� ��ǥ���� ������ �Ϸ�ɶ� ���� ��ٸ���.
typedef BOOL	PASCAL EXPORT funcC5Mco_wait_for_done(INT16 coordinate);

// ���� ����(���� ����) : Master/Slave�� link�Ǿ� ���� ��� ������ �߻� �� �� �ִ�.-==================================
// ���� ����� ���� �Ÿ� �� �ӵ� ���ӵ� ������ ���� ���� �����Ѵ�. ���� ���ۿ� ���� ����ȭ�� ����Ѵ�. 
// start_** : ���� �࿡�� ���� ������ �Լ��� return�Ѵ�. "start_*" �� ������ �̵� �Ϸ��� return�Ѵ�.
// *r*_*    : ���� �࿡�� �Էµ� �Ÿ���ŭ(�����ǥ)�� �̵��Ѵ�. "*r_*�� ������ �Էµ� ��ġ(������ǥ)�� �̵��Ѵ�.
// *qs*_*    : ������ �ӵ� ���������� "Quasi S curve"�� �̿��Ѵ�. "*qs_*"�� ���ٸ� ��ٸ��� �������� �̿��Ѵ�.
// *_ex     : ������ �����ӵ��� ���� �Ǵ� ���� �ð����� �Է� �޴´�. "*_ex"�� ���ٸ� �����ӷ��� �Է� �޴´�.

// ���� �����޽�(Pulse Drive)����, ��ٸ��� ����, ����/�����ǥ(r), ������/���ӽð�(_ex)(�ð�����:Sec)
// Blocking�Լ� (������� ��� �������� �޽� ����� �Ϸ�� �� �Ѿ��)
typedef UINT8	PASCAL EXPORT funcC5Mmove_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mmove_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef UINT8	PASCAL EXPORT funcC5Mr_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mr_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
// Non Blocking�Լ� (�������� ���� ���õ�)
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_r_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
// ���� �����޽�(Pulse Drive)����, S���� ����, ����/�����ǥ(r), ������/���ӽð�(_ex)(�ð�����:Sec)
// Blocking�Լ� (������� ��� �������� �޽� ����� �Ϸ�� �� �Ѿ��)
typedef UINT8	PASCAL EXPORT funcC5Mqs_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mqs_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef UINT8	PASCAL EXPORT funcC5Mrqs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
// Non Blocking�Լ� (�������� ���� ���õ�)
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move_all(INT16 number, INT16 *axes, double *positions, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_qs_move_all_ex(INT16 number, INT16 *axes, double *positions, double *velocities, double *acceltimes);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move_all(INT16 number, INT16 *axes, double *distances, double *velocities, double *accelerations);
typedef BOOL	PASCAL EXPORT funcC5Mstart_rqs_move_all_ex(INT16 number, INT16 *axes, double *distances, double *velocities, double *acceltimes);
//���� ��鿡 ���Ͽ� S���� ������ ���� �����ӽ��� Quasi SĿ���� ������ ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_qs_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);
typedef void	PASCAL EXPORT funcC5Mget_qs_rate_all(INT16 number, INT16 *axes, double *a_percent, double *b_percent);

// ���� ���� Ȯ��-====================================================================================================
// �Է� �ش� ����� ���� ���¸� Ȯ���ϰ� ������ ���� �� ���� ��ٸ���.
typedef UINT8	PASCAL EXPORT funcC5Mwait_for_all(INT16 number, INT16 *axes);

// ���� ���� ����-====================================================================================================
// ���� ����� ���⸦ ������Ų��. - ��������� �������� ���������ʰ� �����.
typedef BOOL	PASCAL EXPORT funcC5Mreset_axis_sync(INT16 nLen, INT16 *aAxis);
// ���� ����� ���⸦ ������Ų��. - ��������� �������� ���������ʰ� �����.
typedef BOOL	PASCAL EXPORT funcC5Mset_axis_sync(INT16 nLen, INT16 *aAxis);
// ������ ���̽� ���忡 ������ ����� ���⼳��/Ȯ���Ѵ�. 
typedef BOOL	PASCAL EXPORT funcC5Mset_sync(INT16 nBoardNo, UINT8 byState);
typedef UINT8	PASCAL EXPORT funcC5Mget_sync_info(INT16 nBoardNo);
// byState:
// bit 7 : (SUB4 Axis 1) - 0: ���� �������� ����, 1: ���� ������
// bit 6 : (SUB4 Axis 0) - 0: ���� �������� ����, 1: ���� ������
// bit 5 : (SUB3 Axis 1) - 0: ���� �������� ����, 1: ���� ������
// bit 4 : (SUB3 Axis 0) - 0: ���� �������� ����, 1: ���� ������
// bit 3 : (SUB2 Axis 1) - 0: ���� �������� ����, 1: ���� ������
// bit 2 : (SUB2 Axis 0) - 0: ���� �������� ����, 1: ���� ������
// bit 1 : (SUB1 Axis 1) - 0: ���� �������� ����, 1: ���� ������
// bit 0 : (SUB1 Axis 0) - 0: ���� �������� ����, 1: ���� ������

// ���� ���� ����-====================================================================================================
// Ȩ ��ġ �����嵵 ����
typedef BOOL	PASCAL EXPORT funcC5Memergency_stop();	

// -�����˻� =========================================================================================================
// ���̺귯�� �󿡼� Thread�� ����Ͽ� �˻��Ѵ�. ���� : ������ Ĩ���� StartStop Speed�� ���� �� �ִ�.
// �����˻��� �����Ѵ�.
/// ���� �˻� �Լ���
typedef BOOL	PASCAL EXPORT funcC5Mabort_home_search(INT16 axis, UINT8 bStop);
// bStop:
// 0: ��������
// 1: ������
// �����˻��� �����Ѵ�. �����ϱ� ���� �����˻��� �ʿ��� ������ �ʿ��ϴ�.
typedef BOOL	PASCAL EXPORT funcC5Mhome_search(INT16 axis);
// �Է� ����� ���ÿ� �����˻��� �ǽ��Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mhome_search_all(INT16 number, INT16 *axes);
// �����˻� ���� �������� Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mget_home_done(INT16 axis);
// ��ȯ��: 0: �����˻� ������, 1: �����˻� ����
// �ش� ����� �����˻� ���� �������� Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mget_home_done_all(INT16 number, INT16 *axes);
// ���� ���� ���� �˻� ������ ���� ���¸� Ȯ���Ѵ�.
typedef UINT8	PASCAL EXPORT funcC5Mget_home_end_status(INT16 axis);
// ��ȯ��: 0: �����˻� ����, 1: �����˻� ����
// ���� ����� ���� �˻� ������ ���� ���¸� Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mget_home_end_status_all(INT16 number, INT16 *axes, UINT8 *endstatus);
//���� �˻��� �� ���ܸ��� method�� ����/Ȯ���Ѵ�.
//Method�� ���� ���� 
//    0 Bit ���� ��뿩�� ���� (0 : ������� ����, 1: �����
//    1 Bit ������ ��� ���� (0 : ������, 1 : ���� �ð�)
//    2 Bit ������� ���� (0 : ���� ����, 1 : �� ����)
//    3 Bit �˻����� ���� (0 : cww(-), 1 : cw(+))
// 7654 Bit detect signal ����(typedef : DETECT_DESTINATION_SIGNAL)
typedef BOOL	PASCAL EXPORT funcC5Mset_home_method(INT16 axis, INT16 nstep, UINT8 *method);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_method(INT16 axis, INT16 nstep, UINT8 *method);
//���� �˻��� �� ���ܸ��� offset�� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_offset(INT16 axis, INT16 nstep, double *offset);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_offset(INT16 axis, INT16 nstep, double *offset);
// �� ���� ���� �˻� �ӵ��� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_velocity(INT16 axis, INT16 nstep, double *velocity);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_velocity(INT16 axis, INT16 nstep, double *velocity);
//���� ���� ���� �˻� �� �� ���ܺ� �������� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_acceleration(INT16 axis, INT16 nstep, double *acceleration);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_acceleration(INT16 axis, INT16 nstep, double *acceleration);
// ���� ���� ���� �˻� �� �� ���ܺ� ���� �ð��� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_home_acceltime(INT16 axis, INT16 nstep, double *acceltime);
typedef BOOL	PASCAL EXPORT funcC5Mget_home_acceltime(INT16 axis, INT16 nstep, double *acceltime);
// ���� �࿡ ���� �˻����� ���ڴ� 'Z'�� ���� ��� �� ���� �Ѱ谪�� ����/Ȯ���Ѵ�.(Pulse) - ������ ����� �˻� ����
typedef BOOL	PASCAL EXPORT funcC5Mset_zphase_search_range(INT16 axis, INT16 pulses);
typedef INT16	PASCAL EXPORT funcC5Mget_zphase_search_range(INT16 axis);
// ���� ��ġ�� ����(0 Position)���� �����Ѵ�. - �������̸� ���õ�.
typedef BOOL	PASCAL EXPORT funcC5Mhome_zero(INT16 axis);
// ������ ��� ���� ���� ��ġ�� ����(0 Position)���� �����Ѵ�. - �������� ���� ���õ�
typedef BOOL	PASCAL EXPORT funcC5Mhome_zero_all(INT16 number, INT16 *axes);	

// ���� �����-=======================================================================================================
// ���� ���
// 0 bit : ���� ��� 0(Servo-On)
// 1 bit : ���� ��� 1(ALARM Clear)
// 2 bit : ���� ��� 2
// 3 bit : ���� ��� 3
// ���� �Է�
// 0 bit : ���� �Է� 0(ORiginal Sensor)
// 1 bit : ���� �Է� 1(Z phase)
// 2 bit : ���� �Է� 2
// 3 bit : ���� �Է� 3
// On ==> ���ڴ� N24V, 'Off' ==> ���ڴ� Open(float).		

// ���� ���� ��°��� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_output(INT16 axis, UINT8 value);
typedef UINT8   PASCAL EXPORT funcC5Mget_output(INT16 axis);
// ���� �Է� ���� Ȯ���Ѵ�.
// '1'('On') <== ���ڴ� N24V�� �����, '0'('Off') <== ���ڴ� P24V �Ǵ� Float.
typedef UINT8   PASCAL EXPORT funcC5Mget_input(INT16 axis);
// �ش� ���� �ش� bit�� ����� On/Off ��Ų��.
// bitNo : 0 ~ 3.
typedef BOOL	PASCAL EXPORT funcC5Mset_output_bit(INT16 axis, UINT8 bitNo);
typedef BOOL	PASCAL EXPORT funcC5Mreset_output_bit(INT16 axis, UINT8 bitNo);
// �ش� ���� �ش� ���� ��� bit�� ��� ���¸� Ȯ���Ѵ�.
// bitNo : 0 ~ 3.
typedef BOOL	PASCAL EXPORT funcC5Moutput_bit_on(INT16 axis, UINT8 bitNo);
// �ش� ���� �ش� ���� ��� bit�� ���¸� �Է� state�� �ٲ۴�.
// bitNo : 0 ~ 3. 
typedef BOOL	PASCAL EXPORT funcC5Mchange_output_bit(INT16 axis, UINT8 bitNo, UINT8 state);
// �ش� ���� �ش� ���� �Է� bit�� ���¸� Ȯ�� �Ѵ�.
// bitNo : 0 ~ 3.
typedef BOOL	PASCAL EXPORT funcC5Minput_bit_on(INT16 axis, UINT8 bitNo);

// �ܿ� �޽� clear-===================================================================================================
// �ش� ���� ������ �ܿ� �޽� Clear ����� ��� ���θ� ����/Ȯ���Ѵ�.
// CLR ��ȣ�� Default ��� ==> ���ڴ� Open�̴�.
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_mask(INT16 axis, INT16 mask);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_mask(INT16 axis);
// �ش� ���� �ܿ� �޽� Clear ����� Active level�� ����/Ȯ���Ѵ�.
// Default Active level ==> '1' ==> ���ڴ� N24V
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_level(INT16 axis, INT16 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_level(INT16 axis);
//�ش� ���� -Emeregency End limit�� ���� Clear��� ��� ������ ����/Ȯ���Ѵ�.    
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_nelm_mask(INT16 axis, INT16 mask);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_nelm_mask(INT16 axis);
// �ش� ���� -Emeregency End limit�� Active level�� ����/Ȯ���Ѵ�. set_nend_limit_level�� �����ϰ� �����Ѵ�.    
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_nelm_level(INT16 axis, INT16 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_nelm_level(INT16 axis);
// �ش� ���� +Emeregency End limit�� ���� Clear��� ��� ������ ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_pelm_mask(INT16 axis, INT16 mask);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_pelm_mask(INT16 axis);
// �ش� ���� +Emeregency End limit�� Active level�� ����/Ȯ���Ѵ�. set_nend_limit_level�� �����ϰ� �����Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_crc_pelm_level(INT16 axis, INT16 level);
typedef UINT8	PASCAL EXPORT funcC5Mget_crc_pelm_level(INT16 axis);
// �ش� ���� �ܿ� �޽� Clear ����� �Է� ������ ���� ���/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_programmed_crc(INT16 axis, INT16 data);
typedef UINT8	PASCAL EXPORT funcC5Mget_programmed_crc(INT16 axis);

// Ʈ���� ��� ======================================================================================================
// ����/�ܺ� ��ġ�� ���Ͽ� �ֱ�/���� ��ġ���� ������ Active level�� Trigger pulse�� �߻� ��Ų��.
// Ʈ���� ��� �޽��� Active level�� ����/Ȯ���Ѵ�.
// ('0' : 5V ���(0 V), 24V �͹̳� ���(Open); '1'(default) : 5V ���(5 V), 24V �͹̳� ���(N24V).
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_level(INT16 axis, UINT8 trigger_level);
typedef UINT8	PASCAL EXPORT funcC5Mget_trigger_level(INT16 axis);
// Ʈ���� ��ɿ� ����� ���� ��ġ�� �����Ѵ�.
// 0x0 : �ܺ� ��ġ External(Actual)
// 0x1 : ���� ��ġ Internal(Command)
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_sel(INT16 axis, UINT8 trigger_sel);
typedef UINT8	PASCAL EXPORT funcC5Mget_trigger_sel(INT16 axis);
// Ʈ���� �޽����� ����/Ȯ���Ѵ�.
// 0Fh : 64 msec
// 0Eh : 32 msec
// 0Dh : 16 mSec
// ..
// 04h : 0.0625 msec
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_time(INT16 axis, UINT8 time);
typedef UINT8	PASCAL EXPORT funcC5Mget_trigger_time(INT16 axis);
// ���� ���� Ʈ���� ����� ��� ���θ� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_enable(INT16 axis, UINT8 ena_status);
typedef UINT8	PASCAL EXPORT funcC5Mis_trigger_enabled(INT16 axis);
// ���� �࿡ Ʈ���� �߻��� ���ͷ�Ʈ�� �߻��ϵ��� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_trigger_interrupt_enable(INT16 axis, UINT8 ena_int);
typedef UINT8	PASCAL EXPORT funcC5Mis_trigger_interrupt_enabled(INT16 axis);

// ��ġ �񱳱� ���� �Լ��� ==========================================================================================
// Internal(Command) comparator���� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_internal_comparator_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_internal_comparator_position(INT16 axis);
// External(Encoder) comparator���� ����/Ȯ���Ѵ�.
typedef void	PASCAL EXPORT funcC5Mset_external_comparator_position(INT16 axis, double position);
typedef double	PASCAL EXPORT funcC5Mget_external_comparator_position(INT16 axis);

// ���ͷ�Ʈ ���� �Լ��� ==========================================================================================
// �������� ���ͷ�Ʈ �߻� ��� ����/Ȯ���Ѵ�.
typedef BOOL	PASCAL EXPORT funcC5Mset_motiondone_interrupt_enable(INT16 axis, UINT8 ena_int);
typedef UINT8	PASCAL EXPORT funcC5Mis_motiondone_interrupt_enabled(INT16 axis);

// �����ڵ� �б� �Լ��� =============================================================================================
// ������ �����ڵ带 �д´�.
typedef INT16	PASCAL EXPORT funcC5Mget_error_code();
// �����ڵ��� ������ ���ڷ� ��ȯ�Ѵ�.
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