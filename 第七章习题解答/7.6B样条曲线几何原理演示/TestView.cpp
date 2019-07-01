// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//数学头文件
#define N_MAX_POINT 20//控制多边形的最大顶点数
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
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_MENUBCurve, OnMENUBCurve)
	ON_COMMAND(ID_MENUStruct, OnMENUStruct)
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
	Flag=false;
	CtrlPoint=0;
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

void CTestView::DrawBSpline()//绘制B曲线
{
	CClientDC dc(this);
	int i,rate=10;
	long lx,ly;
	double F03,F13,F23,F33;
	lx=ROUND((pt[0].x+4.0*pt[1].x+pt[2].x)/6.0);
	ly=ROUND((pt[0].y+4.0*pt[1].y+pt[2].y)/6.0);
	dc.MoveTo(lx,ly);
	CPen NewPen(PS_SOLID,1,RGB(0,0,255));
	CPen *OldPen=dc.SelectObject(&NewPen);
	for(i=1;i<=CtrlPoint-3;i++)
	{
		for(double t=0;t<=1;t+=1.0/rate)
		{
			F03=(-t*t*t+3*t*t-3*t+1)/6;//计算F0,3(t)
			F13=(3*t*t*t-6*t*t+4)/6;//计算F1,3(t)
			F23=(-3*t*t*t+3*t*t+3*t+1)/6;//计算F2,3(t)
			F33=t*t*t/6;//计算B3,3(t)
			lx=ROUND(pt[i-1].x*F03+pt[i].x*F13+pt[i+1].x*F23+pt[i+2].x*F33);
			ly=ROUND(pt[i-1].y*F03+pt[i].y*F13+pt[i+1].y*F23+pt[i+2].y*F33);
			dc.LineTo(lx,ly);
			Sleep(100);
		}
	}
	dc.SelectObject(OldPen);
	NewPen.DeleteObject();	
}

void CTestView::DrawCharPolygon()//绘制控制多边形
{
	CClientDC dc(this);	
	CPen MyPen,*pOldPen;
	MyPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	pOldPen=dc.SelectObject(&MyPen);
	for(int i=0;i<CtrlPoint;i++)
	{
		if(i==0)
		{
			dc.MoveTo(pt[i]);
			dc.Ellipse(pt[i].x-2,pt[i].y-2,pt[i].x+2,pt[i].y+2);
		}
		else
		{
			dc.LineTo(pt[i]);
			dc.Ellipse(pt[i].x-2,pt[i].y-2,pt[i].x+2,pt[i].y+2);
		}
	}
	dc.SelectObject(pOldPen);
	MyPen.DeleteObject();
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//获得屏幕控制点坐标 
{
	// TODO: Add your message handler code here and/or call default	
	CView::OnLButtonDown(nFlags, point);
	if(Flag)
	{
		pt[CtrlPoint].x=point.x;
		pt[CtrlPoint].y=point.y;
		if(CtrlPoint<N_MAX_POINT-1)
			CtrlPoint++;
		else
			Flag=false;
		DrawCharPolygon();
	}
}

void CTestView::OnRButtonDown(UINT nFlags, CPoint point)//调用绘制函数 
{
	// TODO: Add your message handler code here and/or call default
	if(CtrlPoint!=0)
	{
		Flag=false;
		DrawBSpline();
	}
	CView::OnRButtonDown(nFlags, point);
}
void CTestView::DrawStruct()//绘制绘制几何生成原理图 
{
	CClientDC dc(this);	
	CPen NewPen(PS_DOT,1,RGB(0,0,0));
	CPen *OldPen=dc.SelectObject(&NewPen);
	int x,y;
	for(int i=1;i<=CtrlPoint-2;i++)
	{
		x=(pt[i-1].x+pt[i+1].x)/2;
		y=(pt[i-1].y+pt[i+1].y)/2;
		dc.MoveTo(pt[i].x,pt[i].y);
		dc.LineTo(x,y);
		dc.MoveTo(pt[i-1].x,pt[i-1].y);
		dc.LineTo(pt[i+1].x,pt[i+1].y);
	}
	dc.SelectObject(OldPen);
	NewPen.DeleteObject();	

}
void CTestView::OnMENUBCurve()//绘制曲线菜单函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	MessageBox("单击左键绘制控制多边形，单击右键绘制曲线","提示",MB_OK);
	pt=new CPoint[N_MAX_POINT];
	Flag=true;CtrlPoint=0;	
}

void CTestView::OnMENUStruct()//绘制几何结构菜单函数 
{
	// TODO: Add your command handler code here
	DrawStruct();
}
