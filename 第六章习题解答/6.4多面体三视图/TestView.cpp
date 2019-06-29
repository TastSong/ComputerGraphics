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
	ON_COMMAND(ID_MENUTriView, OnMENUTriView)
	ON_UPDATE_COMMAND_UI(ID_MENUTriView, OnUpdateMENUTriView)
	ON_COMMAND(ID_MENUPlygon, OnMENUPlygon)
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

void CTestView::OnDraw(CDC* pDC)//绘制坐标轴
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	GetMaxX();GetMaxY();
	CPen NewPen3d,NewPen2d,NewPen,*OldPen;
	NewPen3d.CreatePen(PS_SOLID,1,RGB(128,128,128));
	OldPen=pDC->SelectObject(&NewPen3d);
	pDC->MoveTo(MaxX/4,MaxY/2);//绘制y轴
	pDC->LineTo(MaxX/2-25,MaxY/2);
	pDC->TextOut(MaxX/2-50,MaxY/2-20,"y");
	pDC->MoveTo(MaxX/4,MaxY/2);//绘制z轴
	pDC->LineTo(MaxX/4,0);
	pDC->TextOut(MaxX/4-20,10,"z");
	pDC->MoveTo(MaxX/4,MaxY/2);//绘制x轴
	pDC->LineTo(MaxX/4-MaxY/2,MaxY);//夹角为135°
	pDC->TextOut(MaxX/4-MaxY/2+70,MaxY-30,"x");
	pDC->TextOut(MaxX/4-20,MaxY/2-10,"0");
	pDC->TextOut(20,20,"斜等测投影图");
	pDC->SelectObject(OldPen);
	NewPen3d.DeleteObject();
	NewPen.CreatePen(PS_SOLID,3,RGB(128,128,128));
	OldPen=pDC->SelectObject(&NewPen);
	pDC->MoveTo(MaxX/2-25,0);//绘制分割线
	pDC->LineTo(MaxX/2-25,MaxY);
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();
	NewPen2d.CreatePen(PS_SOLID,1,RGB(128,128,128));
	OldPen=pDC->SelectObject(&NewPen2d);
	pDC->MoveTo(MaxX/2-25,MaxY/2);//绘制x轴
	pDC->LineTo(3*MaxX/4,MaxY/2);
	pDC->TextOut(MaxX/2-15,MaxY/2-20,"x");
	pDC->MoveTo(3*MaxX/4,MaxY/2);//绘制z轴
	pDC->LineTo(3*MaxX/4,0);
	pDC->TextOut(3*MaxX/4-20,10,"z");
	pDC->MoveTo(3*MaxX/4,MaxY/2);//绘制右y轴
	pDC->LineTo(MaxX,MaxY/2);
	pDC->TextOut(MaxX-20,MaxY/2-20,"y");
	pDC->MoveTo(3*MaxX/4,MaxY/2);//绘制下y轴
	pDC->LineTo(3*MaxX/4,MaxY);
	pDC->TextOut(3*MaxX/4-20,MaxY-20,"y");
	pDC->TextOut(MaxX/2+10,20,"三视图");
	pDC->SelectObject(OldPen);
	NewPen2d.DeleteObject();	
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
void CTestView::ReadPoint()//点表
{
	P3[0][0]=0;  P3[0][1]=0;  P3[0][2]=0;  P3[0][3]=1;//A点
	P3[1][0]=0;  P3[1][1]=200;P3[1][2]=0;  P3[1][3]=1;//B点
	P3[2][0]=0;  P3[2][1]=200;P3[2][2]=100;P3[2][3]=1;//C点
	P3[3][0]=0;  P3[3][1]=0;  P3[3][2]=100;P3[3][3]=1;//D点
	P3[4][0]=100;P3[4][1]=0;  P3[4][2]=0;  P3[4][3]=1;//E点
	P3[5][0]=100;P3[5][1]=200;P3[5][2]=0;  P3[5][3]=1;//F点
	P3[6][0]=100;P3[6][1]=200;P3[6][2]=100;P3[6][3]=1;//G点
	P3[7][0]=100;P3[7][1]=0;  P3[7][2]=100;P3[7][3]=1;//H点
	P3[8][0]=50; P3[8][1]=0;  P3[8][2]=150;P3[8][3]=1;//I点
	P3[9][0]=50; P3[9][1]=200;P3[9][2]=150;P3[9][3]=1;//J点
}
void CTestView::ReadFace()//面表
{//面的边数、面的顶点编号
	F[0].En=4;F[0].p[0]=0;F[0].p[1]=3;F[0].p[2]=2;F[0].p[3]=1;//后面ADEB
	F[1].En=4;F[1].p[0]=4;F[1].p[1]=5;F[1].p[2]=6;F[1].p[3]=7;//前面EFGH
	F[2].En=5;F[2].p[0]=4;F[2].p[1]=7;F[2].p[2]=8;F[2].p[3]=3;F[2].p[4]=0;//左面EHIDA
	F[3].En=5;F[3].p[0]=1;F[3].p[1]=2;F[3].p[2]=9;F[3].p[3]=6;F[3].p[4]=5;//右面BCJGF
	F[4].En=4;F[4].p[0]=3;F[4].p[1]=8;F[4].p[2]=9;F[4].p[3]=2;//后顶面DIJC
	F[5].En=4;F[5].p[0]=7;F[5].p[1]=6;F[5].p[2]=9;F[5].p[3]=8;//前顶面HGJI
	F[6].En=4;F[6].p[0]=0;F[6].p[1]=1;F[6].p[2]=5;F[6].p[3]=4;//底面HBFE
}
void CTestView::DrawPolygon()//绘制多面体斜等测投影图函数
{	
	ReadPoint();
	ReadFace();
	Project(P3,P2,10);//斜等侧投影变换
	CRect Rect;
	GetClientRect(&Rect);//获得客户区大小
	CDC *pDC=GetDC();//客户区DC
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点
	CPoint p[5];//定义多边形顶点数组
	int TotalEdge,PointNumber;
	for(int nFace=0;nFace<7;nFace++)
	{
		TotalEdge=F[nFace].En;//每个面的总边数
		for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//边循环
		{
			PointNumber=F[nFace].p[nEdge];//面的顶点号
			p[nEdge]=CPoint(-MaxX/4+ROUND(P2[PointNumber][0]),ROUND(P2[PointNumber][1]));
		}
		Line(pDC,p,TotalEdge);//绘制斜投影图		    	
	}	
}
void CTestView::Line(CDC *pDC,CPoint p[],int num)//绘制多边形函数
{
	for(int i=0;i<num;i++)
		if(i==0)
			pDC->MoveTo(p[i]);
		else
			pDC->LineTo(p[i]);
		pDC->LineTo(p[0]);
}
void CTestView::Project(const double P3[][4],double P2[][3],const int n)
{//三维坐标变换为二维坐标函数
	for(int i=0;i<n;i++)
	{
		P2[i][0]=P3[i][1]-P3[i][0]/sqrt(2);
		P2[i][1]=P3[i][2]-P3[i][0]/sqrt(2);
	}
}
void CTestView::DrawVView()//主视图变换矩阵
{
	ClearMatrix(TV);
	TV[0][0]=1;
	TV[2][2]=1;
	TV[3][3]=1;
	MultiMatrix(P3,TV);
	DrawTriView();
}
void CTestView::DrawHView()//俯视图变换矩阵
{
	ClearMatrix(TH);
	TH[0][0]=1;
	TH[1][2]=-1;
	TH[3][2]=-30;
	TH[3][3]=1;
	MultiMatrix(P3,TH);
	DrawTriView();
}
void CTestView::DrawWView()//侧视图变换矩阵
{
	ClearMatrix(TW);
	TW[1][0]=-1;
	TW[2][2]=1;
	TW[3][0]=-30;
	TW[3][3]=1;
	MultiMatrix(P3,TW);
	DrawTriView();
}
void CTestView::ClearMatrix(int A[][4])//清除变换矩阵
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
			A[i][j]=0;
	}
}
void CTestView::MultiMatrix(double P[][4],int T[][4])//两个矩阵相乘
{
	for(int i=0;i<10;i++)
		for(int j=0;j<4;j++)
		{
			Tri[i][j]=P3[i][0]*T[0][j]+P3[i][1]*T[1][j]+P3[i][2]*T[2][j]+P3[i][3]*T[3][j];					
		}
}
void CTestView::DrawTriView()//绘制三视图
{
	CRect Rect;
	GetClientRect(&Rect);//获得客户区大小
	CDC *pDC=GetDC();//客户区DC
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴向右，y轴向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点
	CPoint p[5];
	int TotalEdge,PointNumber;
	for(int nFace=0;nFace<7;nFace++)
	{
		TotalEdge=F[nFace].En;//每个面的总边数
		for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//边循环
		{
			PointNumber=F[nFace].p[nEdge];//面的顶点号
			p[nEdge]=CPoint(MaxX/4-ROUND(Tri[PointNumber][0]),ROUND(Tri[PointNumber][2]));		
		}
			Line(pDC,p,TotalEdge);	
	}
}
void CTestView::OnMENUPlygon()//绘制斜等测投影图 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	DrawPolygon();	
}

void CTestView::OnMENUTriView()//绘制三视图 
{
	// TODO: Add your command handler code here
	DrawVView();//主视图
	DrawHView();//俯视图
	DrawWView();//侧视图	
}
void CTestView::OnUpdateMENUTriView(CCmdUI* pCmdUI)  //三视图菜单项无效函数
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((P2[0][0]!=NULL)?FALSE:TRUE);
}


