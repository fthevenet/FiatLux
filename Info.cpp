// Info.cpp : implementation file
//

#include "stdafx.h"
#include "fiat lux.h"
#include "Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog


CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfo)
	m_gl_ext = _T("");
	m_gl_render = _T("");
	m_gl_vendor = _T("");
	m_gl_version = _T("");
	m_surf = _T("");
	m_vertices = _T("");
	m_quads = _T("");
	m_triangles = _T("");
	m_tt = _T("");
	m_surfaces = _T("");
	//}}AFX_DATA_INIT
}


void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfo)
	DDX_Control(pDX, IDC_EDIT_SURF, m_surf_ctrl);
	DDX_Text(pDX, IDC_EDIT_GL_EXT, m_gl_ext);
	DDX_Text(pDX, IDC_EDIT_GL_RENDERER, m_gl_render);
	DDX_Text(pDX, IDC_EDIT_GL_VENDOR, m_gl_vendor);
	DDX_Text(pDX, IDC_EDIT_GL_VERSION, m_gl_version);
	DDX_Text(pDX, IDC_EDIT_SURF, m_surf);
	DDX_Text(pDX, IDC_EDIT_nb_vt, m_vertices);
	DDX_Text(pDX, IDC_EDIT_nq, m_quads);
	DDX_Text(pDX, IDC_EDIT_nt, m_triangles);
	DDX_Text(pDX, IDC_EDIT_ntt, m_tt);
	DDX_Text(pDX, IDC_EDIT_ns, m_surfaces);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfo, CDialog)
	//{{AFX_MSG_MAP(CInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers
