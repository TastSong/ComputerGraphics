// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//四舍五入
#define PI 3.1415926//圆周率
#include "cmath"//数学头文件

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
	ON_COMMAND(ID_MENUDraw, OnMENUDraw)
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
void CTestView::GetMaxX()//获得屏幕宽度
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxX=Rect.right;
}
void CTestView::GetMaxY()//获得屏幕高度
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxY=Rect.bottom;
}
void CTestView::ReadPointFlat()//恒定颜色正六边形点表
{
	int a=200;//正六边形外接圆半径
	for(int i=0;i<6;i++)
	{
		Pf[i].x=MaxX/4+ROUND(a*cos(i*PI/3));
		Pf[i].y=MaxY/2+ROUND(a*sin(i*PI/3));
	}
	Pf[6].x=MaxX/4;Pf[6].y=MaxY/2;//中心点
	Pf[0].c.red=0.0;Pf[0].c.green=0.0;Pf[0].c.blue=1.0;//蓝色
	Pf[1].c.red=0.0;Pf[1].c.green=1.0;Pf[1].c.blue=0.0;//绿色
	Pf[2].c.red=0.0;Pf[2].c.green=1.0;Pf[2].c.blue=1.0;//青色
	Pf[3].c.red=1.0;Pf[3].c.green=0.0;Pf[3].c.blue=0.0;//红色
	Pf[4].c.red=1.0;Pf[4].c.green=0.0;Pf[4].c.blue=1.0;//品红
	Pf[5].c.red=1.0;Pf[5].c.green=1.0;Pf[5].c.blue=0.0;//黄色
	Flag=true;
}

void CTestView::ReadPointSmooth()//渐变颜色正六边形点表
{
	int a=200;//半径
	for(int i=0;i<6;i++)
	{
		Ps[i].x=3*MaxX/4+ROUND(a*cos(i*PI/3));
		Ps[i].y=MaxY/2+ROUND(a*sin(i*PI/3));
	}
	Ps[6].x=3*MaxX/4;Ps[6].y=MaxY/2;//中心点
	Ps[0].c.red=0.0;Ps[0].c.green=0.0;Ps[0].c.blue=1.0;//蓝色
	Ps[1].c.red=0.0;Ps[1].c.green=1.0;Ps[1].c.blue=0.0;//绿色
	Ps[2].c.red=0.0;Ps[2].c.green=1.0;Ps[2].c.blue=1.0;//青色
	Ps[3].c.red=1.0;Ps[3].c.green=0.0;Ps[3].c.blue=0.0;//红色
	Ps[4].c.red=1.0;Ps[4].c.green=0.0;Ps[4].c.blue=1.0;//品红
	Ps[5].c.red=1.0;Ps[5].c.green=1.0;Ps[5].c.blue=0.0;//黄色
	Ps[6].c.red=1.0;Ps[6].c.green=1.0;Ps[6].c.blue=1.0;//白色
	Flag=false;
}

void CTestView::ReadFace()//正六边形面表
{
	//恒定颜色模型以多边形第一个顶点的单一颜色填充
	F[0].En=3;F[0].p[0]=0;F[0].p[1]=1;F[0].p[2]=6;//右下
	F[1].En=3;F[1].p[0]=1;F[1].p[1]=2;F[1].p[2]=6;//下面
	F[2].En=3;F[2].p[0]=2;F[2].p[1]=3;F[2].p[2]=6;//左下
	F[3].En=3;F[3].p[0]=3;F[3].p[1]=4;F[3].p[2]=6;//左上
	F[4].En=3;F[4].p[0]=4;F[4].p[1]=5;F[4].p[2]=6;//上面
	F[5].En=3;F[5].p[0]=5;F[5].p[1]=0;F[5].p[2]=6;//右上	
}

void CTestView::DrawHexagon(CP2 *P)//绘制正六边形
{
	CDC *pDC=GetDC();
	CPi2 Point[3];//面的二维顶点数组
	for(int nFace=0;nFace<6;nFace++)
	{
		int TotalEdge=F[nFace].En;//计算每个面的总边数
		for(int nEdge=0;nEdge<TotalEdge;nEdge++)//边循环
		{
			int PointNumber=F[nFace].p[nEdge];//面的顶点号
			Point[nEdge].x=P[PointNumber].x;
			Point[nEdge].y=ROUND(P[PointNumber].y);
			if(Flag)
				Point[nEdge].c=P[F[nFace].p[0]].c;
			else
				Point[nEdge].c=P[PointNumber].c;
		}
		fill.SetPoint(Point,3);//初始化Fill对象
		fill.CreateBucket();//建立桶表
		fill.CreateEdge();//建立边表
		fill.Gouraud(pDC);//填充三角形	
	}
}

void CTestView::OnMENUDraw()//菜单操作函数 
{
	// TODO: Add your command handler code here
	GetMaxX();GetMaxY();
	ReadPointFlat();
	ReadFace();
	DrawHexagon(Pf);
	ReadPointSmooth();
	DrawHexagon(Ps);
}
