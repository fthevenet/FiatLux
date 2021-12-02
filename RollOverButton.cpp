// RollOverButton.cpp : implementation file
//

#include "stdafx.h"
#include "fiat lux.h"
#include "RollOverButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RollOverButton

RollOverButton::RollOverButton()
{
}

RollOverButton::~RollOverButton()
{
}


BEGIN_MESSAGE_MAP(RollOverButton, CBitmapButton)
	//{{AFX_MSG_MAP(RollOverButton)
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RollOverButton message handlers

UINT RollOverButton::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();
	
	return CBitmapButton::OnNcHitTest(point);
}
