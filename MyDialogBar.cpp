// MyDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "fiat lux.h"
#include "MyDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar dialog


CMyDialogBar::CMyDialogBar()


{
	//{{AFX_DATA_INIT(CMyDialogBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}



BOOL CMyDialogBar::Create(CWnd* pParent, UINT nIDTemplate,
                             UINT nStyle, UINT nID)
   {
      // Call base class create to create the dialog bar window.
      BOOL bReturn = CDialogBar::Create(pParent, nIDTemplate,
                                        nStyle, nID);
      // Load bitmaps for the button and attach
      // to the control in the dialog box.
      if (bReturn){
		    
		  smooth_B.AutoLoad(IDC_SMOOTH, this);
		  flat_B.AutoLoad(IDC_FLAT, this);
		  wf_B.AutoLoad(IDC_WF, this);
		  solid_B.AutoLoad(IDC_SOLID, this);
		  light_B.AutoLoad(IDC_LIGHT, this);
		  info_B.AutoLoad(IDC_INFO, this);
		  color_B.AutoLoad(IDC_COLOR, this);


	//	smooth_B.SetButtonStyle(BS_AUTOCHECKBOX|BS_OWNERDRAW, TRUE);

	  }

      return bReturn;
   }




BEGIN_MESSAGE_MAP(CMyDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(CMyDialogBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDialogBar message handlers
