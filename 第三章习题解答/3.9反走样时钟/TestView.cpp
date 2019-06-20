// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5) //舍入
#define PI 3.1415926
#include "math.h"
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
	ON_COMMAND(ID_MENUClock, OnMENUClock)
	ON_WM_TIMER()
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
	r=220;//表盘的内半径
	r2=250; //表盘的外半径
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
	SetTimer(1,1000,NULL);
	DoubleBuffer();
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
void CTestView::GetMaxX()//得到客户区的最大横坐标
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxX=Rect.right;	
}

void CTestView::GetMaxY()//得到客户区最大纵坐标
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxY=Rect.bottom;	
}

void CTestView::DoubleBuffer()//双缓冲绘图
{
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(Rect.right/2,Rect.bottom/2);//屏幕中心为原点	
	CDC	MemDC,Picture;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SetMapMode(MM_ANISOTROPIC);
	MemDC.SetWindowExt(Rect.Width(),Rect.Height());
	MemDC.SetViewportExt(Rect.Width(),-Rect.Height());
	MemDC.SetViewportOrg(Rect.Width()/2,Rect.Height()/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&Picture,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	LeftClock(&MemDC);
	RightClock(&MemDC);
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
}
void CTestView::LeftClock(CDC *pDC)//绘制左面走样钟表
{
	CLine line;
	GetMaxX();GetMaxY();
	p0.x=-MaxX/4,p0.y=0;//左表的中心坐标
	DrawPlate(pDC,p0);
	//绘制时钟指针 
	CTime Time=CTime::GetCurrentTime();//取当前时间
	Thour=Time.GetHour()+Time.GetMinute()/60.0+Time.GetSecond()/3600.0;
	Tangle=Thour*2*PI/12.0;
	p1.x=p0.x+ROUND(r/2*sin(Tangle));
	p1.y=p0.y+ROUND(r/2*cos(Tangle));
	p0.c=CRGB(0.0,0.0,0.0);
	p1.c=CRGB(0.0,0.0,0.0);
	line.MoveTo(pDC,p0);line.LineTo(pDC,p1);
    //绘制分钟指针
	Thour =Time.GetMinute()+Time.GetSecond()/60.0;
	Tangle=Thour*2*PI/60.0;
	p1.x=p0.x+ROUND((r*2/3)*sin(Tangle));
	p1.y=p0.y+ROUND((r*2/3)*cos(Tangle));
	p0.c=CRGB(0.0,0.0,0.0);
	p1.c=CRGB(0.0,0.0,0.0);
	line.MoveTo(pDC,p0);line.LineTo(pDC,p1);
	//绘制秒钟指针
	Thour=Time.GetSecond();
	Tangle=Thour*2*PI/60.0;   
	p1.x=p0.x+ROUND(r*4/5*sin(Tangle));
    p1.y=p0.y+ROUND(r*4/5*cos(Tangle));
	p0.c=CRGB(0.40,0.0,0.0);
	p1.c=CRGB(0.40,0.0,0.0);
	line.MoveTo(pDC,p0);line.LineTo(pDC,p1);
	pDC->TextOut(-MaxX/4-30,300,"走样时钟");
}
void CTestView::RightClock(CDC *pDC) //绘制右面反走样钟表
{
	CALine aline;
	GetMaxX();GetMaxY();
	p0.x=MaxX/4;
	p0.y=0;
	DrawPlate(pDC,p0);
	CTime Time=CTime::GetCurrentTime();
	//计算时钟秒针的夹角
	Thour=Time.GetSecond();
	Tangle=Thour*2*PI/60.0;
	p1.x=p0.x+ROUND(r*4/5*sin(Tangle));
    p1.y=p0.y+ROUND(r*4/5*cos(Tangle));
	p0.c=CRGB(0.40,0.0,0.0);p1.c=CRGB(0.40,0.0,0.0);
	aline.AMoveTo(pDC,p0);aline.ALineTo(pDC,p1);	
	//计算时钟分针的夹角
	Thour=Time.GetMinute()+Time.GetSecond()/60.0;
	Tangle=Thour*2*PI/60.0;
	p1.x=p0.x+ROUND(r*2/3*sin(Tangle));
	p1.y=p0.y+ROUND(r*2/3*cos(Tangle));
	p0.c=CRGB(0.0,0.0,0.0);p1.c=CRGB(0.0,0.0,0.0);
	aline.AMoveTo(pDC,p0);aline.ALineTo(pDC,p1);
	//计算时针夹角
	Thour=Time.GetHour()+Time.GetMinute()/60.0+Time.GetSecond()/3600.0;
	Tangle=Thour*2*PI/12.0;
	p1.x=p0.x+ROUND(r/2*sin(Tangle));
	p1.y=p0.y+ROUND(r/2*cos(Tangle));
	p0.c=CRGB(0.0,0.0,0.0);p1.c=CRGB(0.0,0.0,0.0);
    aline.AMoveTo(pDC,p0);aline.ALineTo(pDC,p1);
	pDC->TextOut(MaxX/4-30,300,"反走样时钟");
}
void CTestView::DrawPlate(CDC*pDC,CP2 p0)//绘制表盘
{
	CBrush NewBrush1,NewBrush2,*OldBrush;
	NewBrush1.CreateSolidBrush(RGB(144,244,0));
	OldBrush=pDC->SelectObject(&NewBrush1);
	CPen NewPen,*OldPen; 
	NewPen.CreatePen(PS_SOLID,2,RGB(144,244,0));
	OldPen=pDC->SelectObject(&NewPen);
	pDC->Rectangle(ROUND(p0.x-r2),ROUND(p0.y-r2),ROUND(p0.x+r2),ROUND(p0.y+r2));//绘制外框
	pDC->SelectObject(OldBrush);
	pDC->Ellipse(ROUND(p0.x-r),ROUND(p0.y-r),ROUND(p0.x+r),ROUND(p0.y+r));//绘制内框
	pDC->SelectObject(OldPen);
	NewBrush1.DeleteObject();
	NewPen.DeleteObject();
	NewBrush2.CreateSolidBrush(RGB(244,200,20));
	OldBrush=pDC->SelectObject(&NewBrush2);
	pDC->Ellipse(ROUND(p0.x-5),ROUND(p0.y-5),ROUND(p0.x+5),ROUND(p0.y+5));//绘制表芯
	pDC->SelectObject(OldBrush);
	NewBrush2.DeleteObject();
	for(int i=1;i<=12;i++)//写表的时钟值
	{
		CString str;
		str.Format("%d",i);
		CSize size;
		size=pDC->GetTextExtent(str,str.GetLength());
		Tangle=i*2*PI/12.0;
		CP2 p;                                       //计算时钟值放置位置
		p.x=p0.x-(size.cx/2)+ROUND((r-15)*sin(Tangle));
		p.y=p0.y+(size.cy/2)+ROUND((r-15)*cos(Tangle));	
		pDC->SetTextColor(RGB(0,0,255));//输出时钟值
		pDC->TextOut(ROUND(p.x),ROUND(p.y),str);
	}	
}
void CTestView::OnMENUClock()//菜单函数 
{
	// TODO: Add your command handler code here
}

void CTestView::OnTimer(UINT nIDEvent)//定时器函数 
{
	// TODO: Add your message handler code here and/or call default
	DoubleBuffer();
	CView::OnTimer(nIDEvent);
}


