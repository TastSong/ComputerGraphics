// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "InputDlg.h"
#include "math.h"//��ѧͷ�ļ�
#define ROUND(x) int(x+0.5)//��������
#define DX d*cos(PI/4)//б��ͶӰ
#define PI 3.1415926//Բ����
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(ID_MENUDponge, OnMENUDponge)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers
void CTestView::Sponge(CDC *pDC,int n, CP2 p, double d)
{
	if(n==0)
	{
		Cubicf(pDC,p,d);//����������ǰ��
		Cubict(pDC,p,d);//���������嶥��
		Cubicr(pDC,p,d);//��������������
		return;
	}
	d=d/3;
	Sponge(pDC,n-1,CP2(p.x+2*DX,p.y+2*d-2*DX),d);//���1
	Sponge(pDC,n-1,CP2(p.x+2*DX+d,p.y+2*d-2*DX),d);//���2
	Sponge(pDC,n-1,CP2(p.x+2*DX+2*d,p.y+2*d-2*DX),d);//���3
	Sponge(pDC,n-1,CP2(p.x+DX,p.y+2*d-DX),d);//���4
	Sponge(pDC,n-1,CP2(p.x+DX+2*d,p.y+2*d-DX),d);//���5
	Sponge(pDC,n-1,CP2(p.x,p.y+2*d),d);//���6
	Sponge(pDC,n-1,CP2(p.x+d,p.y+2*d),d);//���7
	Sponge(pDC,n-1,CP2(p.x+2*d,p.y+2*d),d);//���8
	Sponge(pDC,n-1,CP2(p.x+2*DX,p.y+d-2*DX),d);//���9
	Sponge(pDC,n-1,CP2(p.x+2*DX+2*d,p.y+d-2*DX),d);//���10
	Sponge(pDC,n-1,CP2(p.x,p.y+d),d);//���11
	Sponge(pDC,n-1,CP2(p.x+2*d,p.y+d),d);//���12
	Sponge(pDC,n-1,CP2(p.x+2*DX,p.y-2*DX),d);//���13
	Sponge(pDC,n-1,CP2(p.x+2*DX+d,p.y-2*DX),d);//���14
	Sponge(pDC,n-1,CP2(p.x+2*DX+2*d,p.y-2*DX),d);//���15
	Sponge(pDC,n-1,CP2(p.x+DX,p.y-DX),d);//���16
	Sponge(pDC,n-1,CP2(p.x+DX+2*d,p.y-DX),d);//���17
	Sponge(pDC,n-1,p,d);//���18
	Sponge(pDC,n-1,CP2(p.x+d,p.y),d);//���19
	Sponge(pDC,n-1,CP2(p.x+2*d,p.y),d);//���20
}

void CTestView::Cubicf(CDC *pDC,CP2 p,double d)//����������ǰ��ĺ���
{
	CBrush brushFront;
	brushFront.CreateSolidBrush(RGB(254,173,139));
	CBrush *pbrushOld=pDC->SelectObject(&brushFront);
	CPoint front[4];
	front[0]=CPoint(ROUND(p.x),ROUND(p.y));
	front[1]=CPoint(ROUND(p.x+d),ROUND(p.y));
	front[2]=CPoint(ROUND(p.x+d),ROUND(p.y+d));
	front[3]=CPoint(ROUND(p.x),ROUND(p.y+d));
	pDC->Polygon(front, 4);
	pDC->SelectObject(pbrushOld);
	brushFront.DeleteObject();
}
void CTestView::Cubict(CDC *pDC,CP2 p, double d)//���������嶥��ĺ���
{
	CBrush brushTop;
	brushTop.CreateSolidBrush(RGB(223,122,79));
	CBrush *pbrushOld=pDC->SelectObject(&brushTop);
	CPoint top[4];
	top[0]=CPoint(ROUND(p.x),ROUND(p.y));
	top[1]=CPoint(ROUND(p.x+DX),ROUND(p.y-DX));
	top[2]=CPoint(ROUND(p.x+d+DX),ROUND(p.y-DX));
	top[3]=CPoint(ROUND(p.x+d),ROUND(p.y));
	pDC->Polygon(top, 4);
	pDC->SelectObject(pbrushOld);
	brushTop.DeleteObject();
}
void CTestView::Cubicr(CDC *pDC,CP2 p, double d)//��������������ĺ���
{
	CBrush brushRight;
	brushRight.CreateSolidBrush(RGB(177,66,66));
	CBrush *pbrushOld=pDC->SelectObject(&brushRight);
	CPoint right[4];
	right[0]=CPoint(ROUND(p.x+d),ROUND(p.y));
	right[1]=CPoint(ROUND(p.x+d+DX),ROUND(p.y-DX));
	right[2]=CPoint(ROUND(p.x+d+DX),ROUND(p.y+d-DX));
	right[3]=CPoint(ROUND(p.x+d),ROUND(p.y+d));
	pDC->Polygon(right, 4);
	pDC->SelectObject(pbrushOld);
	brushRight.DeleteObject();
}
void CTestView::OnMENUDponge() 
{
	// TODO: Add your command handler code here
	
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
		n=dlg.m_n;
	else 
		return;
	RedrawWindow();
	CDC *pDC=GetDC();
	d=300.0;//�����α߳� 	
	Sponge(pDC,n,CP2(250.0,250.0),d);
	ReleaseDC(pDC);
}
