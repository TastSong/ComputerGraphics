// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//数学头文件
#define ROUND(a) int(a+0.5)//四舍五入
#define PI 3.14159265//圆周率
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
	ON_COMMAND(ID_MENUBezierSurface, OnMENUBezierSurface)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENUBezierSurface, OnUpdateMENUBezierSurface)
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
	Play=FALSE;
	Afa=20;
	Beta=50;
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
void CTestView::ReadPoint()//读入控制网格16个顶点坐标
{
	P3Old[0][0].x=-130;P3Old[0][0].y=-50;P3Old[0][0].z=200;//P00
	P3Old[0][1].x=-200;P3Old[0][1].y=100;P3Old[0][1].z=100;//P01
	P3Old[0][2].x=-150;P3Old[0][2].y=60;P3Old[0][2].z=-100;//P02
	P3Old[0][3].x=-100;P3Old[0][3].y=-10;P3Old[0][3].z=-200;//P03

	P3Old[1][0].x=-100;P3Old[1][0].y=80;P3Old[1][0].z=200;//P10
	P3Old[1][1].x=-120;P3Old[1][1].y=120;P3Old[1][1].z=100;//p11
	P3Old[1][2].x=30;P3Old[1][2].y=90;P3Old[1][2].z=-100;//p12
	P3Old[1][3].x=-20;P3Old[1][3].y=60;P3Old[1][3].z=-170;//p13

	P3Old[2][0].x=90;P3Old[2][0].y=60;P3Old[2][0].z=180;//P20
	P3Old[2][1].x=120;P3Old[2][1].y=100;P3Old[2][1].z=120;//P21
	P3Old[2][2].x=125;P3Old[2][2].y=120;P3Old[2][2].z=-80;//P22
	P3Old[2][3].x=110;P3Old[2][3].y=90;P3Old[2][3].z=-150;//P23

	P3Old[3][0].x=150;P3Old[3][0].y=-10;P3Old[3][0].z=200;//P30
	P3Old[3][1].x=170;P3Old[3][1].y=60;P3Old[3][1].z=120;//P31
	P3Old[3][2].x=190;P3Old[3][2].y=90;P3Old[3][2].z=-200;//P32
	P3Old[3][3].x=140;P3Old[3][3].y=40;P3Old[3][3].z=-210;//P33	
}
void CTestView::DoubleBuffer()//双缓冲
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
	MemDC.SetViewportExt(Rect.right,-Rect.bottom);
	MemDC.SetViewportOrg(Rect.right/2,Rect.bottom/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.Width(),Rect.Height(),&Picture,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	Rotate();
	DrawBezier(&MemDC);
	Project(P3New,P2Ctr);
	DrawCtrP1(&MemDC);
	DrawCtrP2(&MemDC);
	SignCtrPoint(&MemDC);
	pDC->BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.right,Rect.bottom,&MemDC,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();	
}

void CTestView::Project(CP3 S[][4],CP2 D[][4])//将源三维坐标变换为目标二维坐标
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			D[i][j].x=S[i][j].x;
			D[i][j].y=S[i][j].y;
		}
}
void CTestView::OnMENUBezierSurface()//绘制双三次Bezier曲面菜单函数
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//设置动画的时间步
		SetTimer(1,15,NULL);	
	else
		KillTimer(1);
}
void CTestView::Line(CDC* pDC,CPoint p[])//画线
{
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,2,RGB(128,128,128));
	OldPen=pDC->SelectObject(&NewPen);
	for(int i=0;i<4;i++)
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
void CTestView::DrawCtrP1(CDC* pDC)//从左到右绘制控制多边形
{
	CPoint p[4];
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			p[j]=CPoint(ROUND(P2Ctr[i][j].x),ROUND(P2Ctr[i][j].y));	pDC->SetPixel(p[i],RGB(0,0,0));			
		}
		Line(pDC,p);
	}
}

void CTestView::DrawCtrP2(CDC* pDC)//从前到后绘制控制多边形
{
	CPoint p[4];
	for(int j=0;j<4;j++)
	{
		for(int i=0;i<4;i++)
		{
			p[i]=CPoint(ROUND(P2Ctr[i][j].x),ROUND(P2Ctr[i][j].y));	
			pDC->SetPixel(p[i],RGB(0,0,0));
		}
		Line(pDC,p);
	}
}
void CTestView::SignCtrPoint(CDC* pDC)//标注控制点的编号
{
	CString str;
    pDC->SetBkMode(TRANSPARENT);
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			str.Format("P%d,%d",i,j);
			pDC->TextOut(ROUND(P2Ctr[i][j].x+20),ROUND(P2Ctr[i][j].y)+5,str);				
		}		
	}
}
void CTestView::DrawBezier(CDC* pDC)//绘制双三次Bezier曲面	
{
	double x,y,u,v,u1,u2,u3,u4,v1,v2,v3,v4;
	double M[4][4];
	CP3 Temp1[4][4],Temp2[4][4];//临时顶点信息，用于矩阵运算，为不改变P3中的定点信息而设
	M[0][0]=-1;M[0][1]=3;M[0][2]=-3;M[0][3]=1;
	M[1][0]=3;M[1][1]=-6;M[1][2]=3;M[1][3]=0;
	M[2][0]=-3;M[2][1]=3;M[2][2]=0;M[2][3]=0;
	M[3][0]=1;M[3][1]=0;M[3][2]=0;M[3][3]=0;
	MultiMatrix1(M,P3New,Temp1);
	MatrixRotate(M);
	MultiMatrix2(Temp1,MT,Temp2);
	Project(Temp2,P2);
	for(u=0;u<=1;u+=0.002)
	{
		for(v=0;v<=1;v+=0.002)
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
	
}
void CTestView::MultiMatrix1(double M0[][4],CP3 P0[][4],CP3 D[][4])//两个矩阵M*P=D相乘
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{	
			D[i][j].x=M0[i][0]*P0[0][j].x+M0[i][1]*P0[1][j].x+M0[i][2]*P0[2][j].x+M0[i][3]*P0[3][j].x;	
			D[i][j].y=M0[i][0]*P0[0][j].y+M0[i][1]*P0[1][j].y+M0[i][2]*P0[2][j].y+M0[i][3]*P0[3][j].y;
			D[i][j].z=M0[i][0]*P0[0][j].z+M0[i][1]*P0[1][j].z+M0[i][2]*P0[2][j].z+M0[i][3]*P0[3][j].z;
		}
}

void CTestView::MultiMatrix2(CP3 P0[][4],double M1[][4],CP3 D[][4])//两个矩阵P*M=D相乘
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{	
			D[i][j].x=P0[i][0].x*M1[0][j]+P0[i][1].x*M1[1][j]+P0[i][2].x*M1[2][j]+P0[i][3].x*M1[3][j];	
			D[i][j].y=P0[i][0].y*M1[0][j]+P0[i][1].y*M1[1][j]+P0[i][2].y*M1[2][j]+P0[i][3].y*M1[3][j];
			D[i][j].z=P0[i][0].z*M1[0][j]+P0[i][1].z*M1[1][j]+P0[i][2].z*M1[2][j]+P0[i][3].z*M1[3][j];
		}
}

void CTestView::MatrixRotate(double M0[][4])//矩阵转置
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{	
			MT[j][i]=M0[i][j];
		}
	}
}

void CTestView::Rotate()//绕x轴旋转Afa,绕y轴旋转Beta
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{	
			CP3	PTemp;
			PTemp.x=P3Old[i][j].x;
			PTemp.y=P3Old[i][j].y*cos(PI*Afa/180)-P3Old[i][j].z*sin(PI*Afa/180);
			PTemp.z=P3Old[i][j].y*sin(PI*Afa/180)+P3Old[i][j].z*cos(PI*Afa/180);
			P3New[i][j].x=PTemp.z*sin(PI*Beta/180)+PTemp.x*cos(PI*Beta/180);
			P3New[i][j].y=PTemp.y;
			P3New[i][j].z=PTemp.z*cos(PI*Beta/180)-PTemp.x*sin(PI*Beta/180);
		}
	}
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//键盘控制函数 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		case VK_UP:
			Afa-=10;//设定步长	
			break;
		case VK_DOWN:
			Afa+=10;
			break;
		case VK_LEFT:
			Beta-=10;
			break;
		case VK_RIGHT:
			Beta+=10;
			break;
		default:
			break;				
	}
	DoubleBuffer();		
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnTimer(UINT nIDEvent)//定时器函数 
{
	// TODO: Add your message handler code here and/or call default
	Afa+=10;//设定步长
	Beta+=10;
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENUBezierSurface(CCmdUI* pCmdUI)//动画按钮状态函数 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
