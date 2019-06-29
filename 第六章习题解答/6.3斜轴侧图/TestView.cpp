// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//四舍五入
#define PI 3.1415926//圆周率
#include "math.h"//数学头文件
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
	ON_COMMAND(ID_MENUDrawCube, OnMENUDrawCube)
	ON_COMMAND(ID_MENUITEMCube2, OnMENUITEMCube2)
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

void CTestView::OnDraw(CDC* pDC)//绘制坐标系
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	GetClientRect(&Rect);//获得客户区大小
	CPen MyPen,*OldPen;
	MyPen.CreatePen(PS_SOLID,3,RGB(128,128,128));
	OldPen=pDC->SelectObject(&MyPen);
	pDC->MoveTo(Rect.Width()/2,Rect.Height()/2);//绘制y轴
	pDC->LineTo(Rect.Width(),Rect.Height()/2);
	pDC->TextOut(Rect.Width()-20,Rect.Height()/2-30,"x");
	pDC->MoveTo(Rect.Width()/2,Rect.Height()/2);//绘制z轴
	pDC->LineTo(Rect.Width()/2,0);
	pDC->TextOut(Rect.Width()/2-20,10,"y");
	pDC->MoveTo(Rect.Width()/2,Rect.Height()/2);//绘制x轴
	pDC->LineTo(Rect.Width()/2-Rect.Height()/2,Rect.Height());//夹角为135°
	pDC->TextOut(Rect.Width()/2-Rect.Height()/2-20,Rect.Height()-30,"z");
	pDC->TextOut(Rect.Width()/2-20,Rect.Height()/2-20,"0");
	pDC->SelectObject(OldPen);
	MyPen.DeleteObject();
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

void CTestView::ReadPoint()//顶点表
{
	int a=200;//立方体边长
	//后面的三维坐标
	P3[0].x=0;P3[0].y=0;P3[0].z=0;//A点
	P3[1].x=0;P3[1].y=a;P3[1].z=0;//B点
	P3[2].x=0;P3[2].y=a;P3[2].z=a;//C点
	P3[3].x=0;P3[3].y=0;P3[3].z=a;//D点
	//前面的三维坐标
	P3[4].x=a;P3[4].y=0;P3[4].z=0;//E点
	P3[5].x=a;P3[5].y=a;P3[5].z=0;//F点
	P3[6].x=a;P3[6].y=a;P3[6].z=a;//G点
	P3[7].x=a;P3[7].y=0;P3[7].z=a;//H点
}
void CTestView::ReadFace()//面表
{
	//面的边数、面的顶点编号
	F[0].En=4;F[0].p[0]=0;F[0].p[1]=3;F[0].p[2]=2;F[0].p[3]=1;//后面ADCB
	F[1].En=4;F[1].p[0]=4;F[1].p[1]=5;F[1].p[2]=6;F[1].p[3]=7;//前面EFGH
	F[2].En=4;F[2].p[0]=0;F[2].p[1]=4;F[2].p[2]=7;F[2].p[3]=3;//左面AEHD
	F[3].En=4;F[3].p[0]=1;F[3].p[1]=2;F[3].p[2]=6;F[3].p[3]=5;//右面BCGF
	F[4].En=4;F[4].p[0]=3;F[4].p[1]=7;F[4].p[2]=6;F[4].p[3]=2;//顶面DHGC
	F[5].En=4;F[5].p[0]=0;F[5].p[1]=1;F[5].p[2]=5;F[5].p[3]=4;//底面ABFE
}

void CTestView::DrawCube()//绘制立方体
{
	GetClientRect(&Rect);//获得客户区大小
	CDC *pDC=GetDC();//客户区DC
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴向右，y轴向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点	
	CP2 Point[4];//定义多边形面顶点数组
	ReadPoint();
	ReadFace();
	for(int nFace=0;nFace<6;nFace++)//面循环
	{		
		for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//边循环
			Point[nEdge]=Project(P3[F[nFace].p[nEdge]]);//斜平行投影		
		Line(pDC,nFace,Point);
	}
	ReleaseDC(pDC);
}
void CTestView::Line(CDC *pDC,int nface,CP2 p[])//绘制正方形
{
	for (int i=0;i<F[nface].En;i++)
	{
		if(i==0)
			pDC->MoveTo(ROUND(p[0].x),ROUND(p[0].y));
		else
			pDC->LineTo(ROUND(p[i].x),ROUND(p[i].y));
	}
	pDC->LineTo(ROUND(p[0].x),ROUND(p[0].y));
}


CP2 CTestView::Project(CP3 P0)//斜平行投影
{
	CP2 Pt;
	Pt.x=P0.y-P0.x*cos(beta*PI/180)/tan(afa*PI/180);
	Pt.y=P0.z-P0.x*sin(beta*PI/180)/tan(afa*PI/180);
	return Pt;
}

void CTestView::OnMENUDrawCube()//绘制斜等侧图 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("斜平行投影:斜等侧图");
	afa=45;beta=45;
	DrawCube();
}

void CTestView::OnMENUITEMCube2()//绘制斜轴侧图  
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("斜平行投影:斜二侧图");
	afa=63.4;beta=45;
	DrawCube();
}
