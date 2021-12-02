#if !defined(AFX_OLOROPTIONS_H__CC8A3586_E8FD_11D2_8999_0040051FEA90__INCLUDED_)
#define AFX_OLOROPTIONS_H__CC8A3586_E8FD_11D2_8999_0040051FEA90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// olorOptions.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ColorOptions dialog

class ColorOptions : public CDialog
{
// Construction
public:
	ColorOptions(CWnd* pParent = NULL);   // standard constructor
	
	float m_bkg_color[3];
	float m_dif_color[4];
	float m_light_color[4];
	float m_spec_val;
	float m_shine_val;
	float m_ambiant_val;
	BOOL m_dif_flag;
	CBitmap Mybitmap;
	CRect Obj_rect;

// Dialog Data
	//{{AFX_DATA(ColorOptions)
	enum { IDD = IDD_DIALOG1 };
	CSliderCtrl	m_Amb_slid;
	CStatic	m_Col_Obj;
	CButton	m_Check_Button;
	CButton	m_dif_col_B;
	CButton	m_Static_dif;
	CSliderCtrl	m_shine_slid;
	CSliderCtrl	m_spec;
	BOOL	m_check;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ColorOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ColorOptions)
	afx_msg void OnLcB();
	afx_msg void OnDifcolB();
	afx_msg void OnBkgcB();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OLOROPTIONS_H__CC8A3586_E8FD_11D2_8999_0040051FEA90__INCLUDED_)
