// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(0,BS_OWNERDRAW); //设置按钮属性为Owner draw
	CButton::PreSubclassWindow();
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);//定义一个指向LPDRAWITEMSTRUCT的指针
    GetWindowText(ButtonText);//获取按钮文本
	ButtonRect=lpDrawItemStruct->rcItem;//获取按钮尺寸
    int nSavedDC=pDC->SaveDC();//保存设备上下文
    CBrush Brush;
    Brush.CreateSolidBrush(BackColor);//背景色画刷
    pDC->SelectObject(&Brush);   
    pDC->RoundRect(&ButtonRect,CPoint(5,5));//画圆角矩形 
	pDC->SetTextColor(RGB(255-GetRValue(BackColor),255-GetGValue(BackColor),255-GetBValue(BackColor)));//设置按钮文字颜色
	pDC->SetBkMode(TRANSPARENT);//设置背景透明模式
	pDC->DrawText(ButtonText,&ButtonRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_END_ELLIPSIS);//绘制按钮文字
	if(GetFocus()==this)//绘制矩形的焦点
	{
		CRect Rect;
		Rect.SetRect(ButtonRect.left+3,ButtonRect.top+2,ButtonRect.right-3,ButtonRect.bottom-2);//矩形尺寸
		pDC->DrawFocusRect(&Rect);//绘制焦点
	}
    pDC->RestoreDC(nSavedDC);//恢复设备上下文
}
void CColorButton::SetBkColor(COLORREF color)//设置背景颜色
{
    BackColor=color;
    Invalidate();
} 

void CColorButton::SetText(CString str)//设置按钮文本
{
    ButtonText=_T("");
    SetWindowText(str);
} 
