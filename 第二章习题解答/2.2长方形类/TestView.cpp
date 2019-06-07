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

/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(ID_MENURectangle, OnMENURectangle)
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

void CTestView::OnMENURectangle()//菜单操作函数 
{
	// TODO: Add your command handler code here
	RedrawWindow();//重绘窗口
	CRectangle Rect;//定义长方形类对象
	Rect.input();//读入对话框的值	
	CString Str;//定义字符串
	CClientDC dc(this);//定义客户区对象
	dc.SetTextColor(RGB(0,0,255));//设置文字颜色为蓝色
	Str.Format("长方形的周长为：%5.2f",Rect.circum());//设置输出格式
	dc.TextOut(100,60,Str);//输出周长
	Str.Format("长方形的面积为：%5.2f",Rect.area());//设置输出格式
	dc.TextOut(100,80,Str);//输出面积
}

