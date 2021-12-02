#if !defined(AFX_ROLLOVERBUTTON_H__58D1F732_1791_11D4_B083_00105A3DECD6__INCLUDED_)
#define AFX_ROLLOVERBUTTON_H__58D1F732_1791_11D4_B083_00105A3DECD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RollOverButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RollOverButton window

class RollOverButton : public CBitmapButton
{
// Construction
public:
	RollOverButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RollOverButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~RollOverButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(RollOverButton)
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROLLOVERBUTTON_H__58D1F732_1791_11D4_B083_00105A3DECD6__INCLUDED_)
