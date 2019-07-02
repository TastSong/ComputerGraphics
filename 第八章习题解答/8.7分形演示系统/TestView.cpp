// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//四舍五入
#include "math.h"//数学头文件
#define PI 3.1415926//圆周率
#define DX d*cos(PI/4)//斜边的投影
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
	ON_COMMAND(ID_MENU_CANTOR, OnMenuCantor)
	ON_COMMAND(ID_MENU_KOCH, OnMenuKoch)
	ON_UPDATE_COMMAND_UI(ID_BTN_ADD, OnUpdateBtnAdd)
	ON_UPDATE_COMMAND_UI(ID_BTN_SUB, OnUpdateBtnSub)
	ON_COMMAND(ID_BTN_ADD, OnBtnAdd)
	ON_COMMAND(ID_BTN_SUB, OnBtnSub)
	ON_COMMAND(ID_MENU_KOCHSNOW, OnMenuKochsnow)
	ON_COMMAND(ID_MENU_PEANO, OnMenuPeano)
	ON_COMMAND(ID_MENU_GASKET, OnMenuGasket)
	ON_COMMAND(ID_MENU_CARPET, OnMenuCarpet)
	ON_COMMAND(ID_MENU_C, OnMenuC)
	ON_COMMAND(ID_MENU_CALEY, OnMenuCaley)
	ON_COMMAND(ID_MENU_SPONGE, OnMenuSponge)
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
	Add_Flag=FALSE;//增加按钮的初始状态为无效
	Sub_Flag=FALSE;//减少按钮的初始状态为无效
	BKColor=RGB(0,128,0);//屏幕背景色
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
void CTestView::GetMaxX()//获得屏幕x方向最大值
{
	CRect rect;
	GetClientRect(rect);
    MaxX=rect.right;
}

void CTestView::GetMaxY()//获得屏幕y方向最大值
{
	CRect rect;
	GetClientRect(rect);
    MaxY=rect.bottom;
}
void CTestView::Cantor(int n,double ax, double ay, double bx, double by)//Cantor函数
{
	CClientDC dc(this);
	if(n==0)
    {
		CPen NewPen,*OldPen;
		NewPen.CreatePen(PS_SOLID,1,Color);
		OldPen=dc.SelectObject(&NewPen);
		dc.MoveTo(ROUND(ax),ROUND(ay+MaxY/2));
		dc.LineTo(ROUND(bx),ROUND(by+MaxY/2));
		dc.SelectObject(OldPen);
		NewPen.DeleteObject();
		return;
	}
	double cx,cy,dx,dy;
	cx=ax+(bx-ax)/3;cy=ay ;    
    Cantor(n-1,ax,ay,cx,cy);
    dx=ax+2*(bx-ax)/3;dy=by ;
    Cantor(n-1,dx,dy,bx,by);
}
void CTestView::Koch(int n, double theta)//koch函数
{
	CClientDC dc(this);
	if(n==0)
    {
		bx+=d*cos(alpha*PI/180);
		by+=d*sin(alpha*PI/180);
		CPen NewPen,*pOldPen;
		NewPen.CreatePen(PS_SOLID,1,Color);
		pOldPen=dc.SelectObject(&NewPen);
		dc.MoveTo(ROUND(ax),ROUND(MaxY-100-ay));
		dc.LineTo(ROUND(bx),ROUND(MaxY-100-by));
		dc.SelectObject(pOldPen);
		NewPen.DeleteObject();
		ax=bx;ay=by;
		return;
     }
	 Koch(n-1,theta);
     alpha+=theta;
     Koch(n-1,theta);
     alpha-=2*theta;
     Koch(n-1,theta);
     alpha+=theta;
     Koch(n-1,theta);
}
void CTestView::Koch1(int n)//雪花函数
{
	CClientDC dc(this);
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,Color);
	OldPen=dc.SelectObject(&NewPen);
	if(n==0)
    {
		bx+=d*cos(alpha*PI/180);
		by+=d*sin(alpha*PI/180);
		dc.MoveTo(ROUND(ax+300),ROUND(ay+MaxY-200));
		dc.LineTo(ROUND(bx+300),ROUND(by+MaxY-200));
		ax=bx;ay=by;
		dc.SelectObject(NewPen);
		NewPen.DeleteObject();
		return;
	}
	Koch1(n-1);
	alpha+=60;
	Koch1(n-1);
	alpha-=120;
	Koch1(n-1);
	alpha+=60;
	Koch1(n-1);
}

void CTestView::Koch2(int n)//雪花函数
{
	CClientDC dc(this);
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,Color);
	OldPen=dc.SelectObject(&NewPen);
	if(n==0)
    {
		bx+=d*cos((alpha+60)*PI/180);
		by+=d*sin((alpha+60)*PI/180);
		dc.MoveTo(ROUND(ax+300),ROUND(MaxY-200-ay));
		dc.LineTo(ROUND(bx+300),ROUND(MaxY-200-by));
		ax=bx;ay=by;
		dc.SelectObject(NewPen);
		NewPen.DeleteObject();
		return;
	}
	Koch2(n-1);
	alpha+=60;
	Koch2(n-1);
	alpha-=120;
	Koch2(n-1);
	alpha+=60;
	Koch2(n-1);
}

void CTestView::Koch3(int n)//雪花函数
{
	CClientDC dc(this);
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,Color);
	OldPen=dc.SelectObject(&NewPen);
	if(n==0)
    {
		bx+=d*cos((alpha-120)*PI/180);
		by+=d*sin((alpha-120)*PI/180);
		dc.MoveTo(ROUND(ax+720),ROUND(ay+MaxY-200));
		dc.LineTo(ROUND(bx+720),ROUND(by+MaxY-200));
		ax=bx;ay=by;
		dc.SelectObject(NewPen);
		NewPen.DeleteObject();
		return;
	}
	Koch3(n-1);
	alpha+=60;
	Koch3(n-1);
	alpha-=120;
	Koch3(n-1);
	alpha+=60;
	Koch3(n-1);
}
void CTestView::Peano(int n,int s,double x1,double y1,double x2,double y2)//Peano曲线函数
{
	CClientDC dc(this);
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,Color);
	OldPen=dc.SelectObject(&NewPen);
	double dx,dy;
	if(n==0)
	{
		
		dx=x2-x1;dy=y2-y1;
		dc.MoveTo(ROUND(x),ROUND(y));
		dc.LineTo(ROUND(x1+dx/4),ROUND(y1+dy/4));
		dc.LineTo(ROUND(x1+(2-s)*dx/4),ROUND(y1+(2+s)*dy/4));
		dc.LineTo(ROUND(x1+3*dx/4),ROUND(y1+3*dy/4));
		dc.LineTo(ROUND(x1+(2+s)*dx/4),ROUND(y1+(2-s)*dy/4));
		x=x1+(2+s)*dx/4;y=y1+(2-s)*dy/4;
		dc.SelectObject(NewPen);
		NewPen.DeleteObject();
		return;
	}
	if(s>0)
	{	
		Peano(n-1,-1,x1,y1,(x1+x2)/2,(y1+y2)/2);
		Peano(n-1,1,x1,(y1+y2)/2,(x1+x2)/2,y2);
		Peano(n-1,1,(x1+x2)/2,(y1+y2)/2,x2,y2);
		Peano(n-1,-1,x2,(y1+y2)/2,(x1+x2)/2,y1);
	}
	else
	{
		Peano(n-1,1,x1,y1,(x1+x2)/2,(y1+y2)/2);
		Peano(n-1,-1,(x1+x2)/2,y1,x2,(y1+y2)/2);
		Peano(n-1,-1,(x1+x2)/2,(y1+y2)/2,x2,y2);
		Peano(n-1,1,(x1+x2)/2,y2,x1,(y1+y2)/2);
		
	}
	dc.SelectObject(NewPen);
	NewPen.DeleteObject();
}
void CTestView::Gasket(int n,double x1, double y1, double x2, double y2,double x3, double y3)//垫片函数
{
	CClientDC dc(this);
	CPoint MT[3];
	MT[0]=CPoint(ROUND(x1),ROUND(y1));
	MT[1]=CPoint(ROUND(x2),ROUND(y2));
	MT[2]=CPoint(ROUND(x3),ROUND(y3));
	CPoint tri[3];
	tri[0]=CPoint(ROUND((x1+x2)/2),ROUND((y1+y2)/2));
	tri[1]=CPoint(ROUND((x2+x3)/2),ROUND((y2+y3)/2));
	tri[2]=CPoint(ROUND((x1+x3)/2),ROUND((y1+y3)/2));
	if(n==0)
	{
		CBrush NewBrush,*OldBrush;
		NewBrush.CreateSolidBrush(RGB(254,173,139));
		OldBrush=dc.SelectObject(&NewBrush);
		CPen NewPen,*OldPen;
		NewPen.CreatePen(PS_SOLID,1,Color);
		OldPen=dc.SelectObject(&NewPen);
		dc.Polygon(MT,3);
		dc.SelectObject(NewPen);
		NewPen.DeleteObject();
		dc.SelectObject(OldBrush);
		NewBrush.DeleteObject();
		return;
	}
	dc.BeginPath();
	dc.Polygon(tri,3);
	dc.EndPath();
	dc.FillPath();
	Gasket(n-1,x1,y1,(x1+x2)/2,(y1+y2)/2,(x1+x3)/2,(y1+y3)/2);
	Gasket(n-1,(x1+x2)/2,(y1+y2)/2,x2,y2,(x2+x3)/2,(y2+y3)/2);
	Gasket(n-1,(x1+x3)/2,(y1+y3)/2,(x2+x3)/2,(y2+y3)/2,x3,y3);
}



void CTestView::Carpet(int n,double x1, double y1, double x2, double y2)//地毯函数
{
	CClientDC dc(this);
	if(n==0)	return;
	CBrush NewBrush,*OldBrush;
	NewBrush.CreateSolidBrush(RGB(254,173,139));
	OldBrush=dc.SelectObject(&NewBrush);
	double L,W;
	L=x2-x1;W=y2-y1;	
	CRect Rect(ROUND(x1+L/3),ROUND(y1+W/3),ROUND(x2-L/3),ROUND(y2-W/3));
	dc.Rectangle(Rect);
	dc.SelectObject(OldBrush);
	NewBrush.DeleteObject();
	Carpet(n-1,x1,y1,x1+L/3,y1+W/3);
	Carpet(n-1,x1+L/3,y1,x2-L/3,y1+W/3);
	Carpet(n-1,x2-L/3,y1,x2,y1+W/3);
	Carpet(n-1,x1,y1+W/3,x1+L/3,y2-W/3);
	Carpet(n-1,x2-L/3,y1+W/3,x2,y2-W/3);
	Carpet(n-1,x1,y2-W/3,x1+L/3,y2);
	Carpet(n-1,x1+L/3,y2-W/3,x2-L/3,y2);
	Carpet(n-1,x2-L/3,y2-W/3,x2,y2);
}
void CTestView::CubicF(double x, double y, double d)//海绵的前面
{
	CClientDC dc(this);
	CBrush BrushFont;
	BrushFont.CreateSolidBrush(RGB(223,122,79));
	CBrush *OldBrush=dc.SelectObject(&BrushFont);
	dc.SelectObject(&BrushFont);
	CPoint font[4];
	font[0]=CPoint(ROUND(x),ROUND(y));
	font[1]=CPoint(ROUND(x+d),ROUND(y));
	font[2]=CPoint(ROUND(x+d),ROUND(y+d));
	font[3]=CPoint(ROUND(x),ROUND(y+d));
	dc.BeginPath();
	dc.Polygon(font,4);
	dc.EndPath();
	dc.FillPath();
	dc.SelectObject(OldBrush);
	BrushFont.DeleteObject();
}

void CTestView::CubicT(double x, double y, double d)//海绵的顶面
{
	CClientDC dc(this);
	CBrush BrushTop;
	BrushTop.CreateSolidBrush(RGB(254,173,139));
	CBrush *OldBrush=dc.SelectObject(&BrushTop);
	dc.SelectObject(&BrushTop);
	CPoint top[4];
	top[0]=CPoint(ROUND(x),ROUND(y));
	top[1]=CPoint(ROUND(x+DX),ROUND(y-DX));
	top[2]=CPoint(ROUND(x+d+DX),ROUND(y-DX));
	top[3]=CPoint(ROUND(x+d),ROUND(y));
	dc.BeginPath();
	dc.Polygon(top,4);
	dc.EndPath();
	dc.FillPath();
	dc.SelectObject(OldBrush);
	BrushTop.DeleteObject();
}

void CTestView::CubicR(double x, double y, double d)//海绵的右面
{
	CClientDC dc(this);
	CBrush BrushRight;
	BrushRight.CreateSolidBrush(RGB(177,66,66));
	CBrush *OldBrush=dc.SelectObject(&BrushRight);
	dc.SelectObject(&BrushRight);
	CPoint right[4];
	right[0]=CPoint(ROUND(x+d),ROUND(y));
	right[1]=CPoint(ROUND(x+d+DX),ROUND(y-DX));
	right[2]=CPoint(ROUND(x+d+DX),ROUND(y+d-DX));
	right[3]=CPoint(ROUND(x+d),ROUND(y+d));
	dc.BeginPath();
	dc.Polygon(right,4);
	dc.EndPath();
	dc.FillPath();
	dc.SelectObject(OldBrush);
	BrushRight.DeleteObject();
}
void CTestView::Sponge(int n, double x, double y, double d)//海绵函数
{
	double dx;
	if(n==0)
	{
		CubicF(x,y,d);
		CubicT(x,y,d);
		CubicR(x,y,d);
		return;
	}
	d=d/3;
	dx=d*cos(PI/4);
	Sponge(n-1,x+2*dx,y+2*d-2*dx,d);
	Sponge(n-1,x+2*dx+d,y+2*d-2*dx,d);
	Sponge(n-1,x+2*dx+2*d,y+2*d-2*dx,d);
	Sponge(n-1,x+dx,y+2*d-dx,d);
	Sponge(n-1,x+dx+2*d,y+2*d-dx,d);
	Sponge(n-1,x,y+2*d,d);
	Sponge(n-1,x+d,y+2*d,d);
	Sponge(n-1,x+2*d,y+2*d,d);
	Sponge(n-1,x+2*dx,y+d-2*dx,d);
	Sponge(n-1,x+2*dx+2*d,y+d-2*dx,d);
	Sponge(n-1,x,y+d,d);
	Sponge(n-1,x+2*d,y+d,d);
	Sponge(n-1,x+2*dx,y-2*dx,d);
	Sponge(n-1,x+2*dx+d,y-2*dx,d);
	Sponge(n-1,x+2*dx+2*d,y-2*dx,d);
	Sponge(n-1,x+dx,y-dx,d);
	Sponge(n-1,x+dx+2*d,y-dx,d);
	Sponge(n-1,x,y,d);
	Sponge(n-1,x+d,y,d);
	Sponge(n-1,x+2*d,y,d);
}
void CTestView::C(int n,double x1,double y1,double x2,double y2)//C字曲线函数
{
	CClientDC dc(this);
	double x3,y3;
	x3=(x1+y1+x2-y2)/2;y3=(x2+y2+y1-x1)/2;
	if(n==0)
	{
		CPen NewPen,*OldPen;
		NewPen.CreatePen(PS_SOLID,1,Color);
		OldPen=dc.SelectObject(&NewPen);
		dc.MoveTo(ROUND(x1),ROUND(y1));
		dc.LineTo(ROUND(x2),ROUND(y2));
		dc.SelectObject(OldPen);
		NewPen.DeleteObject();
		return;
	}
	C(n-1,x1,y1,x2,y2);
	C(n-1,x1,y1,x3,y3);
	C(n-1,x3,y3,x2,y2);
}
void CTestView::Caley(int n, double x, double y, double len, double theta)//Caley树函数
{
	CClientDC dc(this);
	double th1,th2;
	double x1,y1,x2,y2,x3,y3,scale;
	th1=25.0;th2=25.0;scale=0.7;
	if(n==0) return;
	x1=x+len*cos(theta*PI/180);
	y1=y+len*sin(theta*PI/180);
	x2=x1+scale*len*cos((theta+th1)*PI/180);
	y2=y1+scale*len*sin((theta+th1)*PI/180);
	x3=x1+scale*len*cos((theta-th2)*PI/180);
	y3=y1+scale*len*sin((theta-th2)*PI/180);
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,Color);
	OldPen=dc.SelectObject(&NewPen);
	dc.MoveTo(ROUND(x),ROUND(MaxY-y));
	dc.LineTo(ROUND(x1),ROUND(MaxY-y1));
	dc.LineTo(ROUND(x2),ROUND(MaxY-y2));
	dc.MoveTo(ROUND(x1),ROUND(MaxY-y1));
	dc.LineTo(ROUND(x3),ROUND(MaxY-y3));
	dc.SelectObject(OldPen);
	NewPen.DeleteObject();
	Caley(n-1,x1,y1,scale*len,theta+th1);
	Caley(n-1,x1,y1,scale*len,theta-th1);
}
void CTestView::OnMenuCantor()//Cantor菜单操作函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Cantor集");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=1;//Cantor曲线编号为1
	if (dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}	
	Cantor(n,0,0,MaxX,0);
}

void CTestView::OnMenuKoch()//Koch菜单操作函数  
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("分形演示系统:Koch曲线");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=2;//Cantor曲线编号为2
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		Koch_Theta=dlg.m_KochTheta;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	RedrawWindow();
	ax=0,ay=0,bx=0,by=0,alpha=0;
	d=MaxX/pow(2*(1+cos(Koch_Theta*PI/180)),n);
	Koch(n,Koch_Theta);
}
void CTestView::OnMenuKochsnow()//雪花菜单操作函数  
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Koch雪花");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=3;//Cantor曲线编号为3
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	ax=0,ay=0,bx=0,by=0,alpha=0;
	d=(MaxX-600)/pow(3,n);
	Koch1(n);
	ax=0,ay=0,bx=0,by=0,alpha=0;
    Koch2(n);
	ax=0,ay=0,bx=0,by=0,alpha=0;
    Koch3(n);
}
void CTestView::OnMenuPeano()//Peano曲线菜单操作函数  
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Peano曲线");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=4;//Peano曲线编号为4
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		Peano_s=dlg.m_peanoS;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	x=0;y=0;x1=0;y1=0;x2=MaxX;y2=MaxY;
	Peano(n,Peano_s,x1,y1,x2,y2);
}
void CTestView::OnMenuGasket()//垫片菜单操作函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Sier-Gasket垫片");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=5;//Gasket曲线编号为5
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	x1=100;y1=MaxY-50;x2=MaxX-100;y2=MaxY-50;x3=MaxX/2;y3=50;
	Gasket(n,x1,y1,x2,y2,x3,y3);
}
void CTestView::OnMenuCarpet()//地毯菜单操作函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Sier-Carpet地毯");
	CClientDC dc(this);
	CInputDlg dlg;
	dlg.m_flag=Flag=6;//Carpet曲线编号为6
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		carpet_x1=dlg.m_carpetX1;
		carpet_y1=dlg.m_carpetY1;
		carpet_x2=dlg.m_carpetX2;
		carpet_y2=dlg.m_carpetY2;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	CBrush NewBrush,*OldBrush;
	NewBrush.CreateSolidBrush(BKColor);
	OldBrush=dc.SelectObject(&NewBrush);
	CRect rect(ROUND(carpet_x1),ROUND(carpet_y1),ROUND(carpet_x2),ROUND(carpet_y2));
	dc.FillRect(&rect,&NewBrush);
	dc.SelectObject(OldBrush);
	NewBrush.DeleteObject();
	Carpet(n,carpet_x1,carpet_y1,carpet_x2,carpet_y2);
}
void CTestView::OnMenuSponge()//海绵菜单操作函数  
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Sier-sponge海绵");
	CInputDlg dlg;
	dlg.m_flag=Flag=7;//Carpet曲线编号为7
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		sponge_x=dlg.m_spongeX;
		sponge_y=dlg.m_spongeY;
		sponge_d=dlg.m_spongeD;
		Add_Flag=Sub_Flag=TRUE;
		Color=dlg.m_color;
	}
	else
	{
		return;
	}	
	Sponge(n,sponge_x,sponge_y,sponge_d);
}
void CTestView::OnMenuC()//C字曲线菜单操作函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:C字曲线");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=8;//C字曲线编号为8
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		c_x1=dlg.m_cX1;
		c_y1=dlg.m_cY1;
		c_x2=dlg.m_cX2;
		c_y2=dlg.m_cY2;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	C(n,c_x1,c_y1,c_x2,c_y2);
}
	
void CTestView::OnMenuCaley()//Caley树菜单操作函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	AfxGetMainWnd()->SetWindowText("分形演示系统:Caley树");
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	dlg.m_flag=Flag=9;//Caley树编号为9
	if(dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
		Color=dlg.m_color;
		caley_th=dlg.m_caleyTH;
		caley_len=dlg.m_caleyLEN;
		Add_Flag=Sub_Flag=TRUE;
	}
	else
	{
		return;
	}
	
	caley_x0=MaxX/2;caley_y0=20;
	Caley(n,caley_x0,caley_y0,caley_len,caley_th);
}

void CTestView::OnUpdateBtnAdd(CCmdUI* pCmdUI)//"增加"按钮有效函数 
{
	// TODO: Add your command update UI handler code here
	if(!Add_Flag)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CTestView::OnUpdateBtnSub(CCmdUI* pCmdUI)//"减少"按钮有效函数 
{
	// TODO: Add your command update UI handler code here
	if(!Sub_Flag)
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CTestView::OnBtnAdd()//"增加"按钮函数  
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	CBrush NewBrush,*OldBrush;
	NewBrush.CreateSolidBrush(BKColor);
	OldBrush=dc.SelectObject(&NewBrush);
	CRect Rect(ROUND(carpet_x1),ROUND(carpet_y1),ROUND(carpet_x2),ROUND(carpet_y2));
	Sub_Flag=TRUE;
	switch(Flag)
	{
	case 1://Cantor
		n++;
		if(n>=16)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		Cantor(n,0,0,MaxX,0);
		break;
	case 2://Koch
		n++;
		if(n>=10)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		ax=0,ay=0,bx=0,by=0,alpha=0;
		d=MaxX/pow(2*(1+cos(Koch_Theta*PI/180)),n);
		Koch(n,Koch_Theta);
		break;
	case 3://Snow
		n++;
		if(n>=10)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		ax=0,ay=0,bx=0,by=0,alpha=0;
		d=(MaxX-600)/pow(3,n);
		Koch1(n);
		ax=0,ay=0,bx=0,by=0,alpha=0;
		Koch2(n);
		ax=0,ay=0,bx=0,by=0,alpha=0;
		Koch3(n);
		break;
	case 4://Peano
		n++;
		if(n>=10)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		x=0;y=0;x1=0;y1=0;x2=MaxX;y2=MaxY;
		Peano(n,Peano_s,x1,y1,x2,y2);
		break;
	case 5://Gasket
		n++;
		if(n>=13)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		Gasket(n,x1,y1,x2,y2,x3,y3);
		break;
	case 6://Carpet
		n++;
		if(n>=7)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		dc.FillRect(&Rect,&NewBrush);
		Carpet(n,carpet_x1,carpet_y1,carpet_x2,carpet_y2);
		break;
	case 7://Sponge
		n++;
		if(n>=5)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		Sponge(n,sponge_x,sponge_y,sponge_d);
		break;
	case 8://C
		n++;
		if(n>=13)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		C(n,c_x1,c_y1,c_x2,c_y2);
		break;
	case 9://Caley
		n++;
		if(n>=20)
		{
			Add_Flag=FALSE;
		}
		RedrawWindow();
		Caley(n,caley_x0,caley_y0,caley_len,caley_th);
		break;
	}
	dc.SelectObject(OldBrush);
	NewBrush.DeleteObject();
}

void CTestView::OnBtnSub()//"减少"按钮函数 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	CBrush NewBrush,*OldBrush;
	NewBrush.CreateSolidBrush(BKColor);
	OldBrush=dc.SelectObject(&NewBrush);
	CRect Rect(ROUND(carpet_x1),ROUND(carpet_y1),ROUND(carpet_x2),ROUND(carpet_y2));
	Add_Flag=TRUE;
	if(n<=1) Sub_Flag=FALSE;
	switch(Flag)
	{
	case 1://Cantor
		n--;
		RedrawWindow();
		Cantor(n,0,0,MaxX,0);
		break;
	case 2://Koch
		n--;
		RedrawWindow();
		ax=0,ay=0,bx=0,by=0,alpha=0;
		d=MaxX/pow(2*(1+cos(Koch_Theta*PI/180)),n);
		Koch(n,Koch_Theta);
		break;
	case 3://Snow
		n--;
		RedrawWindow();
		ax=0,ay=0,bx=0,by=0,alpha=0;
		d=(MaxX-600)/pow(3,n);
		Koch1(n);
		ax=0,ay=0,bx=0,by=0,alpha=0;
		Koch2(n);
		ax=0,ay=0,bx=0,by=0,alpha=0;
		Koch3(n);
		break;
	case 4://Peano
		n--;
		RedrawWindow();
		x=0;y=0;x1=0;y1=0;x2=MaxX;y2=MaxY;
		Peano(n,Peano_s,x1,y1,x2,y2);
		break;
	case 5://Gasket
		n--;
		RedrawWindow();
		Gasket(n,x1,y1,x2,y2,x3,y3);
		break;
	case 6://Carpet
		n--;
		RedrawWindow();
		dc.FillRect(&Rect,&NewBrush);
		Carpet(n,carpet_x1,carpet_y1,carpet_x2,carpet_y2);
		break;
	case 7://Sponge
		n--;
		RedrawWindow();
		Sponge(n,sponge_x,sponge_y,sponge_d);
		break;
	case 8://C
		n--;
		RedrawWindow();
		C(n,c_x1,c_y1,c_x2,c_y2);
		break;
	case 9://Caley
		n--;
		if(n<=1) Sub_Flag=FALSE;
		RedrawWindow();
		Caley(n,caley_x0,caley_y0,caley_len,caley_th);
		break;
	}
	dc.SelectObject(OldBrush);
	NewBrush.DeleteObject();
	
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC)//更改屏幕背景色 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;   
	GetClientRect(&Rect);   
	pDC->FillSolidRect(Rect,BKColor);
	return true;
}
