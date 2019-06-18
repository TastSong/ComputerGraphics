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
	ModifyStyle(0,BS_OWNERDRAW); //���ð�ť����ΪOwner draw
	CButton::PreSubclassWindow();
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);//����һ��ָ��LPDRAWITEMSTRUCT��ָ��
    GetWindowText(ButtonText);//��ȡ��ť�ı�
	ButtonRect=lpDrawItemStruct->rcItem;//��ȡ��ť�ߴ�
    int nSavedDC=pDC->SaveDC();//�����豸������
    CBrush Brush;
    Brush.CreateSolidBrush(BackColor);//����ɫ��ˢ
    pDC->SelectObject(&Brush);   
    pDC->RoundRect(&ButtonRect,CPoint(5,5));//��Բ�Ǿ��� 
	pDC->SetTextColor(RGB(255-GetRValue(BackColor),255-GetGValue(BackColor),255-GetBValue(BackColor)));//���ð�ť������ɫ
	pDC->SetBkMode(TRANSPARENT);//���ñ���͸��ģʽ
	pDC->DrawText(ButtonText,&ButtonRect,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_END_ELLIPSIS);//���ư�ť����
	if(GetFocus()==this)//���ƾ��εĽ���
	{
		CRect Rect;
		Rect.SetRect(ButtonRect.left+3,ButtonRect.top+2,ButtonRect.right-3,ButtonRect.bottom-2);//���γߴ�
		pDC->DrawFocusRect(&Rect);//���ƽ���
	}
    pDC->RestoreDC(nSavedDC);//�ָ��豸������
}
void CColorButton::SetBkColor(COLORREF color)//���ñ�����ɫ
{
    BackColor=color;
    Invalidate();
} 

void CColorButton::SetText(CString str)//���ð�ť�ı�
{
    ButtonText=_T("");
    SetWindowText(str);
} 
