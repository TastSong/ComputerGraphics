// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "stack_node.h"//���������ͷ�ļ�
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
ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENUNP, OnMenunp)
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
	//������ͨ��	
	Point[0]=CPoint(300,500);
	Point[1]=CPoint(501,500);
	Point[2]=CPoint(501,301);
	Point[3]=CPoint(700,301);
	Point[4]=CPoint(700,100);
	Point[5]=CPoint(500,100);
	Point[6]=CPoint(500,300);
	Point[7]=CPoint(300,300);
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
	pDC->Polygon(Point,8);//new:���ƶ����
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
void CTestView::PolygonFill()//�������
{
	CClientDC *dc;
	dc=new CClientDC(this);
	COLORREF FillColor,BoundaryColor,PixelColor;
	BoundaryColor=RGB(0,0,0);//�߽�ɫΪ��ɫ
	FillColor=RGB(0,0,255);//���ɫΪ��ɫ		
	Head=new CStack_Node();
	Head->PixelPoint=Seed;
	Head->next=NULL;
	while(Head!=NULL)
	{	
		CStack_Node *poppoint;
		poppoint=Pop();
		if(NULL==poppoint)
		{
			dc->TextOut(10,10,"������");
			dc->DeleteDC();
			return;
		}
		Last=Base;
		dc->SetPixel(poppoint->PixelPoint,FillColor);//��������ɫ
		//��
		PLeft.x=poppoint->PixelPoint.x-1;
		PLeft.y=poppoint->PixelPoint.y;
		PixelColor=dc->GetPixel(PLeft.x,PLeft.y);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{//���ڱ߽粢�Ҳ�������		
			Push(PLeft);
		}
		//��
		PTop.x=poppoint->PixelPoint.x;
		PTop.y=poppoint->PixelPoint.y+1;
		PixelColor=dc->GetPixel(PTop);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{		
			Push(PTop);
		}
		//��
		PRight.x=poppoint->PixelPoint.x+1;
		PRight.y=poppoint->PixelPoint.y;
		PixelColor=dc->GetPixel(PRight);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{		
			Push(PRight);
		}
		//��
		PBottom.x=poppoint->PixelPoint.x;
		PBottom.y=poppoint->PixelPoint.y-1;
		PixelColor=dc->GetPixel(PBottom);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PBottom);
		}
		//����
		PLeftTop.x=poppoint->PixelPoint.x-1;
		PLeftTop.y=poppoint->PixelPoint.y+1;
		PixelColor=dc->GetPixel(PLeftTop.x,PLeftTop.y);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PLeftTop);
		}
		//����
		PRightTop.x=poppoint->PixelPoint.x+1;
		PRightTop.y=poppoint->PixelPoint.y+1;
		PixelColor=dc->GetPixel(PRightTop);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{		
			Push(PRightTop);
		}
		//����
		PLeftBottom.x=poppoint->PixelPoint.x-1;
		PLeftBottom.y=poppoint->PixelPoint.y-1;
		PixelColor=dc->GetPixel(PLeftBottom);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PLeftBottom);
		}
		//����
		PRightBottom.x=poppoint->PixelPoint.x+1;
		PRightBottom.y=poppoint->PixelPoint.y-1;
		PixelColor=dc->GetPixel(PRightBottom);
		if(PixelColor!=BoundaryColor && PixelColor!=FillColor)
		{	
			Push(PRightBottom);
		}				
	}
}

void CTestView::Push(CPoint point)//��ջ����
{
	Base=Head;
	Last=new CStack_Node;
	Last->PixelPoint=point;
	Last->next=NULL;
	if(NULL==Base)
	{
		Head=Last;
		return;
	}
	while(NULL!=Base->next)
	{
		Base=Base->next;//ָ���½��Ľ��
	}
	Base->next=Last;
}

CStack_Node *CTestView::Pop()//��ջ����
{
	//�������һ��Ԫ�ص�ָ��
	Base=Head;
	if(NULL==Base->next)//�ѵ���������һ��ָ��ָ��NULL
	{
		Head=NULL;
		return Base;
	}
	while(NULL!=Base->next)
	{
		Base=Base->next;
		if(Base->next==Last) 
		{
			Base->next=NULL;
			return Last;
		}
	}
	return NULL;
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//������º��� 
{
	// TODO: Add your message handler code here and/or call default
	Seed.x=point.x;//���ѡ������λ��
	Seed.y=point.y;
	PolygonFill();//�������
	CView::OnLButtonDown(nFlags, point);
}


void CTestView::OnMenunp()//�˵����� 
{
	// TODO: Add your command handler code here
	RedrawWindow();//��ʾ����
	MessageBox("���������ڲ�ѡȡ���ӵ�","��ʾ",MB_OK);
}
