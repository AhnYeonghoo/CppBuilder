 // TriggerTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TriggerTest.h"
#include "TriggerTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "math.h"

#include "../../../../AXT(Library)/C, C++/AXTLIB.h"
#include "../../../../AXT(Library)/C, C++/AXTKeLIB.h"		// Base Board�� 1�� Low Level �Լ��� ����ϱ� ����
#include "../../../../AXT(Library)/C, C++/AXTCAMCFS20.h"	
#include "../../../../AXT(Library)/C, C++/AxtKeCamcFs20.h"	// FS20�� 1�� Low Level �Լ��� ����ϱ� ����
#include "../../../../AXT(Library)/C, C++/AxtTrigger.h"		// Ʈ���� ���̺귯�� �Լ� ����� ���� 

#pragma comment(lib, "../../../../AXT(Library)/Library/32Bit/AxtLib.lib")
#pragma comment(lib, "../../../../AXT(Library)/Library/32Bit/AxtTriggerLib.lib")
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#define TEST_AX		0

#define TRIG_CMD	0	
#define TRIG_ACT	1
#define TRIG_DNEG	1
#define TRIG_UPEG	0

#define TM_DISPLAY	100

CTriggerTestDlg *g_pDlg;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriggerTestDlg dialog

CTriggerTestDlg::CTriggerTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTriggerTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTriggerTestDlg)	
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nIntCnt = 0;
	m_bOnce = TRUE;
	g_pDlg = this;
}

void CTriggerTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTriggerTestDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_RDO_TRIG_POSITION, m_rdoTriggerSel[0]);
	DDX_Control(pDX, IDC_RDO_TRIG_PERIODIC, m_rdoTriggerSel[1]);
	DDX_Control(pDX, IDC_RDO_TRIG_ABSOLUTE, m_rdoTriggerSel[2]);
	DDX_Control(pDX, IDC_RDO_MESSAGE, m_rdoMessage);
}

BEGIN_MESSAGE_MAP(CTriggerTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTriggerTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START_MOVE, OnStartMove)
	ON_BN_CLICKED(IDC_STOP_MOVE, OnStopMove)
	ON_BN_CLICKED(IDC_TRIGGER_EANBLE, OnTriggerEanble)
	ON_BN_CLICKED(IDC_COUNT_CLEAR, OnCountClear)
	ON_BN_CLICKED(IDC_BTN_TRIG_ONESHOT, OnBtnTrigOneshot)
	ON_BN_CLICKED(IDC_TRIGGER_DISABLE, OnTriggerDisable)
	ON_BN_CLICKED(IDC_RDO_MESSAGE, OnRdoMessage)
	ON_BN_CLICKED(IDC_RDO_CALLBACK, OnRdoCallback)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_CAMCFS_INTERRUPT, OnTriggerInterrupt)	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriggerTestDlg message handlers

// Ʈ���� �ݹ� �Լ�
static void TriggerInterruptCallback(INT16 nBoardNo, INT16 nModulePos, UINT8 byFlag)
{	
	INT16 nAxis = CFS20get_axisno(nBoardNo, nModulePos);
	UINT32 nFlag= CFS20read_interrupt_flag(nAxis);
	if(nFlag & 0x10000000) // Trigger Interrupt �߻�
		g_pDlg->m_nIntCnt++;
}

BOOL CTriggerTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if (InitLibrary()) {
		InitFS(TEST_AX);
		InitParameter(TEST_AX, 1);				// ��� �Ķ���� ����
		CFS20SetWindowMessage(m_hWnd, WM_CAMCFS_INTERRUPT, NULL);
		TriggerInterruptEnable(TEST_AX);	// Ʈ���� ���ͷ�Ʈ ���� 	
		InitControl();						// ��Ʈ�� �ʱ�ȭ 
	}
	
	SetTimer(TM_DISPLAY, 50, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTriggerTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTriggerTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTriggerTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ���� ���̺귯�� �� ��� �ʱ�ȭ �κ�
BOOL CTriggerTestDlg::InitLibrary()
{
	if( !AxtIsInitialized())							// ���� ���̺귯���� ��� �������� (�ʱ�ȭ�� �Ǿ�����) Ȯ��
    {
		if( !AxtInitialize(m_hWnd, NULL))				// ���� ���̺귯�� �ʱ�ȭ
		{
			MessageBox( "Can not Library Initialize!!");
			return FALSE;
		}   
	}		

	if( !AxtIsInitializedBus(BUSTYPE_PCI))			// ������ ����(PCI)�� �ʱ�ȭ �Ǿ����� Ȯ��
	{												// ������ ISA �ϰ�� BUSTYPE_PCI -> BUSTYPE_ISA ����
        if( !AxtOpenDeviceAuto(BUSTYPE_PCI))		// ���ο� ���̽����带 �ڵ����� ���ն��̺귯���� �߰�
		{
			MessageBox("Can not Baseboard Initialize!!");
			return FALSE;
		}
	 }

	if( !CFS20IsInitialized())						// CAMC-FS����� ����� �� �ֵ��� ���̺귯���� �ʱ�ȭ�Ǿ����� Ȯ��
	{
		if( !InitializeCAMCFS20(FALSE))				// CAMC-FS����� �ʱ�ȭ(�����ִ� ��纣�̽����忡�� FS����� �˻��Ͽ� �ʱ�ȭ)
		{
			AfxMessageBox("Can not CAMC-FS Module Initialize!!");
			return FALSE;
		}			
	}
	return TRUE;
}

// CAMC-FS Chip Manual Initialize
void CTriggerTestDlg::InitFS(INT16 nAxisNo)
{	
	CFS20set_e_stop(nAxisNo);
	
	CFS20set_command_position(nAxisNo, 0.0);
	CFS20set_actual_position(nAxisNo, 0.0);
	
	CFS20set_crc_mask(nAxisNo, DISABLE);
	CFS20set_crc_nelm_mask(nAxisNo, LOW);
	CFS20set_crc_pelm_mask(nAxisNo, LOW);
	CFS20set_crc_pelm_level(nAxisNo, LOW);
	CFS20set_crc_nelm_level(nAxisNo, LOW);
	CFS20set_crc_level(nAxisNo, HIGH);
	
	CFS20set_programmed_crc(nAxisNo, DISABLE);	
	
	CFS20set_sync_axis(nAxisNo, FALSE);
	CFS20set_trigger_interrupt_enable(nAxisNo, DISABLE);
}

// ��Ǳ��� �Ķ���� ����
// ����� ������ �°� �ݵ�� ���� �ϼ���
void CTriggerTestDlg::InitParameter(INT16 nAxisNo, double dUnit)
{	
	CFS20set_moveunit_perpulse(nAxisNo, dUnit);			// Unit�� �̵������� ����. �̵��� �� �ӵ��� ������ �ش�		
	CFS20set_startstop_speed(nAxisNo, 1.0 * dUnit);		// �ʱ�ӵ�(Start/Stop speed) ����	
	CFS20set_enc_input_method(nAxisNo, Sqr4Mode);		// ���ڴ� �Է� ��� ����	
	CFS20set_pulse_out_method(nAxisNo, TwoCcwCwHigh);	// �޽� ��� ��� ����
	CFS20set_end_limit_enable(nAxisNo, DISABLE);			// ������ ����Ʈ ��� ��������� ����
	CFS20set_pend_limit_level(nAxisNo, LOW);			// ������ ����Ʈ(+End limit)�� ��Ƽ�극�� ����	
	CFS20set_nend_limit_level(nAxisNo, LOW);			// ������ ����Ʈ(-End limit)�� ��Ƽ�극�� ����
	CFS20set_alarm_enable(nAxisNo, DISABLE);				// ���� �˶� �Է½�ȣ ����� ��������� ����
	CFS20set_alarm_level(nAxisNo, LOW);					// �˶�(Alarm) ��ȣ ��Ƽ�극�� ����
	CFS20set_inposition_enable(nAxisNo, DISABLE);		// ��������(Inposition) ��ȣ ������� ����
	CFS20set_inposition_level(nAxisNo, HIGH);			// ��������(Inposition) ��ȣ ��Ƽ�극�� ����
	CFS20set_servo_enable(nAxisNo, ENABLE);				// ���� ON
}

// ��Ʈ�� �ʱ�ȭ 
void CTriggerTestDlg::InitControl()
{
	SetDlgItemDouble(IDC_INTERRUPT_COUNT, 0);
	SetDlgItemDouble(IDC_CMD_POS, 0.0);
	SetDlgItemDouble(IDC_ACT_POS, 0.0);

	SetDlgItemText(IDC_MOVE_POS, "10000");
	SetDlgItemText(IDC_MOVE_VEL, "1000");
	SetDlgItemText(IDC_MOVE_ACC, "10000");

	SetDlgItemText(IDC_START_POS, "1000");
	SetDlgItemText(IDC_CYCLE, "100");
	SetDlgItemText(IDC_PULSE_WIDTH, "1000");
	SetDlgItemText(IDC_END_POS, "5000");

	m_rdoTriggerSel[1].SetCheck(TRUE);
	m_rdoMessage.SetCheck(TRUE);
}

// Ʈ���� ���ͷ�Ʈ ���� ��ƾ
void CTriggerTestDlg::OnTriggerInterrupt(WPARAM wParam, LPARAM lParam)
{
	if((lParam & 0x30) == FALSE)	return;

	INT16 nBoardNo;
	INT16 nModulePos;
	nBoardNo	= HIWORD(wParam);
	nModulePos	= LOWORD(wParam);
	INT16 nAxis = CFS20get_axisno(nBoardNo, nModulePos) + ((lParam & 0x20) ? 1 : 0);
	UINT32 nFlag= CFS20read_interrupt_flag(nAxis);
	if(nFlag & 0x10000000) // Trigger Interrupt �߻�
		m_nIntCnt++;
}

// Ʈ���� ���ͷ�Ʈ�� ����ϵ��� ���� 
// ���ͷ�Ʈ�� ������� ������ ���� �ʿ���� 
void CTriggerTestDlg::TriggerInterruptEnable(INT16 nAxisNo)
{		
	UINT8 bModuleID;
	INT16 nBoardNo, nModulePos, nAxisPos;
	CFS20get_axis_info(TEST_AX, &nBoardNo, &nModulePos, &bModuleID, &nAxisPos);
	if ( !AxtIsEnableInterrupt(nBoardNo) )
	{
		AxtEnableInterrupt(nBoardNo);
		AxtWriteInterruptMaskModule(nBoardNo, 0x80 | (0x01 << nModulePos));
		// AxtWriteInterruptMaskModule(nBoardNo, 0x8F);		// All Use
		// Bit7  --  Global
		// Bit0~Bit3   -- Module0 ~ Module3
	}
	
    // User Selectable Interrupt Source0����
    // Trigger �߻��ÿ� ���ͷ�Ʈ�� �߻��ϵ��� ������ �����Ѵ�.
	CFS20KeSetCommandData(TEST_AX, FsUserInterruptSourceSelectRegWrite, (EVENT_NONE << 24)
                                                                      | (EVENT_NONE << 16)
                                                                      | (EVENT_NONE << 8)
                                                                      | (EVENT_TRIGGER_ENABLE) );
     // Interrupt Mask �������Ϳ� User Selectable Interrupt Source 0��
     // ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�. ( Bit28 )
    CFS20KeSetCommandData(TEST_AX, FsInterruptMaskWrite, 0x10000000);
}

void CTriggerTestDlg::OnTimer(UINT nIDEvent) 
{
	if ( nIDEvent == TM_DISPLAY )
	{
		CString strTemp;

		double cmd_pos = CFS20get_command_position(TEST_AX);
		double act_pos = CFS20get_actual_position(TEST_AX);

		strTemp.Format("%10.3f", cmd_pos);
		SetDlgItemText(IDC_CMD_POS, strTemp);
		strTemp.Format("%10.3f", act_pos);
		SetDlgItemText(IDC_ACT_POS, strTemp);

		strTemp.Format("%d", m_nIntCnt);
		SetDlgItemText(IDC_INTERRUPT_COUNT, strTemp);

		strTemp.Format("%3d", CFS20KeGetScriptQueueEventIndex(TEST_AX));
		SetDlgItemText(IDC_STC_SCRIPT_INDEX, strTemp);

		strTemp.Format("0x%x", CFS20KeGetCommandData(TEST_AX, FsScriptOperDataRegQueueRead));
		SetDlgItemText(IDC_SCRIPT_DATA, strTemp);		
	}

	CDialog::OnTimer(nIDEvent);
}

// ���� ���� 
void CTriggerTestDlg::OnStartMove() 
{
	double position = GetDlgItemDouble(IDC_MOVE_POS);
	double velocity = GetDlgItemDouble(IDC_MOVE_VEL);
	double acceleration = GetDlgItemDouble(IDC_MOVE_ACC);

	CFS20set_max_speed(TEST_AX, velocity);
	CFS20start_rs_move(TEST_AX, position, velocity, acceleration);
}

// ���� ����
void CTriggerTestDlg::OnStopMove() 
{
	CFS20set_stop(TEST_AX);
}

#define TRIG_POSITION	1
#define TRIG_PERIODIC	2
#define	TRIG_ABSOLUTE	4
// Ʈ���� ��� - ��ġ���� Ʈ����, �ֱ��� Ʈ����, ������ġ��� Ʈ���� �� �����Ͽ� ��� 
void CTriggerTestDlg::OnTriggerEanble() 
{	
	m_nIntCnt = 0;		
	//===================================================================================================
	double	start_pos	= GetDlgItemDouble(IDC_START_POS);
	double  cycle       = GetDlgItemDouble(IDC_CYCLE);
	int		pulse_width	= GetDlgItemInt(IDC_PULSE_WIDTH);
	double	end_pos		= GetDlgItemDouble(IDC_END_POS);
	
	int nSel = m_rdoTriggerSel[0].GetCheck() + (m_rdoTriggerSel[1].GetCheck() * 2) + (m_rdoTriggerSel[2].GetCheck() * 4);
	double trig_pos[] = {	100.0, 110.0, 200.0, 300.0, 400.0, 500.0, 700.0, 750.0, 800.0, 810.0, 
							820.0, 830.0, 840.0, 850.0, 860.0, 870.0, 880.0, 890.0, 900.0, 910.0	};
	double dPos = 2000;		// ������ Ʈ������ ��ġ

	CFS20Trig_Set_Level(TEST_AX, TRIG_UPEG);

	switch(nSel)
	{
	case TRIG_POSITION:		// ������ Ʈ����
		CFS20Trig_Absolute_Profile_Set(TEST_AX, 1, &dPos, pulse_width, TRIG_CMD);
		break;

	case TRIG_PERIODIC:		// �ֱ��� Ʈ����
		CFS20Trig_Periodic_Profile_Set(TEST_AX, start_pos, end_pos, cycle, pulse_width, TRIG_CMD);
		break;

	case TRIG_ABSOLUTE:		// ������ġ Ʈ����
		CFS20Trig_Absolute_Profile_Set(TEST_AX, 10, trig_pos, pulse_width, TRIG_CMD);
		break;
	}	
}

// Ʈ���� ����� �����Ѵ� 
void CTriggerTestDlg::OnTriggerDisable() 
{
	CFS20Trig_Profile_Reset(TEST_AX);	
}

// ���� Ʈ���� - �� �Լ��� �����ϸ� ������ Ʈ���������� Ʈ���Ÿ� 1ȸ ����Ѵ�
void CTriggerTestDlg::OnBtnTrigOneshot() 
{
//	CFS20Trig_Profile_Reset(TEST_AX);
	// axis : ���ȣ , trig_time : Ʈ���� ��� �����ð�
	// Ʈ���� ��½ð� ���� : 2usec ~ 4msec	
	CFS20Trig_One_Shot_Set(TEST_AX, TRIG_DNEG, 4000);	
}

// ī��Ʈ Ŭ���� - ���� ������ġ �� ������ġ�� �ʱ�ȭ �Ѵ� 
void CTriggerTestDlg::OnCountClear() 
{
	m_nIntCnt = 0;
	CFS20set_command_position(TEST_AX, 0.0);
	CFS20set_actual_position(TEST_AX, 0.0);
	CFS20get_command_position(TEST_AX);
}

void CTriggerTestDlg::SetDlgItemDouble(UINT nID, double dValue)
{
	CString strTemp;
	strTemp.Format("%10.3lf", dValue);
	SetDlgItemText(nID, strTemp);
}

double CTriggerTestDlg::GetDlgItemDouble(UINT nID)
{
	CString strTemp;
	double dRet;

	GetDlgItemText(nID, strTemp);
	dRet = atof(strTemp.operator LPCTSTR());

	return dRet;
}

int CTriggerTestDlg::GetDlgItemInt(UINT nID)
{
	CString strTemp;
	int		nRet;

	GetDlgItemText(nID, strTemp);
	nRet = atoi(strTemp.operator LPCTSTR());

	return nRet;
}

void CTriggerTestDlg::OnRdoMessage() 
{
	CFS20SetWindowMessage(m_hWnd, WM_CAMCFS_INTERRUPT, NULL);	
}

void CTriggerTestDlg::OnRdoCallback() 
{
	CFS20SetWindowMessage(NULL, NULL, (AXT_CAMCFS_INTERRUPT_PROC)TriggerInterruptCallback);
	TriggerInterruptEnable(TEST_AX);
}


