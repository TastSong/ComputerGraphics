// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//��ѧͷ�ļ�
#define PI 3.1415926//PI�ĺ궨��
#include "InputDlg.h"//�Ի���
#define ROUND(x) int(x+0.5)//��������
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
	ON_COMMAND(ID_MENUKochSnow, OnMENUKochSnow)
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
void CTestView::GetMaxX()//����Ļ���xֵ
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxX=Rect.right;
}
void CTestView::GetMaxY()//����Ļ���yֵ
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxY=Rect.bottom;
}
	
void CTestView::Koch1(CDC *pDC,int n)//����0��
{
	Position.x=300;Position.y=200;
    if(n==0)
    {
		b.x+=d*cos(alpha*PI/180);
		b.y+=d*sin(alpha*PI/180);
		pDC->MoveTo(ROUND(a.x+Position.x),ROUND(a.y+MaxY-Position.y));
		pDC->LineTo(ROUND(b.x+Position.x),ROUND(b.y+MaxY-Position.y));
		a=b;
		return;
     }
	 Koch1(pDC,n-1);
     alpha+=60;
     Koch1(pDC,n-1);
     alpha-=120;
     Koch1(pDC,n-1);
     alpha+=60;
     Koch1(pDC,n-1);
}
void CTestView::Koch2(CDC *pDC,int n)//����60��
{
	Position.x=300;Position.y=200;
   	if(n==0)
    {
		b.x+=d*cos((alpha+60)*PI/180);
		b.y+=d*sin((alpha+60)*PI/180);
		pDC->MoveTo(ROUND(a.x+Position.x),ROUND(MaxY-Position.y-a.y));
		pDC->LineTo(ROUND(b.x+Position.x),ROUND(MaxY-Position.y-b.y));
		a=b;
		return;
     }
	 Koch2(pDC,n-1);
     alpha+=60;
     Koch2(pDC,n-1);
     alpha-=120;
     Koch2(pDC,n-1);
     alpha+=60;
     Koch2(pDC,n-1);
}
void CTestView::Koch3(CDC *pDC,int n)
{
	Position.x=720;Position.y=200;
   	if(n==0)
    {
		b.x+=d*cos((alpha-120)*PI/180);//����120��
		b.y+=d*sin((alpha-120)*PI/180);
		pDC->MoveTo(ROUND(a.x+Position.x),ROUND(a.y+MaxY-Position.y));
		pDC->LineTo(ROUND(b.x+Position.x),ROUND(b.y+MaxY-Position.y));
		a=b;
		return;
     }
	 Koch3(pDC,n-1);
     alpha+=60;
     Koch3(pDC,n-1);
     alpha-=120;
     Koch3(pDC,n-1);
     alpha+=60;
     Koch3(pDC,n-1);
}

void CTestView::OnMENUKochSnow() 
{
	// TODO: Add your command handler code here
	CInputDlg dlg;
	if (dlg.DoModal()==IDOK)
		n=dlg.m_n;
	else
		return;
	RedrawWindow();	
	CDC *pDC=GetDC();//�ͻ���DC
	GetMaxX();GetMaxY();
	d=(MaxX-600)/pow(3,n);
	a.x=0,a.y=0,b.x=0,b.y=0,alpha=0;	
	Koch1(pDC,n);
	a.x=0,a.y=0,b.x=0,b.y=0,alpha=0;
    Koch2(pDC,n);
	a.x=0,a.y=0,b.x=0,b.y=0,alpha=0;
    Koch3(pDC,n);
	ReleaseDC(pDC);
}
