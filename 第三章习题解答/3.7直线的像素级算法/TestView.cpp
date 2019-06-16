// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//包含数学头文件
#define   ROUND(a) int(a+0.5) //四舍五入
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
	ON_COMMAND(ID_MENUIDrawLine, OnMENUIDrawLine)
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
	DrawGrid(pDC);
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
void CTestView::DrawGrid(CDC *pDC)//绘制网格
{
    int xstart=110,ystart=14;
	a=20;
	pix[0][0].x=xstart+a/2;pix[0][0].y=ystart+a/2;
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,2,RGB(128,128,0));
    OldPen=pDC->SelectObject(&NewPen);
	for(int i=0;i<40;i++)
		for(int j=0;j<30;j++)
		{
			pix[i][j].x=pix[0][0].x+a*i;
			pix[i][j].y=pix[0][0].y+a*j;
			pDC->Rectangle(pix[i][j].x-a/2,pix[i][j].y-a/2,pix[i][j].x+a/2,pix[i][j].y+a/2);
		}
	pDC->SelectObject(OldPen);
	NewPen.DeleteObject();
}

void CTestView::OnMENUIDrawLine() //菜单函数
{
	// TODO: Add your command handler code here
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		P0.x=dlg.m_x0;P0.y=dlg.m_y0;
		P1.x=dlg.m_x1;P1.y=dlg.m_y1;
		if(fabs(P0.x-P1.x)<1e-6 && fabs(P0.y-P1.y)<1e-6)
		{	
			MessageBox("直线起点和终点坐标不能相同");
			return;
		}
		if(P1.y>P1.x)
		{
			MessageBox("直线的斜率K不能大于1!");
			return;
		}
	}
	else
		return;
    RedrawWindow();
	Mbline();
}

void CTestView::Mbline()//Bresenham函数
{
	double d,k;	
	k=(P1.y-P0.y)/(P1.x-P0.x);d=0.5-k;
    for(P.x=P0.x,P.y=P0.y;P.x<=P1.x;P.x++)
    {
		FillPixel(P);
        if(d<0)
		{
			P.y++;
         	d+=1-k;
		}
		else 
            d-=k;
    }
}
void CTestView::FillPixel(CP2 p)//网格填充函数
{  
	CDC *pDC=GetDC();
	int i=ROUND(p.x),j=ROUND(p.y);
	CRect Rect(pix[i][j].x-a/2,pix[i][j].y-a/2,pix[i][j].x+a/2,pix[i][j].y+a/2);
	CBrush NewBrush,*OldBrush;
	NewBrush.CreateSolidBrush(RGB(0,0,0));
	OldBrush=pDC->SelectObject(&NewBrush);
	pDC->FillRect(Rect,&NewBrush);
    ReleaseDC(pDC);
}
