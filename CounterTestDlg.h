// CounterTestDlg.h : ��� ����
//

#pragma once

#define MAX_CHANNEL		2
enum{	CHANNEL_00, CHANNEL_01	};

#define MAX_INPUT		4
#define MAX_OUTPUT		4
enum{	MODE_PERIODIC_DIS, MODE_PERIODIC_TIME	};

// CCounterTestDlg ��ȭ ����
class CCounterTestDlg : public CDialog
{
// �����Դϴ�.
public:
	CCounterTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CCounterTestDlg();

	UINT16			m_lModuleCount;	
	UINT16			m_nModuleNo;
	UINT16			m_nChannelNo[MAX_CHANNEL];

	double			m_dCountOld[MAX_CHANNEL];

	CComboBox		m_cboSelModule;
	CStatic			m_grpChannel[MAX_CHANNEL];

	CStatic			m_stcActPos[MAX_CHANNEL];
	CButton			m_btnPosClear[MAX_CHANNEL];
	CComboBox		m_cboEncMethod[MAX_CHANNEL];
	CComboBox		m_cboEncSource[MAX_CHANNEL];
	CComboBox		m_cboTrigMode[MAX_CHANNEL];
	CComboBox		m_cboActiveLevel[MAX_CHANNEL];
	CComboBox		m_cboDirCheck[MAX_CHANNEL];

	CEdit			m_edtUnitPulse[MAX_CHANNEL];
	CEdit			m_edtPosUpper[MAX_CHANNEL];
	CEdit			m_edtPosLower[MAX_CHANNEL];
	CEdit			m_edtFrequency[MAX_CHANNEL];
	CEdit			m_edtTrigPeriod[MAX_CHANNEL];
	CEdit			m_edtPulseWidth[MAX_CHANNEL];

	CListBox		m_lstLog;
	CFont			m_ftControl;
	
	BOOL			InitLibrary();
	BOOL			InitControl();
	BOOL			UpdateState();

	void			TraceLog(char *fmt, ...);

	DWORD			ConvertComboToAxt(CComboBox *pCboItem);						// ComboBox��Ʈ�ѿ� ���� ���õ� Item Index�� ��Ǻ��忡 ������ ������ �����ϴ� �Լ�.	
	long			ConvertAxtToCombo(CComboBox *pCboItem, DWORD dwCurData);	// �������� ComboBox��Ʈ���� Item�� ��ġ�ϴ� Item�� ã�� �����ϴ� �Լ�.	
	void			SetDlgItemDouble(int nID, double value, int nPoint = 3);	// double���� ������ ��Ʈ�ѿ� �����ϴ� �Լ�
	double			GetDlgItemDouble(int nID);									// ������ ��Ʈ�ѿ� �����Ǿ� �ִ� �ؽ�Ʈ�� double������ ��ȯ�Ͽ� ��ȯ�ϴ� �Լ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_COUNTERTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnTrigApply(UINT nID);
	afx_msg void OnBnClickedChkOut0(UINT nID);
	afx_msg void OnBnClickedChkOut1(UINT nID);
	afx_msg void OnBnClickedBtnPosClear(UINT nID);
	afx_msg void OnBnClickedChkEncReverse(UINT nID);
	afx_msg void OnBnClickedChkOut(UINT nID);
	afx_msg void OnBnClickedBtnSetUnit(UINT nID);
	afx_msg void OnBnClickedChkTrigEnable(UINT nID);
	
	afx_msg void OnLbnDblclkLstLog();
	afx_msg void OnCbnSelchangeCboSelModule();
	afx_msg void OnCbnSelchangeCboTrigMode00();
	afx_msg void OnCbnSelchangeCboTrigMode01();	
	afx_msg void OnCbnSelchangeCboEncMethod00();
	afx_msg void OnCbnSelchangeCboEncMethod01();
	afx_msg void OnCbnSelchangeCboEncSource00();
	afx_msg void OnCbnSelchangeCboEncSource01();
	afx_msg void OnCbnSelchangeCboActiveLevel00();
	afx_msg void OnCbnSelchangeCboActiveLevel01();
	afx_msg void OnCbnSelchangeCboDirCheck00();
	afx_msg void OnCbnSelchangeCboDirCheck01();
};
