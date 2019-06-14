// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "cmath"//������ѧͷ�ļ�
#define PI  3.1415926//Բ����
#define   ROUND(a) int(a+0.5) //��������
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
	ON_COMMAND(ID_APP_Circle, OnAPPCircle)
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
    r=250;
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

void CTestView::DoubleBuffer()//˫�����ͼ
{	
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//�Զ�������ϵ
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//��Ļ����Ϊԭ��	
	CDC	MemDC,Picture;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SetMapMode(MM_ANISOTROPIC);
	MemDC.SetWindowExt(Rect.Width(),Rect.Height());
	MemDC.SetViewportExt(Rect.Width(),-Rect.bottom);
	MemDC.SetViewportOrg(Rect.Width()/2,Rect.Height()/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&Picture,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
    DrawACircle(&MemDC);//���Ʒ�����Բ
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
}
void CTestView::DrawACircle(CDC *pDC)//���Ʒ�����Բ
{
	double e,h=r;
	CP2 p;
	for(p.x=0,p.y=r;p.x<=p.y;p.x++)
	{
		e=h-sqrt(r*r-(p.x+1)*(p.x+1));
		if(e>=1)
		{
			h--;
			e--;
			p.y--;
		}			
		ACirclePoint(pDC,p,e);
	}	
}

void CTestView::ACirclePoint(CDC *pDC,CP2 p,double e)//�˷ַ���Բ�Ӻ���
{
	COLORREF c1=RGB(255*e,255*e,255*e);
	COLORREF c2=RGB(255*(1.0-e),255*(1.0-e),255*(1.0-e));
    //���ݵ�ĶԳ��Կ��Եõ�Բ�ϵĸ��������,����ע��c2�������������
	pDC->SetPixel(ROUND(p.x),ROUND(p.y),c1);//(x,y)
	pDC->SetPixel(ROUND(p.x),ROUND(p.y-1),c2);
	pDC->SetPixel(ROUND(p.y),ROUND(p.x),c1);//(y,x)
	pDC->SetPixel(ROUND(p.y-1),ROUND(p.x),c2);
	pDC->SetPixel(ROUND(p.y),-ROUND(p.x),c1);//(y,-x)
	pDC->SetPixel(ROUND(p.y-1),-ROUND(p.x),c2);
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y),c1);//(x,-y)
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y-1),c2);
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y),c1);//(-x,-y)
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y-1),c2);
    pDC->SetPixel(-ROUND(p.y),-ROUND(p.x),c1);//(-y,-x)
	pDC->SetPixel(-ROUND(p.y-1),-ROUND(p.x),c2);
	pDC->SetPixel(-ROUND(p.y),ROUND(p.x),c1);//(-y,x)
	pDC->SetPixel(-ROUND(p.y-1),ROUND(p.x),c2);
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y),c1);//(-x,y)
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y-1),c2);		
}

void CTestView::OnAPPCircle()//�˵��������� 
{
	// TODO: Add your command handler code here
	DoubleBuffer();
}
