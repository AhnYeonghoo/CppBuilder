//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Motion.h"
#include "math.h"

#include "../../../../AXT(Library)/C, C++/AXTLIB.h"
#include "../../../../AXT(Library)/C, C++/AXTCAMC5M.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma comment(lib, "../../../../AXT(Library)/Library/CBuilder/AxtLib.lib")
//---------------------------------------------------------------------------
TForm1 *Form1;        
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    //-------------------------------------------------------------//
    // ## 통합 라이브러리 및 모듈 초기화 부분 ##
    if( !AxtIsInitialized())            // 통합 라이브러리가 사용 가능하지 (초기화가 되었는지) 확인.
    {                   
        if(!AxtInitialize(Form1->Handle, 0) == true)            // 통합 라이브러리 초기화.
        {
            MessageBoxA(NULL, "Can not Library Initialize!!", "Ajinextek", MB_OK);
        }
    }
    if(AxtIsInitializedBus(BUSTYPE_PCI) == 0)           // 지정한 버스(PCI)가 초기화 되었는지 확인.
    {                                                   // 버스가 ISA 일경우 BUSTYPE_PCI -> BUSTYPE_ISA 변경.
     	if(AxtOpenDeviceAuto(BUSTYPE_PCI) == 0)         // 새로운 베이스보드를 자동으로 통합라이브러리에 추가.
        {
          	MessageBoxA(NULL, "Can not Baseboard Initialize!!", "Ajinextek", MB_OK);
        }
    }
    if(!C5MIsInitialized())         // CAMC-5M모듈을 사용할 수 있도록 라이브러리가 초기화되었는지 확인.
    {
        if(!InitializeCAMC5M(true))
           	MessageBoxA(NULL, "Can not CAMC-5M Module Initilaize!!", "Ajinextek", MB_OK);
    }
    //-------------------------------------------------------------//
    // 지정한 파일에서 초기 설정 파라메터의 설정값을 읽어와 설정.
    char *nfilename= "Camc5M.Mot";
    C5Mload_parameter_all(nfilename);

    searchthread_x = NULL;
    searchthread_y = NULL;
    repeatthread_x = NULL;
    repeatthread_y = NULL;

    Timer1->Enabled = true;
    Timer2->Enabled = true;
    Timer3->Enabled = false;
    TestActive1 = false;
    TestActive2 = false;
    count1 = 0; count2 = 0;

    for( int i=0; i<C5Mget_total_numof_axis(); i++)
        m_axisset->Items->Add( IntToStr(i) + "축");

    m_axisset->ItemIndex = 0;
    axis = m_axisset->ItemIndex;
    module_axis = axis - ( axis % 2);
    m_detectsignal->ItemIndex = 4;
    m_drivedirect->ItemIndex = 1;
    m_stopmethod->ItemIndex = 1;

    // 초기 파라메터중 펄스 출력방식, 엔코더 입력 방식, 초기속도, 펄스당 거리비를 읽어와서 화면에 출력.
    m_pulseout->ItemIndex = C5Mget_pulse_out_method(axis);
    m_encinput->ItemIndex = C5Mget_enc_input_method(axis);

    m_startspeed->Text = FloatToStr(C5Mget_startstop_speed(axis));
    m_moveunit->Text =  FloatToStr(C5Mget_moveunit_perpulse(axis));

    C5Mset_max_speed(module_axis, 500000 * C5Mget_moveunit_perpulse(module_axis));      	// 500KPps에 해당하는 속도를 최고속도로 설정
    C5Mset_max_speed(module_axis+1, 500000 * C5Mget_moveunit_perpulse(module_axis+1));
}

// 모션에 대한 부분을 화면에 보여주기 위한 부분으로 타이머는 50msec으로 설정.
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    double compos0, compos1, intcnt1, intcnt2;

    compos0 = C5Mget_command_position(module_axis);
    compos1 = C5Mget_command_position(module_axis+1);
    intcnt1 = C5Mget_velocity(module_axis);
    intcnt2 = C5Mget_velocity(module_axis+1);

    m_cmdvel0->Text =  FloatToStr(intcnt1);
    m_cmdvel1->Text =  FloatToStr(intcnt2);

    // X축에 대한 속도를 그래프로 출력.
    if (C5Min_motion(module_axis))
    {
        Series1->AddXY(count1, intcnt1, "", (TColor)clTeeColor);
        Chart1->BottomAxis->Automatic = False;
        Chart1->BottomAxis->Maximum = Series1->XValues->Last();
        Chart1->BottomAxis->Minimum = Chart1->BottomAxis->Maximum - 200;
        count1 = count1 + 1;
    }

    // Y축에 대한 속도를 그래프로 출력.
    if (C5Min_motion(module_axis+1))
    {
        Series2->AddXY(count2, intcnt2, "", (TColor)clTeeColor);
        Chart2->BottomAxis->Automatic = False;
        Chart2->BottomAxis->Maximum = Series2->XValues->Last();
        Chart2->BottomAxis->Minimum = Chart2->BottomAxis->Maximum - 200;
        count2 = count2 + 1;
    }

    // X , Y  좌표축의 위치를 그래프로 출력.
    if ((C5Min_motion(module_axis)) || (C5Min_motion(module_axis+1) == 1))
    {
        Series3->AddXY(compos0, compos1, "", (TColor)clTeeColor);
    }
}

//---------------------------------------------------------------------------
// 입출력에 대한 부분을 화면에 나타내기 위한 부분.
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
    BYTE    uoutput, uinput, mech, drivemode2, inposact, alarmact;
    double  command_pos0, command_pos1, actual_pos0, actual_pos1;

    // 범용입출력과 Mechanical 신호
    // 그리고 구동 모드의 설정값을 읽어와 화면에 출력.
    uoutput = C5Mget_output(axis);
    uinput = C5Mget_input(axis);
    mech = C5Mget_mechanical_signal(axis);
    drivemode2 = C5Mget_drive_mode2(axis);

    // 명령위치와 실제 위치를 읽어와 화면에 출력.
    command_pos0 = C5Mget_command_position(module_axis);
	command_pos1 = C5Mget_command_position(module_axis+1);

    actual_pos0 = C5Mget_actual_position(module_axis);
    actual_pos1 = C5Mget_actual_position(module_axis+1);

    m_cmdpulse0->Text = FloatToStr(command_pos0);
    m_cmdpulse1->Text = FloatToStr(command_pos1);

    m_actpulse0->Text = FloatToStr(actual_pos0);
    m_actpulse1->Text = FloatToStr(actual_pos1);

    // 범용입력에 대한 값을 읽어와 픽쳐 박스에서 컬러로 표시
    // 범용 입력0(Home)의 값을 읽음.
    if(((uinput >> 0) & 0x01) == 0x01)  m_in0->Color = clRed;
    else                                m_in0->Color = clMaroon;

    // 범용 입력1(Z Phase)의 값을 읽음.
    if(((uinput >> 1) & 0x01) == 0x01)  m_in1->Color = clRed;
    else                                m_in1->Color = clMaroon;

    // 범용 입력2의 값을 읽음.
    if(((uinput >> 2) & 0x01) == 0x01)  m_in2->Color = clRed;
    else                                m_in2->Color = clMaroon;

    // 범용 입력3의 값을 읽음.
    if(((uinput >> 3) & 0x01) == 0x01)  m_in3->Color = clRed;
    else                                m_in3->Color = clMaroon;

    // 범용출력에 대한 출력값을 읽어와 픽쳐 박스에서 컬러로 표시
    // 범용 출력0(Servo On)을 읽음.
    if(((uoutput >> 0) & 0x01) == 0x01) m_out0->Color = clRed;
    else                                m_out0->Color = clMaroon;

    // 범용 출력1(Alarm Clear)을 읽음.
    if(((uoutput >> 1) & 0x01) == 0x01) m_out1->Color = clRed;
    else                                m_out1->Color = clMaroon;

    // 범용 출력2을 읽음.
    if(((uoutput >> 2) & 0x01) == 0x01) m_out2->Color = clRed;
    else                                m_out2->Color = clMaroon;

    // 범용 출력3을 읽음.
    if(((uoutput >> 3) & 0x01) == 0x01) m_out3->Color = clRed;
    else                                m_out3->Color = clMaroon;

    // Mechanical Signal을 읽어 화면에 표시.
    // 인포지션 신호가 액티브 되었는 지를 읽어와 화면에 출력.
    if (((mech >> 5) & 0x01) == 0x01)   m_inpossignal->Color = clRed;
    else                                m_inpossignal->Color = clMaroon;

    // 알람 신호가 액티브 되었는 지를 읽어와 화면에 출력.
    if (((mech >> 4) & 0x01) == 0x01)   m_alarmsignal->Color = clRed;
    else                                m_alarmsignal->Color = clMaroon;

    // (-) 슬로우 리미트가 액티브 되었는 지를 읽어와 화면에 출력.
    if (((mech >> 3) & 0x01) == 0x01)   m_nslowsignal->Color = clRed;
    else                                m_nslowsignal->Color = clMaroon;

    // (+) 슬로우 리미트가 액티브 되었는 지를 읽어와 화면에 출력.
    if ((( mech >> 2) & 0x01) == 0x01)  m_pslowsignal->Color = clRed;
    else                                m_pslowsignal->Color = clMaroon;

    // (-) 리미트가 액티브 되었는 지를 읽어와 화면에 출력.
    if (((mech >> 1) & 0x01) == 0x01)   m_nendsignal->Color = clRed;
    else                                m_nendsignal->Color = clMaroon;

    // (+) 리미트가 액티브 되었는 지를 읽어와 화면에 출력.
    if (((mech >> 0) & 0x01) == 0x01)   m_pendsignal->Color = clRed;
    else                                m_pendsignal->Color = clMaroon;

    // Level Setting 값을 읽어 화면에 표시.
    // 인포지션 신호의 액티브 레벨을 읽어와 화면에 출력.
    if (((drivemode2 >> 5) & 0x01) == 0x01) m_inposlevel->Checked = true;
    else                                    m_inposlevel->Checked = false;

    // 알람 신호의 액티브 레벨을 읽어와 화면에 출력.
    if (((drivemode2 >> 4) & 0x01) == 0x01) m_alarmlevel->Checked = true;
    else                                    m_alarmlevel->Checked = false;

    // (-) 슬로우 리미트의 액티브 레벨을 읽어와 화면에 출력.
    if (((drivemode2 >> 3) & 0x01) == 0x01) m_nslowlevel->Checked = true;
    else                                    m_nslowlevel->Checked = false;

    // (+) 슬로우 리미트의 액티브 레벨을 읽어와 화면에 출력.
    if (((drivemode2 >> 2) & 0x01) == 0x01) m_pslowlevel->Checked = true;
    else                                    m_pslowlevel->Checked = false;

    // (-) 리미트의 액티브 레벨을 읽어와 화면에 출력.
    if (((drivemode2 >> 1) & 0x01) == 0x01) m_nendlevel->Checked = true;
    else                                    m_nendlevel->Checked = false;

    // (+) 리미트의 액티브 레벨을 읽어와 화면에 출력.
    if (((drivemode2 >> 0) & 0x01) == 0x01) m_pendlevel->Checked = true;
    else                                    m_pendlevel->Checked = false;
    
    // Usagge Setting 신호를 읽어 화면에 표시.
    // 인포지션 신호와 알람 신호의 사용 유무의 설정값을 읽어와 화면에 출력.
    inposact = C5Mget_inposition_enable(axis);
    alarmact = C5Mget_alarm_enable(axis);

    if ((inposact & 0x01) == 0x01)          m_inposaction->Checked = true;
    else                                    m_inposaction->Checked = false;

    if ((alarmact & 0x01) == 0x01)          m_alarmaction->Checked = true;
    else                                    m_alarmaction->Checked = false;

}

//---------------------------------------------------------------------------
// Level Setting을 설정.
// (+) 리미트의 액티브 레벨을 설정.
void __fastcall TForm1::m_pendlevelClick(TObject *Sender)
{
    if (m_pendlevel->Checked == TRUE)   C5Mset_pend_limit_level(axis, 1);
    else                                C5Mset_pend_limit_level(axis, 0);
}

// (-) 리미트의 액티브 레벨을 설정.
void __fastcall TForm1::m_nendlevelClick(TObject *Sender)
{
    if (m_nendlevel->Checked == TRUE)   C5Mset_nend_limit_level(axis, 1);
    else                                C5Mset_nend_limit_level(axis, 0);
}

// + 슬로우 리미트의 액티브 레벨을 설정.
void __fastcall TForm1::m_pslowlevelClick(TObject *Sender)
{
    if (m_pslowlevel->Checked == TRUE)  C5Mset_pslow_limit_level(axis, 1);
    else                                C5Mset_pslow_limit_level(axis, 0);
}

// (-) 슬로우 리미트의 액티브 레벨을 설정.
void __fastcall TForm1::m_nslowlevelClick(TObject *Sender)
{
    if (m_nslowlevel->Checked == TRUE)  C5Mset_nslow_limit_level(axis, 1);
    else                                C5Mset_nslow_limit_level(axis, 0);
}

// 알람신호의 액티브 레벨을 설정.
void __fastcall TForm1::m_alarmlevelClick(TObject *Sender)
{
    if (m_alarmlevel->Checked == TRUE)  C5Mset_alarm_level(axis, 1);
    else                                C5Mset_alarm_level(axis, 0);
}

// 인포지션 신호의 액티브 레벨을 설정.
void __fastcall TForm1::m_inposlevelClick(TObject *Sender)
{
    if (m_inposlevel->Checked == TRUE)  C5Mset_inposition_level(axis, 1);
    else                                C5Mset_inposition_level(axis, 0);
}

//---------------------------------------------------------------------------
// Usage Setting을 설정.
// 인포지션 신호의 사용유무를 설정.
void __fastcall TForm1::m_inposactionClick(TObject *Sender)
{
    if (m_inposaction->Checked == TRUE) C5Mset_inposition_enable(axis, 1);
    else                                C5Mset_inposition_enable(axis, 0);
}

// 알람신호의 사용유무를 설정.
void __fastcall TForm1::m_alarmactionClick(TObject *Sender)
{
    if (m_alarmaction->Checked == TRUE) C5Mset_alarm_enable(axis, 1);
    else                                C5Mset_alarm_enable(axis, 0);
}

//---------------------------------------------------------------------------
// 범용 출력 0번(Servo-On)을 설정.
void __fastcall TForm1::m_out0Click(TObject *Sender)
{
    if(m_out0->Color == clMaroon)   C5Mset_output_bit(axis, 0);
    else                            C5Mreset_output_bit(axis, 0);
}

// 범용 출력 1번(Alarm-Clear)을 설정.
void __fastcall TForm1::m_out1Click(TObject *Sender)
{
    if(m_out1->Color == clMaroon)   C5Mset_output_bit(axis, 1);
    else                            C5Mreset_output_bit(axis, 1);
}

// 범용 출력 2번을 설정.
void __fastcall TForm1::m_out2Click(TObject *Sender)
{
    if(m_out2->Color == clMaroon)   C5Mset_output_bit(axis, 2);
    else                            C5Mreset_output_bit(axis, 2);
}

// 범용 출력 3번을 설정.
void __fastcall TForm1::m_out3Click(TObject *Sender)
{
    if(m_out3->Color == clMaroon)   C5Mset_output_bit(axis, 3);
    else                            C5Mreset_output_bit(axis, 3);
}

//---------------------------------------------------------------------------
// 축을 설정.
void __fastcall TForm1::m_axissetChange(TObject *Sender)
{
    axis = m_axisset->ItemIndex;
    module_axis = axis - ( axis % 2);

    // 초기 파라메터중 펄스 출력방식, 엔코더 입력 방식, 초기속도,
    // 펄스당 거리비를 읽어와서 화면에 출력.
    m_pulseout->ItemIndex = C5Mget_pulse_out_method(axis);
    m_encinput->ItemIndex = C5Mget_enc_input_method(axis);

    m_startspeed->Text = FloatToStr(C5Mget_startstop_speed(axis));
    m_moveunit->Text =  FloatToStr(C5Mget_moveunit_perpulse(axis));
}

//---------------------------------------------------------------------------
// 펄스 출력 방식을 설정.
void __fastcall TForm1::m_pulseoutChange(TObject *Sender)
{
    C5Mset_pulse_out_method(axis, m_pulseout->ItemIndex);
}

//---------------------------------------------------------------------------
// 엔코더 입력 방식을 설정.
void __fastcall TForm1::m_encinputChange(TObject *Sender)
{
    C5Mset_enc_input_method(axis, m_encinput->ItemIndex);
}

//---------------------------------------------------------------------------
// 초기 파라메터중 펄스당 거리비와 초기속도를 설정.
// 펄스당 거리비를 설정하면 최대 속도를 그에 맞게 바꿔줍니다.
void __fastcall TForm1::m_setClick(TObject *Sender)
{
    double moveunit, startstop;

	moveunit = StrToFloat(m_moveunit->Text);
	startstop = StrToFloat(m_startspeed->Text);

	C5Mset_moveunit_perpulse(axis, moveunit);
	C5Mset_startstop_speed(axis, startstop);

    // 500KPps에 해당하는 속도를 최고속도로 설정.
    // 사용자가 원하시는 값으로 바꾸시면 됩니다.
	C5Mset_max_speed(axis, 500000 * C5Mget_moveunit_perpulse(axis));
}

//---------------------------------------------------------------------------
// 명령위치와 실제 위치를 0으로 설정.
void __fastcall TForm1::m_countclearClick(TObject *Sender)
{
    C5Mset_command_position(module_axis, 0.0);
    C5Mset_actual_position(module_axis, 0.0);
    C5Mset_command_position(module_axis+1, 0.0);
    C5Mset_actual_position(module_axis+1, 0.0);
    m_searchlist->Clear();
}

//---------------------------------------------------------------------------
// 트리거가 발생할 수 있도록 인터럽트를  Enable 시키고
// 트리거를 Enable 시킨 후 발생할 위치를 설정.
void __fastcall TForm1::m_triggerdnableClick(TObject *Sender)
{
    INT16 nBoardNo, nModulePos, nAxisPos;
    UINT8 bModuleID;
    double trig_pos;

    // 해당 보드에 대해서 인터럽트를 사용하도록 설정합니다.
    // 여기서 인자는 보드의 ID를 말합니다. 보드가 1장 꽂힐 때에는 0번입니다.
    C5Mget_axis_info(axis, &nBoardNo, &nModulePos, &bModuleID, &nAxisPos);
    AxtEnableInterrupt(nBoardNo);

	AxtWriteInterruptMaskModule(nBoardNo, 0x80 |(0x1 << nModulePos));
    // 지정축에 대한 Trigger 출력을 Enable 한다 .
	C5Mset_trigger_enable(axis, 1);
    // Trigger 출력 Active 시간을 설정합니다. Trigger Pulse는 Active 시간이
    // 경과한 후에는 자동으로 Negate됩니다. 값은 0x00 ~ 0xFF까지 설정하며,
    // 단위 출력 시간은 500 micro sec 입니다.
	C5Mset_trigger_time(axis, 0xFF);
    // Trigger 출력 펄스의 Active Level을 설정합니다.
	C5Mset_trigger_level(axis, 1);
    // 내부 지령치(1) 또는 외부 엔코더(0)에 대한 Trigger Pulse출력을 선택한다.
	C5Mset_trigger_sel(axis, 1);
    trig_pos = StrToFloat(m_position->Text);
    // 해당 축에 트리거 위치 값을 설정.
	C5Mset_internal_comparator_position(axis, trig_pos);    // 내부지령치로 설정
// 	C5Mset_external_comparator_position(axis, trig_pos);    // 외부지령치로 설정

    // 해당축에 대한 인터럽트 사용을 설정합니다.
    // 0 : Disable, 1 : Enable
	if ( C5Mset_trigger_interrupt_enable(axis, 1) == TRUE )
		m_searchlist->Items->Add("Trigger Interrupt 사용을 설정하였습니다.");
	else
		m_searchlist->Items->Add("Trigger Interrupt 사용을 실패하였습니다.");

    m_searchlist->TopIndex = m_searchlist->Count - 1;
}

//---------------------------------------------------------------------------
// 트리거 발생을 하지 못하도록 Disable 시킨다.
void __fastcall TForm1::m_triggerdisableClick(TObject *Sender)
{
    C5Mset_trigger_enable(axis, 0);
    C5Mset_trigger_interrupt_enable(axis, 0);
}

//---------------------------------------------------------------------------
// 에러 카운터 클리어가 발생하도록 설정한다.
void __fastcall TForm1::m_crcenableClick(TObject *Sender)
{
    UINT8 byPLevel, byNLevel;
	// 각 리미트 센서의 레벨과 동일하게 설정
	byPLevel = C5Mget_pend_limit_level(axis);
	byNLevel = C5Mget_nend_limit_level(axis);
	C5Mset_crc_nelm_level(axis, byPLevel);
	C5Mset_crc_pelm_level(axis, byNLevel);
	// (+)리미트 또는 (-)리미트에 감지 되었을때 카운터 클리어 출력
	C5Mset_crc_nelm_mask(axis, ENABLE);
	C5Mset_crc_pelm_mask(axis, ENABLE);
	// 주의 : 서보 드라이버의 카운터 클리어 설정이 Level로 되어 있을경우 모터가 동작하지 않을수 있음
	// 서보 드라이버의 레벨에 맞게 설정하세요
	C5Mset_crc_level(axis, LOW);
	// 카운트 클리어 사용
	C5Mset_crc_mask(axis, ENABLE);
}

//---------------------------------------------------------------------------
// 에러 카운터 클리어가 발생하지 않도록 설정.
void __fastcall TForm1::m_crcdisableClick(TObject *Sender)
{
    C5Mset_crc_nelm_mask(axis, DISABLE);
	C5Mset_crc_pelm_mask(axis, DISABLE);
	C5Mset_crc_mask(axis, DISABLE);
	C5Mset_crc_level(axis, HIGH);
}

//---------------------------------------------------------------------------
// 절대 좌표의 체크박스를 클릭함으로써 체크되어 있으면 상대 좌표로
// 체크되어 있지 않으면 상대 좌표를 체크하여 상대 좌표로 구동.
void __fastcall TForm1::m_absClick(TObject *Sender)
{
    if(m_abs->Checked == True)
        m_inc->Checked = False;
    else
        m_inc->Checked = True;
}

//---------------------------------------------------------------------------
// 상대좌표의 체크박스를 클릭함으로써 체크되어 있으면 상대 좌표로
// 체크되어 있지 않으면 절대 좌표를 체크하여 절대 좌표로 구동.
void __fastcall TForm1::m_incClick(TObject *Sender)
{
    if(m_inc->Checked == True)
        m_abs->Checked = False;
    else
        m_abs->Checked = True;
}

//---------------------------------------------------------------------------
// 에디터 박스에 있는 파라메터값을 읽어와서 지정펄스 구동.
void __fastcall TForm1::m_moveClick(TObject *Sender)
{
    double position, velocity, accel;
    position = StrToFloat(m_position->Text);
    velocity = StrToFloat(m_velocity->Text);
    accel = StrToFloat(m_accel->Text);

    // 각 축의 구동 속도를 차트에 나타내기 위해 차트 최대값 재설정
    if ( axis %2 == 0) Chart1->LeftAxis->Maximum = velocity + (velocity * 0.2);
    else Chart2->LeftAxis->Maximum = velocity + (velocity * 0.2);

    // 구동 최대 속도 재설정
    C5Mset_max_speed(axis, velocity);

    // 상대 좌표인지 절대 좌표인지 확인(r)하고 S 자형인지 아닌지 확인(s)하여 구동.
    if (m_inc->Checked == True )
    {
        if (m_scurve->Checked == True)
            C5Mstart_rqs_move(axis, position, velocity, accel);
        else
            C5Mstart_r_move(axis, position, velocity, accel);
    }
    else
    {
        if (m_scurve->Checked == True)
            C5Mstart_qs_move(axis, position, velocity, accel);
        else
            C5Mstart_move(axis, position, velocity, accel);
    }
}

//---------------------------------------------------------------------------
// 구동하고 있는 축에 대해 감속 정지.
void __fastcall TForm1::m_decelstopClick(TObject *Sender)
{
    if(RepeatFlag == True)
        RepeatFlag = False;
    else
    {
        C5Mabort_home_search(module_axis, 0);         // X축의 원점검색을 중지.
        C5Mabort_home_search(module_axis+1, 0);       // Y축의 원점검색을 중지.
        C5Mset_stop(module_axis);
        C5Mset_stop(module_axis+1);
    }
}

//---------------------------------------------------------------------------
// 구동하고 있는 축에 대해 급정지.
void __fastcall TForm1::m_stopClick(TObject *Sender)
{
    EStop = True;
    RepeatFlag = False;
    C5Mabort_home_search(module_axis, 1);         // X축의 원점검색을 중지.
    C5Mabort_home_search(module_axis+1, 1);       // Y축의 원점검색을 중지.
    C5Mset_e_stop(module_axis);
    C5Mset_e_stop(module_axis+1);
}

//---------------------------------------------------------------------------
// 에디터 박스의 파라메터 설정값을 읽어와서 반복 구동.
void __fastcall TForm1::m_repeatmoveClick(TObject *Sender)
{
    if( (axis % 2) == 0)
    {
        if ( repeatthread_x != 0 || TestActive1 == True)
        {
            m_searchlist->Items->Add("구동중 입니다.");
            m_searchlist->TopIndex = m_searchlist->Count - 1;
        }
        else
        {
            repeatthread_x = new movethread(true);
            repeatthread_x->count = axis;
            RepeatFlag = TRUE;
            EStop = False;
            TestActive1 = True;
            repeatthread_x->Resume();
        }
    }
    else
    {
        if ( repeatthread_y != 0 || TestActive2 == True)
        {
            m_searchlist->Items->Add("구동중 입니다.");
            m_searchlist->TopIndex = m_searchlist->Count - 1;

        }
        else
        {
            repeatthread_y = new movethread(true);
            repeatthread_y->count = axis;
            RepeatFlag = TRUE;
            EStop = False;
            TestActive2 = True;
            repeatthread_y->Resume();
        }
    }
}

//---------------------------------------------------------------------------
// 홈검색을 테스트 하기 위한 부분으로 검색할 신호를 설정하고 검색 방향,
// 검색후 정지 방법에 대해 읽어온후 검색을 시작.
// 검색이 끝나면 리스트 박스에 결과를 출력.
void __fastcall TForm1::m_searchClick(TObject *Sender)
{
    if ( m_detectsignal->ItemIndex < 3) detectsignal = m_detectsignal->ItemIndex + 4;
    else detectsignal = m_detectsignal->ItemIndex + 8;

    if( (axis % 2) == 0)
    {
        if ( searchthread_x != 0 || TestActive1 == True)
        {
            m_searchlist->Items->Add("구동중 입니다.");
            m_searchlist->TopIndex = m_searchlist->Count - 1;
        }
        else
        {
            searchthread_x = new movethread(true);
            searchthread_x->count = 3;
            TestActive1 = True;
            searchthread_x->Resume();
        }
    }
    else
    {
        if ( searchthread_y != 0 || TestActive2 == True)
        {
            m_searchlist->Items->Add("구동중 입니다.");
            m_searchlist->TopIndex = m_searchlist->Count - 1;
        }
        else
        {
            searchthread_y = new movethread(true);
            searchthread_y->count = 3;
            TestActive2 = True;
            searchthread_y->Resume();
        }
    }
}

//---------------------------------------------------------------------------
// 윈도우가 종료될 때 초기 설정 파라메터에 대해 화일로 저장.
// 나중에 이 화일을 읽어와 초기 설정 파라메터를 설정할 수 있습니다.
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    char *nfilename= "Camc5M.Mot";
    C5Msave_parameter_all(nfilename);
    // 서보 OFF
    C5Mreset_output_bit(module_axis, 0);
    C5Mreset_output_bit(module_axis+1, 0);
    // 통합 라이브러리의 사용을 종료한다.
    AxtClose();
}

//---------------------------------------------------------------------------
// 업 조그 버튼을 눌렀을 때 (+)방향으로 연속 구동한다.(Y축 조그 운전)
void __fastcall TForm1::jog1upMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    double velocity, accel;

    velocity = fabs(StrToFloat( m_velocity->Text));
    accel    = fabs(StrToFloat( m_accel->Text));
    C5Mset_max_speed(module_axis+1, velocity);
    Chart2->LeftAxis->Maximum = velocity + (velocity * 0.2);
    if ( m_scurve->Checked == TRUE)
        C5Mv_qs_move(module_axis+1, velocity, accel);
    else
        C5Mv_move(module_axis+1, velocity, accel);
}

//---------------------------------------------------------------------------
// 업 조그 버튼을 떼었을 때 감속 정지 한다.(Y축 조그 운전)
void __fastcall TForm1::jog1upMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis+1);
}

//---------------------------------------------------------------------------
// 다운 조그 버튼을 눌렀을 때 (-)방향으로 연속 구동한다.(Y축 조그 운전)
void __fastcall TForm1::jog1downMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    double velocity, accel;
    velocity = fabs(StrToFloat( m_velocity->Text));
    accel    = fabs(StrToFloat( m_accel->Text));
    C5Mset_max_speed(module_axis+1, velocity);
    Chart2->LeftAxis->Maximum = velocity + (velocity * 0.2);
    if ( m_scurve->Checked == TRUE)
        C5Mv_qs_move(module_axis+1, -velocity, accel);
    else
        C5Mv_move(module_axis+1, -velocity, accel);
}

//---------------------------------------------------------------------------
// 다운 조그 버튼을 떼었을 때 감속 정지한다.(Y축 조그 운전)
void __fastcall TForm1::jog1downMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis+1);
}

//---------------------------------------------------------------------------
// 라이트 조그버튼으로 버튼을 눌렀을 때 (+)방향으로 연속 구동한다.(X축 조그 운전)
void __fastcall TForm1::jog0downMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{ 
    double velocity, accel;
    velocity = fabs(StrToFloat( m_velocity->Text));
    accel    = fabs(StrToFloat( m_accel->Text));
    C5Mset_max_speed(module_axis, velocity);
    Chart1->LeftAxis->Maximum = velocity + (velocity * 0.2);
    if ( m_scurve->Checked == TRUE)
        C5Mv_qs_move(module_axis, -velocity, accel);
    else
        C5Mv_move(module_axis, -velocity, accel);
}

//---------------------------------------------------------------------------
// 라이트 조그 버튼을 떼었을 때 감속 정지한다.(X축 조그 운전)
void __fastcall TForm1::jog0downMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis);
}

//---------------------------------------------------------------------------
// 레프트 조그 버튼을 눌렀을 때 (-)방향으로연속 구동 한다.(X축 조그 운전)
void __fastcall TForm1::jog0upMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    double velocity, accel;
    velocity = fabs(StrToFloat( m_velocity->Text));
    accel    = fabs(StrToFloat( m_accel->Text));
    C5Mset_max_speed(module_axis, velocity);
    Chart1->LeftAxis->Maximum = velocity + (velocity * 0.2);
    if ( m_scurve->Checked == TRUE)
        C5Mv_qs_move(0, velocity, accel);
    else
        C5Mv_move(module_axis, velocity, accel);
}

//---------------------------------------------------------------------------
// 레프트 조그 버튼을 떼었을 때 감속 정지한다.(X축 조그 운전)
void __fastcall TForm1::jog0upMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis);
}

//---------------------------------------------------------------------------
// CW 방향 홈검색 구동
void __fastcall TForm1::m_cwClick(TObject *Sender)
{
    double dHomeVel1, dHomeVel2, dHomeVel3;
    double velocities[4], accelerations[4];
    INT16 axes[2];
    INT8  methods[4];

    axes[0] = module_axis;
    axes[1] = module_axis + 1;

 	if ( !C5Mget_home_done_all(2, axes))
    {
        Form1->m_searchlist->Items->Add( "홈검색 중입니다.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }

    if ( TestActive1 || TestActive2)
    {
        Form1->m_searchlist->Items->Add( "구동 중입니다.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }
	/* Detect Signal---------------------------------------------------------
	PElmNegativeEdge    = 0x0,			// +Elm(End limit) 하강 edge
	NElmNegativeEdge    = 0x1,			// -Elm(End limit) 하강 edge
	PSlmNegativeEdge    = 0x2,			// +Slm(Slowdown limit) 하강 edge
	NSlmNegativeEdge    = 0x3,			// -Slm(Slowdown limit) 하강 edge
	In0DownEdge         = 0x4,			// IN0(ORG) 하강 edge
	In1DownEdge         = 0x5,			// IN1(Z상) 하강 edge
	In2DownEdge         = 0x6,			// IN2(범용) 하강 edge
	In3DownEdge         = 0x7,			// IN3(범용) 하강 edge
	PElmPositiveEdge    = 0x8,			// +Elm(End limit) 상승 edge
	NElmPositiveEdge    = 0x9,			// -Elm(End limit) 상승 edge
	PSlmPositiveEdge    = 0xa,			// +Slm(Slowdown limit) 상승 edge
	NSlmPositiveEdge    = 0xb,			// -Slm(Slowdown limit) 상승 edge
	In0UpEdge           = 0xc,			// IN0(ORG) 상승 edge
	In1UpEdge           = 0xd,			// IN1(Z상) 상승 edge
	In2UpEdge           = 0xe,			// IN2(범용) 상승 edge
	In3UpEdge           = 0xf			// IN3(범용) 상승 edge
	------------------------------------------------------------------------
	------------------------------------------------------------------------
	7-4Bit	detect signal 설정
	3Bit	검색방향 설정 (0 : cww(-), 1 : cw(+))
	2Bit	정지방법 설정 (0 : 감속 정지, 1 : 급 정지)
	1Bit	가감속 방법 설정 (0 : 가속율, 1 : 가속 시간)
	0Bit	스텝 사용여부 설정 (0 : 사용하지 않음, 1: 사용함
	------------------------------------------------------------------------*/
    methods[1] = IN0_DNEDGE | STOP_EMG | USE_STEP | DIR_CW;			        // (-)방향으로 홈 센서의 하강에지 신호를 검색함 정지시 급정지...
	methods[2] = IN0_UPEDGE | STOP_EMG | USE_STEP;					        // (+)방향으로 홈 센서의 상승에지 신호를 검색함 정지시 급정지..
	methods[3] = IN1_DNEDGE | STOP_EMG | USE_STEP | DIR_CW;                 // (-)방향으로 Z상 센서의 하강에지 신호를 검색함 정지시 급정지..

	if ( C5Minput_bit_on(module_axis, HOME_BIT))    methods[0] = 0x0;  		// 원점센서가 감지되어 있을 때 Step0를 사용하지 않음....
	else    methods[0] = IN0_UPEDGE | USE_STEP;                             // 원점센서가 감지되어 있지않을 때....
    C5Mset_home_method(module_axis, HOME_STEP, methods);		            // 축별로 홈검색 방법을 설정한다..

    if ( C5Minput_bit_on(module_axis+1, HOME_BIT))  methods[0] = 0x0; 		// 원점센서가 감지되어 있을 때 Step0를 사용하지 않음....
	else    methods[0] = IN0_UPEDGE | USE_STEP;	                            // 원점센서가 감지되어 있지않을 때....
	C5Mset_home_method(module_axis+1, HOME_STEP, methods);		      	    // 축별로 홈검색 방법을 설정한다..

	// 축에 원점 검색 시 각 스텝별 속도를 설정
	dHomeVel1	= 50000 * C5Mget_moveunit_perpulse(module_axis);            // 기구에 맞는 속도로 변경하여 사용하십시요.
	dHomeVel2	= 10000 * C5Mget_moveunit_perpulse(module_axis);
	dHomeVel3	= 3000  * C5Mget_moveunit_perpulse(module_axis);

	velocities[0] = dHomeVel1;         accelerations[0]  = dHomeVel1 * 4;
    velocities[1] = dHomeVel2;         accelerations[1]  = dHomeVel2 * 4;
    velocities[2] = dHomeVel3;         accelerations[2]  = dHomeVel3 * 4;
    velocities[3] = dHomeVel3 / 2;	   accelerations[3] = dHomeVel3 * 2; 	// 각 스텝의 속도를 설정한다.

    // 축의 원점 검색시 최고속도 설정
  	C5Mset_max_speed(module_axis, dHomeVel1);
	C5Mset_max_speed(module_axis+1, dHomeVel1);

    // 축의 원점 검색 시 각 스텝별 속도 설정
	C5Mset_home_velocity(module_axis, HOME_STEP, velocities);		        // 각 Setp별 X축 홈 검색 속도 설정
	C5Mset_home_velocity(module_axis+1, HOME_STEP, velocities);		        // 각 Setp별 Y축 홈 검색 속도 설정

	// 축의 원점 검색 시 각 스텝별 가속율을 설정
	C5Mset_home_acceleration(module_axis, HOME_STEP, accelerations);        // 각 Setp별 X축 홈 검색 가속도 설정
	C5Mset_home_acceleration(module_axis+1, HOME_STEP, accelerations);      // 각 Setp별 Y축 홈 검색 가속도 설정

    Chart1->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);
    Chart2->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);

    TestActive1 = True;
    TestActive2 = True;
    Timer3->Enabled = True;

    // 1축 이상일 경우 2축 동시 홈 검색
    if (C5Mget_total_numof_axis() > 0 == True) C5Mhome_search_all(2, axes);
    else C5Mhome_search(axis);
}

//---------------------------------------------------------------------------
// CW 방향 홈검색 구동
void __fastcall TForm1::m_ccwClick(TObject *Sender)
{
    double dHomeVel1, dHomeVel2, dHomeVel3;
    double velocities[4], accelerations[4];
    INT16 axes[2];
    INT8  methods[4];

    axes[0] = module_axis;
    axes[1] = module_axis + 1;

 	if ( !C5Mget_home_done_all(2, axes))
    {
        Form1->m_searchlist->Items->Add( "홈검색 중입니다.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }

    if ( TestActive1 || TestActive2)
    {
        Form1->m_searchlist->Items->Add( "구동 중입니다.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }
    /*Detect Signal---------------------------------------------------------
	PElmNegativeEdge    = 0x0,			// +Elm(End limit) 하강 edge
	NElmNegativeEdge    = 0x1,			// -Elm(End limit) 하강 edge
	PSlmNegativeEdge    = 0x2,			// +Slm(Slowdown limit) 하강 edge
	NSlmNegativeEdge    = 0x3,			// -Slm(Slowdown limit) 하강 edge
	In0DownEdge         = 0x4,			// IN0(ORG) 하강 edge
	In1DownEdge         = 0x5,			// IN1(Z상) 하강 edge
	In2DownEdge         = 0x6,			// IN2(범용) 하강 edge
	In3DownEdge         = 0x7,			// IN3(범용) 하강 edge
	PElmPositiveEdge    = 0x8,			// +Elm(End limit) 상승 edge
	NElmPositiveEdge    = 0x9,			// -Elm(End limit) 상승 edge
	PSlmPositiveEdge    = 0xa,			// +Slm(Slowdown limit) 상승 edge
	NSlmPositiveEdge    = 0xb,			// -Slm(Slowdown limit) 상승 edge
	In0UpEdge           = 0xc,			// IN0(ORG) 상승 edge
	In1UpEdge           = 0xd,			// IN1(Z상) 상승 edge
	In2UpEdge           = 0xe,			// IN2(범용) 상승 edge
	In3UpEdge           = 0xf			  // IN3(범용) 상승 edge
	-------------------------------------------------------------------------
	-------------------------------------------------------------------------
	7-4Bit	detect signal 설정
	3Bit	검색방향 설정 (0 : ccw(-), 1 : cw(+))
	2Bit	정지방법 설정 (0 : 감속 정지, 1 : 급 정지)
	1Bit	가감속 방법 설정 (0 : 가속율, 1 : 가속 시간)
	0Bit	스텝 사용여부 설정 (0 : 사용하지 않음, 1: 사용함
	------------------------------------------------------------------------*/
    methods[1] = IN0_DNEDGE | STOP_EMG | USE_STEP;                          // (+)방향으로 홈 센서의 하강에지 신호를 검색함 정지시 급정지...
	methods[2] = IN0_UPEDGE | STOP_EMG | USE_STEP | DIR_CW;                 // (-)방향으로 홈 센서의 상승에지 신호를 검색함 정지시 급정지..
	methods[3] = IN1_DNEDGE | STOP_EMG | USE_STEP;			                // (+)방향으로 Z상 센서의 하강에지 신호를 검색함 정지시 급정지..

	if(C5Minput_bit_on(module_axis, HOME_BIT)) 	methods[0] = 0x0;	        // 원점센서가 감지되어 있을 때 Step0를 사용하지 않음....
	else    methods[0] = IN0_UPEDGE | USE_STEP | DIR_CW;                    // 원점센서가 감지되어 있지않을 때....
	C5Mset_home_method(module_axis, HOME_STEP, methods);				    // 축별로 홈검색 방법을 설정한다..

	if(C5Minput_bit_on(module_axis+1, HOME_BIT)) methods[0] = 0x0;          // 원점센서가 감지되어 있을 때 Step0를 사용하지 않음....
	else    methods[0] = IN0_UPEDGE | USE_STEP | DIR_CW;	                // 원점센서가 감지되어 있지않을 때....
	C5Mset_home_method(module_axis+1, HOME_STEP, methods);			        // 축별로 홈검색 방법을 설정한다..

	// 축에 원점 검색 시 각 스텝별 속도를 설정
	dHomeVel1	= 50000 * C5Mget_moveunit_perpulse(module_axis);            // 기구에 맞는 속도로 변경하여 사용하십시요.
	dHomeVel2	= 10000 * C5Mget_moveunit_perpulse(module_axis);
	dHomeVel3	= 3000  * C5Mget_moveunit_perpulse(module_axis);

	velocities[0] = dHomeVel1;         accelerations[0]  = dHomeVel1 * 4;
    velocities[1] = dHomeVel2;         accelerations[1]  = dHomeVel2 * 4;
    velocities[2] = dHomeVel3;         accelerations[2]  = dHomeVel3 * 4;
    velocities[3] = dHomeVel3 / 2;	    accelerations[3] = dHomeVel3 * 2;  	// 각 스텝의 속도를 설정한다.

    // 축의 원점 검색시 최고속도 설정
  	C5Mset_max_speed(module_axis, dHomeVel1);
	C5Mset_max_speed(module_axis+1, dHomeVel1);

    // 축의 원점 검색 시 각 스텝별 속도 설정
	C5Mset_home_velocity(module_axis, HOME_STEP, velocities);		        // 각 Setp별 X축 홈 검색 속도 설정
	C5Mset_home_velocity(module_axis+1, HOME_STEP, velocities);		        // 각 Setp별 Y축 홈 검색 속도 설정

	// 축의 원점 검색 시 각 스텝별 가속율을 설정
	C5Mset_home_acceleration(module_axis, HOME_STEP, accelerations);        // 각 Setp별 X축 홈 검색 가속도 설정
	C5Mset_home_acceleration(module_axis+1, HOME_STEP, accelerations);      // 각 Setp별 Y축 홈 검색 가속도 설정

    // 각 축의 구동 속도를 차트에 나타내기 위해 차트 최대값 재설정 
    Chart1->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);
    Chart2->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);

    TestActive1 = True;
    TestActive2 = True;
    Timer3->Enabled = TRUE;

	// 1축 이상일 경우 2축 동시 홈 검색
    if (C5Mget_total_numof_axis() > 0 == True) C5Mhome_search_all(2, axes);
    else C5Mhome_search(axis);
}

//---------------------------------------------------------------------------
// 홈 검색 완료 상태 검사
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
    INT16 home_axes[2];
    BOOL home_end, home_end1;

    home_axes[0] = module_axis;
    home_axes[1] = module_axis + 1;
    if ( C5Mget_home_done_all(2, home_axes))
    {
        Timer3->Enabled = False;
        home_end  = C5Mget_home_end_status(module_axis);
        home_end1 = C5Mget_home_end_status(module_axis+1);
        if ( home_end & home_end1)
             m_searchlist->Items->Add("홈검색을 완료 하였습니다.");
        else
            m_searchlist->Items->Add("홈검색을 실패 하였습니다.");

        TestActive1 = False;
        TestActive2 = False;
        m_searchlist->TopIndex = m_searchlist->Count - 1;
    }
}

//---------------------------------------------------------------------------
// 쓰레드 종료
void __fastcall TForm1::MoveThreadDone()
{
   if (repeatthread_x != NULL)
    {
        TestActive1 = False;
        repeatthread_x = NULL;
    }

    if (repeatthread_y != NULL)
    {
        TestActive2 = False;
        repeatthread_y = NULL;
    }

    if (searchthread_x != NULL)
    {
        TestActive1 = False;
        searchthread_x = NULL;
    }

    if (searchthread_y != NULL)
    {
        TestActive2 = False;
        searchthread_y = NULL;
    }
}

//---------------------------------------------------------------------------
// 트리거 인터럽트 서비스 루틴
void TForm1::TriggerInterrupt(TMessage Msg)
{
    m_searchlist->Items->Add(IntToStr(axis) + "축에 인터럽트가 발생하였습니다.");
    m_searchlist->TopIndex = m_searchlist->Count - 1;
}
