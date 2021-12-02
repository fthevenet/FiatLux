#if !defined(AFX_PROGESS_H__18F1DC51_EB88_11D2_899D_0040051FEA90__INCLUDED_)
#define AFX_PROGESS_H__18F1DC51_EB88_11D2_899D_0040051FEA90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Progess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgess dialog

class CProgess : public CDialog
{
// Construction
public:
	CProgess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgess)
	enum { IDD = IDD_Progress };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgess)
	public:
	virtual BOOL Create();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	CWnd* m_pParent;
	int m_nID;

	// Generated message map functions
	//{{AFX_MSG(CProgess)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGESS_H__18F1DC51_EB88_11D2_899D_0040051FEA90__INCLUDED_)
