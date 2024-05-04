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
    // ## ���� ���̺귯�� �� ��� �ʱ�ȭ �κ� ##
    if( !AxtIsInitialized())            // ���� ���̺귯���� ��� �������� (�ʱ�ȭ�� �Ǿ�����) Ȯ��.
    {                   
        if(!AxtInitialize(Form1->Handle, 0) == true)            // ���� ���̺귯�� �ʱ�ȭ.
        {
            MessageBoxA(NULL, "Can not Library Initialize!!", "Ajinextek", MB_OK);
        }
    }
    if(AxtIsInitializedBus(BUSTYPE_PCI) == 0)           // ������ ����(PCI)�� �ʱ�ȭ �Ǿ����� Ȯ��.
    {                                                   // ������ ISA �ϰ�� BUSTYPE_PCI -> BUSTYPE_ISA ����.
     	if(AxtOpenDeviceAuto(BUSTYPE_PCI) == 0)         // ���ο� ���̽����带 �ڵ����� ���ն��̺귯���� �߰�.
        {
          	MessageBoxA(NULL, "Can not Baseboard Initialize!!", "Ajinextek", MB_OK);
        }
    }
    if(!C5MIsInitialized())         // CAMC-5M����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ����� Ȯ��.
    {
        if(!InitializeCAMC5M(true))
           	MessageBoxA(NULL, "Can not CAMC-5M Module Initilaize!!", "Ajinextek", MB_OK);
    }
    //-------------------------------------------------------------//
    // ������ ���Ͽ��� �ʱ� ���� �Ķ������ �������� �о�� ����.
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
        m_axisset->Items->Add( IntToStr(i) + "��");

    m_axisset->ItemIndex = 0;
    axis = m_axisset->ItemIndex;
    module_axis = axis - ( axis % 2);
    m_detectsignal->ItemIndex = 4;
    m_drivedirect->ItemIndex = 1;
    m_stopmethod->ItemIndex = 1;

    // �ʱ� �Ķ������ �޽� ��¹��, ���ڴ� �Է� ���, �ʱ�ӵ�, �޽��� �Ÿ��� �о�ͼ� ȭ�鿡 ���.
    m_pulseout->ItemIndex = C5Mget_pulse_out_method(axis);
    m_encinput->ItemIndex = C5Mget_enc_input_method(axis);

    m_startspeed->Text = FloatToStr(C5Mget_startstop_speed(axis));
    m_moveunit->Text =  FloatToStr(C5Mget_moveunit_perpulse(axis));

    C5Mset_max_speed(module_axis, 500000 * C5Mget_moveunit_perpulse(module_axis));      	// 500KPps�� �ش��ϴ� �ӵ��� �ְ�ӵ��� ����
    C5Mset_max_speed(module_axis+1, 500000 * C5Mget_moveunit_perpulse(module_axis+1));
}

// ��ǿ� ���� �κ��� ȭ�鿡 �����ֱ� ���� �κ����� Ÿ�̸Ӵ� 50msec���� ����.
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    double compos0, compos1, intcnt1, intcnt2;

    compos0 = C5Mget_command_position(module_axis);
    compos1 = C5Mget_command_position(module_axis+1);
    intcnt1 = C5Mget_velocity(module_axis);
    intcnt2 = C5Mget_velocity(module_axis+1);

    m_cmdvel0->Text =  FloatToStr(intcnt1);
    m_cmdvel1->Text =  FloatToStr(intcnt2);

    // X�࿡ ���� �ӵ��� �׷����� ���.
    if (C5Min_motion(module_axis))
    {
        Series1->AddXY(count1, intcnt1, "", (TColor)clTeeColor);
        Chart1->BottomAxis->Automatic = False;
        Chart1->BottomAxis->Maximum = Series1->XValues->Last();
        Chart1->BottomAxis->Minimum = Chart1->BottomAxis->Maximum - 200;
        count1 = count1 + 1;
    }

    // Y�࿡ ���� �ӵ��� �׷����� ���.
    if (C5Min_motion(module_axis+1))
    {
        Series2->AddXY(count2, intcnt2, "", (TColor)clTeeColor);
        Chart2->BottomAxis->Automatic = False;
        Chart2->BottomAxis->Maximum = Series2->XValues->Last();
        Chart2->BottomAxis->Minimum = Chart2->BottomAxis->Maximum - 200;
        count2 = count2 + 1;
    }

    // X , Y  ��ǥ���� ��ġ�� �׷����� ���.
    if ((C5Min_motion(module_axis)) || (C5Min_motion(module_axis+1) == 1))
    {
        Series3->AddXY(compos0, compos1, "", (TColor)clTeeColor);
    }
}

//---------------------------------------------------------------------------
// ����¿� ���� �κ��� ȭ�鿡 ��Ÿ���� ���� �κ�.
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
    BYTE    uoutput, uinput, mech, drivemode2, inposact, alarmact;
    double  command_pos0, command_pos1, actual_pos0, actual_pos1;

    // ��������°� Mechanical ��ȣ
    // �׸��� ���� ����� �������� �о�� ȭ�鿡 ���.
    uoutput = C5Mget_output(axis);
    uinput = C5Mget_input(axis);
    mech = C5Mget_mechanical_signal(axis);
    drivemode2 = C5Mget_drive_mode2(axis);

    // �����ġ�� ���� ��ġ�� �о�� ȭ�鿡 ���.
    command_pos0 = C5Mget_command_position(module_axis);
	command_pos1 = C5Mget_command_position(module_axis+1);

    actual_pos0 = C5Mget_actual_position(module_axis);
    actual_pos1 = C5Mget_actual_position(module_axis+1);

    m_cmdpulse0->Text = FloatToStr(command_pos0);
    m_cmdpulse1->Text = FloatToStr(command_pos1);

    m_actpulse0->Text = FloatToStr(actual_pos0);
    m_actpulse1->Text = FloatToStr(actual_pos1);

    // �����Է¿� ���� ���� �о�� ���� �ڽ����� �÷��� ǥ��
    // ���� �Է�0(Home)�� ���� ����.
    if(((uinput >> 0) & 0x01) == 0x01)  m_in0->Color = clRed;
    else                                m_in0->Color = clMaroon;

    // ���� �Է�1(Z Phase)�� ���� ����.
    if(((uinput >> 1) & 0x01) == 0x01)  m_in1->Color = clRed;
    else                                m_in1->Color = clMaroon;

    // ���� �Է�2�� ���� ����.
    if(((uinput >> 2) & 0x01) == 0x01)  m_in2->Color = clRed;
    else                                m_in2->Color = clMaroon;

    // ���� �Է�3�� ���� ����.
    if(((uinput >> 3) & 0x01) == 0x01)  m_in3->Color = clRed;
    else                                m_in3->Color = clMaroon;

    // ������¿� ���� ��°��� �о�� ���� �ڽ����� �÷��� ǥ��
    // ���� ���0(Servo On)�� ����.
    if(((uoutput >> 0) & 0x01) == 0x01) m_out0->Color = clRed;
    else                                m_out0->Color = clMaroon;

    // ���� ���1(Alarm Clear)�� ����.
    if(((uoutput >> 1) & 0x01) == 0x01) m_out1->Color = clRed;
    else                                m_out1->Color = clMaroon;

    // ���� ���2�� ����.
    if(((uoutput >> 2) & 0x01) == 0x01) m_out2->Color = clRed;
    else                                m_out2->Color = clMaroon;

    // ���� ���3�� ����.
    if(((uoutput >> 3) & 0x01) == 0x01) m_out3->Color = clRed;
    else                                m_out3->Color = clMaroon;

    // Mechanical Signal�� �о� ȭ�鿡 ǥ��.
    // �������� ��ȣ�� ��Ƽ�� �Ǿ��� ���� �о�� ȭ�鿡 ���.
    if (((mech >> 5) & 0x01) == 0x01)   m_inpossignal->Color = clRed;
    else                                m_inpossignal->Color = clMaroon;

    // �˶� ��ȣ�� ��Ƽ�� �Ǿ��� ���� �о�� ȭ�鿡 ���.
    if (((mech >> 4) & 0x01) == 0x01)   m_alarmsignal->Color = clRed;
    else                                m_alarmsignal->Color = clMaroon;

    // (-) ���ο� ����Ʈ�� ��Ƽ�� �Ǿ��� ���� �о�� ȭ�鿡 ���.
    if (((mech >> 3) & 0x01) == 0x01)   m_nslowsignal->Color = clRed;
    else                                m_nslowsignal->Color = clMaroon;

    // (+) ���ο� ����Ʈ�� ��Ƽ�� �Ǿ��� ���� �о�� ȭ�鿡 ���.
    if ((( mech >> 2) & 0x01) == 0x01)  m_pslowsignal->Color = clRed;
    else                                m_pslowsignal->Color = clMaroon;

    // (-) ����Ʈ�� ��Ƽ�� �Ǿ��� ���� �о�� ȭ�鿡 ���.
    if (((mech >> 1) & 0x01) == 0x01)   m_nendsignal->Color = clRed;
    else                                m_nendsignal->Color = clMaroon;

    // (+) ����Ʈ�� ��Ƽ�� �Ǿ��� ���� �о�� ȭ�鿡 ���.
    if (((mech >> 0) & 0x01) == 0x01)   m_pendsignal->Color = clRed;
    else                                m_pendsignal->Color = clMaroon;

    // Level Setting ���� �о� ȭ�鿡 ǥ��.
    // �������� ��ȣ�� ��Ƽ�� ������ �о�� ȭ�鿡 ���.
    if (((drivemode2 >> 5) & 0x01) == 0x01) m_inposlevel->Checked = true;
    else                                    m_inposlevel->Checked = false;

    // �˶� ��ȣ�� ��Ƽ�� ������ �о�� ȭ�鿡 ���.
    if (((drivemode2 >> 4) & 0x01) == 0x01) m_alarmlevel->Checked = true;
    else                                    m_alarmlevel->Checked = false;

    // (-) ���ο� ����Ʈ�� ��Ƽ�� ������ �о�� ȭ�鿡 ���.
    if (((drivemode2 >> 3) & 0x01) == 0x01) m_nslowlevel->Checked = true;
    else                                    m_nslowlevel->Checked = false;

    // (+) ���ο� ����Ʈ�� ��Ƽ�� ������ �о�� ȭ�鿡 ���.
    if (((drivemode2 >> 2) & 0x01) == 0x01) m_pslowlevel->Checked = true;
    else                                    m_pslowlevel->Checked = false;

    // (-) ����Ʈ�� ��Ƽ�� ������ �о�� ȭ�鿡 ���.
    if (((drivemode2 >> 1) & 0x01) == 0x01) m_nendlevel->Checked = true;
    else                                    m_nendlevel->Checked = false;

    // (+) ����Ʈ�� ��Ƽ�� ������ �о�� ȭ�鿡 ���.
    if (((drivemode2 >> 0) & 0x01) == 0x01) m_pendlevel->Checked = true;
    else                                    m_pendlevel->Checked = false;
    
    // Usagge Setting ��ȣ�� �о� ȭ�鿡 ǥ��.
    // �������� ��ȣ�� �˶� ��ȣ�� ��� ������ �������� �о�� ȭ�鿡 ���.
    inposact = C5Mget_inposition_enable(axis);
    alarmact = C5Mget_alarm_enable(axis);

    if ((inposact & 0x01) == 0x01)          m_inposaction->Checked = true;
    else                                    m_inposaction->Checked = false;

    if ((alarmact & 0x01) == 0x01)          m_alarmaction->Checked = true;
    else                                    m_alarmaction->Checked = false;

}

//---------------------------------------------------------------------------
// Level Setting�� ����.
// (+) ����Ʈ�� ��Ƽ�� ������ ����.
void __fastcall TForm1::m_pendlevelClick(TObject *Sender)
{
    if (m_pendlevel->Checked == TRUE)   C5Mset_pend_limit_level(axis, 1);
    else                                C5Mset_pend_limit_level(axis, 0);
}

// (-) ����Ʈ�� ��Ƽ�� ������ ����.
void __fastcall TForm1::m_nendlevelClick(TObject *Sender)
{
    if (m_nendlevel->Checked == TRUE)   C5Mset_nend_limit_level(axis, 1);
    else                                C5Mset_nend_limit_level(axis, 0);
}

// + ���ο� ����Ʈ�� ��Ƽ�� ������ ����.
void __fastcall TForm1::m_pslowlevelClick(TObject *Sender)
{
    if (m_pslowlevel->Checked == TRUE)  C5Mset_pslow_limit_level(axis, 1);
    else                                C5Mset_pslow_limit_level(axis, 0);
}

// (-) ���ο� ����Ʈ�� ��Ƽ�� ������ ����.
void __fastcall TForm1::m_nslowlevelClick(TObject *Sender)
{
    if (m_nslowlevel->Checked == TRUE)  C5Mset_nslow_limit_level(axis, 1);
    else                                C5Mset_nslow_limit_level(axis, 0);
}

// �˶���ȣ�� ��Ƽ�� ������ ����.
void __fastcall TForm1::m_alarmlevelClick(TObject *Sender)
{
    if (m_alarmlevel->Checked == TRUE)  C5Mset_alarm_level(axis, 1);
    else                                C5Mset_alarm_level(axis, 0);
}

// �������� ��ȣ�� ��Ƽ�� ������ ����.
void __fastcall TForm1::m_inposlevelClick(TObject *Sender)
{
    if (m_inposlevel->Checked == TRUE)  C5Mset_inposition_level(axis, 1);
    else                                C5Mset_inposition_level(axis, 0);
}

//---------------------------------------------------------------------------
// Usage Setting�� ����.
// �������� ��ȣ�� ��������� ����.
void __fastcall TForm1::m_inposactionClick(TObject *Sender)
{
    if (m_inposaction->Checked == TRUE) C5Mset_inposition_enable(axis, 1);
    else                                C5Mset_inposition_enable(axis, 0);
}

// �˶���ȣ�� ��������� ����.
void __fastcall TForm1::m_alarmactionClick(TObject *Sender)
{
    if (m_alarmaction->Checked == TRUE) C5Mset_alarm_enable(axis, 1);
    else                                C5Mset_alarm_enable(axis, 0);
}

//---------------------------------------------------------------------------
// ���� ��� 0��(Servo-On)�� ����.
void __fastcall TForm1::m_out0Click(TObject *Sender)
{
    if(m_out0->Color == clMaroon)   C5Mset_output_bit(axis, 0);
    else                            C5Mreset_output_bit(axis, 0);
}

// ���� ��� 1��(Alarm-Clear)�� ����.
void __fastcall TForm1::m_out1Click(TObject *Sender)
{
    if(m_out1->Color == clMaroon)   C5Mset_output_bit(axis, 1);
    else                            C5Mreset_output_bit(axis, 1);
}

// ���� ��� 2���� ����.
void __fastcall TForm1::m_out2Click(TObject *Sender)
{
    if(m_out2->Color == clMaroon)   C5Mset_output_bit(axis, 2);
    else                            C5Mreset_output_bit(axis, 2);
}

// ���� ��� 3���� ����.
void __fastcall TForm1::m_out3Click(TObject *Sender)
{
    if(m_out3->Color == clMaroon)   C5Mset_output_bit(axis, 3);
    else                            C5Mreset_output_bit(axis, 3);
}

//---------------------------------------------------------------------------
// ���� ����.
void __fastcall TForm1::m_axissetChange(TObject *Sender)
{
    axis = m_axisset->ItemIndex;
    module_axis = axis - ( axis % 2);

    // �ʱ� �Ķ������ �޽� ��¹��, ���ڴ� �Է� ���, �ʱ�ӵ�,
    // �޽��� �Ÿ��� �о�ͼ� ȭ�鿡 ���.
    m_pulseout->ItemIndex = C5Mget_pulse_out_method(axis);
    m_encinput->ItemIndex = C5Mget_enc_input_method(axis);

    m_startspeed->Text = FloatToStr(C5Mget_startstop_speed(axis));
    m_moveunit->Text =  FloatToStr(C5Mget_moveunit_perpulse(axis));
}

//---------------------------------------------------------------------------
// �޽� ��� ����� ����.
void __fastcall TForm1::m_pulseoutChange(TObject *Sender)
{
    C5Mset_pulse_out_method(axis, m_pulseout->ItemIndex);
}

//---------------------------------------------------------------------------
// ���ڴ� �Է� ����� ����.
void __fastcall TForm1::m_encinputChange(TObject *Sender)
{
    C5Mset_enc_input_method(axis, m_encinput->ItemIndex);
}

//---------------------------------------------------------------------------
// �ʱ� �Ķ������ �޽��� �Ÿ���� �ʱ�ӵ��� ����.
// �޽��� �Ÿ��� �����ϸ� �ִ� �ӵ��� �׿� �°� �ٲ��ݴϴ�.
void __fastcall TForm1::m_setClick(TObject *Sender)
{
    double moveunit, startstop;

	moveunit = StrToFloat(m_moveunit->Text);
	startstop = StrToFloat(m_startspeed->Text);

	C5Mset_moveunit_perpulse(axis, moveunit);
	C5Mset_startstop_speed(axis, startstop);

    // 500KPps�� �ش��ϴ� �ӵ��� �ְ�ӵ��� ����.
    // ����ڰ� ���Ͻô� ������ �ٲٽø� �˴ϴ�.
	C5Mset_max_speed(axis, 500000 * C5Mget_moveunit_perpulse(axis));
}

//---------------------------------------------------------------------------
// �����ġ�� ���� ��ġ�� 0���� ����.
void __fastcall TForm1::m_countclearClick(TObject *Sender)
{
    C5Mset_command_position(module_axis, 0.0);
    C5Mset_actual_position(module_axis, 0.0);
    C5Mset_command_position(module_axis+1, 0.0);
    C5Mset_actual_position(module_axis+1, 0.0);
    m_searchlist->Clear();
}

//---------------------------------------------------------------------------
// Ʈ���Ű� �߻��� �� �ֵ��� ���ͷ�Ʈ��  Enable ��Ű��
// Ʈ���Ÿ� Enable ��Ų �� �߻��� ��ġ�� ����.
void __fastcall TForm1::m_triggerdnableClick(TObject *Sender)
{
    INT16 nBoardNo, nModulePos, nAxisPos;
    UINT8 bModuleID;
    double trig_pos;

    // �ش� ���忡 ���ؼ� ���ͷ�Ʈ�� ����ϵ��� �����մϴ�.
    // ���⼭ ���ڴ� ������ ID�� ���մϴ�. ���尡 1�� ���� ������ 0���Դϴ�.
    C5Mget_axis_info(axis, &nBoardNo, &nModulePos, &bModuleID, &nAxisPos);
    AxtEnableInterrupt(nBoardNo);

	AxtWriteInterruptMaskModule(nBoardNo, 0x80 |(0x1 << nModulePos));
    // �����࿡ ���� Trigger ����� Enable �Ѵ� .
	C5Mset_trigger_enable(axis, 1);
    // Trigger ��� Active �ð��� �����մϴ�. Trigger Pulse�� Active �ð���
    // ����� �Ŀ��� �ڵ����� Negate�˴ϴ�. ���� 0x00 ~ 0xFF���� �����ϸ�,
    // ���� ��� �ð��� 500 micro sec �Դϴ�.
	C5Mset_trigger_time(axis, 0xFF);
    // Trigger ��� �޽��� Active Level�� �����մϴ�.
	C5Mset_trigger_level(axis, 1);
    // ���� ����ġ(1) �Ǵ� �ܺ� ���ڴ�(0)�� ���� Trigger Pulse����� �����Ѵ�.
	C5Mset_trigger_sel(axis, 1);
    trig_pos = StrToFloat(m_position->Text);
    // �ش� �࿡ Ʈ���� ��ġ ���� ����.
	C5Mset_internal_comparator_position(axis, trig_pos);    // ��������ġ�� ����
// 	C5Mset_external_comparator_position(axis, trig_pos);    // �ܺ�����ġ�� ����

    // �ش��࿡ ���� ���ͷ�Ʈ ����� �����մϴ�.
    // 0 : Disable, 1 : Enable
	if ( C5Mset_trigger_interrupt_enable(axis, 1) == TRUE )
		m_searchlist->Items->Add("Trigger Interrupt ����� �����Ͽ����ϴ�.");
	else
		m_searchlist->Items->Add("Trigger Interrupt ����� �����Ͽ����ϴ�.");

    m_searchlist->TopIndex = m_searchlist->Count - 1;
}

//---------------------------------------------------------------------------
// Ʈ���� �߻��� ���� ���ϵ��� Disable ��Ų��.
void __fastcall TForm1::m_triggerdisableClick(TObject *Sender)
{
    C5Mset_trigger_enable(axis, 0);
    C5Mset_trigger_interrupt_enable(axis, 0);
}

//---------------------------------------------------------------------------
// ���� ī���� Ŭ��� �߻��ϵ��� �����Ѵ�.
void __fastcall TForm1::m_crcenableClick(TObject *Sender)
{
    UINT8 byPLevel, byNLevel;
	// �� ����Ʈ ������ ������ �����ϰ� ����
	byPLevel = C5Mget_pend_limit_level(axis);
	byNLevel = C5Mget_nend_limit_level(axis);
	C5Mset_crc_nelm_level(axis, byPLevel);
	C5Mset_crc_pelm_level(axis, byNLevel);
	// (+)����Ʈ �Ǵ� (-)����Ʈ�� ���� �Ǿ����� ī���� Ŭ���� ���
	C5Mset_crc_nelm_mask(axis, ENABLE);
	C5Mset_crc_pelm_mask(axis, ENABLE);
	// ���� : ���� ����̹��� ī���� Ŭ���� ������ Level�� �Ǿ� ������� ���Ͱ� �������� ������ ����
	// ���� ����̹��� ������ �°� �����ϼ���
	C5Mset_crc_level(axis, LOW);
	// ī��Ʈ Ŭ���� ���
	C5Mset_crc_mask(axis, ENABLE);
}

//---------------------------------------------------------------------------
// ���� ī���� Ŭ��� �߻����� �ʵ��� ����.
void __fastcall TForm1::m_crcdisableClick(TObject *Sender)
{
    C5Mset_crc_nelm_mask(axis, DISABLE);
	C5Mset_crc_pelm_mask(axis, DISABLE);
	C5Mset_crc_mask(axis, DISABLE);
	C5Mset_crc_level(axis, HIGH);
}

//---------------------------------------------------------------------------
// ���� ��ǥ�� üũ�ڽ��� Ŭ�������ν� üũ�Ǿ� ������ ��� ��ǥ��
// üũ�Ǿ� ���� ������ ��� ��ǥ�� üũ�Ͽ� ��� ��ǥ�� ����.
void __fastcall TForm1::m_absClick(TObject *Sender)
{
    if(m_abs->Checked == True)
        m_inc->Checked = False;
    else
        m_inc->Checked = True;
}

//---------------------------------------------------------------------------
// �����ǥ�� üũ�ڽ��� Ŭ�������ν� üũ�Ǿ� ������ ��� ��ǥ��
// üũ�Ǿ� ���� ������ ���� ��ǥ�� üũ�Ͽ� ���� ��ǥ�� ����.
void __fastcall TForm1::m_incClick(TObject *Sender)
{
    if(m_inc->Checked == True)
        m_abs->Checked = False;
    else
        m_abs->Checked = True;
}

//---------------------------------------------------------------------------
// ������ �ڽ��� �ִ� �Ķ���Ͱ��� �о�ͼ� �����޽� ����.
void __fastcall TForm1::m_moveClick(TObject *Sender)
{
    double position, velocity, accel;
    position = StrToFloat(m_position->Text);
    velocity = StrToFloat(m_velocity->Text);
    accel = StrToFloat(m_accel->Text);

    // �� ���� ���� �ӵ��� ��Ʈ�� ��Ÿ���� ���� ��Ʈ �ִ밪 �缳��
    if ( axis %2 == 0) Chart1->LeftAxis->Maximum = velocity + (velocity * 0.2);
    else Chart2->LeftAxis->Maximum = velocity + (velocity * 0.2);

    // ���� �ִ� �ӵ� �缳��
    C5Mset_max_speed(axis, velocity);

    // ��� ��ǥ���� ���� ��ǥ���� Ȯ��(r)�ϰ� S �������� �ƴ��� Ȯ��(s)�Ͽ� ����.
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
// �����ϰ� �ִ� �࿡ ���� ���� ����.
void __fastcall TForm1::m_decelstopClick(TObject *Sender)
{
    if(RepeatFlag == True)
        RepeatFlag = False;
    else
    {
        C5Mabort_home_search(module_axis, 0);         // X���� �����˻��� ����.
        C5Mabort_home_search(module_axis+1, 0);       // Y���� �����˻��� ����.
        C5Mset_stop(module_axis);
        C5Mset_stop(module_axis+1);
    }
}

//---------------------------------------------------------------------------
// �����ϰ� �ִ� �࿡ ���� ������.
void __fastcall TForm1::m_stopClick(TObject *Sender)
{
    EStop = True;
    RepeatFlag = False;
    C5Mabort_home_search(module_axis, 1);         // X���� �����˻��� ����.
    C5Mabort_home_search(module_axis+1, 1);       // Y���� �����˻��� ����.
    C5Mset_e_stop(module_axis);
    C5Mset_e_stop(module_axis+1);
}

//---------------------------------------------------------------------------
// ������ �ڽ��� �Ķ���� �������� �о�ͼ� �ݺ� ����.
void __fastcall TForm1::m_repeatmoveClick(TObject *Sender)
{
    if( (axis % 2) == 0)
    {
        if ( repeatthread_x != 0 || TestActive1 == True)
        {
            m_searchlist->Items->Add("������ �Դϴ�.");
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
            m_searchlist->Items->Add("������ �Դϴ�.");
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
// Ȩ�˻��� �׽�Ʈ �ϱ� ���� �κ����� �˻��� ��ȣ�� �����ϰ� �˻� ����,
// �˻��� ���� ����� ���� �о���� �˻��� ����.
// �˻��� ������ ����Ʈ �ڽ��� ����� ���.
void __fastcall TForm1::m_searchClick(TObject *Sender)
{
    if ( m_detectsignal->ItemIndex < 3) detectsignal = m_detectsignal->ItemIndex + 4;
    else detectsignal = m_detectsignal->ItemIndex + 8;

    if( (axis % 2) == 0)
    {
        if ( searchthread_x != 0 || TestActive1 == True)
        {
            m_searchlist->Items->Add("������ �Դϴ�.");
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
            m_searchlist->Items->Add("������ �Դϴ�.");
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
// �����찡 ����� �� �ʱ� ���� �Ķ���Ϳ� ���� ȭ�Ϸ� ����.
// ���߿� �� ȭ���� �о�� �ʱ� ���� �Ķ���͸� ������ �� �ֽ��ϴ�.
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    char *nfilename= "Camc5M.Mot";
    C5Msave_parameter_all(nfilename);
    // ���� OFF
    C5Mreset_output_bit(module_axis, 0);
    C5Mreset_output_bit(module_axis+1, 0);
    // ���� ���̺귯���� ����� �����Ѵ�.
    AxtClose();
}

//---------------------------------------------------------------------------
// �� ���� ��ư�� ������ �� (+)�������� ���� �����Ѵ�.(Y�� ���� ����)
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
// �� ���� ��ư�� ������ �� ���� ���� �Ѵ�.(Y�� ���� ����)
void __fastcall TForm1::jog1upMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis+1);
}

//---------------------------------------------------------------------------
// �ٿ� ���� ��ư�� ������ �� (-)�������� ���� �����Ѵ�.(Y�� ���� ����)
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
// �ٿ� ���� ��ư�� ������ �� ���� �����Ѵ�.(Y�� ���� ����)
void __fastcall TForm1::jog1downMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis+1);
}

//---------------------------------------------------------------------------
// ����Ʈ ���׹�ư���� ��ư�� ������ �� (+)�������� ���� �����Ѵ�.(X�� ���� ����)
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
// ����Ʈ ���� ��ư�� ������ �� ���� �����Ѵ�.(X�� ���� ����)
void __fastcall TForm1::jog0downMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis);
}

//---------------------------------------------------------------------------
// ����Ʈ ���� ��ư�� ������ �� (-)�������ο��� ���� �Ѵ�.(X�� ���� ����)
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
// ����Ʈ ���� ��ư�� ������ �� ���� �����Ѵ�.(X�� ���� ����)
void __fastcall TForm1::jog0upMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
    C5Mset_stop(module_axis);
}

//---------------------------------------------------------------------------
// CW ���� Ȩ�˻� ����
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
        Form1->m_searchlist->Items->Add( "Ȩ�˻� ���Դϴ�.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }

    if ( TestActive1 || TestActive2)
    {
        Form1->m_searchlist->Items->Add( "���� ���Դϴ�.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }
	/* Detect Signal---------------------------------------------------------
	PElmNegativeEdge    = 0x0,			// +Elm(End limit) �ϰ� edge
	NElmNegativeEdge    = 0x1,			// -Elm(End limit) �ϰ� edge
	PSlmNegativeEdge    = 0x2,			// +Slm(Slowdown limit) �ϰ� edge
	NSlmNegativeEdge    = 0x3,			// -Slm(Slowdown limit) �ϰ� edge
	In0DownEdge         = 0x4,			// IN0(ORG) �ϰ� edge
	In1DownEdge         = 0x5,			// IN1(Z��) �ϰ� edge
	In2DownEdge         = 0x6,			// IN2(����) �ϰ� edge
	In3DownEdge         = 0x7,			// IN3(����) �ϰ� edge
	PElmPositiveEdge    = 0x8,			// +Elm(End limit) ��� edge
	NElmPositiveEdge    = 0x9,			// -Elm(End limit) ��� edge
	PSlmPositiveEdge    = 0xa,			// +Slm(Slowdown limit) ��� edge
	NSlmPositiveEdge    = 0xb,			// -Slm(Slowdown limit) ��� edge
	In0UpEdge           = 0xc,			// IN0(ORG) ��� edge
	In1UpEdge           = 0xd,			// IN1(Z��) ��� edge
	In2UpEdge           = 0xe,			// IN2(����) ��� edge
	In3UpEdge           = 0xf			// IN3(����) ��� edge
	------------------------------------------------------------------------
	------------------------------------------------------------------------
	7-4Bit	detect signal ����
	3Bit	�˻����� ���� (0 : cww(-), 1 : cw(+))
	2Bit	������� ���� (0 : ���� ����, 1 : �� ����)
	1Bit	������ ��� ���� (0 : ������, 1 : ���� �ð�)
	0Bit	���� ��뿩�� ���� (0 : ������� ����, 1: �����
	------------------------------------------------------------------------*/
    methods[1] = IN0_DNEDGE | STOP_EMG | USE_STEP | DIR_CW;			        // (-)�������� Ȩ ������ �ϰ����� ��ȣ�� �˻��� ������ ������...
	methods[2] = IN0_UPEDGE | STOP_EMG | USE_STEP;					        // (+)�������� Ȩ ������ ��¿��� ��ȣ�� �˻��� ������ ������..
	methods[3] = IN1_DNEDGE | STOP_EMG | USE_STEP | DIR_CW;                 // (-)�������� Z�� ������ �ϰ����� ��ȣ�� �˻��� ������ ������..

	if ( C5Minput_bit_on(module_axis, HOME_BIT))    methods[0] = 0x0;  		// ���������� �����Ǿ� ���� �� Step0�� ������� ����....
	else    methods[0] = IN0_UPEDGE | USE_STEP;                             // ���������� �����Ǿ� �������� ��....
    C5Mset_home_method(module_axis, HOME_STEP, methods);		            // �ະ�� Ȩ�˻� ����� �����Ѵ�..

    if ( C5Minput_bit_on(module_axis+1, HOME_BIT))  methods[0] = 0x0; 		// ���������� �����Ǿ� ���� �� Step0�� ������� ����....
	else    methods[0] = IN0_UPEDGE | USE_STEP;	                            // ���������� �����Ǿ� �������� ��....
	C5Mset_home_method(module_axis+1, HOME_STEP, methods);		      	    // �ະ�� Ȩ�˻� ����� �����Ѵ�..

	// �࿡ ���� �˻� �� �� ���ܺ� �ӵ��� ����
	dHomeVel1	= 50000 * C5Mget_moveunit_perpulse(module_axis);            // �ⱸ�� �´� �ӵ��� �����Ͽ� ����Ͻʽÿ�.
	dHomeVel2	= 10000 * C5Mget_moveunit_perpulse(module_axis);
	dHomeVel3	= 3000  * C5Mget_moveunit_perpulse(module_axis);

	velocities[0] = dHomeVel1;         accelerations[0]  = dHomeVel1 * 4;
    velocities[1] = dHomeVel2;         accelerations[1]  = dHomeVel2 * 4;
    velocities[2] = dHomeVel3;         accelerations[2]  = dHomeVel3 * 4;
    velocities[3] = dHomeVel3 / 2;	   accelerations[3] = dHomeVel3 * 2; 	// �� ������ �ӵ��� �����Ѵ�.

    // ���� ���� �˻��� �ְ�ӵ� ����
  	C5Mset_max_speed(module_axis, dHomeVel1);
	C5Mset_max_speed(module_axis+1, dHomeVel1);

    // ���� ���� �˻� �� �� ���ܺ� �ӵ� ����
	C5Mset_home_velocity(module_axis, HOME_STEP, velocities);		        // �� Setp�� X�� Ȩ �˻� �ӵ� ����
	C5Mset_home_velocity(module_axis+1, HOME_STEP, velocities);		        // �� Setp�� Y�� Ȩ �˻� �ӵ� ����

	// ���� ���� �˻� �� �� ���ܺ� �������� ����
	C5Mset_home_acceleration(module_axis, HOME_STEP, accelerations);        // �� Setp�� X�� Ȩ �˻� ���ӵ� ����
	C5Mset_home_acceleration(module_axis+1, HOME_STEP, accelerations);      // �� Setp�� Y�� Ȩ �˻� ���ӵ� ����

    Chart1->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);
    Chart2->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);

    TestActive1 = True;
    TestActive2 = True;
    Timer3->Enabled = True;

    // 1�� �̻��� ��� 2�� ���� Ȩ �˻�
    if (C5Mget_total_numof_axis() > 0 == True) C5Mhome_search_all(2, axes);
    else C5Mhome_search(axis);
}

//---------------------------------------------------------------------------
// CW ���� Ȩ�˻� ����
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
        Form1->m_searchlist->Items->Add( "Ȩ�˻� ���Դϴ�.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }

    if ( TestActive1 || TestActive2)
    {
        Form1->m_searchlist->Items->Add( "���� ���Դϴ�.");
        Form1->m_searchlist->TopIndex = Form1->m_searchlist->Count - 1;
        return;
    }
    /*Detect Signal---------------------------------------------------------
	PElmNegativeEdge    = 0x0,			// +Elm(End limit) �ϰ� edge
	NElmNegativeEdge    = 0x1,			// -Elm(End limit) �ϰ� edge
	PSlmNegativeEdge    = 0x2,			// +Slm(Slowdown limit) �ϰ� edge
	NSlmNegativeEdge    = 0x3,			// -Slm(Slowdown limit) �ϰ� edge
	In0DownEdge         = 0x4,			// IN0(ORG) �ϰ� edge
	In1DownEdge         = 0x5,			// IN1(Z��) �ϰ� edge
	In2DownEdge         = 0x6,			// IN2(����) �ϰ� edge
	In3DownEdge         = 0x7,			// IN3(����) �ϰ� edge
	PElmPositiveEdge    = 0x8,			// +Elm(End limit) ��� edge
	NElmPositiveEdge    = 0x9,			// -Elm(End limit) ��� edge
	PSlmPositiveEdge    = 0xa,			// +Slm(Slowdown limit) ��� edge
	NSlmPositiveEdge    = 0xb,			// -Slm(Slowdown limit) ��� edge
	In0UpEdge           = 0xc,			// IN0(ORG) ��� edge
	In1UpEdge           = 0xd,			// IN1(Z��) ��� edge
	In2UpEdge           = 0xe,			// IN2(����) ��� edge
	In3UpEdge           = 0xf			  // IN3(����) ��� edge
	-------------------------------------------------------------------------
	-------------------------------------------------------------------------
	7-4Bit	detect signal ����
	3Bit	�˻����� ���� (0 : ccw(-), 1 : cw(+))
	2Bit	������� ���� (0 : ���� ����, 1 : �� ����)
	1Bit	������ ��� ���� (0 : ������, 1 : ���� �ð�)
	0Bit	���� ��뿩�� ���� (0 : ������� ����, 1: �����
	------------------------------------------------------------------------*/
    methods[1] = IN0_DNEDGE | STOP_EMG | USE_STEP;                          // (+)�������� Ȩ ������ �ϰ����� ��ȣ�� �˻��� ������ ������...
	methods[2] = IN0_UPEDGE | STOP_EMG | USE_STEP | DIR_CW;                 // (-)�������� Ȩ ������ ��¿��� ��ȣ�� �˻��� ������ ������..
	methods[3] = IN1_DNEDGE | STOP_EMG | USE_STEP;			                // (+)�������� Z�� ������ �ϰ����� ��ȣ�� �˻��� ������ ������..

	if(C5Minput_bit_on(module_axis, HOME_BIT)) 	methods[0] = 0x0;	        // ���������� �����Ǿ� ���� �� Step0�� ������� ����....
	else    methods[0] = IN0_UPEDGE | USE_STEP | DIR_CW;                    // ���������� �����Ǿ� �������� ��....
	C5Mset_home_method(module_axis, HOME_STEP, methods);				    // �ະ�� Ȩ�˻� ����� �����Ѵ�..

	if(C5Minput_bit_on(module_axis+1, HOME_BIT)) methods[0] = 0x0;          // ���������� �����Ǿ� ���� �� Step0�� ������� ����....
	else    methods[0] = IN0_UPEDGE | USE_STEP | DIR_CW;	                // ���������� �����Ǿ� �������� ��....
	C5Mset_home_method(module_axis+1, HOME_STEP, methods);			        // �ະ�� Ȩ�˻� ����� �����Ѵ�..

	// �࿡ ���� �˻� �� �� ���ܺ� �ӵ��� ����
	dHomeVel1	= 50000 * C5Mget_moveunit_perpulse(module_axis);            // �ⱸ�� �´� �ӵ��� �����Ͽ� ����Ͻʽÿ�.
	dHomeVel2	= 10000 * C5Mget_moveunit_perpulse(module_axis);
	dHomeVel3	= 3000  * C5Mget_moveunit_perpulse(module_axis);

	velocities[0] = dHomeVel1;         accelerations[0]  = dHomeVel1 * 4;
    velocities[1] = dHomeVel2;         accelerations[1]  = dHomeVel2 * 4;
    velocities[2] = dHomeVel3;         accelerations[2]  = dHomeVel3 * 4;
    velocities[3] = dHomeVel3 / 2;	    accelerations[3] = dHomeVel3 * 2;  	// �� ������ �ӵ��� �����Ѵ�.

    // ���� ���� �˻��� �ְ�ӵ� ����
  	C5Mset_max_speed(module_axis, dHomeVel1);
	C5Mset_max_speed(module_axis+1, dHomeVel1);

    // ���� ���� �˻� �� �� ���ܺ� �ӵ� ����
	C5Mset_home_velocity(module_axis, HOME_STEP, velocities);		        // �� Setp�� X�� Ȩ �˻� �ӵ� ����
	C5Mset_home_velocity(module_axis+1, HOME_STEP, velocities);		        // �� Setp�� Y�� Ȩ �˻� �ӵ� ����

	// ���� ���� �˻� �� �� ���ܺ� �������� ����
	C5Mset_home_acceleration(module_axis, HOME_STEP, accelerations);        // �� Setp�� X�� Ȩ �˻� ���ӵ� ����
	C5Mset_home_acceleration(module_axis+1, HOME_STEP, accelerations);      // �� Setp�� Y�� Ȩ �˻� ���ӵ� ����

    // �� ���� ���� �ӵ��� ��Ʈ�� ��Ÿ���� ���� ��Ʈ �ִ밪 �缳�� 
    Chart1->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);
    Chart2->LeftAxis->Maximum = dHomeVel1 + (dHomeVel1 * 0.2);

    TestActive1 = True;
    TestActive2 = True;
    Timer3->Enabled = TRUE;

	// 1�� �̻��� ��� 2�� ���� Ȩ �˻�
    if (C5Mget_total_numof_axis() > 0 == True) C5Mhome_search_all(2, axes);
    else C5Mhome_search(axis);
}

//---------------------------------------------------------------------------
// Ȩ �˻� �Ϸ� ���� �˻�
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
             m_searchlist->Items->Add("Ȩ�˻��� �Ϸ� �Ͽ����ϴ�.");
        else
            m_searchlist->Items->Add("Ȩ�˻��� ���� �Ͽ����ϴ�.");

        TestActive1 = False;
        TestActive2 = False;
        m_searchlist->TopIndex = m_searchlist->Count - 1;
    }
}

//---------------------------------------------------------------------------
// ������ ����
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
// Ʈ���� ���ͷ�Ʈ ���� ��ƾ
void TForm1::TriggerInterrupt(TMessage Msg)
{
    m_searchlist->Items->Add(IntToStr(axis) + "�࿡ ���ͷ�Ʈ�� �߻��Ͽ����ϴ�.");
    m_searchlist->TopIndex = m_searchlist->Count - 1;
}
