// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define Xhit	0;//x方向碰撞标志
#define Yhit	1;//y方向碰撞标志
#define Allhit	2;//x和y方向碰撞标志
#define Nohit	3;//未发生碰撞标志
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
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_PLAY, OnMenuPlay)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY, OnUpdateMenuPlay)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()//构造函数
{
	// TODO: add construction code here
	Play=FALSE;
	RGB[0]=RGB(255,0,0);//红色
	RGB[1]=RGB(0,255,0);//绿色
	RGB[2]=RGB(0,0,255);//蓝色
	RGB[3]=RGB(255,255,0);//黄色
	RGB[4]=RGB(255,0,255);//品红
	RGB[5]=RGB(0,255,255);//青色
	pRect[0]=new CRectangle(-200,150,200,300,-1.65,1.5);
	pRect[1]=new CRectangle(300,-200,200,200,0.0,0.8);
	pRect[2]=new CRectangle(80,-50,100,200,0.65,0.5);
	pRect[3]=new CRectangle(300,200,50,50,0.16,0.8);
	pRect[4]=new CRectangle(-250,-200,200,100,0.16,0.8);
	pRect[5]=new CRectangle(250,100,200,60,0.4,0.2);
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
	MemDC.SetWindowExt(Rect.right,Rect.bottom);
	MemDC.SetViewportExt(Rect.right,-Rect.bottom);
	MemDC.SetViewportOrg(Rect.right/2,Rect.bottom/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.Width(),Rect.Height(),&Picture,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
    DrawScene(&MemDC);	
	pDC->BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.right,Rect.bottom,&MemDC,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();	
}

void CTestView::DrawScene(CDC *pDC)//绘制场景
{
	CRect Rect;
	GetClientRect(&Rect);
	CBrush  NewBrush[6],*OldBrush;
	//绘制矩形块
	for(int i=0;i<6;i++)
	{  		
		NewBrush[i].CreateSolidBrush(RGB[i]);
		OldBrush=pDC->SelectObject(&NewBrush[i]);
		pRect[i]->DrawRectangle(pDC);
		int flagB,flagS;
		flagB=TestB(*pRect[i],Rect.right,Rect.bottom);//测试边界碰撞
		HitB(*pRect[i],flagB);//边界碰撞速度计算
		for(int j=0;j<6;j++)//测试矩形块之间的碰撞
		{
			if(j!=i)//不与自身进行检测
			{
				flagS=TestS(*pRect[i],*pRect[j]);//矩形块之间测试
				HitS(*pRect[i],*pRect[j],flagS);//速度计算
			}
		}
		pRect[i]->MoveRectangle();
	    pDC->SelectObject(OldBrush);
	    NewBrush[i].DeleteObject();
	}
}
int CTestView::TestB(CRectangle rect,double width,double height)//测试边界碰撞 
{
	double halfBW=width/2;//半边界的宽度 
	double halfBH=height/2;//半边界的高度
	double halfRW=rect.Width/2;//矩形块半宽
	double halfRH=rect.Height/2;//矩形块半高
	if(fabs(rect.X)+halfRW >= halfBW && fabs(rect.Y)+halfRH >= halfBH)//矩形块位于客户区的四个对角
		return Allhit;
	if(fabs(rect.X)+halfRW >= halfBW)//矩形块位于客户区左右边界
		return Xhit;
	if(fabs(rect.Y)+halfRH >= halfBH)//矩形块位于客户区上下边界
		return Yhit;
	return Nohit;
}
int CTestView::TestS(CRectangle rect1,CRectangle rect2)//测试矩形块之间碰撞
{
	double DX=fabs(rect1.X-rect2.X);//两个矩形块中心点的x方向的距离
	double DY=fabs(rect1.Y-rect2.Y);//两个矩形块中心点的Y方向的距离
	double halfRW12=(rect1.Width+rect2.Width)/2;//两个矩形块中心点的x方向的最小距离
	double halfRH12=(rect1.Height+rect2.Height)/2;//两个矩形块中心点的Y方向的最小距离
	if(DX <= halfRW12 && DY <= halfRH12)//发生碰撞
	{
		double PreDX,PreDY,SpdX,SpdY;//上一个时刻物体间的距离，物体运动的合速度
		PreDX=fabs((rect1.X-rect1.SpeedX)-(rect2.X-rect2.SpeedX));
		PreDY=fabs((rect1.Y-rect1.SpeedY)-(rect2.Y-rect2.SpeedY));
		//计算X方向上的合速度分量
		if( rect1.SpeedX * rect2.SpeedX < 0 )		//两个矩形块移动方向相反的情况
		{
			SpdX=fabs(rect1.SpeedX)+fabs(rect2.SpeedX);
		}
		else							    	//两个矩形块移动方向相同的情况
		{
			if(fabs(rect1.SpeedX) >= fabs(rect2.SpeedX))	//用速度大的减去速度小的
				SpdX=fabs(rect1.SpeedX)-fabs(rect2.SpeedX);
			else
				SpdX=fabs(rect2.SpeedX)-fabs(rect1.SpeedX);
		}
		//计算Y方向上的合速度分量
		if( rect1.SpeedY * rect2.SpeedY < 0 )
		{
			SpdY=fabs(rect1.SpeedY)+fabs(rect2.SpeedY);
		}
		else
		{
			if(fabs(rect1.SpeedY) >= fabs(rect2.SpeedY))
				SpdY=fabs(rect1.SpeedY)-fabs(rect2.SpeedY);
			else
				SpdY=fabs(rect2.SpeedY)-fabs(rect1.SpeedY);
		}
		//判断碰撞时发生在X方向上还是Y方向上
		if(PreDX > halfRW12 && PreDY <= halfRH12)
			return Xhit;
		if(PreDX <= halfRW12 && PreDY > halfRH12)
			return Yhit;
		if(PreDX > halfRW12 && PreDY > halfRH12)
		{
			double SX=fabs(PreDX-halfRW12);
			double SY=fabs(PreDY-halfRH12);
			double TX=SX/SpdX;
			double TY=SY/SpdY;
			if(TX>TY)
			{
				return Yhit;
			}
			else if(TX<TY)
			{
				return Xhit;
			}
			else if(TX==TY)
				return Allhit;
		}
	}
	return Nohit;
}

void CTestView::HitB(CRectangle &rect,int flag)//速度计算 
{
	if(flag==3)//如果没有发生碰撞，则直接返回主程序
		return ;
	//如果发生碰撞
	if(flag==0)//x方向碰撞
	{
		rect.SpeedX=-rect.SpeedX;
	}
	if(flag==1)//y方向碰撞
	{
		rect.SpeedY=-rect.SpeedY;
	}
	if(flag==2)//x和y方向碰撞
	{
		rect.SpeedX=-rect.SpeedX;
		rect.SpeedY=-rect.SpeedY;
	}
}

void CTestView::HitS(CRectangle &rect1,CRectangle &rect2,int flag)//速度计算
{
	if(flag==3)//如果没有发生碰撞，则直接返回主程序
		return ;
	//如果发生碰撞
	double m1=rect1.Width*rect1.Height;//计算矩形块面积，面积模拟质量
	double m2=rect2.Width*rect2.Height;//计算矩形块面积，面积模拟质量
	double v1x,v2x,v1y,v2y;//矩形块移动速度
	if(flag==0)//x方向碰撞
	{
		v2x=(2*m1*rect1.SpeedX+(m2-m1)*rect2.SpeedX)/(m1+m2);//速度计算公式
		v1x=v2x+rect2.SpeedX-rect1.SpeedX;//速度计算公式
		rect1.SpeedX=v1x;
		rect2.SpeedX=v2x;
	}
	if(flag==1)//y方向碰撞
	{
		v2y=(2*m1*rect1.SpeedY+(m2-m1)*rect2.SpeedY)/(m1+m2);
		v1y=v2y+rect2.SpeedY-rect1.SpeedY;
		rect1.SpeedY=v1y;
		rect2.SpeedY=v2y;
	}
	if(flag==2)//x和y方向碰撞
	{
		v2x=(2*m1*rect1.SpeedX+(m2-m1)*rect2.SpeedX)/(m1+m2);
		v1x=v2x+rect2.SpeedX-rect1.SpeedX;
		v2y=(2*m1*rect1.SpeedY+(m2-m1)*rect2.SpeedY)/(m1+m2);
		v1y=v2y+rect2.SpeedY-rect1.SpeedY;
		rect1.SpeedX=v1x;
		rect2.SpeedX=v2x;
		rect1.SpeedY=v1y;
		rect2.SpeedY=v2y;
	}
}

void CTestView::OnTimer(UINT nIDEvent)//设置定时器 
{
	// TODO: Add your message handler code here and/or call default
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnMenuPlay()//动画按钮 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//设置动画的时间步
		SetTimer(1,1,NULL);	
	else
		KillTimer(1);
	
}

void CTestView::OnUpdateMenuPlay(CCmdUI* pCmdUI)//动画按钮状态 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
