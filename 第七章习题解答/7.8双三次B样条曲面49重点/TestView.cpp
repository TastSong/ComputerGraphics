// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
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
	ON_COMMAND(ID_MENUPolygon, OnMENUPolygon)
	ON_COMMAND(ID_MENUBSurface, OnMENUBSurface)
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
	Ori[0][0].x=200;Ori[0][0].y=-200;Ori[0][0].z=100;//P00
	Ori[0][1].x=200;Ori[0][1].y=-200;Ori[0][1].z=100;//P01
	Ori[0][2].x=200;Ori[0][2].y=-200;Ori[0][2].z=100;//P02
	Ori[0][3].x=300;Ori[0][3].y=100;Ori[0][3].z=300;//P03
	Ori[0][4].x=-200;Ori[0][4].y=-200;Ori[0][4].z=100;//P04
	Ori[0][5].x=-200;Ori[0][5].y=-200;Ori[0][5].z=100;//P05
	Ori[0][6].x=-200;Ori[0][6].y=-200;Ori[0][6].z=100;//P06

	Ori[1][0].x=200;Ori[1][0].y=-200;Ori[1][0].z=100;//P10
	Ori[1][1].x=200;Ori[1][1].y=-200;Ori[1][1].z=100;//p11
	Ori[1][2].x=200;Ori[1][2].y=-200;Ori[1][2].z=100;//p12
	Ori[1][3].x=300;Ori[1][3].y=100;Ori[1][3].z=300;//p13
	Ori[1][4].x=-200;Ori[1][4].y=-200;Ori[1][4].z=100;//p14
	Ori[1][5].x=-200;Ori[1][5].y=-200;Ori[1][5].z=100;//p15
	Ori[1][6].x=-200;Ori[1][6].y=-200;Ori[1][6].z=100;//p16

	Ori[2][0].x=200;Ori[2][0].y=-200;Ori[2][0].z=100;//P20
	Ori[2][1].x=200;Ori[2][1].y=-200;Ori[2][1].z=100;//P21
	Ori[2][2].x=200;Ori[2][2].y=-200;Ori[2][2].z=100;//P22
	Ori[2][3].x=300;Ori[2][3].y=100;Ori[2][3].z=300;//P23
	Ori[2][4].x=-200;Ori[2][4].y=-200;Ori[2][4].z=100;//P24
	Ori[2][5].x=-200;Ori[2][5].y=-200;Ori[2][5].z=100;//P25
	Ori[2][6].x=-200;Ori[2][6].y=-200;Ori[2][6].z=100;//P26

	Ori[3][0].x=300;Ori[3][0].y=100;Ori[3][0].z=300;//P30
	Ori[3][1].x=300;Ori[3][1].y=100;Ori[3][1].z=300;//P31
	Ori[3][2].x=300;Ori[3][2].y=100;Ori[3][2].z=300;//P32
	Ori[3][3].x=300;Ori[3][3].y=100;Ori[3][3].z=300;//P33
	Ori[3][4].x=300;Ori[3][4].y=100;Ori[3][4].z=300;//P34
	Ori[3][5].x=300;Ori[3][5].y=100;Ori[3][5].z=300;//P35
	Ori[3][6].x=300;Ori[3][6].y=100;Ori[3][6].z=300;//P36

	Ori[4][0].x=200;Ori[4][0].y=200;Ori[4][0].z=100;//P40
	Ori[4][1].x=200;Ori[4][1].y=200;Ori[4][1].z=100;//P41
	Ori[4][2].x=200;Ori[4][2].y=200;Ori[4][2].z=100;//P42
	Ori[4][3].x=300;Ori[4][3].y=100;Ori[4][3].z=300;//P43
	Ori[4][4].x=-200;Ori[4][4].y=200;Ori[4][4].z=100;//P44	
	Ori[4][5].x=-200;Ori[4][5].y=200;Ori[4][5].z=100;//P45
	Ori[4][6].x=-200;Ori[4][6].y=200;Ori[4][6].z=100;//P46
		
	Ori[5][0].x=200;Ori[5][0].y=200;Ori[5][0].z=100;//P50
	Ori[5][1].x=200;Ori[5][1].y=200;Ori[5][1].z=100;//P51
	Ori[5][2].x=200;Ori[5][2].y=200;Ori[5][2].z=100;//P52
	Ori[5][3].x=300;Ori[5][3].y=100;Ori[5][3].z=300;//P53
	Ori[5][4].x=-200;Ori[5][4].y=200;Ori[5][4].z=100;//P54	
	Ori[5][5].x=-200;Ori[5][5].y=200;Ori[5][5].z=100;//P55
	Ori[5][6].x=-200;Ori[5][6].y=200;Ori[5][6].z=100;//P56

	Ori[6][0].x=200;Ori[6][0].y=200;Ori[6][0].z=100;//P60
	Ori[6][1].x=200;Ori[6][1].y=200;Ori[6][1].z=100;//P61
	Ori[6][2].x=200;Ori[6][2].y=200;Ori[6][2].z=100;//P62
	Ori[6][3].x=300;Ori[6][3].y=100;Ori[6][3].z=300;//P63
	Ori[6][4].x=-200;Ori[6][4].y=200;Ori[6][4].z=100;//P64	
	Ori[6][5].x=-200;Ori[6][5].y=200;Ori[6][5].z=100;//P65
	Ori[6][6].x=-200;Ori[6][6].y=200;Ori[6][6].z=100;//P66
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
	GetClientRect(&Rect);//获得客户区大小
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴向右，y轴向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为圆心
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,RGB(128,128,128));
	OldPen=pDC->SelectObject(&NewPen);
	pDC->MoveTo(0,0);//绘制y轴
	pDC->LineTo(Rect.Width()/2,0);
	pDC->TextOut(Rect.Width()/2-10,20,"y");
	pDC->MoveTo(0,0);//绘制z轴
	pDC->LineTo(0,Rect.Height()/2);
	pDC->TextOut(-20,Rect.Height()/2,"z");
	pDC->MoveTo(0,0);//绘制x轴
	pDC->LineTo(-Rect.Height()/2,-Rect.Height()/2);//夹角为135°
	pDC->TextOut(-Rect.Height()/2,-Rect.Height()/2+30,"x");
	pDC->TextOut(-20,20,"O");
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();	
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
void CTestView::Project1()//分块矩阵三维坐标变换为二维坐标4*4
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			P2[i][j].x=P3[i][j].y-P3[i][j].x/sqrt(2);
			P2[i][j].y=P3[i][j].z-P3[i][j].x/sqrt(2);
		}
}
void CTestView::Project2()//控制点三维坐标变换为二维坐标7*7
{
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
		{
			Ori1[i][j].x=Ori[i][j].y-Ori[i][j].x/sqrt(2);
			Ori1[i][j].y=Ori[i][j].z-Ori[i][j].x/sqrt(2);
		}
}
void CTestView::Line(CDC *pDC,CPoint p[])//绘制控制多边形
{
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));
	OldPen=pDC->SelectObject(&NewPen);
	for(int i=0;i<N;i++)
		if(i==0)
		{
			pDC->MoveTo(p[0]);
		    pDC->Ellipse(p[0].x-2,p[0].y-2,p[0].x+2,p[0].y+2);
		}
		else
		{
			pDC->LineTo(p[i]);
			pDC->Ellipse(p[i].x-2,p[i].y-2,p[i].x+2,p[i].y+2);
		}
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();
}
void CTestView::DrawCtrP1(CDC *pDC)//从左到右绘制控制多边形
{
	CPoint p[N];
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			p[j]=CPoint(ROUND(Ori1[i][j].x),ROUND(Ori1[i][j].y));				
		}
		Line(pDC,p);
	}
}
void CTestView::DrawCtrP2(CDC *pDC)//从前到后绘制控制多边形
{
	CPoint p[N];
	for(int j=0;j<N;j++)
	{
		for(int i=0;i<N;i++)
		{
			p[i]=CPoint(ROUND(Ori1[i][j].x),ROUND(Ori1[i][j].y));				
		}
		Line(pDC,p);
	}
}
void CTestView::SignCtrPoint(CDC *pDC)//标注控制点
{
	CString str;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			str.Format("P%d,%d",i,j);
			pDC->TextOut(ROUND(Ori1[i][j].x),ROUND(Ori1[i][j].y),str);				
		}		
	}
}
void CTestView::DrawBFace(CDC *pDC)//绘制双三次B样条曲面	
{
	double x,y,u,v,u1,u2,u3,u4,v1,v2,v3,v4;
	M[0][0]=-1;M[0][1]=3;M[0][2]=-3;M[0][3]=1;
	M[1][0]=3;M[1][1]=-6;M[1][2]=3;M[1][3]=0;
	M[2][0]=-3;M[2][1]=0;M[2][2]=3;M[2][3]=0;
	M[3][0]=1;M[3][1]=4;M[3][2]=1;M[3][3]=0;
	for(int i=0;i<4;i++)//矩阵元素除以6
		for(int j=0;j<4;j++)
			M[i][j]=M[i][j]/6.0;
	MultiMatrix1(M,P3);//结果在P3中
	MatrixRotate(M);//结果在Mz中
	MultiMatrix2(P3,Mz);//结果在P3中
	Project1();
	for(u=0;u<=1;u+=0.001)
		for(v=0;v<=1;v+=0.001)
		{
			u1=u*u*u;u2=u*u;u3=u;u4=1;v1=v*v*v;v2=v*v;v3=v;v4=1;
			x=(u1*P2[0][0].x+u2*P2[1][0].x+u3*P2[2][0].x+u4*P2[3][0].x)*v1
			 +(u1*P2[0][1].x+u2*P2[1][1].x+u3*P2[2][1].x+u4*P2[3][1].x)*v2
			 +(u1*P2[0][2].x+u2*P2[1][2].x+u3*P2[2][2].x+u4*P2[3][2].x)*v3
			 +(u1*P2[0][3].x+u2*P2[1][3].x+u3*P2[2][3].x+u4*P2[3][3].x)*v4;
			y=(u1*P2[0][0].y+u2*P2[1][0].y+u3*P2[2][0].y+u4*P2[3][0].y)*v1
			 +(u1*P2[0][1].y+u2*P2[1][1].y+u3*P2[2][1].y+u4*P2[3][1].y)*v2
			 +(u1*P2[0][2].y+u2*P2[1][2].y+u3*P2[2][2].y+u4*P2[3][2].y)*v3
			 +(u1*P2[0][3].y+u2*P2[1][3].y+u3*P2[2][3].y+u4*P2[3][3].y)*v4;
			pDC->SetPixel(ROUND(x),ROUND(y),RGB(255,0,0));
		}
}
void CTestView::MultiMatrix1(double M0[][4],CP3 P0[][4])//矩阵M*P
{
	KeepOriginalMatrix(P0,T);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{	
			P3[i][j].x=M0[i][0]*T[0][j].x+M0[i][1]*T[1][j].x+M0[i][2]*T[2][j].x+M0[i][3]*T[3][j].x;	
			P3[i][j].y=M0[i][0]*T[0][j].y+M0[i][1]*T[1][j].y+M0[i][2]*T[2][j].y+M0[i][3]*T[3][j].y;
			P3[i][j].z=M0[i][0]*T[0][j].z+M0[i][1]*T[1][j].z+M0[i][2]*T[2][j].z+M0[i][3]*T[3][j].z;
		}
}
void CTestView::MultiMatrix2(CP3 P0[][4],double M0[][4])//矩阵P*M
{
	KeepOriginalMatrix(P0,T);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{	
			P3[i][j].x=T[i][0].x*M0[0][j]+T[i][1].x*M0[1][j]+T[i][2].x*M0[2][j]+T[i][3].x*M0[3][j];	
			P3[i][j].y=T[i][0].y*M0[0][j]+T[i][1].y*M0[1][j]+T[i][2].y*M0[2][j]+T[i][3].y*M0[3][j];
			P3[i][j].z=T[i][0].z*M0[0][j]+T[i][1].z*M0[1][j]+T[i][2].z*M0[2][j]+T[i][3].z*M0[3][j];
		}
}
void CTestView::KeepOriginalMatrix(CP3 Orig[4][4],CP3 Dest[4][4])
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			Dest[i][j].x=Orig[i][j].x;
			Dest[i][j].y=Orig[i][j].y;
			Dest[i][j].z=Orig[i][j].z;
		}
}

void CTestView::MatrixRotate(double M0[][4])//矩阵转置
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{	
			Mz[j][i]=M0[i][j];
		}
}

void CTestView::OnMENUPolygon() 
{
	// TODO: Add your command handler code here
	GetClientRect(&Rect);//获得客户区大小
	CDC *pDC=GetDC();//客户区DC
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点
	Project2();
	DrawCtrP1(pDC);
	DrawCtrP2(pDC);
	SignCtrPoint(pDC);
	ReleaseDC(pDC);
}

void CTestView::OnMENUBSurface() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	GetClientRect(&Rect);//获得客户区大小
	CDC *pDC=GetDC();//客户区DC
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴向右，y轴向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为圆心
	BlockMatrix(pDC);
	ReleaseDC(pDC);
}
void CTestView::BlockMatrix(CDC *pDC)//矩阵分块
{ 
	for(int s=0;s<=N-4;s++)
		for(int r=0;r<=N-4;r++)
		{
			for(int i=0;i<4;i++)
				for(int j=0;j<4;j++)
					P3[i][j]=Ori[r+i][s+j];
			DrawBFace(pDC);
		}
}