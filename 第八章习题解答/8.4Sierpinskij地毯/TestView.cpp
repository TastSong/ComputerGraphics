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
	ON_COMMAND(ID_MENUCarpet, OnMENUCarpet)
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

void CTestView::Carpet(CDC *pDC,CP2 p1, CP2 p2, int n)//地毯函数
{
	CClientDC dc(this);
	double Length,Width;//矩形的长和宽
	if(n==0) return;
	Length=p2.x-p1.x;Width=p2.y-p1.y;
	CRect Rect(ROUND(p1.x+Length/3),ROUND(p1.y+Width/3),ROUND(p2.x-Length/3),ROUND(p2.y-Width/3));
	pDC->Rectangle(Rect);
	Carpet(pDC,p1,CP2(p1.x+Length/3,p1.y+Width/3),n-1);//绘制生成元的矩形1
	Carpet(pDC,CP2(p1.x+Length/3,p1.y),CP2(p1.x+2*Length/3,p1.y+Width/3),n-1);//绘制生成元的矩形2
	Carpet(pDC,CP2(p1.x+2*Length/3,p1.y),CP2(p2.x,p1.y+Width/3),n-1);//绘制生成元的矩形3
	Carpet(pDC,CP2(p1.x,p1.y+Width/3),CP2(p1.x+Length/3,p1.y+2*Width/3),n-1);//绘制生成元的矩形4
	Carpet(pDC,CP2(p1.x+2*Length/3,p1.y+Width/3),CP2(p2.x,p1.y+2*Width/3),n-1);//绘制生成元的矩形5
	Carpet(pDC,CP2(p1.x,p1.y+2*Width/3),CP2(p1.x+Length/3,p2.y),n-1);//绘制生成元的矩形6
	Carpet(pDC,CP2(p1.x+Length/3,p1.y+2*Width/3),CP2(p1.x+2*Length/3,p2.y),n-1);//绘制生成元的矩形7
	Carpet(pDC,CP2(p1.x+2*Length/3,p1.y+2*Width/3),CP2(p2.x,p2.y),n-1);//绘制生成元的矩形8
}

void CTestView::OnMENUCarpet()//菜单函数 
{
	// TODO: Add your command handler code here
	GetMaxX();GetMaxY();
	CDC *pDC=GetDC();
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
		n=dlg.m_n;
	else
		return;
	RedrawWindow();
	pDC->Rectangle(0,0,MaxX,MaxY);
	Carpet(pDC,CP2(0,0),CP2(MaxX,MaxY),n);
	ReleaseDC(pDC);
}
