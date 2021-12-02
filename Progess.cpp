// Progess.cpp : implementation file
//

#include "stdafx.h"
#include "fiat lux.h"
#include "Progess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgess dialog


CProgess::CProgess(CWnd* pParent /*=NULL*/)
	: CDialog(CProgess::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgess)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	ASSERT(pParent != NULL);

	m_pParent = pParent;
	m_nID = CProgess::IDD;
}


void CProgess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgess)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgess, CDialog)
	//{{AFX_MSG_MAP(CProgess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgess message handlers

BOOL CProgess::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CProgess::Create() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, m_pParent);
}
