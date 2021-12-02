// Fiat Lux.h : main header file for the FIAT LUX application
//

#if !defined(AFX_FIATLUX_H__6C41F9C4_C5AA_11D2_B626_002018549ABD__INCLUDED_)
#define AFX_FIATLUX_H__6C41F9C4_C5AA_11D2_B626_002018549ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Fiat LuxDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxApp:
// See Fiat Lux.cpp for the implementation of this class
//

class CFiatLuxApp : public CWinApp
{
public:
	CFiatLuxApp();



//	CFiatLuxDoc* pDoc;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiatLuxApp)
	public:
	virtual BOOL InitInstance();
//	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFiatLuxApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*
#ifndef _DEBUG  // debug version in Fiat LuxView.cpp
inline CFiatLuxDoc* CFiatLuxApp::GetDocument()
   { return (CFiatLuxDoc*)m_pDocument; }
#endif
*/
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIATLUX_H__6C41F9C4_C5AA_11D2_B626_002018549ABD__INCLUDED_)
