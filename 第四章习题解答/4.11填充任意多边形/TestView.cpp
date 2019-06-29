// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "MainFrm.h"//包含头文件，用于状态栏显示鼠标坐标位置
#define   ROUND(a) long(a+0.5) //四舍五入
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
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENUDrawPolygon, OnMENUDrawPolygon)
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_MENUFillPolygon, OnUpdateMENUFillPolygon)
	ON_COMMAND(ID_MENUFillPolygon, OnMENUFillPolygon)
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
	Number=0;
	Flag=LBDown=Attach=MState=FALSE;
	Arrow=TRUE;
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
	CRect Rect;//定义客户区
	GetClientRect(&Rect);//获得客户区的大小
	CDC MemDC;//定义一个内存设备上下文
	CBitmap NewBitmap,*OldBitmap;//定义一个CBitmap对象和一个指针
	NewBitmap.LoadBitmap(IDB_BITMAP2);//从资源中导入图片
	MemDC.CreateCompatibleDC(pDC);///建立与pDC兼容的内存设备上下文
	OldBitmap=MemDC.SelectObject(&NewBitmap);//把内存设备上下文换成位图图像
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);//将位图数据传送到内存
	CPen NewPen,*OldPen; 
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0)); 
	OldPen=MemDC.SelectObject(&NewPen);	
	MemDC.MoveTo(p[0]);
	for(int i=1;i<Number;i++)
	{
		MemDC.LineTo(p[i]);
	}
	if(Flag==FALSE)
	{
		MemDC.LineTo(p[0]);		
	}
	MemDC.SelectObject(OldPen);
	NewPen.DeleteObject();
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);//将内存数据传送到屏幕
	MemDC.SelectObject(OldBitmap);//从内存设备上下文中释放位图图像
	NewBitmap.DeleteObject();//从内存设备上下文中删除位图图像
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
void CTestView::OnMENUDrawPolygon()//绘制菜单操作函数 
{
	// TODO: Add your command handler code here
	Arrow=FALSE;
	Flag=TRUE;
	Number=0;
	MState=FALSE;
	if(FALSE==Attach)
	{
		CClientDC dc(this);
		Picture.CreateCompatibleDC(&dc);		
		MessageBox("请使用鼠标在屏幕上绘制多边形","提示", MB_ICONINFORMATION);	
	}
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=Picture.SelectObject(&NewBitmap);
	Attach=TRUE;
	Invalidate(FALSE);	
}
void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//左键按下函数 
{
	// TODO: Add your message handler code here and/or call default
	if(Flag==TRUE)
	{
		if(Number<50)
		{
			LBDown=TRUE;
			p[Number]=point;
			if(!Number)
			{				
				Number++;
			}
			Number++;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnMouseMove(UINT nFlags, CPoint point)//鼠标移动函数 
{
	// TODO: Add your message handler code here and/or call default
	if(Arrow)
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	CString Str;//状态栏显示鼠标位置
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//包含MainFrm.h头文件
	CStatusBar *pStatus=&pFrame->m_wndStatusBar;//需要将m_wndStatusBar属性修改为公有
	if(pStatus)
	{
		Str.Format("%d,%d",point.x,point.y);
		pStatus->SetPaneText(2,Str);//状态栏显示鼠标光标位置值
	}
	if(LBDown)
	{
		p[Number-1]=point;
		if(nFlags==MK_SHIFT)//约束:测试按下了Shift键
		{
			if(abs(p[Number-1].x-p[Number-2].x)>=abs(p[Number-1].y-p[Number-2].y))
			{
				p[Number-1].y=p[Number-2].y;//x方向的垂线
			}
			else
			{
				p[Number-1].x=p[Number-2].x;//y方向的垂线
			}
		}
	}
	if(Number-1>=3)
	{
		if((abs(p[Number-1].x-p[0].x)<=5) && (abs(p[Number-1].y-p[0].y)<=5))//引力域:边长为10的正方形
		{
			p[Number-1]=p[0];
			Arrow=TRUE;
			LBDown=FALSE;
			MState=TRUE;
		}
	}
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}
void CTestView::OnRButtonDown(UINT nFlags, CPoint point)//右键按下函数 
{
	// TODO: Add your message handler code here and/or call default
	Arrow=TRUE;
	LBDown=FALSE;
	Flag=FALSE;
	MState=TRUE;
	CView::OnRButtonDown(nFlags, point);
}
void CTestView::OnMENUFillPolygon()//填充菜单操作函数 
{
	// TODO: Add your command handler code here
	COLORREF FColor;//填充颜色
	CColorDialog ccd(RGB(0,0,255));
	if(ccd.DoModal()==IDOK)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
		FColor=ccd.GetColor();
		CPoint BPoint,EPoint;//边的起点和终点
		long MaxX=p[0].x;//多边形的x坐标最大值
		for(long Num=0;Num<Number;Num++)//求多边形的最大x值
		{	
			BPoint.x=p[Num].x;
			EPoint.x=p[(Num+1)%Number].x;
			//求余的作用是封闭多边形，如果Number＝4，那么循环(Num+1)%Number的点是1，2，3和0
			if(EPoint.x>MaxX)
				MaxX=EPoint.x;			
		}			
		for(Num=0;Num<Number;Num++)//处理每条边
		{
			BPoint.x=p[Num].x,BPoint.y=p[Num].y;
			EPoint.x=p[(Num+1)%Number].x,EPoint.y=p[(Num+1)%Number].y;			
			if(BPoint.y>EPoint.y)//确保起点的y值小于终点的y值
			{
				CPoint t;//临时对象
				t=BPoint;
				BPoint=EPoint;
				EPoint=t;				
			}
			double k=double(BPoint.x-EPoint.x)/(BPoint.y-EPoint.y);//计算1/k
			for(long y=BPoint.y;y<EPoint.y;y++)//边缘填充算法
			{
				long x=ROUND(double(BPoint.x)+(double(y)-double(BPoint.y))*k);//处理一条边上各个点的x起始坐标
				for(;x<MaxX;x++)
				{
					if(Picture.GetPixel(x,y)==FColor)
					{
						Picture.SetPixel(x,y,RGB(255,255,255));
					}
					else
					{
						Picture.SetPixel(x,y,FColor);
					}
				}
			}
		}
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
}
void CTestView::OnUpdateMENUFillPolygon(CCmdUI* pCmdUI)//填充菜单状态控制函数  
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((MState)?TRUE:FALSE);
}
