// TriggerTest.h : main header file for the TRIGGERTEST application
//

#if !defined(AFX_TRIGGERTEST_H__8E79C4AC_6435_4CE8_A949_9C9A4F3DED41__INCLUDED_)
#define AFX_TRIGGERTEST_H__8E79C4AC_6435_4CE8_A949_9C9A4F3DED41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTriggerTestApp:
// See TriggerTest.cpp for the implementation of this class
//

class CTriggerTestApp : public CWinApp
{
public:
	CTriggerTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTriggerTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTriggerTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRIGGERTEST_H__8E79C4AC_6435_4CE8_A949_9C9A4F3DED41__INCLUDED_)
