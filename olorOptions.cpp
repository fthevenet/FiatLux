// olorOptions.cpp : implementation file
//

#include "stdafx.h"
#include "fiat lux.h"
#include "olorOptions.h"
#include "colorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ColorOptions dialog


ColorOptions::ColorOptions(CWnd* pParent /*=NULL*/)
	: CDialog(ColorOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(ColorOptions)
	m_check = FALSE;
	//}}AFX_DATA_INIT
//	m_dif_flag = FALSE;
	

}


void ColorOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ColorOptions)
	DDX_Control(pDX, IDC_Amb_slid, m_Amb_slid);
	DDX_Control(pDX, IDC_COL_OBJ, m_Col_Obj);
	DDX_Control(pDX, IDC_CHECK1, m_Check_Button);
	DDX_Control(pDX, IDC_DIFCOL_B, m_dif_col_B);
	DDX_Control(pDX, IDC_STATIC_DIf, m_Static_dif);
	DDX_Control(pDX, IDC_shin_SLID, m_shine_slid);
	DDX_Control(pDX, IDC_GLOS_SLID, m_spec);
	DDX_Check(pDX, IDC_CHECK1, m_check);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ColorOptions, CDialog)
	//{{AFX_MSG_MAP(ColorOptions)
	ON_BN_CLICKED(IDC_LC_B, OnLcB)
	ON_BN_CLICKED(IDC_DIFCOL_B, OnDifcolB)
	ON_BN_CLICKED(IDC_BKGC_B, OnBkgcB)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ColorOptions message handlers

void ColorOptions::OnLcB() 
{
	int colref = ((int)(m_light_color[2] * 0xFF)) << 16;
	colref = colref | ((int)(m_light_color[1] * 0xFF)) << 8;
	colref |= (int)(m_light_color[0] * 0xFF);

	CColorDialog  color(colref,CC_FULLOPEN,NULL);

	if (color.DoModal()== IDOK)
		{
			int colref = color.GetColor();
			m_light_color[2] = (float)((colref & 0x00FF0000) >> 16) / 0xFF;
			m_light_color[1] = (float)((colref & 0x0000FF00) >> 8) / 0xFF;
			m_light_color[0] = (float)(colref & 0x000000FF) / 0xFF;
			m_light_color[3] = 1.0;

		}	
}

void ColorOptions::OnDifcolB() 
{
	int colref = ((int)(m_dif_color[2] * 0xFF)) << 16;
	colref |= ((int)(m_dif_color[1] * 0xFF)) << 8;
	colref |= (int)(m_dif_color[0] * 0xFF);

	CColorDialog  color(colref,CC_FULLOPEN,NULL);
	
	if (color.DoModal()== IDOK)
	{
		int colref = color.GetColor();
		m_dif_color[2] = (float)((colref & 0x00FF0000) >> 16) / 0xFF;
		m_dif_color[1] = (float)((colref & 0x0000FF00) >> 8) / 0xFF;
		m_dif_color[0] = (float)(colref & 0x000000FF)  / 0xFF;
		m_dif_color[3] = 1.0;

	}
}

void ColorOptions::OnBkgcB() 
{
	int colref = ((int)(m_bkg_color[2] * 0xFF)) << 16;
	colref = colref | ((int)(m_bkg_color[1] * 0xFF)) << 8;
	colref |= (int)(m_bkg_color[0] * 0xFF);

	CColorDialog  color(colref,CC_FULLOPEN,NULL);

	if (color.DoModal()== IDOK)
		{
			int colref = color.GetColor();
			m_bkg_color[2] = (float)((colref & 0x00FF0000) >> 16) / 0xFF;
			m_bkg_color[1] = (float)((colref & 0x0000FF00) >> 8) / 0xFF;
			m_bkg_color[0] = (float)(colref & 0x000000FF)  / 0xFF;
		
		}
}

BOOL ColorOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//short int lpBits[20*20*3] ;
	CBrush MyBrush;
	COLORREF crColor = 0x00FF0000;
//	CDC	*MyDC;
	

	m_shine_slid.SetRange(0,128);
	m_shine_slid.SetTicFreq(10);
	m_shine_slid.SetPos(128 - (int)m_shine_val);

	m_spec.SetRange(0,100);
	m_spec.SetTicFreq(10);
	m_spec.SetPos(100 - (int)m_spec_val);

	
	
/*	for (int i=0;i < 20*20*3;i++)
	{
		lpBits[i] = 255;
		
	}

	Mybitmap.CreateBitmap( 20, 20, 1, 16,(const void*) lpBits );
	m_Col_Obj.SetBitmap(Mybitmap);

	MyBrush.CreateSolidBrush( crColor );
	Obj_rect.SetRect( 20, 20, 20,20 );
	GetClientRect(Obj_rect);
	MyDC = GetDC();
	

	FillRect(MyDC->m_hDC, &Obj_rect, MyBrush);
//	m_Col_Obj.
	Invalidate(TRUE);*/

	if (m_dif_flag) {
		m_dif_col_B.EnableWindow(TRUE);
		m_Static_dif.EnableWindow(TRUE);
		m_Check_Button.SetCheck(0x0001);
	//	 TRUE;
	}
	else {
	//	;
		m_dif_col_B.EnableWindow(FALSE);
		m_Static_dif.EnableWindow(FALSE);
	//	m_dif_flag = FALSE;
	}

	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void ColorOptions::OnOK() 
{
	// TODO: Add extra validation here
	m_spec_val = (float)m_spec.GetPos();
	m_shine_val = (float)m_shine_slid.GetPos();



	CDialog::OnOK();
}



void ColorOptions::OnCheck1() 
{
	// TODO: Add your control notification handler code here

	m_dif_flag = m_Check_Button.GetState() & 0x0003;
	if (m_dif_flag) {
		m_dif_col_B.EnableWindow(TRUE);
		m_Static_dif.EnableWindow(TRUE);
	//	 TRUE;
	}
	else {
	//	;
		m_dif_col_B.EnableWindow(FALSE);
		m_Static_dif.EnableWindow(FALSE);
	//	m_dif_flag = FALSE;
	}

	
}
