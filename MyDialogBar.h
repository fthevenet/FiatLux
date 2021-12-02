#if !defined(AFX_MYDIALOGBAR_H__58D1F735_1791_11D4_B083_00105A3DECD6__INCLUDED_)
#define AFX_MYDIALOGBAR_H__58D1F735_1791_11D4_B083_00105A3DECD6__INCLUDED_
#include "RollOverButton.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyDialogBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar dialog

class CMyDialogBar : public CDialogBar
{
// Construction
public:
	CMyDialogBar();   // standard constructor
	Create(CWnd* pParent, UINT nIDTemplate, UINT nStyle, UINT nID);

// Dialog Data
	//{{AFX_DATA(CMyDialogBar)
	enum { IDD = IDD_Progress };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDialogBar)
	protected:

	//}}AFX_VIRTUAL

// Implementation
protected:

	RollOverButton smooth_B, flat_B, solid_B, wf_B, light_B, info_B, color_B;


	// Generated message map functions
	//{{AFX_MSG(CMyDialogBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYDIALOGBAR_H__58D1F735_1791_11D4_B083_00105A3DECD6__INCLUDED_)
