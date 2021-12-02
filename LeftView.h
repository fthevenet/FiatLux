// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__6C41F9CE_C5AA_11D2_B626_002018549ABD__INCLUDED_)
#define AFX_LEFTVIEW_H__6C41F9CE_C5AA_11D2_B626_002018549ABD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFiatLuxDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CFiatLuxDoc* GetDocument();
	void RefreshDrive (UINT nDrive);
	CString GetPathFromItem (HTREEITEM hItem);
	BOOL ExpandPath (LPCTSTR pszPath, BOOL bSelectItem);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnSelectionChanged (CString& strPathName); 
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
	UINT InitTree ();
	BOOL AddDriveNode (CString& strDrive);
	UINT AddDirectoryNodes (HTREEITEM hItem, CString& strPathName);
	UINT AddLwoNodes (HTREEITEM hItem, CString& strPathName);
	void SetButtonState (HTREEITEM hItem, CString& strPathName);
	void UpdateButtonState (HTREEITEM hItem, CString& strPathName);
	BOOL HasSubdirectory (CString& strPathName);
	BOOL IsDriveNode (HTREEITEM hItem);
	void AddDummyNode (HTREEITEM hItem);
	HTREEITEM FindItem (HTREEITEM hItem, CString& strTarget);
	UINT DeleteChildren (HTREEITEM hItem);
	HTREEITEM GetDriveNode (HTREEITEM hItem);
	DWORD GetSerialNumber (CString& strDrive);
	BOOL IsMediaValid (CString& strPathName);
	BOOL IsPathValid (CString& strPathName);
	void RefreshDirectory (HTREEITEM hItem);
	BOOL init;
	BOOL m_lock;

	/*
	typedef struct PTHREADINFO{   
		
		UINT nDrive;
		struct PolyListStruct * NextRec;
		struct PolyListStruct * PrevRec;
		unsigned short pt_index;
		int tri_index;
		
		} THREADINFO;
	*/
	
	CImageList m_imglDrives;
	CEvent m_event;
	int m_nThreadCount;
	DWORD m_dwMediaID[20];
	CONST HANDLE *m_hThreads;


// Generated message map functions
protected:
	//{{AFX_MSG(CLeftView)
	afx_msg void OnDestroy();
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LONG OnDriveContentsChanged (UINT wParam, LONG lParam);
	afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CFiatLuxDoc* CLeftView::GetDocument()
   { return (CFiatLuxDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__6C41F9CE_C5AA_11D2_B626_002018549ABD__INCLUDED_)
