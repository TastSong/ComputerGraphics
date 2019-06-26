// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#define   ROUND(a) int(a+0.5) //四舍五入
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
	ON_COMMAND(ID_MENUEdgeFill, OnMENUEdgeFill)
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
	FillColor=RGB(0,0,0);
	Point[0]=CPoint(800,200);
	Point[1]=CPoint(550,250);
	Point[2]=CPoint(350,50);
	Point[3]=CPoint(250,300);
	Point[4]=CPoint(350,600);
	Point[5]=CPoint(500,400);
	Point[6]=CPoint(600,600);	
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
	MinX=Point[0].x;MaxX=Point[0].x;
	MinY=Point[0].y;MaxY=Point[0].y;
	DrawPolygon();//绘制多边形
	for(int i=0;i<=6;i++)
	{
		if(Point[i].x>MaxX)
		{
			MaxX=Point[i].x;
		}
		if(Point[i].x<MinX)
		{
			MinX=Point[i].x;
		}
		if(Point[i].y>MaxY)
		{
			MaxY=Point[i].y;
		}
		if(Point[i].y<MinY)
		{
			MinY=Point[i].y;
		}		
	}
	DrawFrame();//绘制外接矩形
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
void CTestView::Fill()//填充函数 
{
	COLORREF BackColor=RGB(255,255,255);//背景色为白色
	CClientDC dc(this);
	int m,n;
	int LowerY,LargerY;	
	double x,y,k;
	for(int i=0;i<=6;i++)
	{
		m=i,n=i+1;
		n=(i+1)%7;
		k=(double(Point[m].x-Point[n].x))/(Point[m].y-Point[n].y);//计算1/k	
		if(Point[m].y<Point[n].y)//得到每条边的y最大值和y最小值
		{
			LowerY=Point[m].y;
			LargerY=Point[n].y;
			x=Point[m].x;//得到x|ymin
		}
		else
		{
			LowerY=Point[n].y;
			LargerY=Point[m].y;
			x=Point[n].x;
		}
		for(y=LowerY;y<LargerY;y++)//对每一条边填充
		{			
			for(int j=ROUND(x);j<MaxX;j++)
			{
				if(dc.GetPixel(j,ROUND(y))==FillColor)
					dc.SetPixel(j,ROUND(y),BackColor);
				else
					dc.SetPixel(j,ROUND(y),FillColor);
			}
			x+=k;//计算下一个x起点坐标
			DrawPolygon();//重绘多边形
			DrawFrame();//重绘外接矩形
		}		
	}	
}

void CTestView::DrawPolygon()//绘制多边形
{
	CClientDC dc(this);
	int m,n;
	for(int j=0;j<=6;j++)
	{
		m=j,n=j+1;
		if(7==n) n=0;
		dc.MoveTo(Point[m]);
		dc.LineTo(Point[n]);
	}
}
void CTestView::DrawFrame()//绘制外接矩形
{
	CClientDC dc(this);
	dc.MoveTo(MinX,MinY);
	dc.LineTo(MinX,MaxY);
	dc.LineTo(MaxX,MaxY);
	dc.LineTo(MaxX,MinY);
	dc.LineTo(MinX,MinY);
}
void CTestView::OnMENUEdgeFill()//菜单函数 
{
	// TODO: Add your command handler code here
	CColorDialog ccd(FillColor);
	if(ccd.DoModal()==IDOK)
	{
		FillColor=ccd.GetColor();
	}
	RedrawWindow();
	Fill();
}


