// Fiat LuxView.h : interface of the CFiatLuxView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIATLUXVIEW_H__6C41F9CC_C5AA_11D2_B626_002018549ABD__INCLUDED_)
#define AFX_FIATLUXVIEW_H__6C41F9CC_C5AA_11D2_B626_002018549ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFiatLuxView : public CView
{
protected: // create from serialization only
	CPoint m_LDownPos;
	CPoint m_RDownPos;
	BOOL m_LButtonDown;
	BOOL m_RButtonDown;
	HGLRC m_hGLContext;
	BOOL CreateViewGLContext(HDC hDC);
	int m_GLPixelIndex;
	BOOL SetWindowPixelFormat(HDC hDC);
	CFiatLuxView();
	DECLARE_DYNCREATE(CFiatLuxView)


// Attributes
public:
	BOOL m_move_light;
	
	
	CFiatLuxDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFiatLuxView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void PointToVector(int x, int y, int width, int height, float v[]);
	virtual ~CFiatLuxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFiatLuxView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Fiat LuxView.cpp
inline CFiatLuxDoc* CFiatLuxView::GetDocument()
   { return (CFiatLuxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIATLUXVIEW_H__6C41F9CC_C5AA_11D2_B626_002018549ABD__INCLUDED_)
