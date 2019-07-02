// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "InputDlg.h"//对话框
#define PI 3.1415926//圆周率
#include "math.h"//数学头文件
#define ROUND(a) int(a+0.5)//四舍五入
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
	ON_COMMAND(ID_MENUCaley, OnMENUCaley)
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
void CTestView::GetMaxX()//屏幕x方向最大值
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxX=Rect.right;
}

void CTestView::GetMaxY()//屏幕y方向最大值
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxY=Rect.bottom;
}

void CTestView::Cayley3(CDC *pDC, int n, CP2 p0, double L, double th)//Cayley三叉树
{
	double S;//树干与树枝的比例
	CP2 p1,p2,p3,p4;
	S=2.0/3.0;
	if(n==1) return;
	p1=CP2(p0.x+L*cos(th*PI/180),p0.y+L*sin(th*PI/180));
	p2=CP2(p1.x+S*L*cos((th+afa)*PI/180),p1.y+S*L*sin((th+afa)*PI/180));
	p3=CP2(p1.x+S*L*cos((th-afa)*PI/180),p1.y+S*L*sin((th-afa)*PI/180));
	p4=CP2(p1.x+S*L*cos(th*PI/180),p1.y+S*L*sin(th*PI/180));
	pDC->MoveTo(ROUND(p0.x),ROUND(MaxY-p0.y));
	pDC->LineTo(ROUND(p1.x),ROUND(MaxY-p1.y));
	pDC->LineTo(ROUND(p2.x),ROUND(MaxY-p2.y));
	pDC->MoveTo(ROUND(p1.x),ROUND(MaxY-p1.y));
	pDC->LineTo(ROUND(p3.x),ROUND(MaxY-p3.y));
	pDC->MoveTo(ROUND(p1.x),ROUND(MaxY-p1.y));
	pDC->LineTo(ROUND(p4.x),ROUND(MaxY-p4.y));
	Cayley3(pDC,n-1,p1,S*L,th+afa);
	Cayley3(pDC,n-1,p1,S*L,th-afa);
	Cayley3(pDC,n-1,p1,S*L,th);
}

void CTestView::OnMENUCaley()//菜单函数 
{
	// TODO: Add your command handler code here
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		L=dlg.m_len;
		afa=dlg.m_afa;
	}
	else 
		return;
	RedrawWindow();
	CDC *pDC=GetDC();
	GetMaxX();GetMaxY();
	CP2 p0=CP2(MaxX/2,20);;//树根
	th=90;//树干与地面的夹角
	Cayley3(pDC,n,p0,L,th);	
	ReleaseDC(pDC);
}
