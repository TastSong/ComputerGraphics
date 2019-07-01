// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "math.h"//调用数学头文件
#define ROUND(a) int(a+0.5)//四舍五入
#define N_MAX_POINT 10//控制多边形的最大顶点数
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
	ON_COMMAND(ID_MENUBezierCurve, OnMENUBezierCurve)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
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

void CTestView::OnMENUBezierCurve() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	MessageBox("单击左键绘制特征多边形，单击右键绘制曲线","提示",MB_OK);
	pt=new CPoint [N_MAX_POINT];
	Flag=true;CtrlPoint=0;
}
void CTestView::DrawBezier()//绘制Bezier曲线	
{
	CClientDC dc(this);
	int rate=500,n;
	n=CtrlPoint-1;
	double x,y;
	double px[N_MAX_POINT],py[N_MAX_POINT];
	for(int k=0;k<=n;k++)
	{
		px[k]=pt[k].x;
		py[k]=pt[k].y;
	}
    for(double t=0;t<=1;t+=0.01/rate)
	{
		x=DeCasteliau(t,px);
		y=DeCasteliau(t,py); 
        dc.SetPixel(ROUND(x),ROUND(y),RGB(0,0,255));
	}
}

double CTestView::DeCasteliau(double t,double p[])//德卡斯特里奥函数
{
	double pp[N_MAX_POINT][N_MAX_POINT];
	int n=CtrlPoint-1;
	for(int k=0;k<=n;k++)
	{
		pp[k][0]=p[k];
	}
	for(int r=1;r<=n;r++)
	{
		for(int i=0;i<=n-r;i++)
		{ 
			pp[i][r]=(1-t)*pp[i][r-1]+t*pp[i+1][r-1];
		} 
    }
    return(pp[0][n]);
}

void CTestView::DrawCharPolygon()//绘制控制多边形
{
	CClientDC dc(this);	
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	OldPen=dc.SelectObject(&NewPen);
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
	dc.SelectObject(OldPen);
	NewPen.DeleteObject();
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
		Flag=FALSE;
		DrawBezier();
	}
	CView::OnRButtonDown(nFlags, point);
}
