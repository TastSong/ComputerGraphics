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
	ON_COMMAND(ID_MENURGB, OnMenurgb)
	ON_COMMAND(ID_MENUCMY, OnMenucmy)
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
void CTestView::GetMaxX()//�����Ļ���
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxX=Rect.right;
}

void CTestView::GetMaxY()//�����Ļ�߶�
{
	CRect Rect;
	GetClientRect(&Rect);
	MaxY=Rect.bottom;
}

void CTestView::OnMenurgb() 
{
	// TODO: Add your command handler code here
	GetMaxX();GetMaxY();
	AfxGetMainWnd()->SetWindowText("����:RGBģ��");
	int x0,y0,x1,y1,x2,y2,x3,y3,a,r;
	a=100;r=130;
	x0=MaxX/2;y0=MaxY/2;
	x1=x0;y1=y0-a+26;//��ԲԲ��
	x2=x0-a;y2=y0+a;//��ԲԲ��
	x3=x0+a;y3=y0+a;//��ԲԲ��
	CRect Rect;
	GetClientRect(&Rect);
	CDC MemDC;
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	MemDC.CreateCompatibleDC(GetDC());
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);
	
	CPen NewPen,*OldPen;//�ڱ�
	NewPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	OldPen=MemDC.SelectObject(&NewPen);
	MemDC.Arc(x1-r,y1-r,x1+r,y1+r,x1-r,y1-r,x1-r,y1-r);
	MemDC.Arc(x2-r,y2-r,x2+r,y2+r,x2-r,y2-r,x2-r,y2-r);
	MemDC.Arc(x3-r,y3-r,x3+r,y3+r,x3-r,y3-r,x3-r,y3-r);
	MemDC.SelectObject(OldPen);
	NewPen.DeleteObject();	
	
	CBrush NewBrushR,*OldBrushR;//��ɫ
	NewBrushR.CreateSolidBrush(RGB(255,0,0));
	OldBrushR=MemDC.SelectObject(&NewBrushR);
	MemDC.FloodFill(x1,y1,RGB(0,0,0));
	MemDC.SelectObject(OldBrushR);
	NewBrushR.DeleteObject();

	CBrush NewBrushG,*OldBrushG;//��ɫ
	NewBrushG.CreateSolidBrush(RGB(0,255,0));
	OldBrushG=MemDC.SelectObject(&NewBrushG);
	MemDC.FloodFill(x2,y2,RGB(0,0,0));
	MemDC.SelectObject(OldBrushG);
	NewBrushG.DeleteObject();

	CBrush NewBrushB,*OldBrushB;//��ɫ
	NewBrushB.CreateSolidBrush(RGB(0,0,255));
	OldBrushB=MemDC.SelectObject(&NewBrushB);
	MemDC.FloodFill(x3,y3,RGB(0,0,0));
	MemDC.SelectObject(OldBrushB);
	NewBrushB.DeleteObject();
	
	CBrush NewBrushRGB,*OldBrushRGB;//��ɫ����ɫ����ɫ
	NewBrushRGB.CreateSolidBrush(RGB(255,0,0)|RGB(0,255,0)|RGB(0,0,255));
	OldBrushRGB=MemDC.SelectObject(&NewBrushRGB);
	MemDC.FloodFill((x1+x2+x3)/3,(y1+y2+y3)/3,RGB(0,0,0));
	MemDC.SelectObject(OldBrushRGB);
	NewBrushRGB.DeleteObject();

	CBrush NewBrushRB,*OldBrushRB;//��ɫ����ɫ
	NewBrushRB.CreateSolidBrush(RGB(255,0,0)|RGB(0,255,0));
	OldBrushRB=MemDC.SelectObject(&NewBrushRB);
	MemDC.FloodFill(x0-a/2,y0,RGB(0,0,0));
	MemDC.SelectObject(OldBrushRB);
	NewBrushRB.DeleteObject();

	CBrush NewBrushRG,*OldBrushRG;//��ɫ����ɫ
	NewBrushRG.CreateSolidBrush(RGB(255,0,0)|RGB(0,0,255));
	OldBrushRG=MemDC.SelectObject(&NewBrushRG);
	MemDC.FloodFill(x0+a/2,y0,RGB(0,0,0));
	MemDC.SelectObject(OldBrushRG);
	NewBrushRG.DeleteObject();

	CBrush NewBrushBG,*OldBrushBG;//��ɫ����ɫ
	NewBrushBG.CreateSolidBrush(RGB(0,255,0)|RGB(0,0,255));
	OldBrushBG=MemDC.SelectObject(&NewBrushBG);
	MemDC.FloodFill(x0,y0+a,RGB(0,0,0));
	MemDC.SelectObject(OldBrushBG);
	NewBrushBG.DeleteObject();

	CClientDC dc(this);
	dc.BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(OldBitmap);
}

void CTestView::OnMenucmy() 
{
	// TODO: Add your command handler code here
	GetMaxX();GetMaxY();
	AfxGetMainWnd()->SetWindowText("����:CMYģ��");
	int x0,y0,x1,y1,x2,y2,x3,y3,a,r;
	a=100;r=130;
	x0=MaxX/2;y0=MaxY/2;
	x1=x0;y1=y0-a+26;//��ԲԲ��
	x2=x0-a;y2=y0+a;//��ԲԲ��
	x3=x0+a;y3=y0+a;//��ԲԲ��
	CRect Rect;
	GetClientRect(&Rect);
	CDC MemDC;
	CBitmap Bitmap,*OldBitmap;
	Bitmap.LoadBitmap(IDB_BITMAP2);
	MemDC.CreateCompatibleDC(GetDC());
	OldBitmap=MemDC.SelectObject(&Bitmap);
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);
	
	CPen NewPen,*OldPen;//�ڱ�
	NewPen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	OldPen=MemDC.SelectObject(&NewPen);
	MemDC.Arc(x1-r,y1-r,x1+r,y1+r,x1-r,y1-r,x1-r,y1-r);
	MemDC.Arc(x2-r,y2-r,x2+r,y2+r,x2-r,y2-r,x2-r,y2-r);
	MemDC.Arc(x3-r,y3-r,x3+r,y3+r,x3-r,y3-r,x3-r,y3-r);
	MemDC.SelectObject(OldPen);
	NewPen.DeleteObject();	
	
	CBrush NewBrushM,*OldBrushM;//Ʒ��
	NewBrushM.CreateSolidBrush(RGB(255,0,255));
	OldBrushM=MemDC.SelectObject(&NewBrushM);
	MemDC.FloodFill(x1,y1,RGB(0,0,0));
	MemDC.SelectObject(OldBrushM);
	NewBrushM.DeleteObject();

	CBrush NewBrushY,*OldBrushY;//��ɫ
	NewBrushY.CreateSolidBrush(RGB(255,255,0));
	OldBrushY=MemDC.SelectObject(&NewBrushY);
	MemDC.FloodFill(x2,y2,RGB(0,0,0));
	MemDC.SelectObject(OldBrushY);
	NewBrushY.DeleteObject();

	CBrush NewBrushC,*OldBrushC;//��ɫ
	NewBrushC.CreateSolidBrush(RGB(0,255,255));
	OldBrushC=MemDC.SelectObject(&NewBrushC);
	MemDC.FloodFill(x3,y3,RGB(0,0,0));
	MemDC.SelectObject(OldBrushC);
	NewBrushC.DeleteObject();
	
	CBrush NewBrushCMY,*OldBrushCMY;//��ɫ��Ʒ�죭��ɫ
	NewBrushCMY.CreateSolidBrush(RGB(0,255,255)&RGB(255,0,255)&RGB(255,255,0));
	OldBrushCMY=MemDC.SelectObject(&NewBrushCMY);
	MemDC.FloodFill((x1+x2+x3)/3,(y1+y2+y3)/3,RGB(0,0,0));
	MemDC.SelectObject(OldBrushCMY);
	NewBrushCMY.DeleteObject();

	CBrush NewBrushMY,*OldBrushMY;//Ʒ�죭��ɫ
	NewBrushMY.CreateSolidBrush(RGB(255,0,255)&RGB(255,255,0));
	OldBrushMY=MemDC.SelectObject(&NewBrushMY);
	MemDC.FloodFill(x0-a/2,y0,RGB(0,0,0));
	MemDC.SelectObject(OldBrushMY);
	NewBrushMY.DeleteObject();

	CBrush NewBrushMC,*OldBrushMC;//Ʒ�죭��ɫ
	NewBrushMC.CreateSolidBrush(RGB(255,0,255)&RGB(0,255,255));
	OldBrushMC=MemDC.SelectObject(&NewBrushMC);
	MemDC.FloodFill(x0+a/2,y0,RGB(0,0,0));
	MemDC.SelectObject(OldBrushMC);
	NewBrushMC.DeleteObject();

	CBrush NewBrushYC,*OldBrushYC;//��ɫ����ɫ
	NewBrushYC.CreateSolidBrush(RGB(255,255,0)&RGB(0,255,255));
	OldBrushYC=MemDC.SelectObject(&NewBrushYC);
	MemDC.FloodFill(x0,y0+a,RGB(0,0,0));
	MemDC.SelectObject(OldBrushYC);
	NewBrushYC.DeleteObject();

	CClientDC dc(this);
	dc.BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(OldBitmap);
}
