// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "InputDlg.h" //包含输入对话框
#define   ROUND(a) int(a+0.5) //四舍五入
#include "math.h" //包含数学头文件
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
	ON_COMMAND(ID_MENUDDA, OnMenudda)
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

void CTestView::OnMenudda() 
{
	// TODO: Add your command handler code here
	CInputDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		P0.x=dlg.m_x0;
		P0.y=dlg.m_y0;
		P1.x=dlg.m_x1;
		P1.y=dlg.m_y1;
	}	
	DDALine();
}

void CTestView::DDALine()
{   
	RedrawWindow();//清屏
	CClientDC dc(this);
	CP2 P,d,Incre;
	int Epsl;
	d.x=P1.x-P0.x;d.y=P1.y-P0.y;P=P0;
	if(fabs(d.x)>fabs(d.y))
		Epsl=ROUND(fabs(d.x));
	else
		Epsl=ROUND(fabs(d.y));
	Incre.x=d.x/double(Epsl);Incre.y=d.y/double(Epsl);
	double k=d.y/d.x;
	CString data;//输出直线的斜率
	data.Format("k=%f",k);
	dc.TextOut(10,10,data);
	for(int i=0;i<=Epsl;i++)
	{
		dc.SetPixel(ROUND(P.x),ROUND(P.y),RGB(0,0,0));
		P.x+=Incre.x;
		P.y+=Incre.y;
	}
}