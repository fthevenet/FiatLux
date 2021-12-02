// DrivesView.cpp : implementation file
//

#include "stdafx.h"
#include "fiat lux.h"
#include "DrivesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrivesView

IMPLEMENT_DYNCREATE(CDrivesView, CTreeView)

CDrivesView::CDrivesView () 
{
}

CDrivesView::~CDrivesView()
{
}


BEGIN_MESSAGE_MAP(CDrivesView, CTreeView)
	//{{AFX_MSG_MAP(CDrivesView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrivesView drawing

void CDrivesView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CDrivesView diagnostics

#ifdef _DEBUG
void CDrivesView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDrivesView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrivesView message handlers
