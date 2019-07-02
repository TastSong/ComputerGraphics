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
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_COMMAND(ID_MENUPlay, OnMENUPlay)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENUPlay, OnUpdateMENUPlay)
	ON_WM_KEYDOWN()
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
	R=800.0;d=1000;Phi=0;Theta=-90;	
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

void CTestView::ReadPoint()//点表
{
	double a=200;//等边三角形的边长
	double b=300;//棱柱高
	//顶点的三维坐标(x,y,z)
	P[0].x=-b/2;P[0].y=a*sqrt(3)/3; P[0].z=0;
	P[1].x=-b/2;P[1].y=-a*sqrt(3)/6;P[1].z=-a/2;  
	P[2].x=-b/2;P[2].y=-a*sqrt(3)/6;P[2].z=a/2;    
	P[3].x=b/2; P[3].y=a*sqrt(3)/3; P[3].z=0;
	P[4].x=b/2; P[4].y=-a*sqrt(3)/6;P[4].z=-a/2; 
	P[5].x=b/2; P[5].y=-a*sqrt(3)/6;P[5].z=a/2; 
}

void CTestView::ReadFace()//面表
{
	//面的边数、面的顶点编号
	F[0].En=3;F[0].p[0]=0;F[0].p[1]=1;F[0].p[2]=2;
	F[1].En=3;F[1].p[0]=3;F[1].p[1]=5;F[1].p[2]=4;
	F[2].En=4;F[2].p[0]=0;F[2].p[1]=3;F[2].p[2]=4;F[2].p[3]=1;
	F[3].En=4;F[3].p[0]=2;F[3].p[1]=1;F[3].p[2]=4;F[3].p[3]=5;
	F[4].En=4;F[4].p[0]=0;F[4].p[1]=2;F[4].p[2]=5;F[4].p[3]=3;
}

void CTestView::InitParameter()//透视变换参数初始化
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
	ScreenP.x=ROUND(d*ViewP.x/ViewP.z);//屏幕坐标系二维坐标
	ScreenP.y=ROUND(d*ViewP.y/ViewP.z);
	ScreenP.c=ViewP.c;
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

void CTestView::DrawObject(CDC* pDC)//绘制物体
{
	for(int nFace=0;nFace<5;nFace++)
	{
		CVector VS(P[F[nFace].p[1]],ViewPoint);//面的视矢量
		CVector V01(P[F[nFace].p[0]],P[F[nFace].p[1]]);//面的一个边矢量
		CVector V12(P[F[nFace].p[1]],P[F[nFace].p[2]]);//面的另一个边矢量		
		CVector VN=V01*V12;//面的法矢量	
		if(Dot(VS,VN)>=0)//凸多面体消隐
			DrawFace(pDC,nFace);//数量积大于零，表面画出
	}	
}

void CTestView::DrawFace(CDC* pDC,int nface)//绘制表面
{
	CP2 t;
	CLine line;
	for(int nEdge=0;nEdge<F[nface].En;nEdge++)//边循环
	{
		PerProject(P[F[nface].p[nEdge]]);//透视投影
		if(nEdge==0)
		{
			line.MoveTo(pDC,ScreenP);
			t=ScreenP;
		}
		else
		{
			line.LineTo(pDC,ScreenP);
		}		
	}
	line.LineTo(pDC,t.x,t.y,t.c);//闭合四边形
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//鼠标左键函数
{
	// TODO: Add your message handler code here and/or call default
	R=R+100;
	DoubleBuffer();
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnRButtonDblClk(UINT nFlags, CPoint point)//鼠标右键函数 
{
	// TODO: Add your message handler code here and/or call default
	R=R-100;
	DoubleBuffer();
	CView::OnRButtonDblClk(nFlags, point);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //键盘响应函数 
{
	// TODO: Add your message handler code here and/or call default
	if(!Play)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi-=1;//设定步长
			break;
		case VK_DOWN:
			Phi+=1;
			break;
		case VK_LEFT:
			Theta-=1;
			break;
		case VK_RIGHT:
		    Theta+=1;
			break;
		default:
			break;			
		}
		InitParameter();
		DoubleBuffer();		
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnMENUPlay()//动画按钮函数 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//设置动画的时间步
		SetTimer(1,15,NULL);	
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent)//动画时间函数 
{
	// TODO: Add your message handler code here and/or call default
	Phi-=1;//设定步长
	Theta-=1;
	InitParameter();
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI) //动画按钮状态函数 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}


