// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "math.h"//new
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//四舍五入
#define PI 3.1415926//圆周率
#define Thta PI/180//旋转角
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
	ON_COMMAND(ID_MENURotatecube, OnMENURotatecube)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENURotatecube, OnUpdateMENURotatecube)
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
	a=0;b=0;c=0;//初始角度	
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
	GetMaxX();GetMaxY();
	ReadCube();
	DrawCube();
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
void CTestView::ReadCube()//读入顶点表
{
	//后面的三维坐标
	double a=150;
	P[0].x=-a;P[0].y=-a;P[0].z=-a;
	P[1].x=a;P[1].y=-a;P[1].z=-a;
	P[2].x=a;P[2].y=a;P[2].z=-a;
	P[3].x=-a;P[3].y=a;P[3].z=-a;
	//前面的三维坐标
	P[4].x=-a;P[4].y=-a;P[4].z=a;
	P[5].x=a;P[5].y=-a;P[5].z=a;
	P[6].x=a;P[6].y=a;P[6].z=a;
	P[7].x=-a;P[7].y=a;P[7].z=a;
}

void CTestView::Fill(POINT *x, POINT *y, POINT *z, int i, int j, int q)//填充函数
{
	CRect Rect;
	GetClientRect(&Rect);
	CDC MemDC;
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	MemDC.CreateCompatibleDC(GetDC());
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);
	CBrush NewBrush[6];
	NewBrush[0].CreateSolidBrush(RGB(255,0,255));
	NewBrush[1].CreateSolidBrush(RGB(0,0,255));
	NewBrush[2].CreateSolidBrush(RGB(255,0,0));
	NewBrush[3].CreateSolidBrush(RGB(0,255,0));
	NewBrush[4].CreateSolidBrush(RGB(255,255,0));
	NewBrush[5].CreateSolidBrush(RGB(0,255,255));
	CBrush *OldBrush=MemDC.SelectObject(&NewBrush[i]);
	MemDC.Polygon(x,4);
	MemDC.SelectObject(&NewBrush[j]);
	MemDC.Polygon(y,4);
	MemDC.SelectObject(&NewBrush[q]);
	MemDC.Polygon(z,4);
	MemDC.SelectObject(OldBrush);
	for(int n=0;n<6;n++)
		NewBrush[n].DeleteObject();
	CClientDC dc(this);
	dc.BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(OldBitmap);
}

void CTestView::DrawCube()
{	
	ReadCube();
	CPoint p0[4],p1[4],p2[4],p3[4],p4[4],p5[4],w[8];
	int z[8];
	for(int i=0;i<8;i++)//三维坐标旋转
	{
		R[i].x=P[i].x;//绕x轴旋转
		R[i].y=ROUND(P[i].y*cos(a*Thta)-P[i].z*sin(a*Thta));
		R[i].z=ROUND(P[i].y*sin(a*Thta)+P[i].z*cos(a*Thta));

		P[i].x=ROUND(R[i].x*cos(b*Thta)+R[i].z*sin(b*Thta));
		P[i].y=R[i].y;//绕y轴旋转
		P[i].z=ROUND(R[i].z*cos(b*Thta)-R[i].x*sin(b*Thta));

		R[i].x=ROUND(P[i].x*cos(c*Thta)-P[i].y*sin(c*Thta));
		R[i].y=ROUND(P[i].x*sin(c*Thta)+P[i].y*cos(c*Thta));
		R[i].z=P[i].z;//绕z轴旋转

		w[i].x=ROUND(R[i].x+MaxX/2);
		w[i].y=ROUND(R[i].y+MaxY/2);
		z[i]=ROUND(R[i].z);
	}
	p0[0]=w[0];p0[1]=w[1];p0[2]=w[2];p0[3]=w[3];//面表
	p1[0]=w[4];p1[1]=w[5];p1[2]=w[6];p1[3]=w[7];
    p2[0]=w[0];p2[1]=w[1];p2[2]=w[5];p2[3]=w[4];
	p3[0]=w[1];p3[1]=w[2];p3[2]=w[6];p3[3]=w[5];
	p4[0]=w[2];p4[1]=w[3];p4[2]=w[7];p4[3]=w[6];
	p5[0]=w[0];p5[1]=w[3];p5[2]=w[7];p5[3]=w[4];
	int k=Maxnum(z,8);
	switch (k)
	{
		case 0: Fill(p0,p2,p5,0,2,5);break;
		case 1: Fill(p0,p2,p3,0,2,3);break;
		case 2: Fill(p0,p3,p4,0,3,4);break;
		case 3: Fill(p0,p4,p5,0,4,5);break;
		case 4: Fill(p1,p2,p5,1,2,5);break;
		case 5: Fill(p1,p2,p3,1,2,3);break;
		case 6: Fill(p1,p3,p4,1,3,4);break;
		case 7: Fill(p1,p4,p5,1,4,5);break;
	}
}

int CTestView::Maxnum(int *p, int n)//排序
{
	int x=0,max=p[0];
	for(int i=0;i<n;i++)
	{
		if(p[i]>max)
		{
			max=p[i];
			x=i;
		}
	}
	return x;
}
void CTestView::OnMENURotatecube() 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//设置动画的时间步
		SetTimer(1,15,NULL);	
	else
		KillTimer(1);	
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
		case VK_UP:
			a+=1;
			break;
		case VK_LEFT:		
			b+=1;
			break;
		case VK_RIGHT:
			c+=1;
			break;
		case VK_DOWN:
			a=0;b=0;c=0;
			break;
		default:
			break;
	}	
	DrawCube();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnTimer(UINT nIDEvent)//动画时间函数 
{
	// TODO: Add your message handler code here and/or call default
	a-=1;//设定步长
	b-=1;
	DrawCube();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENURotatecube(CCmdUI* pCmdUI)//动画按钮控制 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
