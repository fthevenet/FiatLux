#if !defined(AFX_INFO_H__E37C2580_3B83_11D3_91A9_00105A3DECD6__INCLUDED_)
#define AFX_INFO_H__E37C2580_3B83_11D3_91A9_00105A3DECD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Info.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog

class CInfo : public CDialog
{
// Construction
public:
	CInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfo)
	enum { IDD = IDD_INFO };
	CEdit	m_surf_ctrl;
	CString	m_gl_ext;
	CString	m_gl_render;
	CString	m_gl_vendor;
	CString	m_gl_version;
	CString	m_surf;
	CString	m_vertices;
	CString	m_quads;
	CString	m_triangles;
	CString	m_tt;
	CString	m_surfaces;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFO_H__E37C2580_3B83_11D3_91A9_00105A3DECD6__INCLUDED_)
