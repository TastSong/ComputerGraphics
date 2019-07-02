// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "InputDlg.h"
#define ROUND(x) int(x+0.5)//四舍五入
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
	ON_COMMAND(ID_MENUGasket, OnMENUGasket)
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
void CTestView::GetMaxX()//获得屏幕最大x值
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxX=Rect.right;
}

void CTestView::GetMaxY()//获得屏幕最大y值
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxY=Rect.bottom;
}

void CTestView::Gasket(CDC *pDC,int n, CP2 p1,CP2 p2,CP2 p3)//垫片函数 
{
	if(n==0) return;
	CP2 Tri[3];
	Tri[0]=(p1+p2)/2;
	Tri[1]=(p2+p3)/2;
	Tri[2]=(p1+p3)/2;
	Triangle(pDC,Tri);//绘制三角形
	Gasket(pDC,n-1,p1,(p1+p2)/2,(p1+p3)/2);
	Gasket(pDC,n-1,(p1+p2)/2,p2,(p2+p3)/2);
	Gasket(pDC,n-1,(p1+p3)/2,(p2+p3)/2,p3);
}

void CTestView::OnMENUGasket()//菜单函数
{
	// TODO: Add your command handler code here
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
		n=dlg.m_n;
	else
		return;
	RedrawWindow();
	CDC *pDC=GetDC();
	CP2 TriAngle[3];
	TriAngle[0]=CP2(100,MaxY-50);
	TriAngle[1]=CP2(100,50);
	TriAngle[2]=CP2(MaxX-100,MaxY-50);
	Triangle(pDC,TriAngle);	
	Gasket(pDC,n,TriAngle[0],TriAngle[1],TriAngle[2]);
	ReleaseDC(pDC);
}
void CTestView::Triangle(CDC *pDC,CP2 point[])//绘制直角三角形 
{
	for(int i=0;i<3;i++)
	{
		if(i==0)
			pDC->MoveTo(ROUND(point[0].x),ROUND(point[0].y));
		else
			pDC->LineTo(ROUND(point[i].x),ROUND(point[i].y));
	}
	pDC->LineTo(ROUND(point[0].x),ROUND(point[0].y));
}