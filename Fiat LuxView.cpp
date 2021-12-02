// Fiat LuxView.cpp : implementation of the CFiatLuxView class
//

#include "stdafx.h"
#include "Fiat Lux.h"
#include <math.h>

#include "Fiat LuxDoc.h"
#include "Fiat LuxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxView

IMPLEMENT_DYNCREATE(CFiatLuxView, CView)

BEGIN_MESSAGE_MAP(CFiatLuxView, CView)
	//{{AFX_MSG_MAP(CFiatLuxView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxView construction/destruction

CFiatLuxView::CFiatLuxView()
{
	m_hGLContext = NULL;
	m_GLPixelIndex = 0;
	m_LButtonDown = FALSE;
	m_RButtonDown = FALSE;
	m_move_light = FALSE;
	
/*
 SetTimer(NULL,             // handle of window for timer messages
            // timer identifier
  100,           // time-out value
  NULL   // address of timer procedure
);*/
 


}

CFiatLuxView::~CFiatLuxView()
{
}

BOOL CFiatLuxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS );
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxView drawing

void CFiatLuxView::OnDraw(CDC* pDC)
{
	CFiatLuxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here



}

void CFiatLuxView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	glEnable(GL_LIGHTING);
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxView diagnostics

#ifdef _DEBUG
void CFiatLuxView::AssertValid() const
{
	CView::AssertValid();
}

void CFiatLuxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFiatLuxDoc* CFiatLuxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFiatLuxDoc)));
	return (CFiatLuxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFiatLuxView message handlers
void CFiatLuxView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}


BOOL CFiatLuxView::CreateViewGLContext(HDC hDC)
{
	m_hGLContext = wglCreateContext(hDC);
	if (m_hGLContext == NULL)
	{
		return FALSE;
	}

	if (wglMakeCurrent(hDC, m_hGLContext)==FALSE)
	{
		return FALSE;
	}

	return TRUE;
}


BOOL CFiatLuxView::SetWindowPixelFormat(HDC hDC)
{
	PIXELFORMATDESCRIPTOR pixelDesc;

	pixelDesc.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion	= 1;

	pixelDesc.dwFlags	=	PFD_DRAW_TO_WINDOW | 
							PFD_SUPPORT_OPENGL | 
							PFD_DOUBLEBUFFER |
							PFD_STEREO_DONTCARE;  

	pixelDesc.iPixelType		= PFD_TYPE_RGBA;
	pixelDesc.cColorBits		= 32;
	pixelDesc.cRedBits		= 8;
	pixelDesc.cRedShift		= 16;
	pixelDesc.cGreenBits		= 8;
	pixelDesc.cGreenShift		= 8;
	pixelDesc.cBlueBits		= 8;
	pixelDesc.cBlueShift		= 0;
	pixelDesc.cAlphaBits		= 0;
	pixelDesc.cAlphaShift		= 0;
	pixelDesc.cAccumBits		= 64;	
	pixelDesc.cAccumRedBits		= 16;
	pixelDesc.cAccumGreenBits	= 16;
	pixelDesc.cAccumBlueBits	= 16;
	pixelDesc.cAccumAlphaBits	= 0;
	pixelDesc.cDepthBits		= 32;
	pixelDesc.cStencilBits		= 8;
	pixelDesc.cAuxBuffers		= 0;
	pixelDesc.iLayerType		= PFD_MAIN_PLANE;
	pixelDesc.bReserved		= 0;
	pixelDesc.dwLayerMask		= 0;
	pixelDesc.dwVisibleMask		= 0;
	pixelDesc.dwDamageMask		= 0;


	
	
	/*
	pixelDesc.dwExStyle = WS_EX_TOPMOST;
	pixelDesc. dwStyle = WS_POPUP | WS_VISIBLE;

       
*/
	m_GLPixelIndex = ChoosePixelFormat( hDC, &pixelDesc);
	if (m_GLPixelIndex==0) // Let's choose a default index.
	{
		m_GLPixelIndex = 1;	
		if (DescribePixelFormat(hDC, 
						m_GLPixelIndex, 
						sizeof(PIXELFORMATDESCRIPTOR), 
						&pixelDesc)==0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat( hDC, 
				  m_GLPixelIndex, 
				  &pixelDesc)==FALSE)
	{
		return FALSE;
	}

	return TRUE;

}

int CFiatLuxView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	HWND hWnd = GetSafeHwnd();
	HDC hDC = ::GetDC(hWnd);

	if (SetWindowPixelFormat(hDC)==FALSE)
		return 0;
	
	if (CreateViewGLContext(hDC)==FALSE)
		return 0;
	
	return 0;
	
	
}

void CFiatLuxView::OnDestroy() 
{
	
	if(wglGetCurrentContext()!=NULL) 
	{
		// make the rendering context not current
		wglMakeCurrent(NULL, NULL) ;
	}
	
	if (m_hGLContext!=NULL)
	{
		wglDeleteContext(m_hGLContext);
		m_hGLContext = NULL;
	}

	// Now the associated DC can be released.
	CView::OnDestroy();
	
}

void CFiatLuxView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	CFiatLuxDoc* pDoc = GetDocument();
	pDoc->RenderScene();

	
	SwapBuffers(dc.m_ps.hdc);


}

void CFiatLuxView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

		
	GLsizei width, height;
	GLdouble aspect;

	width = cx;
	height = cy;

	if (cy==0)
		aspect = (GLdouble)width;
	else
		aspect = (GLdouble)width/(GLdouble)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, aspect, 0.1, 180.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST); 


	
}

void CFiatLuxView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_move_light == TRUE) ShowCursor(FALSE);	
	m_LButtonDown = TRUE;
	SetCapture();
	m_LDownPos = point;
	

	CView::OnLButtonDown(nFlags, point);
}

void CFiatLuxView::OnLButtonUp(UINT nFlags, CPoint point) 
{

	if (m_move_light == TRUE) ShowCursor(TRUE);
 
	ReleaseCapture();
	m_LButtonDown = FALSE;	
	CView::OnLButtonUp(nFlags, point);
}

void CFiatLuxView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CFiatLuxDoc* pDoc = GetDocument();
	
	if (m_move_light == FALSE)
	{
	if (m_LButtonDown)
	{
		
		CSize rotate = m_LDownPos - point;
		m_LDownPos = point;
		pDoc->m_yRotate += rotate.cx/2;
		pDoc->m_xRotate += rotate.cy/2;
		InvalidateRect(NULL, FALSE);
	}
	if (m_RButtonDown)
	{
		
		
		CSize zoom = m_RDownPos - point;
		m_RDownPos = point;
	
	//	pDoc->Rescale_normal(&(pDoc->MyModel), 1/(pDoc->m_Zoom));
	
		
		pDoc->m_Zoom -= ((double)(zoom.cy) / 200) ;/// (pDoc->maxsize/3);

		if (pDoc->m_Zoom < 0)
		{
			pDoc->m_Zoom = 0.00001;
		}
	
	//	pDoc->Rescale_normal(&(pDoc->MyModel), pDoc->m_Zoom);

		
		InvalidateRect(NULL, FALSE);
	}
	}
	else
	
	if (m_LButtonDown)
	{
		
		
		CSize rotate = m_LDownPos - point;
		m_LDownPos = point;
		pDoc->m_ylight_trans += (float)(rotate.cy) / 10;
		pDoc->m_xlight_trans  -= (float)(rotate.cx) / 10;
		InvalidateRect(NULL, FALSE);
	}

	CView::OnMouseMove(nFlags, point);
}



void CFiatLuxView::OnRButtonDown(UINT nFlags, CPoint point) 
{

	CFiatLuxDoc* pDoc = GetDocument();
	m_RButtonDown = TRUE;
	SetCapture();
	m_RDownPos = point;

/*	pDoc->Rescale_normal(&(pDoc->MyModel), 1/(pDoc->m_Zoom));
	pDoc->m_ZoomNorm = 1;

	glEnable(GL_NORMALIZE);*/

	CView::OnRButtonDown(nFlags, point);
}

void CFiatLuxView::OnRButtonUp(UINT nFlags, CPoint point) 
{

	CFiatLuxDoc* pDoc = GetDocument();
	
	ReleaseCapture();
	m_RButtonDown = FALSE;	

/*	if (pDoc->TR_flag == FALSE) glDisable(GL_NORMALIZE);
	pDoc->Rescale_normal(&(pDoc->MyModel), pDoc->m_Zoom);
	pDoc->m_ZoomNorm = pDoc->m_Zoom;	*/
	
	CView::OnRButtonUp(nFlags, point);
}

BOOL CFiatLuxView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}

//DEL void CFiatLuxView::OnTimer(UINT nIDEvent) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 
//DEL 	AfxMessageBox("werw");
//DEL 	
//DEL 	CView::OnTimer(nIDEvent);
//DEL }

void CFiatLuxView::PointToVector(int x, int y, int width, int height, float v[])
{

	float d, a;

	/* project x, y onto a hemi-sphere centered within width, height. */
	v[0] = (2.0 * x - width) / width;
	v[1] = (height - 2.0 * y) / height;
	d = sqrt(v[0] * v[0] + v[1] * v[1]);
	v[2] = cos((3.14159265 / 2.0) * ((d < 1.0) ? d : 1.0));
  /*
	a = 1.0 / sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] *= a;
	v[1] *= a;
	v[2] *= a;*/


}
