// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
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
	ON_WM_ERASEBKGND()
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
	ReadPoint();
	ReadFace();
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

void CTestView::ReadPoint()//点表
{
	int i;	
	//红色长方条顶点的三维坐标(x,y,z)
	P[0][0].x=-150;P[0][0].y=-200;P[0][0].z=0;
	P[0][1].x=-150;P[0][1].y=-200;P[0][1].z=0;
	P[0][2].x=-125;P[0][2].y=-200;P[0][2].z=0;
	P[0][3].x=-125;P[0][3].y=-200;P[0][3].z=0;
	P[0][4].x=25;P[0][4].y=200;P[0][4].z=-100;
	P[0][5].x=25;P[0][5].y=200;P[0][5].z=-100;
	P[0][6].x=50;P[0][6].y=200;P[0][6].z=-100;
	P[0][7].x=50;P[0][7].y=200;P[0][7].z=-100;
	for(i=0;i<8;i++)//顶点颜色赋值
	{
		P[0][i].c=CRGB(1.0,0.0,0.0);
	}	
	//蓝色长方条顶点的三维坐标(x,y,z)
	P[1][0].x=150;P[1][0].y=-200;P[1][0].z=50;
	P[1][1].x=150;P[1][1].y=-200;P[1][1].z=50;
	P[1][2].x=125;P[1][2].y=-200;P[1][2].z=50;
	P[1][3].x=125;P[1][3].y=-200;P[1][3].z=50;
	P[1][4].x=-25;P[1][4].y=200;P[1][4].z=100;
	P[1][5].x=-25;P[1][5].y=200;P[1][5].z=100;
	P[1][6].x=-50;P[1][6].y=200;P[1][6].z=100;
	P[1][7].x=-50;P[1][7].y=200;P[1][7].z=100;
	for(i=0;i<8;i++)
	{
		P[1][i].c=CRGB(0.0,0.0,1.0);
	}
	//绿色长方条顶点的三维坐标(x,y,z)
	P[2][0].x=-200;P[2][0].y=-150;P[2][0].z=-100;
	P[2][1].x=-200;P[2][1].y=-150;P[2][1].z=-100;
	P[2][2].x=-200;P[2][2].y=-125;P[2][2].z=-100;
	P[2][3].x=-200;P[2][3].y=-125;P[2][3].z=-100;
	P[2][4].x=200;P[2][4].y=-150;P[2][4].z=120;
	P[2][5].x=200;P[2][5].y=-150;P[2][5].z=120;
	P[2][6].x=200;P[2][6].y=-125;P[2][6].z=120;
	P[2][7].x=200;P[2][7].y=-125;P[2][7].z=120;
	for(i=0;i<8;i++)
	{
		P[2][i].c=CRGB(0.0,1.0,0.0);
	}
}
void CTestView::ReadFace()//面表
{
	//面的边数、面的顶点编号和面的颜色
	F[0].En=4;F[0].p[0]=0;F[0].p[1]=3;F[0].p[2]=2;F[0].p[3]=1;//每个条的后面
	F[1].En=4;F[1].p[0]=4;F[1].p[1]=5;F[1].p[2]=6;F[1].p[3]=7;//每个条的前面
	F[2].En=4;F[2].p[0]=0;F[2].p[1]=4;F[2].p[2]=7;F[2].p[3]=3;//每个条的左面
	F[3].En=4;F[3].p[0]=1;F[3].p[1]=2;F[3].p[2]=6;F[3].p[3]=5;//每个条的右面
	F[4].En=4;F[4].p[0]=3;F[4].p[1]=7;F[4].p[2]=6;F[4].p[3]=2;//每个条的顶面
	F[5].En=4;F[5].p[0]=0;F[5].p[1]=1;F[5].p[2]=5;F[5].p[3]=4;//每个条的底面
}

void CTestView::DoubleBuffer()//双缓冲
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
	MemDC.SetViewportExt(Rect.Width(),-Rect.Height());
	MemDC.SetViewportOrg(Rect.Width()/2,Rect.Height()/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&Picture,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	DrawObject(&MemDC);
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();	
}

void CTestView::DrawObject(CDC *pDC)//绘制交叉面
{
	CPi3 Point[4];	
	zbuf.InitDeepBuffer(800,800,-1000);//深度初始化
	for(int nBar=0;nBar<3;nBar++)
	{		
		for(int nFace=0;nFace<6;nFace++)
		{
			for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//边循环
			{
				Point[nEdge].x=P[nBar][F[nFace].p[nEdge]].x;
				Point[nEdge].y=ROUND(P[nBar][F[nFace].p[nEdge]].y);
				Point[nEdge].z=P[nBar][F[nFace].p[nEdge]].z;
				Point[nEdge].c=P[nBar][F[nFace].p[nEdge]].c;
			}
			zbuf.SetPoint(Point,4);			
			zbuf.CreateBucket();//建立桶表
			zbuf.CreateEdge();//建立边表
			zbuf.Gouraud(pDC);//颜色渐变填充四边形
		}
	}
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC)//设置背景色函数 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;   
	GetClientRect(&Rect);   
	pDC->FillSolidRect(Rect,RGB(0,0,0));
	return true;
}
