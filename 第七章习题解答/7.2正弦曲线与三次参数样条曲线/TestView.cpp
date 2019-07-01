// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//四舍五入
#define PI 3.1415926//圆周率
#include "math.h"//数学头文件
#include "MainFrm.h"
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
	ON_COMMAND(ID_MENUParaSpline, OnMENUParaSpline)
	ON_COMMAND(ID_MENUSin, OnMENUSin)
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
	px[1]=-360;py[1]=0;//定义型值点
	px[2]=-315;py[2]=-71;
	px[3]=-270;py[3]=-100;
	px[4]=-225;py[4]=-71;
	px[5]=-180;py[5]=0;
	px[6]=-135;py[6]=71;
	px[7]=-90;py[7]=100;
	px[8]=-45;py[8]=71;
	px[9]=0;py[9]=0;
	px[10]=45;py[10]=-71;
	px[11]=90;py[11]=-100;
	px[12]=135;py[12]=-71;
	px[13]=180;py[13]=0;
	px[14]=225;py[14]=71;
	px[15]=270;py[15]=100;
	px[16]=315;py[16]=71;
	px[17]=360;py[17]=0;
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
	DrawPoint();
	pDC->MoveTo(0,MaxY/2);//划中线
	pDC->LineTo(MaxX,MaxY/2);
	
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
void CTestView::DrawPoint()//绘制型值点
{
	CClientDC dc(this);	
	CPen NewPen,*OldPen;
	CBrush NewBrush,*OldBrush;
	NewPen.CreatePen(PS_SOLID,1,RGB(255,255,0));
	OldPen=dc.SelectObject(&NewPen);
	NewBrush.CreateSolidBrush(RGB(0,0,0));
	OldBrush=dc.SelectObject(&NewBrush);
	for(int i=1;i<N;i++)
	{
		dc.Ellipse(ROUND(px[i]-5+MaxX/2),ROUND(py[i]-5+MaxY/2),ROUND(px[i]+5+MaxX/2),ROUND(py[i]+5+MaxY/2));//椭圆的4个坐标点		
	}
	dc.SelectObject(OldPen);
	NewPen.DeleteObject();
	dc.SelectObject(OldBrush);
	NewBrush.DeleteObject();
}

void CTestView::ParaSpline()//三次参数样条曲线
{//将参数分别投影到x,y方向求解
	double L[N];//样条曲线的参数为弦长
    double lmdx[N],mux[N],Dx[N];
    double lmdy[N],muy[N],Dy[N];
    double lx[N],mx[N],ux[N];
    double ly[N],my[N],uy[N];
    double Mx[N],Kx[N];
    double My[N],Ky[N];
    double B1x[N],B2x[40],B3x[N],B4x[N];//x方向系数数组
    double B1y[N],B2y[N],B3y[N],B4y[N];//y方向系数数组
    double dx[N],dy[N];
    double x,y,t;
    for(int i=1;i<=n-1;i++)
    {
		dx[i]=px[i+1]-px[i];dy[i]=py[i+1]-py[i];
		L[i]=sqrt(dx[i]*dx[i]+dy[i]*dy[i]);//计算弦长
		
    }
    //x方向
	for(i=2;i<=n-1;i++)
    {
		lmdx[i]=L[i-1]/(L[i-1]+L[i]);
		mux[i]=L[i]/(L[i-1]+L[i]);
		Dx[i]=6/(L[i-1]+L[i])*((px[i+1]-px[i])/L[i]-(px[i]-px[i-1])/L[i-1]);
	}
	//计算夹持端边界条件x方向的系数
    Dx[1]=0;Dx[n]=0;
	mux[1]=1;lmdx[n]=1;
     //y方向
	for(i=2;i<=n-1;i++)
    {
		lmdy[i]=L[i-1]/(L[i-1]+L[i]);
		muy[i]=L[i]/(L[i-1]+L[i]);
		Dy[i]=6/(L[i-1]+L[i])*((py[i+1]-py[i])/L[i]-(py[i]-py[i-1])/L[i-1]);
	}
	//计算夹持端边界条件y方向的系数
	Dy[1]=0;Dy[n]=0;
	muy[1]=1;lmdy[n]=1;
	lx[1]=2;ux[1]=mux[1]/lx[1];//追赶法求解x方向三弯矩方程
	for(i=2;i<=n;i++)
    {
		mx[i]=lmdx[i];
		lx[i]=2-mx[i]*ux[i-1];
		ux[i]=mux[i]/lx[i];
	}
    Kx[1]=Dx[1]/lx[1];
    for(i=2;i<=n;i++)
    {
		Kx[i]=(Dx[i]-mx[i]*Kx[i-1])/lx[i];
	}
	Mx[n]=Kx[n];
	for(i=n-1;i>=1;i--)
	{
		Mx[i]=Kx[i]-ux[i]*Mx[i+1];
    }
    ly[1]=2;uy[1]=muy[1]/ly[1];//追赶法求解y方向三弯矩方程
    for(i=2;i<=n;i++)
    {
		my[i]=lmdy[i];
		ly[i]=2-my[i]*uy[i-1];
		uy[i]=muy[i]/ly[i];
	}
    Ky[1]=Dy[1]/ly[1];
    for(i=2;i<=n;i++)
    {
		Ky[i]=(Dy[i]-my[i]*Ky[i-1])/ly[i];
	}
	My[n]=Ky[n];
	for(i=n-1;i>=1;i--)
	{
		My[i]=Ky[i]-uy[i]*My[i+1];
    }
    for(i=1;i<=n-1;i++)//计算三次参数样条函数的x方向系数
    {
		B1x[i]=px[i];
        B2x[i]=(px[i+1]-px[i])/L[i]-L[i]*(Mx[i]/3+Mx[i+1]/6);
        B3x[i]=Mx[i]/2;
        B4x[i]=(Mx[i+1]-Mx[i])/(6*L[i]);
    }
    for(i=1;i<=n-1;i++)//计算三次参数样条函数的y方向系数
	{
		B1y[i]=py[i];
		B2y[i]=(py[i+1]-py[i])/L[i]-L[i]*(My[i]/3+My[i+1]/6);
		B3y[i]=My[i]/2;
		B4y[i]=(My[i+1]-My[i])/(6*L[i]);
    }
	CClientDC dc(this);	
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	OldPen=dc.SelectObject(&NewPen);
	dc.MoveTo(ROUND(px[1]+MaxX/2),ROUND(py[1]+MaxY/2));
    for(i=1;i<=n-1;i++)//绘制样条曲线
    {
		for(t=0;t<=L[i];t++)//遍历型值点，分别绘制各段三次样条曲线
        {
			x=B1x[i]+B2x[i]*t+B3x[i]*t*t+B4x[i]*t*t*t;
            y=B1y[i]+B2y[i]*t+B3y[i]*t*t+B4y[i]*t*t*t;
			dc.LineTo(ROUND(x+MaxX/2),ROUND(y+MaxY/2));
		}
    }
    dc.SelectObject(OldPen);
	NewPen.DeleteObject();		
}
void CTestView::SinCurve()//正弦曲线
{
	CClientDC dc(this);	
	double y;
	for(int i=0;i<=720;i++)
	{
		y=100*sin(i*PI/180);
		dc.SetPixel(ROUND(i+MaxX/2+px[1]),ROUND(MaxY/2-y),RGB(0,0,255));
	}   
}
void CTestView::OnMENUParaSpline() 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("曲线和曲面:三次参数样条曲线");
	n=N-1;
	ParaSpline();
}

void CTestView::OnMENUSin() 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("曲线和曲面:正弦曲线");
	SinCurve();
}
