// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define ROUND(a) int(a+0.5)//四舍五入
#define LEFT 1//编码0001
#define RIGHT 2//编码0010
#define BOTTOM 4//编码0100
#define TOP 8//编码1000
/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(ID_MENUcohen, OnMENUCohen)
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
	 wxl=100;wxr=400;wyb=200;wyt=500;
	 vxl=550;vxr=950;vyb=250;vyt=450;
	 a=(vxr-vxl)/(wxr-wxl);b=vxl-wxl*a;
	 c=(vyt-vyb)/(wyt-wyb);d=vyb-wyb*c;
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
	CPen Pen1,Pen2,Pen3,*pOldPen;//定义3个像素的画笔
	Pen1.CreatePen(PS_SOLID,3,RGB(0,0,255));
	pOldPen=pDC->SelectObject(&Pen1);
	//绘制窗口
	pDC->MoveTo(ROUND(wxl),ROUND(wyt));pDC->LineTo(ROUND(wxr),ROUND(wyt));
	pDC->LineTo(ROUND(wxr),ROUND(wyb));pDC->LineTo(ROUND(wxl),ROUND(wyb));
	pDC->LineTo(ROUND(wxl),ROUND(wyt));
	pDC->TextOut((ROUND(wxl)+ROUND(wxr))/2,ROUND(wyb)-20,"窗口");//窗口标题
	pDC->SelectObject(pOldPen);
	Pen1.DeleteObject();	
	Pen2.CreatePen(PS_SOLID,3,RGB(255,0,0));
	pOldPen=pDC->SelectObject(&Pen2);
	//绘制视区
	pDC->MoveTo(ROUND(vxl),ROUND(vyt));pDC->LineTo(ROUND(vxr),ROUND(vyt));
	pDC->LineTo(ROUND(vxr),ROUND(vyb));pDC->LineTo(ROUND(vxl),ROUND(vyb));
	pDC->LineTo(ROUND(vxl),ROUND(vyt));
	pDC->TextOut((ROUND(vxl)+ROUND(vxr))/2,ROUND(vyb)-20,"视区");//视区标题
	pDC->SelectObject(pOldPen);
	Pen2.DeleteObject();
	//绘制窗口与视区的分割线
	GetClientRect(&Rect);//获得客户区的大小
	Pen3.CreatePen(PS_SOLID,3,RGB(128,128,128));
	pOldPen=pDC->SelectObject(&Pen3);
	pDC->MoveTo(Rect.Width()/2,0);
	pDC->LineTo(Rect.Width()/2,Rect.Height());	
	pDC->SelectObject(pOldPen);
	Pen3.DeleteObject();	
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

void CTestView::OnMENUCohen()//菜单操作函数 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	double xw1,yw1,xw2,yw2;
	CInputDlg dlg;	
	if(dlg.DoModal()==IDOK)
	{
		xw1=dlg.m_x1;xw2=dlg.m_x2;yw1=dlg.m_y1;yw2=dlg.m_y2;		
	}
	RedrawWindow();//刷新屏幕	
	//窗口绘制直线
	dc.MoveTo(ROUND(xw1),ROUND(yw1));
	dc.LineTo(ROUND(xw2),ROUND(yw2));	
	clip(xw1,yw1,xw2,yw2);
	
}
void CTestView::clip(double xw1,double yw1,double xw2,double yw2)//裁剪函数
{
	double xv1,yv1,xv2,yv2;
	double x,y;
	BOOL Change;
	CClientDC dc(this);
	RC1=EnCode(xw1,yw1);RC2=EnCode(xw2,yw2);
	while(TRUE)
	{
		Change=FALSE;	
		if( (RC1 | RC2)==0)
		{//简取之
			xv1=a*xw1+b;yv1=c*yw1+d;xv2=a*xw2+b;yv2=c*yw2+d;//计算视区坐标	
			dc.MoveTo(ROUND(xv1),ROUND(yv1));
			dc.LineTo(ROUND(xv2),ROUND(yv2));
			return;
		}
		else if((RC1 & RC2)!=0)
		{//简弃之
			return;
		}
		else
		{
			if(RC1==0)//如果P1点在窗口内，交换P1和P2,保证p1点在窗口外
			{
				//交换点的坐标值
				double tx,ty;
				tx=xw1;ty=yw1;
				xw1=xw2;yw1=yw2;
				xw2=tx;yw2=ty;
				//交换点的编码值
				unsigned int RC;
				RC=RC1;RC1=RC2;RC2=RC;
				}
			if(RC1 & LEFT )//P1点位于窗口的左侧
			{
				x=wxl;y=yw1+(yw2-yw1)*(x-xw1)/(xw2-xw1);
				xw1=x;yw1=y;
				Change=TRUE;
				RC1=EnCode(xw1,yw1);RC2=EnCode(xw2,yw2);
			}			
			if(RC1 & RIGHT )//P1点位于窗口的右侧
			{
				x=wxr;y=yw1+(yw2-yw1)*(x-xw1)/(xw2-xw1);
				xw1=x;yw1=y;
				Change=TRUE;
				RC1=EnCode(xw1,yw1);RC2=EnCode(xw2,yw2);
			}				
			if(RC1 & BOTTOM )//P1点位于窗口的下侧
			{
				y=wyb;x=xw1+(xw2-xw1)*(y-yw1)/(yw2-yw1);
				xw1=x;yw1=y;
				Change=TRUE;
				RC1=EnCode(xw1,yw1);RC2=EnCode(xw2,yw2);
			}			
			if(RC1 & TOP )//P1点位于窗口的上侧
			{
				y=wyt;x=xw1+(xw2-xw1)*(y-yw1)/(yw2-yw1);
				xw1=x;yw1=y;
				Change=TRUE;
				RC1=EnCode(xw1,yw1);RC2=EnCode(xw2,yw2);
			}
			if(Change==FALSE)
			{
				return;
			}			
		}
	}
}
unsigned int CTestView::EnCode(double x,double y)//编码函数
{//顺序左右下上
	unsigned int RC=0;	
	if(x<wxl)
	{
		RC=RC | LEFT;
	}
	if(x>wxr)
	{
		RC=RC | RIGHT;
	}
	if(y<wyb)
	{
		RC=RC | BOTTOM;
	}
	if(y>wyt)
	{
		RC=RC | TOP;
	}
	return RC;
}
