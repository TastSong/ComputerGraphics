// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#define ROUND(a) long(a+0.5)//四舍五入
#include "TestDoc.h"
#include "TestView.h"

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
	ON_COMMAND(ID_MENU_B, OnMenuB)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	AbleToLeftBtn=FALSE;
	AbleToMove=FALSE;
	Number=-1;
	//4个顶点的初始化
	P[0][0]=228;P[0][1]=456;
	P[1][0]=294;P[1][1]=247;
	P[2][0]=452;P[2][1]=123;
	P[3][0]=705;P[3][1]=197;
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
	CRect Rect;
	GetClientRect(&Rect);//获得客户区的大小
	CBitmap	*pBitmap,Bitmap;
	Bitmap.LoadBitmap(IDB_BITMAP2);		
	CDC MemDC,Picture;
	MemDC.CreateCompatibleDC(GetDC());
	pBitmap=MemDC.SelectObject(&Bitmap);
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);	
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));//黑色笔绘制控制多边形
	OldPen=MemDC.SelectObject(&NewPen);	
	MemDC.MoveTo(P[0][0],P[0][1]);
	MemDC.Ellipse(P[0][0]-2,P[0][1]-2,P[0][0]+2,P[0][1]+2);//绘制控制多边形顶点
	for(int i=1;i<4;i++)
	{
		MemDC.LineTo(P[i][0],P[i][1]);
		MemDC.Ellipse(P[i][0]-2,P[i][1]-2,P[i][0]+2,P[i][1]+2);
	}
	if(Number!=-1)
	{
		CString	str;
		str.Format("x=%d y=%d,拖动鼠标移动此点",P[Number][0],P[Number][1]);
		MemDC.TextOut(P[Number][0]+5,P[Number][1]+5,str);
	}
	B3_curves(P,&MemDC);
	Bezier3_curves(P,&MemDC);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pBitmap);
	MemDC.SelectObject(OldPen);
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
void CTestView::B3_curves(int xq[][2],CDC *pDC)//B样条曲线函数
{
	int i,rate=10;//rate是平滑程度
	long lx,ly;
	double F03,F13,F23,F33;
	lx=ROUND((xq[0][0]+4.0*xq[1][0]+xq[2][0])/6.0);//t＝0的起点x坐标
	ly=ROUND((xq[0][1]+4.0*xq[1][1]+xq[2][1])/6.0);//t＝0的起点y坐标
	pDC->MoveTo(lx,ly);
	CPen MyPen2(PS_SOLID,1,RGB(255,0,0));//红笔画B样条
	CPen *POldPen2=pDC->SelectObject(&MyPen2);
	for(i=1;i<2;i++)//2个控制三角形
	{
		for(double t=0;t<=1;t+=1.0/rate)
		{
			F03=(-t*t*t+3*t*t-3*t+1)/6;//计算F0,3(t)
			F13=(3*t*t*t-6*t*t+4)/6;//计算F1,3(t)
			F23=(-3*t*t*t+3*t*t+3*t+1)/6;//计算F2,3(t)
			F33=t*t*t/6;//计算B3,3(t)
			lx=ROUND(xq[i-1][0]*F03+xq[i][0]*F13+xq[i+1][0]*F23+xq[i+2][0]*F33);
			ly=ROUND(xq[i-1][1]*F03+xq[i][1]*F13+xq[i+1][1]*F23+xq[i+2][1]*F33);
			pDC->LineTo(lx,ly);
		}
	}
	pDC->SelectObject(POldPen2);
	MyPen2.DeleteObject();	
}

void CTestView::OnMenuB() 
{
	// TODO: Add your command handler code here
	MessageBox("请直接拖动特征多边形的顶点，观察效果！","信息",MB_ICONINFORMATION|MB_OK);		
}

void CTestView::OnMouseMove(UINT nFlags, CPoint point)//鼠标移动函数 
{
	// TODO: Add your message handler code here and/or call default
	if(AbleToMove==TRUE)
	{
		P[Number][0]=point.x;
		P[Number][1]=point.y;
	}
	Number=-1;
	for(int i=0;i<9;i++)
	{
		if((point.x-P[i][0])*(point.x-P[i][0])
			+(point.y-P[i][1])*(point.y-P[i][1])<100)
		{
			Number=i;
			AbleToLeftBtn=TRUE;
			SetCursor(LoadCursor(NULL,IDC_SIZEALL));//改变为十字箭头光标
			break;
		}
	}
	if(10==i)
	{
		Number=-1;
	}
	Invalidate(FALSE);	
	CView::OnMouseMove(nFlags, point);
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//鼠标左键按下函数 
{
	// TODO: Add your message handler code here and/or call default
	if(TRUE==AbleToLeftBtn)
	{
		AbleToMove=TRUE;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnLButtonUp(UINT nFlags, CPoint point) //鼠标左键弹起函数 
{
	// TODO: Add your message handler code here and/or call default
	AbleToLeftBtn=FALSE;
	AbleToMove=FALSE;
	Number=0;
	CView::OnLButtonUp(nFlags, point);
}
void CTestView::Bezier3_curves(int P[][2],CDC *pDC)//Bezier函数
{//绘制三次Bezier曲线
	int lx,ly,rate=100;
	double Bern03,Bern13,Bern23,Bern33;
	lx=P[0][0];ly=P[0][1];//t＝0的起点x,y坐标
	pDC->MoveTo(lx,ly);
	CPen NewPen(PS_SOLID,1,RGB(0,0,0));//黑色画笔绘制画3次Bezier曲线
	CPen *OldPen=pDC->SelectObject(&NewPen);
	for(double t=0;t<=1;t+=1.0/rate)
	{
		Bern03=(1-t)*(1-t)*(1-t);//计算Bern0,3(t)
		Bern13=3*t*(1-t)*(1-t);//计算Bern1,3(t)
		Bern23=3*t*t*(1-t);//计算Bern2,3(t)
		Bern33=t*t*t;//计算Bern3,3(t)
		lx=ROUND(P[0][0]*Bern03+P[1][0]*Bern13+P[2][0]*Bern23+P[3][0]*Bern33);
		ly=ROUND(P[0][1]*Bern03+P[1][1]*Bern13+P[2][1]*Bern23+P[3][1]*Bern33);
		pDC->LineTo(lx,ly);
	}
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();	
}