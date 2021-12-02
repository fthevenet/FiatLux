// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Fiat Lux.h"
#include "Fiat LuxDoc.h"
#include "MainFrm.h"
#include "LeftView.h"
#include "Fiat LuxView.h"
#include "olorOptions.h"
//#include "FiatLuxControlBar.h"
//#include "TestButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_TB_Fill, OnUpdateTBFill)
	ON_UPDATE_COMMAND_UI(ID_TB_Smooth, OnUpdateTBSmooth)
	ON_COMMAND(ID_Color, OnColor)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS, OnUpdateRenderoptions)
	ON_COMMAND(ID_RENDEROPTIONS, OnRenderoptions)
	ON_COMMAND(ID_MENU_SHOW_NORMAL, OnMenuShowNormal)
	ON_UPDATE_COMMAND_UI(ID_MENU_SHOW_NORMAL, OnUpdateMenuShowNormal)
	ON_COMMAND(ID_FILE_TXT, OnFileTxt)
	ON_BN_CLICKED(IDC_LC_B, OnLcB)
	ON_BN_CLICKED(IDC_BKGC_B, OnBkgcB)
	ON_BN_CLICKED(IDC_FLAT, OnFlat)
	ON_BN_CLICKED(IDC_SMOOTH, OnSmooth)
	ON_BN_CLICKED(IDC_WF, OnWf)
	ON_BN_CLICKED(IDC_SOLID, OnSolid)
	ON_BN_CLICKED(IDC_LIGHT, OnLight)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_COMMAND(MENU_BCK_CULL, OnBckCull)
	ON_UPDATE_COMMAND_UI(MENU_BCK_CULL, OnUpdateBckCull)
	ON_COMMAND(MENU_SHOW_FPS, OnShowFps)
	ON_UPDATE_COMMAND_UI(MENU_SHOW_FPS, OnUpdateShowFps)
	ON_COMMAND(MENU_2LIGHT, On2light)
	ON_UPDATE_COMMAND_UI(MENU_2LIGHT, OnUpdate2light)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnUpdateViewStyles)
	ON_COMMAND_RANGE(AFX_ID_VIEW_MINIMUM, AFX_ID_VIEW_MAXIMUM, OnViewStyle)
END_MESSAGE_MAP()


static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
//	ID_INDICATOR_CAPS,
//	ID_INDICATOR_NUM,
//	ID_INDICATOR_SCRL,
//	ID_FPS,
//	ID_EDIT_COPY
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{

	m_Init_filled = TRUE;
	m_Init_smooth = TRUE;
	truc = 0;
	m_light = FALSE;
//	FacesCulling = TRUE;
	
	 
	
	
	
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct)== -1)
		return -1;
/*	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_viewToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_viewToolBar.LoadToolBar(IDR_VIEW_TOOLB))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
*/
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


		 
	



	if (!m_wndDlgBar.Create(this, IDD_TOOLBAR,
		 WS_CHILD | WS_VISIBLE | CBRS_RIGHT
		| /*CBRS_GRIPPER |*/ CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, IDD_TOOLBAR))
	{
		TRACE0("Failed to create DlgBar\n");
		return -1;      // fail to create
	}



/*	m_wndDlgBar.EnableDocking(CBRS_ALIGN_RIGHT|CBRS_FLOAT_MULTI);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndDlgBar);

*/


	int strPartDim[4]= {80, 160, 240, -1};
	


/*	m_viewToolBar.SetButtonStyle(0, TBBS_CHECKGROUP);
	m_viewToolBar.SetButtonStyle(1, TBBS_CHECKGROUP);
	m_viewToolBar.SetButtonStyle(3, TBBS_CHECKGROUP);
	m_viewToolBar.SetButtonStyle(4, TBBS_CHECKGROUP);
	m_viewToolBar.SetButtonStyle(5, TBBS_CHECKGROUP);
	m_viewToolBar.SetButtonStyle(7, TBBS_CHECKBOX);
	m_viewToolBar.SetButtonStyle(8, TBBS_CHECKBOX);


	m_viewToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_viewToolBar);
	
	CFiatLuxView* pView = GetRightPane();
	CFiatLuxDoc* pDoc = pView->GetDocument();
	char str[20];
	m_wndStatusBar.SetPaneText(1,gcvt(pDoc->FPS,2,str),TRUE);*/




	
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs,
	CCreateContext* pContext)
{
	
	
	
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(220, 220), pContext) ||
//	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CFiatLuxControlBar), CSize(200, 200), pContext) ||

		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFiatLuxView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	
/*	char str[50];
	AfxMessageBox(itoa(lpcs->cy, str, 10));*/
	

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

CFiatLuxView* CMainFrame::GetRightPane()
{
	CWnd* pWnd = m_wndSplitter.GetPane(0, 1);
	CFiatLuxView* pView = DYNAMIC_DOWNCAST(CFiatLuxView, pWnd);
	return pView;
}

void CMainFrame::OnUpdateViewStyles(CCmdUI* pCmdUI)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.

	
	CFiatLuxView* pView = GetRightPane();



	// if the right-hand pane hasn't been created or isn't a view,
	// disable commands in our range

	if (pView == NULL)
		pCmdUI->Enable(FALSE);
	else
	{
		DWORD dwStyle = pView->GetStyle() & LVS_TYPEMASK;

		// if the command is ID_VIEW_LINEUP, only enable command
		// when we're in LVS_ICON or LVS_SMALLICON mode

		if (pCmdUI->m_nID == ID_VIEW_LINEUP)
		{
			if (dwStyle == LVS_ICON || dwStyle == LVS_SMALLICON)
				pCmdUI->Enable();
			else
				pCmdUI->Enable(FALSE);
		}
		else
		{
			// otherwise, use dots to reflect the style of the view
			pCmdUI->Enable();
			BOOL bChecked = FALSE;

			switch (pCmdUI->m_nID)
			{
			case ID_VIEW_DETAILS:
				bChecked = (dwStyle == LVS_REPORT);
				break;

			case ID_VIEW_SMALLICON:
				bChecked = (dwStyle == LVS_SMALLICON);
				break;

			case ID_VIEW_LARGEICON:
				bChecked = (dwStyle == LVS_ICON);
				break;

			case ID_VIEW_LIST:
				bChecked = (dwStyle == LVS_LIST);
				break;

			default:
				bChecked = FALSE;
				break;
			}

			pCmdUI->SetRadio(bChecked ? 1 : 0);
		}
	}
}


void CMainFrame::OnViewStyle(UINT nCommandID)
{
	// TODO: customize or extend this code to handle choices on the
	// View menu.



}


//DEL void CMainFrame::OnTBGLinfos() 
//DEL {
//DEL 		
//DEL 	CFiatLuxView* pView = GetRightPane();
//DEL 	CFiatLuxDoc* pDoc = pView->GetDocument();
//DEL 	pDoc->disp_infos();
//DEL 
//DEL }

//DEL void CMainFrame::OnTBFill() 
//DEL {
//DEL 	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//DEL 	//CFiatLuxView* pView = GetRightPane(); 
//DEL 	//pView->SendMessage( WM_PAINT );
//DEL 	Invalidate(TRUE);
//DEL }



//DEL void CMainFrame::OnTBSmooth() 
//DEL {
//DEL 	glEnable(GL_LIGHTING);
//DEL 	CFiatLuxView* pView = GetRightPane(); 
//DEL 	CFiatLuxDoc* pDoc = pView->GetDocument();
//DEL 	//pDoc->Disp_list = pDoc->List_smooth;
//DEL 	
//DEL 	pDoc->Lighting_flag = 1;
//DEL 	if 	(pDoc->TR_flag == TRUE)
//DEL 	pDoc->build_disp_list();
//DEL //	pView->SendMessage( WM_PAINT );
//DEL 	Invalidate(TRUE);
//DEL 	
//DEL }

//DEL void CMainFrame::OnTBWireFrame() 
//DEL {
//DEL 	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//DEL //	CFiatLuxView* pView = GetRightPane(); 
//DEL //	pView->SendMessage( WM_PAINT );
//DEL 	Invalidate(TRUE);
//DEL 
//DEL }

//DEL void CMainFrame::OnTBFlat() 
//DEL {
//DEL 	glEnable(GL_LIGHTING);
//DEL 	CFiatLuxView* pView = GetRightPane(); 
//DEL 	CFiatLuxDoc* pDoc = pView->GetDocument();
//DEL //	pDoc->Disp_list = pDoc->List_flat;
//DEL 	pDoc->Lighting_flag = 2;
//DEL 
//DEL 	if 	(pDoc->TR_flag == TRUE)
//DEL 	pDoc->build_disp_list();
//DEL //	pView->SendMessage( WM_PAINT );
//DEL 	Invalidate(TRUE);
//DEL 	
//DEL }

//DEL void CMainFrame::OnTbSolid() 
//DEL {
//DEL 	
//DEL 
//DEL 	glDisable(GL_LIGHTING);
//DEL 	//CFiatLuxView* pView = GetRightPane(); 
//DEL 	//pView->SendMessage( WM_PAINT );
//DEL 	Invalidate(TRUE);
//DEL 	
//DEL 
//DEL }

void CMainFrame::OnUpdateTBFill(CCmdUI* pCmdUI) 
{
	if (m_Init_filled) {
					pCmdUI->SetCheck(1);
					m_Init_filled = FALSE;
				}
	
	
	
}

void CMainFrame::OnUpdateTBSmooth(CCmdUI* pCmdUI) 
{
	if (m_Init_smooth) {
					pCmdUI->SetCheck(1);
					m_Init_smooth = FALSE;
				}
}

//DEL void CMainFrame::OnTbBckface() 
//DEL {
//DEL 
//DEL 	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
//DEL 
//DEL 	if (pDoc->FacesCulling == FALSE)
//DEL 	{
//DEL     	pDoc->FacesCulling = TRUE;
//DEL 		glEnable(GL_CULL_FACE);
//DEL 		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
//DEL 		//CFiatLuxView* pView = GetRightPane(); 
//DEL 		//pView->SendMessage( WM_PAINT );
//DEL 		Invalidate(TRUE);
//DEL 		
//DEL 	}
//DEL     else 
//DEL 	{
//DEL 		pDoc->FacesCulling = FALSE;
//DEL 		glDisable (GL_CULL_FACE);
//DEL 		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
//DEL 		//CFiatLuxView* pView = GetRightPane(); 
//DEL 		//pView->SendMessage( WM_PAINT );
//DEL 		Invalidate(TRUE);
//DEL 		
//DEL 	}
//DEL 
//DEL }



//DEL void CMainFrame::OnTBlight() 
//DEL {
//DEL 
//DEL 	CFiatLuxView* pView = GetRightPane(); 
//DEL 	CFiatLuxDoc* pDoc = pView->GetDocument();
//DEL 	
//DEL 	if (m_light == FALSE)
//DEL 	{
//DEL 		m_light = TRUE;
//DEL 	
//DEL 		pView->m_move_light = TRUE;
//DEL 		pDoc->Move_Light_flag = TRUE;
//DEL 	}
//DEL 	else
//DEL 	{
//DEL 		m_light = FALSE;
//DEL 	
//DEL 		pView->m_move_light = FALSE;
//DEL 		pDoc->Move_Light_flag = FALSE;
//DEL 	}
//DEL 		
//DEL 	Invalidate(TRUE);
//DEL 	
//DEL }


void CMainFrame::OnColor() 
{

	// Create color option dialog
	ColorOptions color;
	CFiatLuxView* pView = GetRightPane();
	CFiatLuxDoc* pDoc = pView->GetDocument();
	for (int i=0;i<4;i++) color.m_dif_color[i] = pDoc->mat_diffuse[i];
	for (i=0;i<3;i++)  color.m_bkg_color[i] = pDoc->bkg_color[i];
	for (i=0;i<4;i++)  color.m_light_color[i] = pDoc->Light_color[i];
	color.m_dif_flag = col_state;
	color.m_spec_val = (pDoc->mat_specular[0])*100.0f;
	color.m_shine_val = pDoc->mat_shininess;
	
	if (color.DoModal() == IDOK)
	{
			
		for (i=0;i<4;i++) pDoc->mat_diffuse[i] = color.m_dif_color[i];
		for (i=0;i<3;i++) pDoc->bkg_color[i] = color.m_bkg_color[i];
		for (i=0;i<4;i++) pDoc->Light_color[i] = color.m_light_color[i];
		for (i=0;i<3;i++) pDoc->mat_specular[i] = (float)(100 - color.m_spec_val) / 100;
		pDoc->mat_shininess = 128.0f - color.m_shine_val;
		pDoc->SingleColor = color.m_dif_flag;
		col_state = color.m_dif_flag;
		pDoc->UpdateColours();
		Invalidate(TRUE);
	//	pView->SendMessage( WM_PAINT );
		
		
	
	}



}



//DEL void CMainFrame::OnUpdateFPS(CCmdUI* pCmdUI) 
//DEL {
//DEL //	CFiatLuxView* pView = GetRightPane();
//DEL //	CFiatLuxDoc* pDoc = pView->GetDocument();
//DEL //	char str[20];
//DEL //	CString fps_str;
//DEL //	fps_str = "FPS: " + (CString)gcvt(pDoc->FPS,4,str);
//DEL //	SetWindowText(fps_str);
//DEL 
//DEL //	int dec;
//DEL //	int sign;
//DEL 	
//DEL //	m_wndStatusBar.SetPaneText(1,gcvt(pDoc->FPS,2,str),TRUE);
//DEL //	pCmdUI->Enable(TRUE);
//DEL 
//DEL 
//DEL //	pCmdUI->SetText(fps_str);
//DEL 
//DEL 	
//DEL 
//DEL //	CString fps_str;
//DEL 
//DEL 
//DEL 
//DEL 		
//DEL //	fps_str = "FPS: " + (CString)gcvt(pDoc->FPS,4,str);
//DEL 	
//DEL //	CWnd* MyCWnd = AfxGetMainWnd( );
//DEL 
//DEL //	MyCWnd->SetWindowText(fps_str);
//DEL 
//DEL 
//DEL 
//DEL }




void CMainFrame::OnUpdateRenderoptions(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
		CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
		
		if (pDoc->TR_flag)	pCmdUI->SetCheck(1);

		else pCmdUI->SetCheck(0);
		

}

void CMainFrame::OnRenderoptions() 
{
	// TODO: Add your command handler code here

	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
	
	
	if (pDoc->TR_flag) {
	
		pDoc->TR_flag = FALSE;
		pDoc->Dump_disp_list();
		//glDisable(GL_NORMALIZE);

	}
	else {
		
		pDoc->TR_flag = TRUE;
		pDoc->build_disp_list();
	//	glEnable(GL_NORMALIZE);
	}


}	


void CMainFrame::OnMenuShowNormal() 
{
	// TODO: Add your command handler code here
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();

	if (pDoc->Show_Normal_flag) pDoc->Show_Normal_flag = FALSE;
		else pDoc->Show_Normal_flag = TRUE;

	Invalidate(TRUE);


	
}

void CMainFrame::OnUpdateMenuShowNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
	if (pDoc->Show_Normal_flag) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
	
	
	
}

void CMainFrame::OnFileTxt() 
{
	// TODO: Add your command handler code here
/*	CString newName;
	if(AfxGetApp()->DoPromptFileName(newName, AFX_IDS_SAVEFILE, OFN_EXTENSIONDIFFERENT | OFN_OVERWRITEPROMPT, FALSE, NULL))
	AfxMessageBox(newName);
  
	//    return; // open cancelled
*/
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
	pDoc->Save_to_txt();
/*	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for filename
	HWND hwnd;              // owner window
	//HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0C code\0*.C\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_OVERWRITEPROMPT;

	// Display the Open dialog box. 

	GetOpenFileName(&ofn);

/*	if (GetSaveFileName(&ofn)==TRUE) 
		AfxMessageBox(ofn.lpstrFile);*/

	
}

void CMainFrame::OnLcB() 
{
	// TODO: Add your control notification handler code here
	CFiatLuxDoc* pDoc = GetRightPane()->GetDocument();

	int colref = ((int)(pDoc->Light_color[2] * 0xFF)) << 16;
	colref = colref | ((int)(pDoc->Light_color[1] * 0xFF)) << 8;
	colref |= (int)(pDoc->Light_color[0] * 0xFF);

	CColorDialog color(colref,CC_FULLOPEN,NULL);

	if (color.DoModal()== IDOK)
		{
			int colref = color.GetColor();
			pDoc->Light_color[2] = (float)((colref & 0x00FF0000) >> 16) / 0xFF;
			pDoc->Light_color[1] = (float)((colref & 0x0000FF00) >> 8) / 0xFF;
			pDoc->Light_color[0] = (float)(colref & 0x000000FF) / 0xFF;
			pDoc->Light_color[3] = 1.0;

			pDoc->UpdateColours();

		}	

	Invalidate(TRUE);
/*///////////////////////////////////////////////////////////////
		ColorOptions color;
	CFiatLuxView* pView = GetRightPane();
	CFiatLuxDoc* pDoc = GetRightPane()->GetDocument();
	for (int i=0;i<4;i++) color.m_dif_color[i] = pDoc->mat_diffuse[i];
	for (i=0;i<3;i++)  color.m_bkg_color[i] = pDoc->bkg_color[i];
	for (i=0;i<4;i++)  color.m_light_color[i] = pDoc->Light_color[i];
	color.m_dif_flag = col_state;
	color.m_spec_val = (pDoc->mat_specular[0])*100.0f;
	color.m_shine_val = pDoc->mat_shininess;
	
	if (color.DoModal() == IDOK)
	{
			
		for (i=0;i<4;i++) pDoc->mat_diffuse[i] = color.m_dif_color[i];
		for (i=0;i<3;i++) pDoc->bkg_color[i] = color.m_bkg_color[i];
		for (i=0;i<4;i++) pDoc->Light_color[i] = color.m_light_color[i];
		for (i=0;i<3;i++) pDoc->mat_specular[i] = (float)(100 - color.m_spec_val) / 100;
		pDoc->mat_shininess = 128.0f - color.m_shine_val;
		pDoc->SingleColor = color.m_dif_flag;
		col_state = color.m_dif_flag;
		pDoc->UpdateColours();
		Invalidate(TRUE);

/*////////////////////////////////////////////////


}


void CMainFrame::OnBkgcB() 
{

	CFiatLuxDoc* pDoc = GetRightPane()->GetDocument();

	int colref = ((int)(pDoc->bkg_color[2] * 0xFF)) << 16;
	colref = colref | ((int)(pDoc->bkg_color[1] * 0xFF)) << 8;
	colref |= (int)(pDoc->bkg_color[0] * 0xFF);

	CColorDialog color(colref,CC_FULLOPEN,NULL);

	if (color.DoModal()== IDOK)
		{
			int colref = color.GetColor();
			pDoc->bkg_color[2] = (float)((colref & 0x00FF0000) >> 16) / 0xFF;
			pDoc->bkg_color[1] = (float)((colref & 0x0000FF00) >> 8) / 0xFF;
			pDoc->bkg_color[0] = (float)(colref & 0x000000FF)  / 0xFF;
			pDoc->UpdateColours();
		
		}	

	Invalidate(TRUE);
}


void CMainFrame::OnFlat() 
{

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glEnable(GL_LIGHTING);
	CFiatLuxView* pView = GetRightPane(); 
	CFiatLuxDoc* pDoc = pView->GetDocument();



	pDoc->Lighting_flag = 2;

	if 	(pDoc->TR_flag == TRUE)
	pDoc->build_disp_list();
	Invalidate(TRUE);

	
}

void CMainFrame::OnSmooth() 
{

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	glEnable(GL_LIGHTING);
	CFiatLuxView* pView = GetRightPane(); 
	CFiatLuxDoc* pDoc = pView->GetDocument();

	
	pDoc->Lighting_flag = 1;
	if 	(pDoc->TR_flag == TRUE)
	pDoc->build_disp_list();

	Invalidate(TRUE);	
}

void CMainFrame::OnWf() 
{
	

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glEnable(GL_LIGHTING);
	CFiatLuxView* pView = GetRightPane(); 
	CFiatLuxDoc* pDoc = pView->GetDocument();



	pDoc->Lighting_flag = 2;

	if 	(pDoc->TR_flag == TRUE)
	pDoc->build_disp_list();
	Invalidate(TRUE);
	
}

void CMainFrame::OnSolid() 
{

	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glDisable(GL_LIGHTING);
	Invalidate(TRUE);
	
}

void CMainFrame::OnLight() 
{
	CFiatLuxView* pView = GetRightPane(); 
	CFiatLuxDoc* pDoc = pView->GetDocument();
	
	if (m_light == FALSE)
	{
		m_light = TRUE;
	
		pView->m_move_light = TRUE;
		pDoc->Move_Light_flag = TRUE;
	}
	else
	{
		m_light = FALSE;
	
		pView->m_move_light = FALSE;
		pDoc->Move_Light_flag = FALSE;
	}
		
	Invalidate(TRUE);
	
}

void CMainFrame::OnInfo() 
{
			
	CFiatLuxView* pView = GetRightPane();
	CFiatLuxDoc* pDoc = pView->GetDocument();
	pDoc->disp_infos();	
}

void CMainFrame::OnBckCull() 
{
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();

	if (pDoc->FacesCulling == FALSE)
	{
    	pDoc->FacesCulling = TRUE;
		glEnable(GL_CULL_FACE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
		Invalidate(TRUE);
		
	}
    else 
	{
		pDoc->FacesCulling = FALSE;
		glDisable (GL_CULL_FACE);
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
		Invalidate(TRUE);
		
	}
}

void CMainFrame::OnUpdateBckCull(CCmdUI* pCmdUI) 
{

	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
	
	if (pDoc->FacesCulling) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);	
}

void CMainFrame::OnShowFps() 
{
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();

	if (pDoc->ShowFPS) pDoc->ShowFPS = FALSE;
	else pDoc->ShowFPS = TRUE;

}

void CMainFrame::OnUpdateShowFps(CCmdUI* pCmdUI) 
{

	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
	
	if (pDoc->ShowFPS) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);	

}

void CMainFrame::On2light() 
{
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();

	if (pDoc->TwoLights){
		pDoc->TwoLights = FALSE;
		glDisable(GL_LIGHT2);

		pDoc->m_xlight_trans = 0.0f;
		pDoc->m_ylight_trans = 0.0f;

	}
	else {
		pDoc->TwoLights = TRUE;
		glEnable(GL_LIGHT2);
		pDoc->m_xlight_trans = -2.0f;
		pDoc->m_ylight_trans = 2.0f;
	}

	float Light_position[]  = { pDoc->m_xlight_trans, pDoc->m_ylight_trans, 5.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, Light_position);


	Invalidate(TRUE);
}

void CMainFrame::OnUpdate2light(CCmdUI* pCmdUI) 
{
	CFiatLuxDoc* pDoc = (GetRightPane())->GetDocument();
	
	if (pDoc->TwoLights) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

//DEL void CMainFrame::OnChecktest() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL }
