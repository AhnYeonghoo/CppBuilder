// CounterTestDlg.cpp : ���� ����
//
#include "stdafx.h"
#include "CounterTest.h"
#include "CounterTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef  _M_X64
#pragma comment(lib, "../../../../AXT(Library)/Library/64Bit/AxtLib.lib")
#else
#pragma comment(lib, "../../../../AXT(Library)/Library/32Bit/AxtLib.lib")
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
#define TM_DISPLAY		100
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCounterTestDlg ��ȭ ����
CCounterTestDlg::CCounterTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCounterTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nModuleNo					= -1;
	m_nChannelNo[CHANNEL_00]	= -1;
	m_nChannelNo[CHANNEL_01]	= -1;
	m_dCountOld[CHANNEL_00]		= 0.0;
	m_dCountOld[CHANNEL_01]		= 0.0;
}

void CCounterTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_LOG, m_lstLog);
}

BEGIN_MESSAGE_MAP(CCounterTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_COMMAND_RANGE(IDC_BTN_TRIG_APPLY_00, IDC_BTN_TRIG_APPLY_01, OnBnClickedBtnTrigApply)
	ON_COMMAND_RANGE(IDC_BTN_POS_CLEAR_00, IDC_BTN_POS_CLEAR_01, OnBnClickedBtnPosClear)
	ON_COMMAND_RANGE(IDC_BTN_SET_UNIT_00, IDC_BTN_SET_UNIT_01, OnBnClickedBtnSetUnit)
	ON_COMMAND_RANGE(IDC_CHK_ENC_REVERSE_00, IDC_CHK_ENC_REVERSE_01, OnBnClickedChkEncReverse)
	ON_COMMAND_RANGE(IDC_CHK_OUT_00, IDC_CHK_OUT_03, OnBnClickedChkOut0)
	ON_COMMAND_RANGE(IDC_CHK_OUT_10, IDC_CHK_OUT_13, OnBnClickedChkOut1)
	ON_COMMAND_RANGE(IDC_CHK_TRIG_ENABLE_00, IDC_CHK_TRIG_ENABLE_01, OnBnClickedChkTrigEnable)
	ON_LBN_DBLCLK(IDC_LST_LOG, OnLbnDblclkLstLog)
	ON_CBN_SELCHANGE(IDC_CBO_SEL_MODULE, OnCbnSelchangeCboSelModule)
	ON_CBN_SELCHANGE(IDC_CBO_ENC_METHOD_00, OnCbnSelchangeCboEncMethod00)
	ON_CBN_SELCHANGE(IDC_CBO_ENC_METHOD_01, OnCbnSelchangeCboEncMethod01)
	ON_CBN_SELCHANGE(IDC_CBO_ENC_SOURCE_00, OnCbnSelchangeCboEncSource00)
	ON_CBN_SELCHANGE(IDC_CBO_ENC_SOURCE_01, OnCbnSelchangeCboEncSource01)
	ON_CBN_SELCHANGE(IDC_CBO_TRIG_MODE_00, OnCbnSelchangeCboTrigMode00)
	ON_CBN_SELCHANGE(IDC_CBO_TRIG_MODE_01, OnCbnSelchangeCboTrigMode01)
	ON_CBN_SELCHANGE(IDC_CBO_ACTIVE_LEVEL_00, OnCbnSelchangeCboActiveLevel00)
	ON_CBN_SELCHANGE(IDC_CBO_ACTIVE_LEVEL_01, OnCbnSelchangeCboActiveLevel01)
	ON_CBN_SELCHANGE(IDC_CBO_DIR_CHECK_00, OnCbnSelchangeCboDirCheck00)
	ON_CBN_SELCHANGE(IDC_CBO_DIR_CHECK_01, OnCbnSelchangeCboDirCheck01)
END_MESSAGE_MAP()


// CCounterTestDlg �޽��� ó����

BOOL CCounterTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	if(InitLibrary() == TRUE){
		InitControl();
		UpdateState();
	}
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

CCounterTestDlg::~CCounterTestDlg()
{

}

void CCounterTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCounterTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCounterTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CCounterTestDlg::InitLibrary()
{
	CString string;

	if (AxtInitialize(m_hWnd, 7)){
		AxtOpenDeviceAuto(BUSTYPE_PCI);	
		if (AxtGetBoardCounts() != 0){
			if (InitializeCNT(TRUE)){
				return TRUE;
			}else{
				TraceLog("ERROR: Baseboard Not initialized.");
			}
		}
		else
		{
			AfxMessageBox("CNT Module Not initialized.");
		}
	}
	else			// Error
	{
		AfxMessageBox("CNT Module Not initialized.");		
	}	

	return FALSE;
}

BOOL CCounterTestDlg::InitControl()
{
	m_ftControl.CreateFont (16, 0, 0, 0, 300,
		FALSE, FALSE, 0, ANSI_CHARSET,
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, 
		DEFAULT_PITCH|FF_SWISS, "Arial") ;

	m_cboSelModule.SubclassDlgItem(IDC_CBO_SEL_MODULE, this);
	m_cboSelModule.SetFont(&m_ftControl);

	m_grpChannel[CHANNEL_00].SubclassDlgItem(IDC_GRP_CHANNEL_00, this);
	m_grpChannel[CHANNEL_01].SubclassDlgItem(IDC_GRP_CHANNEL_01, this);

	m_stcActPos[CHANNEL_00].SubclassDlgItem(IDC_STC_ACT_POS_00, this);
	m_stcActPos[CHANNEL_00].SetFont(&m_ftControl);

	m_stcActPos[CHANNEL_01].SubclassDlgItem(IDC_STC_ACT_POS_01, this);
	m_stcActPos[CHANNEL_01].SetFont(&m_ftControl);

	m_btnPosClear[CHANNEL_00].SubclassDlgItem(IDC_BTN_POS_CLEAR_00, this);
	m_btnPosClear[CHANNEL_01].SubclassDlgItem(IDC_BTN_POS_CLEAR_01, this);

	m_cboEncMethod[CHANNEL_00].SubclassDlgItem(IDC_CBO_ENC_METHOD_00, this);
	m_cboEncMethod[CHANNEL_00].SetFont(&m_ftControl);
	m_cboEncMethod[CHANNEL_01].SubclassDlgItem(IDC_CBO_ENC_METHOD_01, this);
	m_cboEncMethod[CHANNEL_01].SetFont(&m_ftControl);

	m_cboEncSource[CHANNEL_00].SubclassDlgItem(IDC_CBO_ENC_SOURCE_00, this);
	m_cboEncSource[CHANNEL_00].SetFont(&m_ftControl);
	m_cboEncSource[CHANNEL_01].SubclassDlgItem(IDC_CBO_ENC_SOURCE_01, this);
	m_cboEncSource[CHANNEL_01].SetFont(&m_ftControl);

	m_cboTrigMode[CHANNEL_00].SubclassDlgItem(IDC_CBO_TRIG_MODE_00, this);
	m_cboTrigMode[CHANNEL_00].SetFont(&m_ftControl);
	m_cboTrigMode[CHANNEL_01].SubclassDlgItem(IDC_CBO_TRIG_MODE_01, this);
	m_cboTrigMode[CHANNEL_01].SetFont(&m_ftControl);

	m_cboActiveLevel[CHANNEL_00].SubclassDlgItem(IDC_CBO_ACTIVE_LEVEL_00, this);
	m_cboActiveLevel[CHANNEL_00].SetFont(&m_ftControl);
	m_cboActiveLevel[CHANNEL_01].SubclassDlgItem(IDC_CBO_ACTIVE_LEVEL_01, this);
	m_cboActiveLevel[CHANNEL_01].SetFont(&m_ftControl);

	m_cboDirCheck[CHANNEL_00].SubclassDlgItem(IDC_CBO_DIR_CHECK_00, this);
	m_cboDirCheck[CHANNEL_00].SetFont(&m_ftControl);
	m_cboDirCheck[CHANNEL_01].SubclassDlgItem(IDC_CBO_DIR_CHECK_01, this);
	m_cboDirCheck[CHANNEL_01].SetFont(&m_ftControl);

	m_edtUnitPulse[CHANNEL_00].SubclassDlgItem(IDC_EDT_UNIT_PULSE_00, this);
	m_edtUnitPulse[CHANNEL_00].SetFont(&m_ftControl);
	m_edtUnitPulse[CHANNEL_01].SubclassDlgItem(IDC_EDT_UNIT_PULSE_01, this);
	m_edtUnitPulse[CHANNEL_01].SetFont(&m_ftControl);

	m_edtPosUpper[CHANNEL_00].SubclassDlgItem(IDC_EDT_POS_UPPER_00, this);
	m_edtPosUpper[CHANNEL_00].SetFont(&m_ftControl);
	m_edtPosUpper[CHANNEL_01].SubclassDlgItem(IDC_EDT_POS_UPPER_01, this);
	m_edtPosUpper[CHANNEL_01].SetFont(&m_ftControl);

	m_edtPosLower[CHANNEL_00].SubclassDlgItem(IDC_EDT_POS_LOWER_00, this);
	m_edtPosLower[CHANNEL_00].SetFont(&m_ftControl);
	m_edtPosLower[CHANNEL_01].SubclassDlgItem(IDC_EDT_POS_LOWER_01, this);
	m_edtPosLower[CHANNEL_01].SetFont(&m_ftControl);

	m_edtFrequency[CHANNEL_00].SubclassDlgItem(IDC_EDT_FREQUENCY_00, this);
	m_edtFrequency[CHANNEL_00].SetFont(&m_ftControl);
	m_edtFrequency[CHANNEL_01].SubclassDlgItem(IDC_EDT_FREQUENCY_01, this);
	m_edtFrequency[CHANNEL_01].SetFont(&m_ftControl);
	
	m_edtTrigPeriod[CHANNEL_00].SubclassDlgItem(IDC_EDT_TRIG_PERIOD_00, this);
	m_edtTrigPeriod[CHANNEL_00].SetFont(&m_ftControl);
	m_edtTrigPeriod[CHANNEL_01].SubclassDlgItem(IDC_EDT_TRIG_PERIOD_01, this);
	m_edtTrigPeriod[CHANNEL_01].SetFont(&m_ftControl);
	
	m_edtPulseWidth[CHANNEL_00].SubclassDlgItem(IDC_EDT_PULSE_WIDTH_00, this);
	m_edtPulseWidth[CHANNEL_00].SetFont(&m_ftControl);
	m_edtPulseWidth[CHANNEL_01].SubclassDlgItem(IDC_EDT_PULSE_WIDTH_01, this);
	m_edtPulseWidth[CHANNEL_01].SetFont(&m_ftControl);
	  
	m_lstLog.SetFont(&m_ftControl);

	int i;
	for(i = 0; i < MAX_CHANNEL; i++){
		m_cboEncMethod[i].AddString("00:UpDownMode");
		m_cboEncMethod[i].AddString("01:Sqr1Mode");
		m_cboEncMethod[i].AddString("02:Sqr2Mode");
		m_cboEncMethod[i].AddString("03:Sqr4Mode");

		m_cboDirCheck[i].AddString("00:None");
		m_cboDirCheck[i].AddString("01:CW");
		m_cboDirCheck[i].AddString("02:CCW");

		m_cboEncSource[i].AddString("00:AB Phase");
		m_cboEncSource[i].AddString("01: Z Phase");

		m_cboTrigMode[i].AddString("00:Periodic Distance");
		m_cboTrigMode[i].AddString("01:Periodic Time");

		m_cboActiveLevel[i].AddString("00:Active Low");
		m_cboActiveLevel[i].AddString("01:Active High");
	}	

	CString strData;
	DWORD	dwModuleID;
	m_lModuleCount = 0;
	m_lModuleCount = CNTget_module_count();

	for(i = 0; i < m_lModuleCount; i++)
	{
		dwModuleID = CNTget_module_id(i);
		switch(dwModuleID){
		case AXT_SIO_CN2CH:		strData.Format(" %02ld-[PCIB-CH2: Reversible 2 Channel Counter Module]", i);	break;
		default:				strData.Format(" %02ld-[Unknown]",i);
		}

		m_cboSelModule.AddString(strData);
	}
	if(m_lModuleCount > 0){
		m_nModuleNo				= 0;
		m_nChannelNo[CHANNEL_00]= 0;
		m_nChannelNo[CHANNEL_01]= 1;

		m_cboSelModule.SetCurSel(m_nModuleNo);
	}else{
		TraceLog("ERROR: Cannot find counter modules");
		return FALSE;
	}

	SetTimer(TM_DISPLAY, 100, NULL);

	return TRUE;
}

BOOL CCounterTestDlg::UpdateState()
{
	int		i;
	WORD	wData;
	DWORD	dwFrequency;
	double	dPeriod, dLowerPos, dUpperPos, dPulseWidth, dMoveUnit;

	for(i = 0; i < MAX_CHANNEL; i++){
		dMoveUnit = 1.0;
		dMoveUnit = CNTget_moveunit_perpulse(m_nChannelNo[i]);
		SetDlgItemDouble(IDC_EDT_UNIT_PULSE_00 + i, dMoveUnit);

		wData	= 0;
		wData	= CNTget_enc_input_method(m_nChannelNo[i]);
		ConvertAxtToCombo(&m_cboEncMethod[i], wData);

		wData	= 0;
		wData	= CNTget_enc_source_sel(m_nChannelNo[i]);
		ConvertAxtToCombo(&m_cboEncSource[i], wData);

		wData	= 0;
		wData	= CNTget_trigger_direction_check(m_nChannelNo[i]);
		ConvertAxtToCombo(&m_cboDirCheck[i], wData);

		wData	= 0;
		wData	= CNTget_trigger_mode(m_nChannelNo[i]);
		ConvertAxtToCombo(&m_cboTrigMode[i], wData);
		if(wData == 0){
			m_edtPosUpper[i].EnableWindow(TRUE);
			m_edtPosLower[i].EnableWindow(TRUE);
			m_edtFrequency[i].EnableWindow(FALSE);		
		}else{
			m_edtPosUpper[i].EnableWindow(FALSE);
			m_edtPosLower[i].EnableWindow(FALSE);
			m_edtFrequency[i].EnableWindow(TRUE);
		}

		wData	= 0;
		wData	= CNTget_trigger_active_level(m_nChannelNo[i]);
		ConvertAxtToCombo(&m_cboActiveLevel[i], wData);

		dLowerPos = dUpperPos = dPeriod = 0;
		CNTget_trigger_block(m_nChannelNo[i], &dLowerPos, &dUpperPos, &dPeriod);

		SetDlgItemDouble(IDC_EDT_TRIG_PERIOD_00 + i, dPeriod);
		SetDlgItemDouble(IDC_EDT_POS_LOWER_00 + i, dLowerPos);
		SetDlgItemDouble(IDC_EDT_POS_UPPER_00 + i, dUpperPos);

		dPulseWidth = 0.0;
		dPulseWidth = CNTget_trigger_pulse_width(m_nChannelNo[i]);
		SetDlgItemDouble(IDC_EDT_PULSE_WIDTH_00 + i, dPulseWidth);

		dwFrequency	= CNTget_time_trigger_frequency(m_nChannelNo[i]);	
		SetDlgItemInt(IDC_EDT_FREQUENCY_00 + i, dwFrequency);

		CheckDlgButton(IDC_CHK_TRIG_ENABLE_00 + i, CNTget_trigger_enable(m_nChannelNo[i]));
	}
	
	return TRUE;
}

// ++ =======================================================================
// >> ConvertComboToAxt(...) : ComboBox��Ʈ�ѿ� ���� ���õ� Item Index�� ���
//    ���忡 ������ ������ �����ϴ� �Լ�.
//  - ComboBox�� ���õ� Item Index�� ���� ��Ǻ��忡 �����Ǵ� ���� �ٸ��Ƿ� 
//    ���õ� ���ڿ����� ��Ǻ��忡 ������ ���� �����ؼ� ��ȯ�ϴ� �Լ��Դϴ�.
//  - ��ȯ �� ComboBox ��Ʈ���� ����Ʈ�� ���ڷ� �����մϴ�.
//  - �� �Լ��� ����ϰ��� �� �� ����Ÿ ����� ������ ������� �����ؾߵ˴ϴ�.
//    Format) XX: String, XX=���̺귯���� ���޵� ��, String=���� ����
//    Ex) "01: HIGH", "00: COMMAND", "04: HomeSensor"
// --------------------------------------------------------------------------
DWORD CCounterTestDlg::ConvertComboToAxt(CComboBox *pCboItem)
{
	if(pCboItem == NULL)	return 0;

	CString strText;
	long	lCount, lSelData;	

	lCount = pCboItem->GetCount();
	if(lCount == 0)		return 0;

	lSelData = pCboItem->GetCurSel();
	if(lSelData < 0)	return 0;

	pCboItem->GetLBText(lSelData, strText);	
	return (DWORD)atoi(strText);
}

// ++ =======================================================================
// >> ConvertAxtToCombo(...) : ������ ��Ǻ��忡 �������� ComboBox��Ʈ����  
//    Item�� ��ġ�ϴ� Item�� ã�� �����ϴ� �Լ�.
//  - ���� ��Ǻ��忡 �����Ǵ� ���� ComboBox�� Item Index��  �ٸ��Ƿ� ������
//    ���� ��ġ�ϴ� Item�� ã�� �����ϰ� ���õ� Item�� Index�� ��ȯ�մϴ�.
//  - �����ϰ����ϴ� ComboBox ��Ʈ���� ����Ʈ�� ���ڷ� �����մϴ�.
//  - �� �Լ��� ����ϰ��� �� �� ����Ÿ ����� ������ ������� �����ؾߵ˴ϴ�.
//    Format) XX: String, XX=���̺귯���� ���޵� ��, String=���� ����
//    Ex) "01: HIGH", "00: COMMAND", "04: HomeSensor"
// --------------------------------------------------------------------------
long CCounterTestDlg::ConvertAxtToCombo(CComboBox *pCboItem, DWORD dwCurData)
{
	if(pCboItem == NULL)	return 0;

	long	lCount, lSelData;
	CString strText;

	lCount = pCboItem->GetCount();
	if(lCount == 0)	return 0;

	for(int i = 0; i < lCount; i++){
		pCboItem->GetLBText(i, strText);
		lSelData = atoi(strText);
		if(lSelData == (long)dwCurData){	
			pCboItem->SetCurSel(i);
			return i;
		}
	}

	pCboItem->SetCurSel(0);
	return 0;
}

// ++ =======================================================================
// >> SetDlgItemDouble(...) : double���� ������ ��Ʈ�ѿ� �����ϴ� �Լ�.
//  - ������ ��Ʈ���� ID�� double���� �Է��մϴ�. �̶� ǥ�� �� �Ҽ��� �ڸ�����
//    ������ �� �ֽ��ϴ�. (�⺻�� �Ҽ��� 3�ڸ��� ������)
//  - Edit, Static ��Ʈ�ѿ� ����� �� ������ double���� �Է��ϸ�ǹǷ� �ڵ带
//    �����ϰ� ������ �� �ֽ��ϴ�.
// --------------------------------------------------------------------------
void CCounterTestDlg::SetDlgItemDouble(int nID, double value, int nPoint)
{
	CString sTemp, sTemp2;
	sTemp2.Format("%%.%df", nPoint);
	sTemp.Format(sTemp2, value);
	GetDlgItem(nID)->SetWindowText(sTemp);
}

// ++ =======================================================================
// >> GetDlgItemDouble(...) : ������ ��Ʈ�ѿ� �����Ǿ� �ִ� �ؽ�Ʈ�� 
//    double������ ��ȯ�Ͽ� ��ȯ�ϴ� �Լ�.
//  - Edit, Static ��Ʈ�ѿ� ������ �ؽ�Ʈ�� double������ �о�鿩 �ڵ带 ����
//    �ϰ� ������ �� �ֽ��ϴ�.
// --------------------------------------------------------------------------
double CCounterTestDlg::GetDlgItemDouble(int nID)
{
	double dRet;
	CString sTemp;
	GetDlgItem(nID)->GetWindowText(sTemp);
	dRet = atof((LPCTSTR)sTemp);
	return dRet;
}

void CCounterTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	int		i, j;
	double	dCount;
	CString strData;
	UINT8	uOutput;
	UINT8	uInput;

	switch(nIDEvent){
	case TM_DISPLAY:		
		for(i = 0; i < MAX_CHANNEL; i++){
			dCount = 0.0;
			dCount = CNTget_pulse_counter(m_nChannelNo[i]);
			if(m_dCountOld[i] != dCount){				
				strData.Format("%.3lf", dCount);
				m_stcActPos[i].SetWindowText(strData);
				m_dCountOld[i] = dCount;
			}
			uOutput = CNTget_output(m_nChannelNo[i]);
			uInput	= CNTget_input(m_nChannelNo[i]);
			for(j = 0; j < MAX_INPUT; j++){
				CheckDlgButton(IDC_CHK_OUT_00 + (i * MAX_INPUT) + j, (uOutput >> j) & 0x1);
				CheckDlgButton(IDC_CHK_IN_00 + (i * MAX_INPUT) + j, (uInput >> j) & 0x1);
			}	
		}
		
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CCounterTestDlg::OnCbnSelchangeCboTrigMode00()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_00;
	DWORD	dwSetMode;
	
	dwSetMode	= ConvertComboToAxt(&m_cboTrigMode[nSelChannel]);
	bRetCode	= CNTset_trigger_mode(m_nChannelNo[nSelChannel], (UINT8)dwSetMode);
	
	if(dwSetMode == 0){
		m_edtPosUpper[nSelChannel].EnableWindow(TRUE);
		m_edtPosLower[nSelChannel].EnableWindow(TRUE);
		m_edtFrequency[nSelChannel].EnableWindow(FALSE);		
	}else{
		m_edtPosUpper[nSelChannel].EnableWindow(FALSE);
		m_edtPosLower[nSelChannel].EnableWindow(FALSE);
		m_edtFrequency[nSelChannel].EnableWindow(TRUE);
	}
	
	if(bRetCode== FALSE){
		TraceLog("ERROR: CNTset_trigger_mode(%02d, %d)", m_nChannelNo[nSelChannel], dwSetMode);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboTrigMode01()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_01;
	DWORD	dwSetMode;
	
	dwSetMode	= ConvertComboToAxt(&m_cboTrigMode[nSelChannel]);
	bRetCode	= CNTset_trigger_mode(m_nChannelNo[nSelChannel], (UINT8)dwSetMode);
	
	if(dwSetMode == 0){
		m_edtPosUpper[nSelChannel].EnableWindow(TRUE);
		m_edtPosLower[nSelChannel].EnableWindow(TRUE);
		m_edtFrequency[nSelChannel].EnableWindow(FALSE);		
	}else{
		m_edtPosUpper[nSelChannel].EnableWindow(FALSE);
		m_edtPosLower[nSelChannel].EnableWindow(FALSE);
		m_edtFrequency[nSelChannel].EnableWindow(TRUE);
	}
	
	if(bRetCode== FALSE){
		TraceLog("ERROR: CNTset_trigger_mode(%02d, %d)", m_nChannelNo[nSelChannel], dwSetMode);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboActiveLevel00()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_00;
	UINT8	wActiveLevel;
	
	wActiveLevel= (UINT8)ConvertComboToAxt(&m_cboActiveLevel[nSelChannel]);
	bRetCode	= CNTset_trigger_active_level(m_nChannelNo[nSelChannel], wActiveLevel);
	
	if(bRetCode== FALSE){
		TraceLog("ERROR: CNTset_trigger_active_level(%02d, %d)", m_nChannelNo[nSelChannel], wActiveLevel);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboActiveLevel01()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_01;
	UINT8	wActiveLevel;
	
	wActiveLevel=  (UINT8)ConvertComboToAxt(&m_cboActiveLevel[nSelChannel]);
	bRetCode	= CNTset_trigger_active_level(m_nChannelNo[nSelChannel], wActiveLevel);
	
	if(bRetCode== FALSE){
		TraceLog("ERROR: CNTset_trigger_active_level(%02d, %d)", m_nChannelNo[nSelChannel], wActiveLevel);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboDirCheck00()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_00;
	UINT8	wDirCheck;
	
	wDirCheck =  (UINT8)ConvertComboToAxt(&m_cboDirCheck[nSelChannel]);
	bRetCode  = CNTset_trigger_direction_check(m_nChannelNo[nSelChannel], wDirCheck);
	
	if(bRetCode== FALSE){
		TraceLog("ERROR: CNTset_trigger_direction_check(%02d, %d)", m_nChannelNo[nSelChannel], wDirCheck);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboDirCheck01()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_01;
	UINT8	wDirCheck;
	
	wDirCheck =  (UINT8)ConvertComboToAxt(&m_cboDirCheck[nSelChannel]);
	bRetCode  = CNTset_trigger_direction_check(m_nChannelNo[nSelChannel], wDirCheck);
	
	if(bRetCode== FALSE){
		TraceLog("ERROR: CNTset_trigger_direction_check(%02d, %d)", m_nChannelNo[nSelChannel], wDirCheck);
	}
}

void CCounterTestDlg::OnBnClickedBtnTrigApply(UINT nID)
{
	BOOL	bRetCode;
	UINT32	dwFrequency;
	double	dLowerPos, dUpperPos, dPulseWidth, dPeriod;
	UINT	nSelChannel = nID - IDC_BTN_TRIG_APPLY_00;
	
	dPulseWidth = GetDlgItemDouble(IDC_EDT_PULSE_WIDTH_00 + nSelChannel);
	bRetCode	= CNTset_trigger_pulse_width(m_nChannelNo[nSelChannel], dPulseWidth);	
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_trigger_pulse_width(%02d, %lf)", m_nChannelNo[nSelChannel], dPulseWidth);
	}
	
	if(CNTget_trigger_mode(m_nChannelNo[nSelChannel]) == MODE_PERIODIC_DIS){
		dLowerPos	= GetDlgItemDouble(IDC_EDT_POS_LOWER_00 + nSelChannel);
		dUpperPos	= GetDlgItemDouble(IDC_EDT_POS_UPPER_00 + nSelChannel);
		dPeriod		= GetDlgItemDouble(IDC_EDT_TRIG_PERIOD_00 + nSelChannel);
		
		bRetCode	= CNTset_trigger_block(m_nChannelNo[nSelChannel], dLowerPos, dUpperPos, dPeriod);
		if(bRetCode == FALSE){
			TraceLog("ERROR: CNTset_trigger_block(%02d, %lf, %lf, %lf)", m_nChannelNo[nSelChannel], dLowerPos, dUpperPos, dPeriod);
		}	
	}else{
		dwFrequency = GetDlgItemInt(IDC_EDT_FREQUENCY_00 + nSelChannel);
		bRetCode	= CNTset_time_trigger_frequency(m_nChannelNo[nSelChannel], dwFrequency);	
		if(bRetCode == FALSE){
			TraceLog("ERROR: CNTset_time_trigger_frequency(%02d, %ld)", m_nChannelNo[nSelChannel], dwFrequency);
		}
	}
}

void CCounterTestDlg::OnLbnDblclkLstLog()
{
	m_lstLog.ResetContent();	
}

#include <sys/timeb.h>
void CCounterTestDlg::TraceLog(char *fmt, ...)
{
	va_list ap;
	char    buf[2048];

	CString	output_string;
	CString	error_code;
	struct _timeb time_tb;
	_ftime(&time_tb);
	CTime tim(time_tb.time);
	CString timeString = tim.Format("[%H:%M:%S]");

	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	va_end(ap);

	output_string	= timeString + buf;

	m_lstLog.AddString(output_string);
	m_lstLog.SetTopIndex(m_lstLog.GetCount() - 1);
}

void CCounterTestDlg::OnBnClickedBtnPosClear(UINT nID)
{
	BOOL	bRetCode;
	UINT	nSelChannel = nID - IDC_BTN_POS_CLEAR_00;

	bRetCode = CNTset_pulse_counter(m_nChannelNo[nSelChannel], 0.0);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_pulse_counter(%02d, %lf)", m_nChannelNo[nSelChannel], 0.0);
	}
}

void CCounterTestDlg::OnBnClickedBtnSetUnit(UINT nID)
{
	BOOL	bRetCode;
	double	dMoveUnit;
	UINT	nSelChannel = nID - IDC_BTN_SET_UNIT_00;
	
	dMoveUnit= GetDlgItemDouble(IDC_EDT_UNIT_PULSE_00 + nSelChannel);
	bRetCode = CNTset_moveunit_perpulse(m_nChannelNo[nSelChannel], dMoveUnit);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_moveunit_perpulse(%02d, %lf)", m_nChannelNo[nSelChannel], dMoveUnit);
	}
}

void CCounterTestDlg::OnBnClickedChkEncReverse(UINT nID)
{
	BOOL	bRetCode;
	UINT8	uReverse;
	UINT	nSelChannel = nID - IDC_BTN_POS_CLEAR_00;
	
	uReverse = IsDlgButtonChecked(nID);
	bRetCode = CNTset_enc_reverse(m_nChannelNo[nSelChannel], uReverse);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_enc_reverse(%02d, %d)", m_nChannelNo[nSelChannel], uReverse);
	}
}

void CCounterTestDlg::OnBnClickedChkOut0(UINT nID)
{
	BOOL	bRetCode;
	UINT8	uOutput;
	UINT	nBit = nID - IDC_CHK_OUT_00;
	
	uOutput	 = IsDlgButtonChecked(nID);
	bRetCode = CNTchange_output_bit(m_nChannelNo[CHANNEL_00], nBit, uOutput);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTchange_output_bit(%02d, %d, %d)", m_nChannelNo[CHANNEL_00], nBit, uOutput);
	}
}

void CCounterTestDlg::OnBnClickedChkOut1(UINT nID)
{
	BOOL	bRetCode;
	UINT8	uOutput;
	UINT	nBit = nID - IDC_CHK_OUT_10;
	
	uOutput	 = IsDlgButtonChecked(nID);
	bRetCode = CNTchange_output_bit(m_nChannelNo[CHANNEL_01], nBit, uOutput);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTchange_output_bit(%02d, %d, %d)", m_nChannelNo[CHANNEL_01], nBit, uOutput);
	}
}

void CCounterTestDlg::OnBnClickedChkTrigEnable(UINT nID)
{
	BOOL	bRetCode;
	UINT	nSelChannel = nID - IDC_CHK_TRIG_ENABLE_00;
	
	if(CNTget_trigger_enable(m_nChannelNo[nSelChannel])){
		bRetCode = CNTset_trigger_disable(m_nChannelNo[nSelChannel]);
		if(bRetCode == FALSE){
			TraceLog("ERROR: CNTset_trigger_disable(%02d)", m_nChannelNo[nSelChannel]);
		}
	}else{
		bRetCode = CNTset_trigger_enable(m_nChannelNo[nSelChannel]);
		if(bRetCode == FALSE){
			TraceLog("ERROR: CNTset_trigger_enable(%02d)", m_nChannelNo[nSelChannel]);
		}
	}
}

void CCounterTestDlg::OnCbnSelchangeCboSelModule()
{
	UINT16	lModultNo, lChannelNo;
	lModultNo = (UINT16)ConvertComboToAxt(&m_cboSelModule);
	if(lModultNo > -1 && lModultNo >= m_lModuleCount){
		return;
	}

	if(lModultNo == m_nModuleNo)	return;

	lChannelNo	= 0;
	m_nModuleNo = lModultNo;

	m_nChannelNo[CHANNEL_00] = lModultNo * 2;
	m_nChannelNo[CHANNEL_01] = m_nChannelNo[CHANNEL_00] + 1;

	CString strData;
	strData.Format("Channel %02d", m_nChannelNo[CHANNEL_00]);
	m_grpChannel[CHANNEL_00].SetWindowText(strData);

	strData.Format("Channel %02d", m_nChannelNo[CHANNEL_01]);
	m_grpChannel[CHANNEL_01].SetWindowText(strData);

	UpdateState();
}

void CCounterTestDlg::OnCbnSelchangeCboEncMethod00()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_00;
	UINT8	wSetMethod;
	
	wSetMethod	= (UINT8)ConvertComboToAxt(&m_cboEncMethod[nSelChannel]);
	bRetCode	= CNTset_enc_input_method(m_nChannelNo[nSelChannel], wSetMethod);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_enc_input_method(%02d, %d)", m_nChannelNo[nSelChannel], wSetMethod);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboEncMethod01()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_01;
	UINT8	wSetMethod;
	
	wSetMethod	= (UINT8)ConvertComboToAxt(&m_cboEncMethod[nSelChannel]);
	bRetCode	= CNTset_enc_input_method(m_nChannelNo[nSelChannel], wSetMethod);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_enc_input_method(%02d, %d)", m_nChannelNo[nSelChannel], wSetMethod);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboEncSource00()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_00;
	UINT8	wSetMethod;
	
	wSetMethod	= (UINT8)ConvertComboToAxt(&m_cboEncSource[nSelChannel]);
	bRetCode	= CNTset_enc_source_sel(m_nChannelNo[nSelChannel], wSetMethod);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_enc_source_sel(%02d, %d)", m_nChannelNo[nSelChannel], wSetMethod);
	}
}

void CCounterTestDlg::OnCbnSelchangeCboEncSource01()
{
	BOOL	bRetCode;
	UINT	nSelChannel = CHANNEL_01;
	UINT8	wSetMethod;
	
	wSetMethod	= (UINT8)ConvertComboToAxt(&m_cboEncSource[nSelChannel]);
	bRetCode	= CNTset_enc_source_sel(m_nChannelNo[nSelChannel], wSetMethod);
	if(bRetCode == FALSE){
		TraceLog("ERROR: CNTset_enc_source_sel(%02d, %d)", m_nChannelNo[nSelChannel], wSetMethod);
	}
}


