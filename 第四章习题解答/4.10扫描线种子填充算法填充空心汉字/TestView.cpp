// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "vector"
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
	ON_COMMAND(ID_MENUFill, OnMENUFill)
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
	Fillcolor=RGB(0,0,255);
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
	GetClientRect(&Rect);
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);	
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
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

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//左键按下函数 
{
	// TODO: Add your message handler code here and/or call default
	Seed=point;//选择种子位置
	CharFill();//进行填充
	CView::OnLButtonDown(nFlags, point);
}
void CTestView::CharFill()//文字填充函数
{
	CRect Rect;
	GetClientRect(&Rect);
	CClientDC dc(this);
	COLORREF BoundColor;//边界色
	int Width=Rect.right-Rect.left;
	int Hight=Rect.bottom-Rect.top ;
	int Flag;
	int x0,y0,x,y;
	CPoint Point;
	std::vector<CPoint> FillBuffle;//定义CPoint类型的数组序列对象
	FillBuffle.reserve(10);//定义数组序列的大小
	FillBuffle.push_back(CPoint(Seed)); //把种子结点压入数组序列
	BoundColor=RGB(0,0,0);//定义边界色为黑色
	while(!FillBuffle.empty())//如果数组序列非空
	{
      	Point=FillBuffle.front();//弹出数组序列头元素
		x=Point.x;y=Point.y;
		FillBuffle.erase(FillBuffle.begin());//清除数组序列内的元素
		dc.SetPixel(Point,Fillcolor);//绘制像素
		//判断像素的位置是否在图形内部
		x0=x+1;//右方判断
		while(dc.GetPixel(x0,y)!=BoundColor&&dc.GetPixel(x0,y)!=Fillcolor)
		{
			x0=x0+1;
			if(x0>=Width)//到达屏幕最右端
			{
				MessageBox("种子超出范围","警告");
			    RedrawWindow();
				return;
			}
		}
		y0=y+1;//下方判断
        while(dc.GetPixel(x,y0)!=BoundColor&&dc.GetPixel(x,y0)!=Fillcolor)
		{
			y0=y0+1;
			if(y0>=Hight)//到达屏幕最下端
			{
				MessageBox("种子超出范围","警告");
				RedrawWindow();
				return;
			}
		}
		RightPoint.x=x0;//右边界内的左邻点
		x0=x-1;
		while(dc.GetPixel(x0,y)!=Fillcolor&&dc.GetPixel(x0,y)!=BoundColor)
		{
			dc.SetPixel(x0,y,Fillcolor);
			x0=x0-1;
			if(x0<=0)//到达屏幕最左端
			{
				MessageBox("种子超出范围","警告");
				RedrawWindow();
				return;
			}
		}
		y0=y-1;
        while(dc.GetPixel(x,y0)!=BoundColor&&dc.GetPixel(x,y0)!=Fillcolor)
		{
			y0=y0-1;
			if(y0<=0)//到达屏幕最上端
			{
				MessageBox("种子超出范围","警告");
				RedrawWindow();
				return;
			}
		}
		LeftPoint.x=x0+1;//左边界内的右邻点
		x0=LeftPoint.x;
		y=y+1;//下一条扫描线
		while(x0<RightPoint.x)
		{
			Flag=0;
			while((dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor))
			{
				if(Flag==0)
					Flag=1;
				x0++ ;
			}
			if(Flag==1)
			{
				if((x0==RightPoint.x)&&(dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor))
					FillBuffle.push_back(CPoint(x0,y));//进入数组序列
				else
				{
					
					FillBuffle.push_back(CPoint(x0-1,y));
				}
				Flag=0;
			}
			PointNext.x=x0;
			while(((dc.GetPixel(x0,y)==Fillcolor)&&(x0<RightPoint.x))||((dc.GetPixel(x0,y)==BoundColor)&&(x0<RightPoint.x)))
			{
				x0 ++;
			}
		}
        x0=LeftPoint.x;
		y=y-2;
		while(x0<RightPoint.x)
		{
			Flag=0;
			while((dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor)&&(x0<RightPoint.x))
			{
				if(Flag==0)
					Flag=1;
				x0++ ;
			}
			if(Flag==1)
			{
				if((x0==RightPoint.x)&&(dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor))
					FillBuffle.push_back(CPoint(x0,y));
				else
				{
					
					FillBuffle.push_back(CPoint(x0-1,y));
				}
				Flag=0;
			}
			PointNext.x=x0;
			while((dc.GetPixel(x0,y)==Fillcolor&&x0<RightPoint.x)||(dc.GetPixel(x0,y)==BoundColor&&x0<RightPoint.x))
			{
				x0++;
			}
		}
	}
	FillBuffle.clear();
	return;
}

void CTestView::OnMENUFill() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	MessageBox("请在空心字体内部单击鼠标左键!","提示");
}
