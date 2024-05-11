//---------------------------------------------------------------------------

#ifndef IODefinesH
#define IODefinesH
//---------------------------------------------------------------------------
enum IO_DEFINES
{
	I_EMERGENCY_SWITCH_ON					=	0	,	// X000
	I_BUZZER_OFF_SWITCH_ON					=	1	,	// X001
	I_DOOR_OPEN_CYLINDER_ON					=	2	,	// X002
	I_N2_PRESSURE_DETECTED					=	3	,	// X003
	I_HEATER_OVERLOAD_DETECTED				=	4	,	// X004
	I_BLOW_MOTOR_OVERLOAD_DETECTED			=	5	,	// X005
	I_CHAMBER_OVER_TEMP1_DETECTED			=	6	,	// X006
	I_HEATER_SINK_TEMP_CHECK_DETECTED		=	7	,	// X007
	I_CHAMBER_DOOR_CLOSE_DETECTED			=	8	,	// X008
	I_X009									=	9	,	// X009
	I_CHAMBER_OVER_TEMP2_DETECTED			=	10	,	// X00A
	I_X00B									=	11	,	// X00B
	I_X00C									=	12	,	// X00C
	I_X00D									=	13	,	// X00D
	I_X00E									=	14	,	// X00E
	I_X00F									=	15	,	// X00F

	I_X010									=	16	,	// X010
	I_X011	 								=	17	,	// X011
	I_X012									=	18	,	// X012
	I_X013									=	19	,	// X013
	I_X014	   								=	20	,	// X014
	I_X015	   								=	21	,	// X015
	I_X016	   								=	22	,	// X016
	I_X017	   								=	23	,	// X017
	I_X018									=	24	,	// X018
	I_X019	   								=	25	,	// X019
	I_X01A	   								=	26	,	// X01A
	I_X01B	   								=	27	,	// X01B
	I_X01C	   								=	28	,	// X01C
	I_X01D	   								=	29	,	// X01D
	I_X01E	   								=	30	,	// X01E
	I_X01F									=	31	,	// X01F

	O_TOWER_LAMP_RED						=	32	,	// Y000
	O_TOWER_LAMP_GREEN						=	33	,	// Y001
	O_TOWER_LAMP_YELLOW						=	34	,	// Y002
	O_BUZZER_ON								=	35	,	// Y003
	O_BUZZER_KIND							=	36	,	// Y004
	O_BUZZER_OFF_SWITCH_LAMP_ON				=	37	,	// Y005
	O_Y006									=	38	,	// Y006
	O_Y007									=	39	,	// Y007
	O_Y008									=	40	,	// Y008
	O_Y009									=	41	,	// Y009
	O_Y00A									=	42	,	// Y00A
	O_Y00B									=	43	,	// Y00B
	O_Y00C									=	44	,	// Y00C
	O_Y00D									=	45	,	// Y00D
	O_Y00E									=	46	,	// Y00E
	O_Y00F									=	47	,	// Y00F

	O_UP55A_RUN								=	48	,	// Y010
	O_UP55A_STOP   							=	49	,	// Y011
	O_UP55A_LOCAL  							=	50	,	// Y012
	O_UP55A_PATTERN_BIT0					=	51	,	// Y013
	O_UP55A_PATTERN_BIT1					=	52	,	// Y014
	O_UP55A_PATTERN_BIT2   					=	53	,	// Y015
	O_UP55A_PATTERN_BIT3   					=	54	,	// Y016
	O_UP55A_PATTERN_BIT4   					=	55	,	// Y017
	O_Y018									=	56	,	// Y018
	O_Y019									=	57	,	// Y019
	O_Y01A 									=	58	,	// Y01A
	O_Y01B 									=	59	,	// Y01B
	O_Y01C 									=	60	,	// Y01C
	O_Y01D									=	61	,	// Y01D
	O_Y01E 									=	62	,	// Y01E
	O_Y01F 									=	63	,	// Y01F

	IO_COUNT
};

const int INPUT_COUNT	= 32;
const int OUTPUT_COUNT  = 32;

#endif
