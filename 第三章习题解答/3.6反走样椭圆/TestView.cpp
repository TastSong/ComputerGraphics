// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "cmath"//引入数学头文件
#define   ROUND(a) int(a+0.5) //四舍五入
#define PI  3.1415926//圆周率
#include "TestDoc.h"
#include "TestView.h"
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
	ON_COMMAND(ID_APP_Ellipse, OnAPPEllipse)
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
    a=400;b=150;//椭圆的长半轴为400，段半轴为150
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

void CTestView::DoubleBuffer()//双缓冲绘图
{	
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点	
	CDC	MemDC,Picture;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SetMapMode(MM_ANISOTROPIC);
	MemDC.SetWindowExt(Rect.Width(),Rect.Height());
	MemDC.SetViewportExt(Rect.Width(),-Rect.bottom);
	MemDC.SetViewportOrg(Rect.Width()/2,Rect.Height()/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&Picture,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
    DrawAEllipse(&MemDC);//绘制反走样椭圆
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
}
void CTestView::DrawAEllipse(CDC *pDC)//绘制反走样椭圆
{
	double e,h;
	CP2 p,pc;//点的坐标
	pc.x=a*a/sqrt(a*a+b*b),pc.y=b*b/sqrt(a*a+b*b);
	for(p.x=0,p.y=b,h=b;p.x<=pc.x;p.x++)//绘制AC段
	{
		e=h-sqrt(b*b-b*b*(p.x+1)*(p.x+1)/(a*a));
		if(e>=1)
		{
			h--;
			e--;
			p.y--;
		}	
		AEllipsePointAC(pDC,p,e);
	}
	for(p.x=a,p.y=0,h=a;p.y<pc.y;p.y++)//绘制BC段
	{
		e=h-sqrt(a*a-a*a*(p.y+1)*(p.y+1)/(b*b));
		if(e>=1)
		{
			h--;
			e--;
			p.x--;
		}	
		AEllipsePointBC(pDC,p,e);
	}
}

void  CTestView::AEllipsePointAC(CDC *pDC,CP2 p,double e)//四分法画椭圆AC子函数
{
	COLORREF c1=RGB(255*e,255*e,255*e);
	COLORREF c2=RGB(255*(1.0-e),255*(1.0-e),255*(1.0-e));
	pDC->SetPixel(ROUND(p.x),ROUND(p.y),c1);//(x,y)
	pDC->SetPixel(ROUND(p.x),ROUND(p.y-1),c2);
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y),c1);//(x,-y)
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y-1),c2);
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y),c1);//(-x,-y)
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y-1),c2);
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y),c1);//(-x,y)
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y-1),c2);	
}

void CTestView::AEllipsePointBC(CDC *pDC,CP2 p,double e)//四分法画椭圆BC子函数
{	
	COLORREF c1=RGB(255*e,255*e,255*e);
	COLORREF c2=RGB(255*(1.0-e),255*(1.0-e),255*(1.0-e));
	pDC->SetPixel(ROUND(p.x),ROUND(p.y),c1);//(x,y)
	pDC->SetPixel(ROUND(p.x-1),ROUND(p.y),c2);    
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y),c1);//(x,-y)
	pDC->SetPixel(ROUND(p.x-1),-ROUND(p.y),c2);
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y),c1);//(-x,-y)
	pDC->SetPixel(-ROUND(p.x-1),-ROUND(p.y),c2);
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y),c1);//(-x,y)
	pDC->SetPixel(-ROUND(p.x-1),ROUND(p.y),c2);	
}

void CTestView::OnAPPEllipse()//菜单操作函数 
{
	// TODO: Add your command handler code here
	DoubleBuffer();
}
