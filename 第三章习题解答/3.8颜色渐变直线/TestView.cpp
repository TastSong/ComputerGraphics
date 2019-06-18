// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "cmath"//数学头文件
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
	ON_COMMAND(ID_APP_LINE, OnAppLine)
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

void CTestView::OnDraw(CDC* pDC)//绘制直角坐标系
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect Rect;
	GetClientRect(&Rect);
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(128,128,128));
	OldPen=pDC->SelectObject(&NewPen);
	pDC->MoveTo(Rect.left,Rect.bottom/2);//绘制x轴
	pDC->LineTo(Rect.right,Rect.bottom/2);	
	pDC->MoveTo(Rect.right-10,Rect.bottom/2-3);//绘制右箭头　
	pDC->LineTo(Rect.right,Rect.bottom/2);
	pDC->LineTo(Rect.right-10,Rect.bottom/2+3);
	pDC->LineTo(Rect.right-10,Rect.bottom/2-3);
	pDC->TextOut(Rect.right-15,Rect.bottom/2+10,"x");
	pDC->MoveTo(Rect.right/2,Rect.top);//绘制y轴
	pDC->LineTo(Rect.right/2,Rect.bottom);
	pDC->MoveTo(Rect.right/2-3,Rect.top+10);//绘制上箭头
	pDC->LineTo(Rect.right/2,Rect.top);
	pDC->LineTo(Rect.right/2+3,Rect.top+10);
	pDC->LineTo(Rect.right/2-3,Rect.top+10);
	pDC->TextOut(Rect.right/2-15,Rect.top+10,"y");
	pDC->TextOut(Rect.right/2-20,Rect.bottom/2+10,"O");
	pDC->SelectObject(OldPen);
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

void CTestView::OnAppLine() 
{
	// TODO: Add your command handler code here
	RedrawWindow();//清屏
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		p0.x=dlg.m_x0;p0.y=dlg.m_y0;p0.c=CRGB(GetRValue(dlg.cc0)/255,GetGValue(dlg.cc0)/255,GetBValue(dlg.cc0)/255);
		p1.x=dlg.m_x1;p1.y=dlg.m_y1;p1.c=CRGB(GetRValue(dlg.cc1)/255,GetGValue(dlg.cc1)/255,GetBValue(dlg.cc1)/255);
		if(fabs(p0.x-p1.x)<1e-6 && fabs(p0.y-p1.y)<1e-6)
		{	
			AfxMessageBox("直线起点和终点坐标不能相同");
			return;
		}
	}
	else
		return;
	CreateScene();	
}
void CTestView::CreateScene()//建立二维场景
{
	CRect Rect;
	GetClientRect(&Rect);//获得客户区大小
	CDC *pDC=GetDC();//客户区dc
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上 
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点
	CLine line;
	line.MoveTo(pDC,p0);
	line.LineTo(pDC,p1);//绘制BresenhamLine
	ReleaseDC(pDC);
}




