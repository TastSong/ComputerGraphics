// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
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
	ON_COMMAND(ID_MENUCantor, OnMENUCantor)
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
void CTestView::GetMaxX()//求屏幕最大x值
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxX=Rect.right;
}
void CTestView::GetMaxY()//求屏幕最大y值
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxY=Rect.bottom;
}
void CTestView::Cantor(CP2 a,CP2 b,int n)
{
	CClientDC dc(this);
	if(n==0)
    {
		dc.MoveTo(ROUND(a.x),ROUND(a.y+MaxY/2));
		dc.LineTo(ROUND(b.x),ROUND(b.y+MaxY/2));
		return;
     }
	c.x=a.x+(b.x-a.x)/3;c.y=a.y ;    
    Cantor(a,c,n-1);
    d.x=a.x+2*(b.x-a.x)/3;d.y=b.y ;
    Cantor(d,b,n-1);
}
void CTestView::OnMENUCantor() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	GetMaxX();GetMaxY();
	double y;int n=0;
	for(y=-250;y<=650;y+=100)
	{
		CP2 b(0,y);CP2 e(MaxX,y);
		Cantor(b,e,n);
		n+=1;
	}
}
