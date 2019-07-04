// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#include "cmath"//包含数学头文件
#define  PI 3.1415926//圆周率
#define  ROUND(x)  int(x+0.5)//四舍五入


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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENUPlay, OnMENUPlay)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENUPlay, OnUpdateMENUPlay)
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
	R=1000,d=800,Phi=0.0,Theta=-90.0;
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
	InitParameter();
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

void CTestView::InitParameter()//初始化透视变换常数
{
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[3]*k[2];
	k[6]=k[1]*k[2];
	k[7]=k[3]*k[4];
	k[8]=k[1]*k[4];
	ViewPoint.x=R*k[5];//用户坐标系的视点球坐标
	ViewPoint.y=R*k[6];
	ViewPoint.z=R*k[4];
}
void CTestView::PerProject(CP3 P)//透视变换
{
	CP3 ViewP;
	ViewP.x=-k[1]*P.x+k[3]*P.y;//观察坐标系三维坐标
	ViewP.y=-k[7]*P.x-k[8]*P.y+k[2]*P.z;
	ViewP.z=-k[5]*P.x-k[6]*P.y-k[4]*P.z+R;
	ViewP.c=P.c;
	ScreenP.x=d*ViewP.x/ViewP.z;//屏幕坐标系三维坐标
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.z=d*(R-ViewP.z)/ViewP.z;
	ScreenP.c=ViewP.c;	
}

void CTestView::DoubleBuffer()//双缓冲绘图
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

void CTestView::DrawObject(CDC *pDC)//计算顶点函数
{
	double afa,afa1,afa2,angle=72;
	double	k=sin(18*PI/180)/cos(36*PI/180);//五角星外点和内点圆半径之间的比例
	R1=300;//五角星外点圆半径
	R2=k*R1;//五角星内点圆半径
    double Height=100;//五角星中心点距离
	zbuf.InitDeepBuffer(600,600,-600);//深度初始化
	for(afa=0;afa<360;afa=afa+angle)
	{
		afa1=(afa+angle/2)*PI/180;
		afa2=(afa-angle/2)*PI/180;
		P[0].x=0;//P0点
		P[0].y=0;
		P[0].z=Height;
		P[0].c=CRGB(1.0,1.0,1.0);
		P[1].x=R2*sin(afa1);//P1点
		P[1].y=R2*cos(afa1);
		P[1].z=0;
		P[1].c=CRGB(1.0,0.0,0.0);
		P[2].x=R1*sin(afa*PI/180);//P2点
		P[2].y=R1*cos(afa*PI/180);
		P[2].z=0;
		P[2].c=CRGB(1.0,0.0,0.0);
		DrawFace(pDC,P);//绘制角的前面右侧三角形面元
		P[0].x=0;//P0点
		P[0].y=0;
		P[0].z=Height;
		P[0].c=CRGB(1.0,1.0,1.0);
		P[1].x=R1*sin(afa*PI/180);//P2点
		P[1].y=R1*cos(afa*PI/180);
		P[1].z=0;
		P[1].c=CRGB(1.0,0.0,0.0);
		P[2].x=R2*sin(afa2);//P1点
		P[2].y=R2*cos(afa2);
		P[2].z=0;
		P[2].c=CRGB(1.0,0.0,0.0);
		DrawFace(pDC,P);//绘制角的前面左侧三角形面元
		P[0].x=0;//P0点
		P[0].y=0;
		P[0].z=-Height;
		P[0].c=CRGB(1.0,1.0,1.0);
		P[1].x=R1*sin(afa*PI/180);//P1点
		P[1].y=R1*cos(afa*PI/180);
		P[1].z=0;
		P[1].c=CRGB(1.0,0.0,0.0);
		P[2].x=R2*sin(afa1);//P2点
		P[2].y=R2*cos(afa1);
		P[2].z=0;
		P[2].c=CRGB(1.0,0.0,0.0);		
		DrawFace(pDC,P);//绘制角的后面右侧三角形面元
		P[0].x=0;//P0点
		P[0].y=0;
		P[0].z=-Height;
		P[0].c=CRGB(1.0,1.0,1.0);
		P[1].x=R2*sin(afa2);//P1点
		P[1].y=R2*cos(afa2);
		P[1].z=0;
		P[1].c=CRGB(1.0,0.0,0.0);
		P[2].x=R1*sin(afa*PI/180);//P2点
		P[2].y=R1*cos(afa*PI/180);
		P[2].z=0;
		P[2].c=CRGB(1.0,0.0,0.0);
		DrawFace(pDC,P);//绘制角的后面左侧三角形面元		
	}
}
	
void CTestView::DrawFace(CDC *pDC,CP3 *P)//绘制五角星
{
	CPi3  Point[3];
	CVector VS(P[1],ViewPoint);//面的视矢量
	CVector V01(P[0],P[1]);//面的一个边矢量
	CVector V12(P[1],P[2]);//面的另一个边矢量				
	CVector VN=V01*V12;//面的法矢量	
	for(int i=0;i<3;i++)
	{
		PerProject(P[i]);//透视投影
		Point[i].x=ScreenP.x;
		Point[i].y=ROUND(ScreenP.y);
		Point[i].z=ScreenP.z;
		Point[i].c=ScreenP.c;
	}
	if(Dot(VS,VN)>=0)//判断数量积正负
	{	
		zbuf.SetPoint(Point,3);			
		zbuf.CreateBucket();//建立桶表
		zbuf.CreateEdge();//建立边表
		zbuf.Gouraud(pDC);//颜色渐变填充三角形	
	}	
}
void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(!Play)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi-=10;//设定步长
			break;
		case VK_DOWN:
			Phi+=10;
			break;
		case VK_LEFT:
			Theta-=10;
			break;
		case VK_RIGHT:
		    Theta+=10;
			break;
		default:
			break;			
		}
		InitParameter();
		DoubleBuffer();		
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnMENUPlay() 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//设置动画的时间步
		SetTimer(1,15,NULL);	
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Phi-=10;//设定步长
	Theta-=10;
	InitParameter();
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI)//动画按钮状态函数  
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

