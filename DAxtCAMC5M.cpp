#include "stdafx.h"
#include "DAxtCAMC5M.h"

HINSTANCE	g_hAxtCAMC5M = NULL;

funcInitializeCAMC5M							*InitializeCAMC5M;
funcC5MIsInitialized							*C5MIsInitialized;
funcC5MStopService								*C5MStopService;

funcC5Mget_boardno								*C5Mget_boardno;
funcC5Mget_numof_boards							*C5Mget_numof_boards;
funcC5Mget_numof_axes							*C5Mget_numof_axes;
funcC5Mget_total_numof_axis						*C5Mget_total_numof_axis;
funcC5Mget_axisno								*C5Mget_axisno;
funcC5Mget_axis_info							*C5Mget_axis_info;

funcC5Mload_parameter							*C5Mload_parameter;
funcC5Msave_parameter							*C5Msave_parameter;
funcC5Mload_parameter_all						*C5Mload_parameter_all;
funcC5Msave_parameter_all						*C5Msave_parameter_all;

funcC5MSetWindowMessage							*C5MSetWindowMessage;

funcC5MKeSetMainClk								*C5MKeSetMainClk;
funcC5Mset_drive_mode1							*C5Mset_drive_mode1;
funcC5Mget_drive_mode1							*C5Mget_drive_mode1;
funcC5Mset_drive_mode2							*C5Mset_drive_mode2;
funcC5Mget_drive_mode2							*C5Mget_drive_mode2;
funcC5Mset_moveunit_perpulse					*C5Mset_moveunit_perpulse;
funcC5Mget_moveunit_perpulse					*C5Mget_moveunit_perpulse;
funcC5Mset_movepulse_perunit					*C5Mset_movepulse_perunit;
funcC5Mget_movepulse_perunit					*C5Mget_movepulse_perunit;
funcC5Mset_startstop_speed						*C5Mset_startstop_speed;
funcC5Mget_startstop_speed						*C5Mget_startstop_speed;
funcC5Mset_max_speed							*C5Mset_max_speed;
funcC5Mget_max_speed							*C5Mget_max_speed;
funcC5Mset_qs_rate								*C5Mset_qs_rate;
funcC5Mget_qs_rate								*C5Mget_qs_rate;
funcC5Mset_slowdown_rear_pulse					*C5Mset_slowdown_rear_pulse;
funcC5Mget_slowdown_rear_pulse					*C5Mget_slowdown_rear_pulse;
funcC5Mset_decel_point							*C5Mset_decel_point;
funcC5Mget_decel_point							*C5Mget_decel_point;

funcC5Min_motion								*C5Min_motion;
funcC5Mmotion_done								*C5Mmotion_done;
funcC5Mget_drive_pulse_counts					*C5Mget_drive_pulse_counts;
funcC5Mget_drive_status							*C5Mget_drive_status;
funcC5Mget_end_status							*C5Mget_end_status;
funcC5Mget_mechanical_signal					*C5Mget_mechanical_signal;
funcC5Mget_velocity								*C5Mget_velocity;
funcC5Mget_error								*C5Mget_error;
funcC5Mget_drivedistance						*C5Mget_drivedistance;

funcC5Mset_enc_input_method						*C5Mset_enc_input_method;
funcC5Mget_enc_input_method						*C5Mget_enc_input_method;

funcC5Mset_pulse_out_method						*C5Mset_pulse_out_method;
funcC5Mget_pulse_out_method						*C5Mget_pulse_out_method;

funcC5Mset_actual_position						*C5Mset_actual_position;
funcC5Mget_actual_position						*C5Mget_actual_position;
funcC5Mset_command_position						*C5Mset_command_position;
funcC5Mget_command_position						*C5Mget_command_position;

funcC5Mset_servo_level							*C5Mset_servo_level;
funcC5Mget_servo_level							*C5Mget_servo_level;
funcC5Mset_servo_enable							*C5Mset_servo_enable;
funcC5Mget_servo_enable							*C5Mget_servo_enable;

funcC5Mset_inposition_enable					*C5Mset_inposition_enable;
funcC5Mget_inposition_enable					*C5Mget_inposition_enable;
funcC5Mset_inposition_level						*C5Mset_inposition_level;
funcC5Mget_inposition_level						*C5Mget_inposition_level;
funcC5Mget_inposition_switch					*C5Mget_inposition_switch;
funcC5Min_position								*C5Min_position;
funcC5Mset_alarm_enable							*C5Mset_alarm_enable;
funcC5Mget_alarm_enable							*C5Mget_alarm_enable;
funcC5Mset_alarm_level							*C5Mset_alarm_level;
funcC5Mget_alarm_level							*C5Mget_alarm_level;
funcC5Mget_alarm_switch							*C5Mget_alarm_switch;

funcC5Mset_nend_limit_level						*C5Mset_nend_limit_level;
funcC5Mget_nend_limit_level						*C5Mget_nend_limit_level;
funcC5Mget_nend_limit_switch					*C5Mget_nend_limit_switch;
funcC5Mset_pend_limit_level						*C5Mset_pend_limit_level;
funcC5Mget_pend_limit_level						*C5Mget_pend_limit_level;
funcC5Mget_pend_limit_switch					*C5Mget_pend_limit_switch;
funcC5Mset_nslow_limit_level					*C5Mset_nslow_limit_level;
funcC5Mget_nslow_limit_level					*C5Mget_nslow_limit_level;
funcC5Mget_nslow_limit_switch					*C5Mget_nslow_limit_switch;
funcC5Mset_pslow_limit_level					*C5Mset_pslow_limit_level;
funcC5Mget_pslow_limit_level					*C5Mget_pslow_limit_level;
funcC5Mget_pslow_limit_switch					*C5Mget_pslow_limit_switch;
funcC5Mset_nlimit_sel							*C5Mset_nlimit_sel;
funcC5Mget_nlimit_sel							*C5Mget_nlimit_sel;
funcC5Mset_plimit_sel							*C5Mset_plimit_sel;
funcC5Mget_plimit_sel							*C5Mget_plimit_sel;

funcC5Mset_stop_sel								*C5Mset_stop_sel;
funcC5Mget_stop_sel								*C5Mget_stop_sel;


funcC5Mmove										*C5Mmove;
funcC5Mmove_ex									*C5Mmove_ex;
funcC5Mr_move									*C5Mr_move;
funcC5Mr_move_ex								*C5Mr_move_ex;
funcC5Mstart_move								*C5Mstart_move;
funcC5Mstart_move_ex							*C5Mstart_move_ex;
funcC5Mstart_r_move								*C5Mstart_r_move;
funcC5Mstart_r_move_ex							*C5Mstart_r_move_ex;
funcC5Mqs_move									*C5Mqs_move;
funcC5Mqs_move_ex								*C5Mqs_move_ex;
funcC5Mrqs_move									*C5Mrqs_move;
funcC5Mrqs_move_ex								*C5Mrqs_move_ex;
funcC5Mstart_qs_move							*C5Mstart_qs_move;
funcC5Mstart_qs_move_ex							*C5Mstart_qs_move_ex;
funcC5Mstart_rqs_move							*C5Mstart_rqs_move;
funcC5Mstart_rqs_move_ex						*C5Mstart_rqs_move_ex;


funcC5Mv_move									*C5Mv_move;
funcC5Mv_move_ex								*C5Mv_move_ex;
funcC5Mv_qs_move								*C5Mv_qs_move;
funcC5Mv_qs_move_ex								*C5Mv_qs_move_ex;


funcC5Mstart_signal_search1						*C5Mstart_signal_search1;
funcC5Mstart_signal_search1_ex					*C5Mstart_signal_search1_ex;
funcC5Mstart_qs_signal_search1					*C5Mstart_qs_signal_search1;
funcC5Mstart_qs_signal_search1_ex				*C5Mstart_qs_signal_search1_ex;
funcC5Mstart_signal_search2						*C5Mstart_signal_search2;

funcC5Mposition_override						*C5Mposition_override;
funcC5Mposition_r_override						*C5Mposition_r_override;

funcC5Mwait_for_done							*C5Mwait_for_done;

funcC5Mset_e_stop								*C5Mset_e_stop;
funcC5Mset_stop									*C5Mset_stop;
funcC5Mset_stop_decel							*C5Mset_stop_decel;
funcC5Mset_stop_deceltime						*C5Mset_stop_deceltime;

funcC5Mlink										*C5Mlink;
funcC5Mendlink									*C5Mendlink;

funcC5Mmap_axes									*C5Mmap_axes;
funcC5Mget_mapped_axes							*C5Mget_mapped_axes;
funcC5Mset_coordinate_mode						*C5Mset_coordinate_mode;
funcC5Mget_coordinate_mode						*C5Mget_coordinate_mode;
funcC5Mset_move_profile							*C5Mset_move_profile;
funcC5Mget_move_profile							*C5Mget_move_profile;
funcC5Mset_move_startstop_velocity				*C5Mset_move_startstop_velocity;
funcC5Mget_move_startstop_velocity				*C5Mget_move_startstop_velocity;
funcC5Mset_move_velocity						*C5Mset_move_velocity;
funcC5Mget_move_velocity						*C5Mget_move_velocity;
funcC5Mset_move_acceleration					*C5Mset_move_acceleration;
funcC5Mget_move_acceleration					*C5Mget_move_acceleration;
funcC5Mset_move_acceltime						*C5Mset_move_acceltime;
funcC5Mget_move_acceltime						*C5Mget_move_acceltime;
funcC5Mco_get_velocity							*C5Mco_get_velocity;

funcC5Mmove_2									*C5Mmove_2;
funcC5Mmove_3									*C5Mmove_3;
funcC5Mmove_4									*C5Mmove_4;
funcC5Mstart_move_2								*C5Mstart_move_2;
funcC5Mstart_move_3								*C5Mstart_move_3;
funcC5Mstart_move_4								*C5Mstart_move_4;
funcC5Mco_motion_done							*C5Mco_motion_done;
funcC5Mco_wait_for_done							*C5Mco_wait_for_done;


funcC5Mmove_all									*C5Mmove_all;
funcC5Mmove_all_ex								*C5Mmove_all_ex;
funcC5Mr_move_all								*C5Mr_move_all;
funcC5Mr_move_all_ex							*C5Mr_move_all_ex;
funcC5Mstart_move_all							*C5Mstart_move_all;
funcC5Mstart_move_all_ex						*C5Mstart_move_all_ex;
funcC5Mstart_r_move_all							*C5Mstart_r_move_all;
funcC5Mstart_r_move_all_ex						*C5Mstart_r_move_all_ex;
funcC5Mqs_move_all								*C5Mqs_move_all;
funcC5Mqs_move_all_ex							*C5Mqs_move_all_ex;
funcC5Mrqs_move_all								*C5Mrqs_move_all;
funcC5Mrqs_move_all_ex							*C5Mrqs_move_all_ex;
funcC5Mstart_qs_move_all						*C5Mstart_qs_move_all;
funcC5Mstart_qs_move_all_ex						*C5Mstart_qs_move_all_ex;
funcC5Mstart_rqs_move_all						*C5Mstart_rqs_move_all;
funcC5Mstart_rqs_move_all_ex					*C5Mstart_rqs_move_all_ex;
funcC5Mset_qs_rate_all							*C5Mset_qs_rate_all;
funcC5Mget_qs_rate_all							*C5Mget_qs_rate_all;

funcC5Mwait_for_all								*C5Mwait_for_all;

funcC5Mreset_axis_sync							*C5Mreset_axis_sync;
funcC5Mset_axis_sync							*C5Mset_axis_sync;
funcC5Mset_sync									*C5Mset_sync;
funcC5Mget_sync_info							*C5Mget_sync_info;

funcC5Memergency_stop							*C5Memergency_stop;

funcC5Mabort_home_search						*C5Mabort_home_search;
funcC5Mhome_search								*C5Mhome_search;
funcC5Mhome_search_all							*C5Mhome_search_all;
funcC5Mget_home_done							*C5Mget_home_done;
funcC5Mget_home_done_all						*C5Mget_home_done_all;
funcC5Mget_home_end_status						*C5Mget_home_end_status;
funcC5Mget_home_end_status_all					*C5Mget_home_end_status_all;
funcC5Mset_home_method							*C5Mset_home_method;
funcC5Mget_home_method							*C5Mget_home_method;
funcC5Mset_home_offset							*C5Mset_home_offset;
funcC5Mget_home_offset							*C5Mget_home_offset;
funcC5Mset_home_velocity						*C5Mset_home_velocity;
funcC5Mget_home_velocity						*C5Mget_home_velocity;
funcC5Mset_home_acceleration					*C5Mset_home_acceleration;
funcC5Mget_home_acceleration					*C5Mget_home_acceleration;
funcC5Mset_home_acceltime						*C5Mset_home_acceltime;
funcC5Mget_home_acceltime						*C5Mget_home_acceltime;
funcC5Mset_zphase_search_range					*C5Mset_zphase_search_range;
funcC5Mget_zphase_search_range					*C5Mget_zphase_search_range;
funcC5Mhome_zero								*C5Mhome_zero;
funcC5Mhome_zero_all							*C5Mhome_zero_all;


funcC5Mset_output								*C5Mset_output;
funcC5Mget_output								*C5Mget_output;
funcC5Mget_input								*C5Mget_input;
funcC5Mset_output_bit							*C5Mset_output_bit;
funcC5Mreset_output_bit							*C5Mreset_output_bit;
funcC5Moutput_bit_on							*C5Moutput_bit_on;
funcC5Mchange_output_bit						*C5Mchange_output_bit;
funcC5Minput_bit_on								*C5Minput_bit_on;

funcC5Mset_crc_mask								*C5Mset_crc_mask;
funcC5Mget_crc_mask								*C5Mget_crc_mask;
funcC5Mset_crc_level							*C5Mset_crc_level;
funcC5Mget_crc_level							*C5Mget_crc_level;
funcC5Mset_crc_nelm_mask						*C5Mset_crc_nelm_mask;
funcC5Mget_crc_nelm_mask						*C5Mget_crc_nelm_mask;
funcC5Mset_crc_nelm_level						*C5Mset_crc_nelm_level;
funcC5Mget_crc_nelm_level						*C5Mget_crc_nelm_level;
funcC5Mset_crc_pelm_mask						*C5Mset_crc_pelm_mask;
funcC5Mget_crc_pelm_mask						*C5Mget_crc_pelm_mask;
funcC5Mset_crc_pelm_level						*C5Mset_crc_pelm_level;
funcC5Mget_crc_pelm_level						*C5Mget_crc_pelm_level;
funcC5Mset_programmed_crc						*C5Mset_programmed_crc;
funcC5Mget_programmed_crc						*C5Mget_programmed_crc;

funcC5Mset_trigger_level						*C5Mset_trigger_level;
funcC5Mget_trigger_level						*C5Mget_trigger_level;
funcC5Mset_trigger_sel							*C5Mset_trigger_sel;
funcC5Mget_trigger_sel							*C5Mget_trigger_sel;
funcC5Mset_trigger_time							*C5Mset_trigger_time;
funcC5Mget_trigger_time							*C5Mget_trigger_time;
funcC5Mset_trigger_enable						*C5Mset_trigger_enable;
funcC5Mis_trigger_enabled						*C5Mis_trigger_enabled;
funcC5Mset_trigger_interrupt_enable				*C5Mset_trigger_interrupt_enable;
funcC5Mis_trigger_interrupt_enabled				*C5Mis_trigger_interrupt_enabled;

funcC5Mset_internal_comparator_position			*C5Mset_internal_comparator_position;
funcC5Mget_internal_comparator_position			*C5Mget_internal_comparator_position;
funcC5Mset_external_comparator_position			*C5Mset_external_comparator_position;
funcC5Mget_external_comparator_position			*C5Mget_external_comparator_position;

funcC5Mset_motiondone_interrupt_enable			*C5Mset_motiondone_interrupt_enable;
funcC5Mis_motiondone_interrupt_enabled			*C5Mis_motiondone_interrupt_enabled;

funcC5Mget_error_code							*C5Mget_error_code;
funcC5Mget_error_msg							*C5Mget_error_msg;



BOOL LoadAxtCAMC5M()
{
	g_hAxtCAMC5M	= LoadLibrary("AxtLib.dll");

	if (g_hAxtCAMC5M)
	{
		InitializeCAMC5M						= (funcInitializeCAMC5M *)GetProcAddress(g_hAxtCAMC5M, "InitializeCAMC5M");
		C5MIsInitialized						= (funcC5MIsInitialized *)GetProcAddress(g_hAxtCAMC5M, "C5MIsInitialized");
		C5MStopService							= (funcC5MStopService *)GetProcAddress(g_hAxtCAMC5M, "C5MStopService");

		C5Mget_boardno							= (funcC5Mget_boardno *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_boardno");
		C5Mget_numof_boards						= (funcC5Mget_numof_boards *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_numof_boards");
		C5Mget_numof_axes						= (funcC5Mget_numof_axes *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_numof_axes");
		C5Mget_total_numof_axis					= (funcC5Mget_total_numof_axis *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_total_numof_axis");
		C5Mget_axisno							= (funcC5Mget_axisno *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_axisno");
		C5Mget_axis_info						= (funcC5Mget_axis_info *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_axis_info");

		C5Mload_parameter						= (funcC5Mload_parameter *)GetProcAddress(g_hAxtCAMC5M, "C5Mload_parameter");
		C5Msave_parameter						= (funcC5Msave_parameter *)GetProcAddress(g_hAxtCAMC5M, "C5Msave_parameter");
		C5Mload_parameter_all					= (funcC5Mload_parameter_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mload_parameter_all");
		C5Msave_parameter_all					= (funcC5Msave_parameter_all *)GetProcAddress(g_hAxtCAMC5M, "C5Msave_parameter_all");

		C5MSetWindowMessage						= (funcC5MSetWindowMessage *)GetProcAddress(g_hAxtCAMC5M, "C5MSetWindowMessage");

		C5MKeSetMainClk							= (funcC5MKeSetMainClk *)GetProcAddress(g_hAxtCAMC5M, "C5MKeSetMainClk");
		C5Mset_drive_mode1						= (funcC5Mset_drive_mode1 *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_drive_mode1");
		C5Mget_drive_mode1						= (funcC5Mget_drive_mode1 *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_drive_mode1");
		C5Mset_drive_mode2						= (funcC5Mset_drive_mode2 *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_drive_mode2");
		C5Mget_drive_mode2						= (funcC5Mget_drive_mode2 *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_drive_mode2");
		C5Mset_moveunit_perpulse				= (funcC5Mset_moveunit_perpulse *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_moveunit_perpulse");
		C5Mget_moveunit_perpulse				= (funcC5Mget_moveunit_perpulse *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_moveunit_perpulse");
		C5Mset_movepulse_perunit				= (funcC5Mset_movepulse_perunit *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_movepulse_perunit");
		C5Mget_movepulse_perunit				= (funcC5Mget_movepulse_perunit *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_movepulse_perunit");
		C5Mset_startstop_speed					= (funcC5Mset_startstop_speed *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_startstop_speed");
		C5Mget_startstop_speed					= (funcC5Mget_startstop_speed *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_startstop_speed");
		C5Mset_max_speed						= (funcC5Mset_max_speed *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_max_speed");
		C5Mget_max_speed						= (funcC5Mget_max_speed *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_max_speed");
		C5Mset_qs_rate							= (funcC5Mset_qs_rate *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_qs_rate");
		C5Mget_qs_rate							= (funcC5Mget_qs_rate *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_qs_rate");
		C5Mset_slowdown_rear_pulse				= (funcC5Mset_slowdown_rear_pulse *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_slowdown_rear_pulse");
		C5Mget_slowdown_rear_pulse				= (funcC5Mget_slowdown_rear_pulse *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_slowdown_rear_pulse");
		C5Mset_decel_point						= (funcC5Mset_decel_point *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_decel_point");
		C5Mget_decel_point						= (funcC5Mget_decel_point *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_decel_point");

		C5Min_motion							= (funcC5Min_motion *)GetProcAddress(g_hAxtCAMC5M, "C5Min_motion");
		C5Mmotion_done							= (funcC5Mmotion_done *)GetProcAddress(g_hAxtCAMC5M, "C5Mmotion_done");
		C5Mget_drive_pulse_counts				= (funcC5Mget_drive_pulse_counts *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_drive_pulse_counts");
		C5Mget_drive_status						= (funcC5Mget_drive_status *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_drive_status");
		C5Mget_end_status						= (funcC5Mget_end_status *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_end_status");
		C5Mget_mechanical_signal				= (funcC5Mget_mechanical_signal *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_mechanical_signal");
		C5Mget_velocity							= (funcC5Mget_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_velocity");
		C5Mget_error							= (funcC5Mget_error *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_error");
		C5Mget_drivedistance					= (funcC5Mget_drivedistance *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_drivedistance");

		C5Mset_enc_input_method					= (funcC5Mset_enc_input_method *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_enc_input_method");
		C5Mget_enc_input_method					= (funcC5Mget_enc_input_method *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_enc_input_method");

		C5Mset_pulse_out_method					= (funcC5Mset_pulse_out_method *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_pulse_out_method");
		C5Mget_pulse_out_method					= (funcC5Mget_pulse_out_method *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_pulse_out_method");

		C5Mset_actual_position					= (funcC5Mset_actual_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_actual_position");
		C5Mget_actual_position					= (funcC5Mget_actual_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_actual_position");
		C5Mset_command_position					= (funcC5Mset_command_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_command_position");
		C5Mget_command_position					= (funcC5Mget_command_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_command_position");

		C5Mset_servo_level						= (funcC5Mset_servo_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_servo_level");
		C5Mget_servo_level						= (funcC5Mget_servo_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_servo_level");
		C5Mset_servo_enable						= (funcC5Mset_servo_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_servo_enable");
		C5Mget_servo_enable						= (funcC5Mget_servo_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_servo_enable");

		C5Mset_inposition_enable				= (funcC5Mset_inposition_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_inposition_enable");
		C5Mget_inposition_enable				= (funcC5Mget_inposition_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_inposition_enable");
		C5Mset_inposition_level					= (funcC5Mset_inposition_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_inposition_level");
		C5Mget_inposition_level					= (funcC5Mget_inposition_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_inposition_level");
		C5Mget_inposition_switch				= (funcC5Mget_inposition_switch *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_inposition_switch");
		C5Min_position							= (funcC5Min_position *)GetProcAddress(g_hAxtCAMC5M, "C5Min_position");
		C5Mset_alarm_enable						= (funcC5Mset_alarm_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_alarm_enable");
		C5Mget_alarm_enable						= (funcC5Mget_alarm_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_alarm_enable");
		C5Mset_alarm_level						= (funcC5Mset_alarm_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_alarm_level");
		C5Mget_alarm_level						= (funcC5Mget_alarm_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_alarm_level");
		C5Mget_alarm_switch						= (funcC5Mget_alarm_switch *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_alarm_switch");

		C5Mset_nend_limit_level					= (funcC5Mset_nend_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_nend_limit_level");
		C5Mget_nend_limit_level					= (funcC5Mget_nend_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_nend_limit_level");
		C5Mget_nend_limit_switch				= (funcC5Mget_nend_limit_switch *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_nend_limit_switch");
		C5Mset_pend_limit_level					= (funcC5Mset_pend_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_pend_limit_level");
		C5Mget_pend_limit_level					= (funcC5Mget_pend_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_pend_limit_level");
		C5Mget_pend_limit_switch				= (funcC5Mget_pend_limit_switch *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_pend_limit_switch");
		C5Mset_nslow_limit_level				= (funcC5Mset_nslow_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_nslow_limit_level");
		C5Mget_nslow_limit_level				= (funcC5Mget_nslow_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_nslow_limit_level");
		C5Mget_nslow_limit_switch				= (funcC5Mget_nslow_limit_switch *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_nslow_limit_switch");
		C5Mset_pslow_limit_level				= (funcC5Mset_pslow_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_pslow_limit_level");
		C5Mget_pslow_limit_level				= (funcC5Mget_pslow_limit_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_pslow_limit_level");
		C5Mget_pslow_limit_switch				= (funcC5Mget_pslow_limit_switch *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_pslow_limit_switch");
		C5Mset_nlimit_sel						= (funcC5Mset_nlimit_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_nlimit_sel");
		C5Mget_nlimit_sel						= (funcC5Mget_nlimit_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_nlimit_sel");
		C5Mset_plimit_sel						= (funcC5Mset_plimit_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_plimit_sel");
		C5Mget_plimit_sel						= (funcC5Mget_plimit_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_plimit_sel");

		C5Mset_stop_sel							= (funcC5Mset_stop_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_stop_sel");
		C5Mget_stop_sel							= (funcC5Mget_stop_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_stop_sel");


		C5Mmove									= (funcC5Mmove *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove");
		C5Mmove_ex								= (funcC5Mmove_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove_ex");
		C5Mr_move								= (funcC5Mr_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mr_move");
		C5Mr_move_ex							= (funcC5Mr_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mr_move_ex");
		C5Mstart_move							= (funcC5Mstart_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move");
		C5Mstart_move_ex						= (funcC5Mstart_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move_ex");
		C5Mstart_r_move							= (funcC5Mstart_r_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_r_move");
		C5Mstart_r_move_ex						= (funcC5Mstart_r_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_r_move_ex");
		C5Mqs_move								= (funcC5Mqs_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mqs_move");
		C5Mqs_move_ex							= (funcC5Mqs_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mqs_move_ex");
		C5Mrqs_move								= (funcC5Mrqs_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mrqs_move");
		C5Mrqs_move_ex							= (funcC5Mrqs_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mrqs_move_ex");
		C5Mstart_qs_move						= (funcC5Mstart_qs_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_qs_move");
		C5Mstart_qs_move_ex						= (funcC5Mstart_qs_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_qs_move_ex");
		C5Mstart_rqs_move						= (funcC5Mstart_rqs_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_rqs_move");
		C5Mstart_rqs_move_ex					= (funcC5Mstart_rqs_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_rqs_move_ex");


		C5Mv_move								= (funcC5Mv_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mv_move");
		C5Mv_move_ex							= (funcC5Mv_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mv_move_ex");
		C5Mv_qs_move							= (funcC5Mv_qs_move *)GetProcAddress(g_hAxtCAMC5M, "C5Mv_qs_move");
		C5Mv_qs_move_ex							= (funcC5Mv_qs_move_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mv_qs_move_ex");


		C5Mstart_signal_search1					= (funcC5Mstart_signal_search1 *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_signal_search1");
		C5Mstart_signal_search1_ex				= (funcC5Mstart_signal_search1_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_signal_search1_ex");
		C5Mstart_qs_signal_search1				= (funcC5Mstart_qs_signal_search1 *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_qs_signal_search1");
		C5Mstart_qs_signal_search1_ex			= (funcC5Mstart_qs_signal_search1_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_qs_signal_search1_ex");
		C5Mstart_signal_search2					= (funcC5Mstart_signal_search2 *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_signal_search2");

		C5Mposition_override					= (funcC5Mposition_override *)GetProcAddress(g_hAxtCAMC5M, "C5Mposition_override");
		C5Mposition_r_override					= (funcC5Mposition_r_override *)GetProcAddress(g_hAxtCAMC5M, "C5Mposition_r_override");

		C5Mwait_for_done						= (funcC5Mwait_for_done *)GetProcAddress(g_hAxtCAMC5M, "C5Mwait_for_done");

		C5Mset_e_stop							= (funcC5Mset_e_stop *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_e_stop");
		C5Mset_stop								= (funcC5Mset_stop *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_stop");
		C5Mset_stop_decel						= (funcC5Mset_stop_decel *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_stop_decel");
		C5Mset_stop_deceltime					= (funcC5Mset_stop_deceltime *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_stop_deceltime");

		C5Mlink									= (funcC5Mlink *)GetProcAddress(g_hAxtCAMC5M, "C5Mlink");
		C5Mendlink								= (funcC5Mendlink *)GetProcAddress(g_hAxtCAMC5M, "C5Mendlink");

		C5Mmap_axes								= (funcC5Mmap_axes *)GetProcAddress(g_hAxtCAMC5M, "C5Mmap_axes");
		C5Mget_mapped_axes						= (funcC5Mget_mapped_axes *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_mapped_axes");
		C5Mset_coordinate_mode					= (funcC5Mset_coordinate_mode *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_coordinate_mode");
		C5Mget_coordinate_mode					= (funcC5Mget_coordinate_mode *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_coordinate_mode");
		C5Mset_move_profile						= (funcC5Mset_move_profile *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_move_profile");
		C5Mget_move_profile						= (funcC5Mget_move_profile *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_move_profile");
		C5Mset_move_startstop_velocity			= (funcC5Mset_move_startstop_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_move_startstop_velocity");
		C5Mget_move_startstop_velocity			= (funcC5Mget_move_startstop_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_move_startstop_velocity");
		C5Mset_move_velocity					= (funcC5Mset_move_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_move_velocity");
		C5Mget_move_velocity					= (funcC5Mget_move_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_move_velocity");
		C5Mset_move_acceleration				= (funcC5Mset_move_acceleration *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_move_acceleration");
		C5Mget_move_acceleration				= (funcC5Mget_move_acceleration *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_move_acceleration");
		C5Mset_move_acceltime					= (funcC5Mset_move_acceltime *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_move_acceltime");
		C5Mget_move_acceltime					= (funcC5Mget_move_acceltime *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_move_acceltime");
		C5Mco_get_velocity						= (funcC5Mco_get_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mco_get_velocity");

		C5Mmove_2								= (funcC5Mmove_2 *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove_2");
		C5Mmove_3								= (funcC5Mmove_3 *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove_3");
		C5Mmove_4								= (funcC5Mmove_4 *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove_4");
		C5Mstart_move_2							= (funcC5Mstart_move_2 *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move_2");
		C5Mstart_move_3							= (funcC5Mstart_move_3 *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move_3");
		C5Mstart_move_4							= (funcC5Mstart_move_4 *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move_4");
		C5Mco_motion_done						= (funcC5Mco_motion_done *)GetProcAddress(g_hAxtCAMC5M, "C5Mco_motion_done");
		C5Mco_wait_for_done						= (funcC5Mco_wait_for_done *)GetProcAddress(g_hAxtCAMC5M, "C5Mco_wait_for_done");


		C5Mmove_all								= (funcC5Mmove_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove_all");
		C5Mmove_all_ex							= (funcC5Mmove_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mmove_all_ex");
		C5Mr_move_all							= (funcC5Mr_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mr_move_all");
		C5Mr_move_all_ex						= (funcC5Mr_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mr_move_all_ex");
		C5Mstart_move_all						= (funcC5Mstart_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move_all");
		C5Mstart_move_all_ex					= (funcC5Mstart_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_move_all_ex");
		C5Mstart_r_move_all						= (funcC5Mstart_r_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_r_move_all");
		C5Mstart_r_move_all_ex					= (funcC5Mstart_r_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_r_move_all_ex");
		C5Mqs_move_all							= (funcC5Mqs_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mqs_move_all");
		C5Mqs_move_all_ex						= (funcC5Mqs_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mqs_move_all_ex");
		C5Mrqs_move_all							= (funcC5Mrqs_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mrqs_move_all");
		C5Mrqs_move_all_ex						= (funcC5Mrqs_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mrqs_move_all_ex");
		C5Mstart_qs_move_all					= (funcC5Mstart_qs_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_qs_move_all");
		C5Mstart_qs_move_all_ex					= (funcC5Mstart_qs_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_qs_move_all_ex");
		C5Mstart_rqs_move_all					= (funcC5Mstart_rqs_move_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_rqs_move_all");
		C5Mstart_rqs_move_all_ex				= (funcC5Mstart_rqs_move_all_ex *)GetProcAddress(g_hAxtCAMC5M, "C5Mstart_rqs_move_all_ex");
		C5Mset_qs_rate_all						= (funcC5Mset_qs_rate_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_qs_rate_all");
		C5Mget_qs_rate_all						= (funcC5Mget_qs_rate_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_qs_rate_all");

		C5Mwait_for_all							= (funcC5Mwait_for_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mwait_for_all");

		C5Mreset_axis_sync						= (funcC5Mreset_axis_sync *)GetProcAddress(g_hAxtCAMC5M, "C5Mreset_axis_sync");
		C5Mset_axis_sync						= (funcC5Mset_axis_sync *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_axis_sync");
		C5Mset_sync								= (funcC5Mset_sync *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_sync");
		C5Mget_sync_info						= (funcC5Mget_sync_info *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_sync_info");

		C5Memergency_stop						= (funcC5Memergency_stop *)GetProcAddress(g_hAxtCAMC5M, "C5Memergency_stop");

		C5Mabort_home_search					= (funcC5Mabort_home_search *)GetProcAddress(g_hAxtCAMC5M, "C5Mabort_home_search");
		C5Mhome_search							= (funcC5Mhome_search *)GetProcAddress(g_hAxtCAMC5M, "C5Mhome_search");
		C5Mhome_search_all						= (funcC5Mhome_search_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mhome_search_all");
		C5Mget_home_done						= (funcC5Mget_home_done *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_done");
		C5Mget_home_done_all					= (funcC5Mget_home_done_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_done_all");
		C5Mget_home_end_status					= (funcC5Mget_home_end_status *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_end_status");
		C5Mget_home_end_status_all				= (funcC5Mget_home_end_status_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_end_status_all");
		C5Mset_home_method						= (funcC5Mset_home_method *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_home_method");
		C5Mget_home_method						= (funcC5Mget_home_method *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_method");
		C5Mset_home_offset						= (funcC5Mset_home_offset *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_home_offset");
		C5Mget_home_offset						= (funcC5Mget_home_offset *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_offset");
		C5Mset_home_velocity					= (funcC5Mset_home_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_home_velocity");
		C5Mget_home_velocity					= (funcC5Mget_home_velocity *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_velocity");
		C5Mset_home_acceleration				= (funcC5Mset_home_acceleration *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_home_acceleration");
		C5Mget_home_acceleration				= (funcC5Mget_home_acceleration *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_acceleration");
		C5Mset_home_acceltime					= (funcC5Mset_home_acceltime *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_home_acceltime");
		C5Mget_home_acceltime					= (funcC5Mget_home_acceltime *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_home_acceltime");
		C5Mset_zphase_search_range				= (funcC5Mset_zphase_search_range *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_zphase_search_range");
		C5Mget_zphase_search_range				= (funcC5Mget_zphase_search_range *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_zphase_search_range");
		C5Mhome_zero							= (funcC5Mhome_zero *)GetProcAddress(g_hAxtCAMC5M, "C5Mhome_zero");
		C5Mhome_zero_all						= (funcC5Mhome_zero_all *)GetProcAddress(g_hAxtCAMC5M, "C5Mhome_zero_all");


		C5Mset_output							= (funcC5Mset_output *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_output");
		C5Mget_output							= (funcC5Mget_output *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_output");
		C5Mget_input							= (funcC5Mget_input *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_input");
		C5Mset_output_bit						= (funcC5Mset_output_bit *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_output_bit");
		C5Mreset_output_bit						= (funcC5Mreset_output_bit *)GetProcAddress(g_hAxtCAMC5M, "C5Mreset_output_bit");
		C5Moutput_bit_on						= (funcC5Moutput_bit_on *)GetProcAddress(g_hAxtCAMC5M, "C5Moutput_bit_on");
		C5Mchange_output_bit					= (funcC5Mchange_output_bit *)GetProcAddress(g_hAxtCAMC5M, "C5Mchange_output_bit");
		C5Minput_bit_on							= (funcC5Minput_bit_on *)GetProcAddress(g_hAxtCAMC5M, "C5Minput_bit_on");

		C5Mset_crc_mask							= (funcC5Mset_crc_mask *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_crc_mask");
		C5Mget_crc_mask							= (funcC5Mget_crc_mask *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_crc_mask");
		C5Mset_crc_level						= (funcC5Mset_crc_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_crc_level");
		C5Mget_crc_level						= (funcC5Mget_crc_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_crc_level");
		C5Mset_crc_nelm_mask					= (funcC5Mset_crc_nelm_mask *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_crc_nelm_mask");
		C5Mget_crc_nelm_mask					= (funcC5Mget_crc_nelm_mask *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_crc_nelm_mask");
		C5Mset_crc_nelm_level					= (funcC5Mset_crc_nelm_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_crc_nelm_level");
		C5Mget_crc_nelm_level					= (funcC5Mget_crc_nelm_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_crc_nelm_level");
		C5Mset_crc_pelm_mask					= (funcC5Mset_crc_pelm_mask *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_crc_pelm_mask");
		C5Mget_crc_pelm_mask					= (funcC5Mget_crc_pelm_mask *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_crc_pelm_mask");
		C5Mset_crc_pelm_level					= (funcC5Mset_crc_pelm_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_crc_pelm_level");
		C5Mget_crc_pelm_level					= (funcC5Mget_crc_pelm_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_crc_pelm_level");
		C5Mset_programmed_crc					= (funcC5Mset_programmed_crc *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_programmed_crc");
		C5Mget_programmed_crc					= (funcC5Mget_programmed_crc *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_programmed_crc");

		C5Mset_trigger_level					= (funcC5Mset_trigger_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_trigger_level");
		C5Mget_trigger_level					= (funcC5Mget_trigger_level *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_trigger_level");
		C5Mset_trigger_sel						= (funcC5Mset_trigger_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_trigger_sel");
		C5Mget_trigger_sel						= (funcC5Mget_trigger_sel *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_trigger_sel");
		C5Mset_trigger_time						= (funcC5Mset_trigger_time *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_trigger_time");
		C5Mget_trigger_time						= (funcC5Mget_trigger_time *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_trigger_time");
		C5Mset_trigger_enable					= (funcC5Mset_trigger_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_trigger_enable");
		C5Mis_trigger_enabled					= (funcC5Mis_trigger_enabled *)GetProcAddress(g_hAxtCAMC5M, "C5Mis_trigger_enabled");
		C5Mset_trigger_interrupt_enable			= (funcC5Mset_trigger_interrupt_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_trigger_interrupt_enable");
		C5Mis_trigger_interrupt_enabled			= (funcC5Mis_trigger_interrupt_enabled *)GetProcAddress(g_hAxtCAMC5M, "C5Mis_trigger_interrupt_enabled");

		C5Mset_internal_comparator_position		= (funcC5Mset_internal_comparator_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_internal_comparator_position");
		C5Mget_internal_comparator_position		= (funcC5Mget_internal_comparator_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_internal_comparator_position");
		C5Mset_external_comparator_position		= (funcC5Mset_external_comparator_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_external_comparator_position");
		C5Mget_external_comparator_position		= (funcC5Mget_external_comparator_position *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_external_comparator_position");

		C5Mset_motiondone_interrupt_enable		= (funcC5Mset_motiondone_interrupt_enable *)GetProcAddress(g_hAxtCAMC5M, "C5Mset_motiondone_interrupt_enable");
		C5Mis_motiondone_interrupt_enabled		= (funcC5Mis_motiondone_interrupt_enabled *)GetProcAddress(g_hAxtCAMC5M, "C5Mis_motiondone_interrupt_enabled");

		C5Mget_error_code						= (funcC5Mget_error_code *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_error_code");
		C5Mget_error_msg						= (funcC5Mget_error_msg *)GetProcAddress(g_hAxtCAMC5M, "C5Mget_error_msg");


		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL FreeAxtCAMC5M()
{
	if (g_hAxtCAMC5M)
	{
		FreeLibrary(g_hAxtCAMC5M);
		g_hAxtCAMC5M	 = NULL;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}