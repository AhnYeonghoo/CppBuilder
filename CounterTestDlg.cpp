// CounterTestDlg.cpp : 구현 파일
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


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
#define TM_DISPLAY		100
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CCounterTestDlg 대화 상자
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


// CCounterTestDlg 메시지 처리기

BOOL CCounterTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	if(InitLibrary() == TRUE){
		InitControl();
		UpdateState();
	}
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCounterTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
// >> ConvertComboToAxt(...) : ComboBox콘트롤에 현재 선택된 Item Index를 모션
//    보드에 설정할 값으로 변경하는 함수.
//  - ComboBox에 선택된 Item Index와 실제 모션보드에 설정되는 값이 다르므로 
//    선택된 문자열에서 모션보드에 설정할 값을 추출해서 반환하는 함수입니다.
//  - 변환 할 ComboBox 콘트롤의 포인트를 인자로 전달합니다.
//  - 이 함수를 사용하고자 할 때 데이타 등록을 지정된 양식으로 설정해야됩니다.
//    Format) XX: String, XX=라이브러리로 전달될 값, String=인자 설명
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
// >> ConvertAxtToCombo(...) : 지정한 모션보드에 설정값과 ComboBox콘트롤의  
//    Item과 일치하는 Item을 찾아 선택하는 함수.
//  - 실제 모션보드에 설정되는 값과 ComboBox의 Item Index와  다르므로 지정한
//    값과 일치하는 Item을 찾아 선택하고 선택된 Item의 Index를 반환합니다.
//  - 변경하고자하는 ComboBox 콘트롤의 포인트를 인자로 전달합니다.
//  - 이 함수를 사용하고자 할 때 데이타 등록을 지정된 양식으로 설정해야됩니다.
//    Format) XX: String, XX=라이브러리로 전달될 값, String=인자 설명
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
// >> SetDlgItemDouble(...) : double값을 지정한 콘트롤에 설정하는 함수.
//  - 설정한 콘트롤의 ID와 double값을 입력합니다. 이때 표현 할 소숫점 자릿수를
//    지정할 수 있습니다. (기본은 소숫점 3자리로 지정됨)
//  - Edit, Static 콘트롤에 사용할 수 있으며 double값을 입력하면되므로 코드를
//    간결하게 구현할 수 있습니다.
// --------------------------------------------------------------------------
void CCounterTestDlg::SetDlgItemDouble(int nID, double value, int nPoint)
{
	CString sTemp, sTemp2;
	sTemp2.Format("%%.%df", nPoint);
	sTemp.Format(sTemp2, value);
	GetDlgItem(nID)->SetWindowText(sTemp);
}

// ++ =======================================================================
// >> GetDlgItemDouble(...) : 지정한 콘트롤에 설정되어 있는 텍스트를 
//    double값으로 변환하여 반환하는 함수.
//  - Edit, Static 콘트롤에 설정된 텍스트를 double값으로 읽어들여 코드를 간결
//    하게 구현할 수 있습니다.
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


