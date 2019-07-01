// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#define ROUND(a) int(a+0.5)//四舍五入
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
	//3个顶点的初始化
	P[0][0]=350;P[0][1]=450;
	P[1][0]=450;P[1][1]=110;
	P[2][0]=700;P[2][1]=270;	
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
	CBitmap	*OldBitmap,NewBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);		
	CDC MemDC,Picture;
	MemDC.CreateCompatibleDC(GetDC());
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);	
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));//黑色画笔绘制控制多边形
	OldPen=MemDC.SelectObject(&NewPen);	
	MemDC.MoveTo(P[0][0],P[0][1]);
	MemDC.Ellipse(P[0][0]-2,P[0][1]-2,P[0][0]+2,P[0][1]+2);//绘制特征多边形顶点
	for(int i=1;i<3;i++)
	{
		MemDC.LineTo(P[i][0],P[i][1]);
		MemDC.Ellipse(P[i][0]-2,P[i][1]-2,P[i][0]+2,P[i][1]+2);
	}
	MemDC.TextOut(P[0][0],P[0][1]+5,"P0");
	MemDC.TextOut(P[1][0],P[1][1]-20,"P1");
	MemDC.TextOut(P[2][0],P[2][1]-20,"P2");
	if(Number!=-1)
	{
		CString	str;
		str.Format("x=%d y=%d,拖动鼠标移动",P[Number][0],P[Number][1]);
		MemDC.TextOut(P[Number][0]+5,P[Number][1]+5,str);
	}
	Bezier2_curves(P,&MemDC);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(OldBitmap);
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
void CTestView::Bezier2_curves(int p[][2],CDC *pDC)//绘制二次Bezier曲线
{
	int lx,ly;
	double Bern02,Bern12,Bern22;
	lx=p[0][0];ly=p[0][1];//t＝0的起点x,y坐标
	CPen NewPen(PS_SOLID,1,RGB(0,0,255));//蓝色画笔绘制Bezier曲线
	CPen *OldPen=pDC->SelectObject(&NewPen);
	pDC->MoveTo(lx,ly);
	for(double t=0;t<=1;t+=0.01)
	{
		Bern02=(1-t)*(1-t);//计算Bern0,2(t)
		Bern12=2*t*(1-t);//计算Bern1,2(t)
		Bern22=t*t;//计算Bern2,2(t)
		lx=ROUND(p[0][0]*Bern02+p[1][0]*Bern12+p[2][0]*Bern22);
		ly=ROUND(p[0][1]*Bern02+p[1][1]*Bern12+p[2][1]*Bern22);
		pDC->LineTo(lx,ly);
	}
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();
}

void CTestView::OnMenuB()//菜单函数 
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
	int i;
	for(i=0;i<3;i++)
	{//判断鼠标当前点和顶点的距离
		if((point.x-P[i][0])*(point.x-P[i][0])+(point.y-P[i][1])*(point.y-P[i][1])<100)
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

void CTestView::OnLButtonUp(UINT nFlags, CPoint point)//鼠标左键弹起函数 
{
	// TODO: Add your message handler code here and/or call default
	AbleToLeftBtn=FALSE;
	AbleToMove=FALSE;
	Number=0;
	CView::OnLButtonUp(nFlags, point);
}
