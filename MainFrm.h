// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6C41F9C8_C5AA_11D2_B626_002018549ABD__INCLUDED_)
#define AFX_MAINFRM_H__6C41F9C8_C5AA_11D2_B626_002018549ABD__INCLUDED_


#include "RollOverButton.h"
#include "MyDialogBar.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFiatLuxView;

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
//	CSplitterWnd m_wndSplitter;

public:
	float m_bkg_color[4];
	float m_dif_color[4];
	float m_light_color[4];
	CSplitterWnd m_wndSplitter;
	int truc;
	int col_state;
//	BOOL TR_flag;

	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	CFiatLuxView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
//	CToolBar    m_wndToolBar;
//	CToolBar    m_viewToolBar;
	CMyDialogBar	m_wndDlgBar;

	RollOverButton smooth_B, flat_B;


	BOOL m_Init_filled, m_Init_smooth, /*FacesCulling,*/ m_light;
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateTBFill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTBSmooth(CCmdUI* pCmdUI);
	afx_msg void OnColor();
	afx_msg void OnUpdateRenderoptions(CCmdUI* pCmdUI);
	afx_msg void OnRenderoptions();
	afx_msg void OnMenuShowNormal();
	afx_msg void OnUpdateMenuShowNormal(CCmdUI* pCmdUI);
	afx_msg void OnFileTxt();
	afx_msg void OnLcB();
	afx_msg void OnBkgcB();
	afx_msg void OnButton2();
	afx_msg void OnFlat();
	afx_msg void OnSmooth();
	afx_msg void OnWf();
	afx_msg void OnSolid();
	afx_msg void OnLight();
	afx_msg void OnInfo();
	afx_msg void OnBckCull();
	afx_msg void OnUpdateBckCull(CCmdUI* pCmdUI);
	afx_msg void OnShowFps();
	afx_msg void OnUpdateShowFps(CCmdUI* pCmdUI);
	afx_msg void On2light();
	afx_msg void OnUpdate2light(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnUpdateViewStyles(CCmdUI* pCmdUI);
	afx_msg void OnViewStyle(UINT nCommandID);
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6C41F9C8_C5AA_11D2_B626_002018549ABD__INCLUDED_)
