// TriggerTestDlg.h : header file
//

#if !defined(AFX_TRIGGERTESTDLG_H__6EB39133_D9BE_4582_8940_849893C87169__INCLUDED_)
#define AFX_TRIGGERTESTDLG_H__6EB39133_D9BE_4582_8940_849893C87169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../../AXT(Library)/C, C++/AxtLIBDef.h"
/////////////////////////////////////////////////////////////////////////////
// CTriggerTestDlg dialog

class CTriggerTestDlg : public CDialog
{
// Construction
public:
	CTriggerTestDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL	m_bOnce;	
	UINT16	m_nIntCnt;

private:
	void	SetDlgItemDouble(UINT nID, double dValue);
	double	GetDlgItemDouble(UINT nID);
	int		GetDlgItemInt(UINT nID);

public:	
	BOOL	InitLibrary();
	void	InitFS(INT16 nAxisNo);
	void	InitControl();	
	void	InitParameter(INT16 nAxisNo, double dUnit);
	void	TriggerInterruptEnable(INT16 nAxisNo);	

// Dialog Data
	//{{AFX_DATA(CTriggerTestDlg)
	enum { IDD = IDD_TRIGGERTEST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriggerTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTriggerTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStartMove();
	afx_msg void OnStopMove();
	afx_msg void OnTriggerEanble();
	afx_msg void OnCountClear();
	afx_msg void OnBtnTrigOneshot();
	afx_msg void OnTriggerDisable();
	afx_msg void OnRdoMessage();
	afx_msg void OnRdoCallback();
	//}}AFX_MSG
	afx_msg void OnTriggerInterrupt(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()	
	CButton	m_rdoTriggerSel[3];	
	CButton m_rdoMessage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIGGERTESTDLG_H__6EB39133_D9BE_4582_8940_849893C87169__INCLUDED_)
