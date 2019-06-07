// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#define PI 3.1415926//PI�ĺ궨��
#include "math.h"//��ѧͷ�ļ�
#define ROUND(a) int(a+0.5)//��������
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
	ON_COMMAND(ID_MENURing, OnMENURing)
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

void CTestView::GetMaxX()//������Ļ�ͻ������
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxX=Rect.right;
}
void CTestView::GetMaxY()//������Ļ�ͻ������߶�
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxY=Rect.bottom;
}
void CTestView::Ring()///Բ������
{//RΪ��Բ�뾶��rΪСԲ�뾶
    CClientDC dc(this);
	CBrush *OldBrush;
	OldBrush=(CBrush *)dc.SelectStockObject(NULL_BRUSH);//ʹ��͸����ˢ���ƿ���Բ
	for(double i=0;i<=2*PI;i+=PI/20)
	{
		p.x=R*cos(i)+MaxX/2;
		p.y=R*sin(i)+MaxY/2;
		dc.Ellipse(ROUND(p.x-r),ROUND(p.y-r),ROUND(p.x+r),ROUND(p.y+r));//����Բ��������Բ
	}
}
void CTestView::OnMENURing() 
{
	// TODO: Add your command handler code here
	CInputDlg dlg;
	if (IDOK==dlg.DoModal())
	{
		R=dlg.m_R;
		r=dlg.m_r;
	}
	GetMaxX();
	GetMaxY();
	RedrawWindow();//����
	Ring();	
}
