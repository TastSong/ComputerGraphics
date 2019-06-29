// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "stack_node.h"//包含结点类头文件
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
	ON_COMMAND(ID_MENUNP, OnMenunp)
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
	//设置连通域	
	Point[0]=CPoint(300,500);
	Point[1]=CPoint(501,500);
	Point[2]=CPoint(501,301);
	Point[3]=CPoint(700,301);
	Point[4]=CPoint(700,100);
	Point[5]=CPoint(500,100);
	Point[6]=CPoint(500,300);
	Point[7]=CPoint(300,300);
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
	pDC->Polygon(Point,8);//new:绘制多边形
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
void CTestView::PolygonFill()//区域填充
{
	CClientDC *dc;
	dc=new CClientDC(this);
	COLORREF FillColor,BoundaryColor,PixelColor;
	BoundaryColor=RGB(0,0,0);//边界色为黑色
	FillColor=RGB(0,0,255);//填充色为蓝色		
	Head=new CStack_Node();
	Head->PixelPoint=Seed;
	Head->next=NULL;
	while(Head!=NULL)
	{	
		CStack_Node *poppoint;
		poppoint=Pop();
		if(NULL==poppoint)
		{
			dc->TextOut(10,10,"填充完毕");
			dc->DeleteDC();
			return;
		}
		Last=Base;
		dc->SetPixel(poppoint->PixelPoint,FillColor);//画种子蓝色
		//左
		PLeft.x=poppoint->PixelPoint.x-1;
		PLeft.y=poppoint->PixelPoint.y;
		PixelColor=dc->GetPixel(PLeft.x,PLeft.y);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{//不在边界并且不是种子		
			Push(PLeft);
		}
		//上
		PTop.x=poppoint->PixelPoint.x;
		PTop.y=poppoint->PixelPoint.y+1;
		PixelColor=dc->GetPixel(PTop);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{		
			Push(PTop);
		}
		//右
		PRight.x=poppoint->PixelPoint.x+1;
		PRight.y=poppoint->PixelPoint.y;
		PixelColor=dc->GetPixel(PRight);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{		
			Push(PRight);
		}
		//下
		PBottom.x=poppoint->PixelPoint.x;
		PBottom.y=poppoint->PixelPoint.y-1;
		PixelColor=dc->GetPixel(PBottom);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PBottom);
		}
		//左上
		PLeftTop.x=poppoint->PixelPoint.x-1;
		PLeftTop.y=poppoint->PixelPoint.y+1;
		PixelColor=dc->GetPixel(PLeftTop.x,PLeftTop.y);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PLeftTop);
		}
		//右上
		PRightTop.x=poppoint->PixelPoint.x+1;
		PRightTop.y=poppoint->PixelPoint.y+1;
		PixelColor=dc->GetPixel(PRightTop);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{		
			Push(PRightTop);
		}
		//左下
		PLeftBottom.x=poppoint->PixelPoint.x-1;
		PLeftBottom.y=poppoint->PixelPoint.y-1;
		PixelColor=dc->GetPixel(PLeftBottom);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PLeftBottom);
		}
		//右下
		PRightBottom.x=poppoint->PixelPoint.x+1;
		PRightBottom.y=poppoint->PixelPoint.y-1;
		PixelColor=dc->GetPixel(PRightBottom);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PRightBottom);
		}				
	}
}

void CTestView::Push(CPoint point)//入栈函数
{
	Base=Head;
	Last=new CStack_Node;
	Last->PixelPoint=point;
	Last->next=NULL;
	if(NULL==Base)
	{
		Head=Last;
		return;
	}
	while(NULL!=Base->next)
	{
		Base=Base->next;//指向新建的结点
	}
	Base->next=Last;
}

CStack_Node *CTestView::Pop()//出栈函数
{
	//弹出最后一个元素的指针
	Base=Head;
	if(NULL==Base->next)//把弹出后的最后一个指针指向NULL
	{
		Head=NULL;
		return Base;
	}
	while(NULL!=Base->next)
	{
		Base=Base->next;
		if(Base->next==Last) 
		{
			Base->next=NULL;
			return Last;
		}
	}
	return NULL;
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//左键按下函数 
{
	// TODO: Add your message handler code here and/or call default
	Seed.x=point.x;//鼠标选择种子位置
	Seed.y=point.y;
	PolygonFill();//进行填充
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnMenunp()//菜单函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();//显示标题
	MessageBox("请在区域内部选取种子点","提示",MB_OK);
}
