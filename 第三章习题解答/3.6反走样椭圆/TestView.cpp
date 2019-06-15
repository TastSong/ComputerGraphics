// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "cmath"//������ѧͷ�ļ�
#define   ROUND(a) int(a+0.5) //��������
#define PI  3.1415926//Բ����
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
	ON_COMMAND(ID_APP_Ellipse, OnAPPEllipse)
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
    a=400;b=150;//��Բ�ĳ�����Ϊ400���ΰ���Ϊ150
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
    DrawAEllipse(&MemDC);//���Ʒ�������Բ
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
}
void CTestView::DrawAEllipse(CDC *pDC)//���Ʒ�������Բ
{
	double e,h;
	CP2 p,pc;//�������
	pc.x=a*a/sqrt(a*a+b*b),pc.y=b*b/sqrt(a*a+b*b);
	for(p.x=0,p.y=b,h=b;p.x<=pc.x;p.x++)//����AC��
	{
		e=h-sqrt(b*b-b*b*(p.x+1)*(p.x+1)/(a*a));
		if(e>=1)
		{
			h--;
			e--;
			p.y--;
		}	
		AEllipsePointAC(pDC,p,e);
	}
	for(p.x=a,p.y=0,h=a;p.y<pc.y;p.y++)//����BC��
	{
		e=h-sqrt(a*a-a*a*(p.y+1)*(p.y+1)/(b*b));
		if(e>=1)
		{
			h--;
			e--;
			p.x--;
		}	
		AEllipsePointBC(pDC,p,e);
	}
}

void  CTestView::AEllipsePointAC(CDC *pDC,CP2 p,double e)//�ķַ�����ԲAC�Ӻ���
{
	COLORREF c1=RGB(255*e,255*e,255*e);
	COLORREF c2=RGB(255*(1.0-e),255*(1.0-e),255*(1.0-e));
	pDC->SetPixel(ROUND(p.x),ROUND(p.y),c1);//(x,y)
	pDC->SetPixel(ROUND(p.x),ROUND(p.y-1),c2);
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y),c1);//(x,-y)
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y-1),c2);
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y),c1);//(-x,-y)
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y-1),c2);
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y),c1);//(-x,y)
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y-1),c2);	
}

void CTestView::AEllipsePointBC(CDC *pDC,CP2 p,double e)//�ķַ�����ԲBC�Ӻ���
{	
	COLORREF c1=RGB(255*e,255*e,255*e);
	COLORREF c2=RGB(255*(1.0-e),255*(1.0-e),255*(1.0-e));
	pDC->SetPixel(ROUND(p.x),ROUND(p.y),c1);//(x,y)
	pDC->SetPixel(ROUND(p.x-1),ROUND(p.y),c2);    
	pDC->SetPixel(ROUND(p.x),-ROUND(p.y),c1);//(x,-y)
	pDC->SetPixel(ROUND(p.x-1),-ROUND(p.y),c2);
	pDC->SetPixel(-ROUND(p.x),-ROUND(p.y),c1);//(-x,-y)
	pDC->SetPixel(-ROUND(p.x-1),-ROUND(p.y),c2);
	pDC->SetPixel(-ROUND(p.x),ROUND(p.y),c1);//(-x,y)
	pDC->SetPixel(-ROUND(p.x-1),ROUND(p.y),c2);	
}

void CTestView::OnAPPEllipse()//�˵��������� 
{
	// TODO: Add your command handler code here
	DoubleBuffer();
}
