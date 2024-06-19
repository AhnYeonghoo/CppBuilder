// CCounterTest.h : main header file for the CounterTest application
//

#if !defined(AFX_CounterTest_H__6C64C185_2AD6_488F_AEB6_04AFDB2268FF__INCLUDED_)
#define AFX_CounterTest_H__6C64C185_2AD6_488F_AEB6_04AFDB2268FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CCounterTestApp:
// 이 클래스의 구현에 대해서는 CounterTest.cpp을 참조하십시오.
//
class CCounterTestApp : public CWinApp
{
public:
	CCounterTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCounterTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCounterTestApp)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CounterTest_H__6C64C185_2AD6_488F_AEB6_04AFDB2268FF__INCLUDED_)
