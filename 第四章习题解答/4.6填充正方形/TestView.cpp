// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)
#include "math.h"
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
	ON_COMMAND(ID_MENUIFill, OnMENUIFill)
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
	GetMaxX();GetMaxY();
	ReadPoint();
	DrawRect(pDC,P1);//����������1
	DrawRect(pDC,P2);//����������2
	DrawRect(pDC,P3);//����������3
	DrawRect(pDC,P4);//����������4
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
void CTestView::ReadPoint()//���������εĶ�������
{
	int a=200;
	//�������������εĶ�������
	P1[0]=CP2(MaxX/2-a,MaxY/2-a,CRGB(1.0,0.0,0.0));//P1
	P1[1]=CP2(MaxX/2-a,MaxY/2,CRGB(1.0,0.0,0.0));//P2
	P1[2]=CP2(MaxX/2,MaxY/2,CRGB(1.0,0.0,0.0));//P3
	P1[3]=CP2(MaxX/2,MaxY/2-a,CRGB(1.0,0.0,0.0));//P3
	//�������������εĶ�������
	P2[0]=CP2(MaxX/2-a,MaxY/2,CRGB(0.0,1.0,0.0));
	P2[1]=CP2(MaxX/2-a,MaxY/2+a,CRGB(0.0,1.0,0.0));
	P2[2]=CP2(MaxX/2,MaxY/2+a,CRGB(0.0,1.0,0.0));
	P2[3]=CP2(MaxX/2,MaxY/2,CRGB(0.0,1.0,0.0));
	//�������������εĶ�������
	P3[0]=CP2(MaxX/2,MaxY/2,CRGB(1.0,1.0,0.0));
	P3[1]=CP2(MaxX/2,MaxY/2+a,CRGB(1.0,1.0,0.0));
	P3[2]=CP2(MaxX/2+a,MaxY/2+a,CRGB(1.0,1.0,0.0));
	P3[3]=CP2(MaxX/2+a,MaxY/2,CRGB(1.0,1.0,0.0));
	//�������������εĶ�������
	P4[0]=CP2(MaxX/2,MaxY/2-a,CRGB(0.0,0.0,1.0));
	P4[1]=CP2(MaxX/2,MaxY/2,CRGB(0.0,0.0,1.0));
	P4[2]=CP2(MaxX/2+a,MaxY/2,CRGB(0.0,0.0,1.0));
	P4[3]=CP2(MaxX/2+a,MaxY/2-a,CRGB(0.0,0.0,1.0));
}

void CTestView::DrawRect(CDC *pDC,CP2 *P)//����������
{
	CP2 T;
	CLine line;
	for(int i=0;i<4;i++)//��ѭ��
	{
		if(i==0)
		{
			line.MoveTo(pDC,P[i]);
			T=P[0];
		}
		else
		{
			line.LineTo(pDC,P[i]);;
		}		
	}
	line.LineTo(pDC,T);//�պ�
}		

void CTestView::OnMENUIFill() 
{
	// TODO: Add your command handler code here
	RedrawWindow();//ˢ����Ļ
	FillRect(P1);//���������1
	FillRect(P2);//���������2
	FillRect(P3);//���������3
	FillRect(P4);//���������4
}
void CTestView::FillRect(CP2 *P)//���������
{
	CFill fill;
	CPi2 Point[4];
	for(int i=0;i<4;i++)
	{
		Point[i].x=P[i].x;
		Point[i].y=ROUND(P[i].y);
		Point[i].c=P[i].c;
	}
	CDC *pDC=GetDC();
	fill.SetPoint(Point,4);//���������
	fill.CreateBucket();
	fill.CreateEdge();
    fill.Gouraud(pDC);	
	ReleaseDC(pDC);
}
