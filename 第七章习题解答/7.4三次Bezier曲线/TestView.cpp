// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#define ROUND(a) int(a+0.5)//��������
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
	ON_COMMAND(ID_MENU_B, OnMenuB)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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
	AbleToLeftBtn=FALSE;
	AbleToMove=FALSE;
	Number=-1;
	//4������ĳ�ʼ��
	P[0][0]=200;P[0][1]=360;
	P[1][0]=350;P[1][1]=150;
	P[2][0]=650;P[2][1]=150;
	P[3][0]=800;P[3][1]=375;	
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
	CRect Rect;
	GetClientRect(&Rect);//��ÿͻ����Ĵ�С
	CBitmap	*OldBitmap,NewBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);		
	CDC MemDC,Picture;
	MemDC.CreateCompatibleDC(GetDC());
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);	
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));//��ɫ�ʻ��ƿ��ƶ����
	OldPen=MemDC.SelectObject(&NewPen);	
	MemDC.MoveTo(P[0][0],P[0][1]);
	MemDC.Ellipse(P[0][0]-2,P[0][1]-2,P[0][0]+2,P[0][1]+2);//������������ζ���
	for(int i=1;i<4;i++)
	{
		MemDC.LineTo(P[i][0],P[i][1]);
		MemDC.Ellipse(P[i][0]-2,P[i][1]-2,P[i][0]+2,P[i][1]+2);
	}
	MemDC.TextOut(P[0][0],P[0][1]+5,"P0");
	MemDC.TextOut(P[1][0],P[1][1]-20,"P1");
	MemDC.TextOut(P[2][0],P[2][1]-20,"P2");
	MemDC.TextOut(P[3][0],P[3][1]+5,"P3");
	if(Number!=-1)
	{
		CString	str;
		str.Format("x=%d y=%d,�϶�����ƶ�",P[Number][0],P[Number][1]);
		MemDC.TextOut(P[Number][0]+5,P[Number][1]+5,str);
	}
	Bezier3_curves(P,&MemDC);
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(OldBitmap);
	MemDC.SelectObject(OldPen);
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
void CTestView::Bezier3_curves(int P[][2],CDC *pDC)//��������Bezier����
{
	int lx,ly,rate=100;
	double Bern03,Bern13,Bern23,Bern33;
	lx=P[0][0];ly=P[0][1];//t��0�����x,y����
	pDC->MoveTo(lx,ly);
	CPen NewPen(PS_SOLID,1,RGB(0,0,255));//��ɫ���ʻ�3��Bezier����
	CPen *POldPen=pDC->SelectObject(&NewPen);
	for(double t=0;t<=1;t+=1.0/rate)
	{
		Bern03=(1-t)*(1-t)*(1-t);//����Bern0,3(t)
		Bern13=3*t*(1-t)*(1-t);//����Bern1,3(t)
		Bern23=3*t*t*(1-t);//����Bern2,3(t)
		Bern33=t*t*t;//����Bern3,3(t)
		lx=ROUND(P[0][0]*Bern03+P[1][0]*Bern13+P[2][0]*Bern23+P[3][0]*Bern33);
		ly=ROUND(P[0][1]*Bern03+P[1][1]*Bern13+P[2][1]*Bern23+P[3][1]*Bern33);
		pDC->LineTo(lx,ly);
	}
	pDC->SelectObject(POldPen);
	NewPen.DeleteObject();	
}

void CTestView::OnMenuB()//�˵����� 
{
	// TODO: Add your command handler code here
	MessageBox("��ֱ���϶���������εĶ��㣬�۲�Ч����","��Ϣ",MB_ICONINFORMATION|MB_OK);		
}

void CTestView::OnMouseMove(UINT nFlags, CPoint point)//����ƶ����� 
{
	// TODO: Add your message handler code here and/or call default
	if(AbleToMove==TRUE)
	{
		P[Number][0]=point.x;
		P[Number][1]=point.y;
	}
	Number=-1;
	int i;
	for(i=0;i<4;i++)
	{//�ж���굱ǰ��Ͷ���ľ���
		if((point.x-P[i][0])*(point.x-P[i][0])+(point.y-P[i][1])*(point.y-P[i][1])<100)
		{
			Number=i;
			AbleToLeftBtn=TRUE;
			SetCursor(LoadCursor(NULL,IDC_SIZEALL));//�ı�Ϊʮ�ּ�ͷ���
			break;
		}
	}
	if(10==i)
	{
		Number=-1;
	}
	Invalidate(FALSE);	
	CView::OnMouseMove(nFlags, point);
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//���������º���  
{
	// TODO: Add your message handler code here and/or call default
	if(TRUE==AbleToLeftBtn)
	{
		AbleToMove=TRUE;
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnLButtonUp(UINT nFlags, CPoint point)//������������ 
{
	// TODO: Add your message handler code here and/or call default
	AbleToLeftBtn=FALSE;
	AbleToMove=FALSE;
	Number=0;
	CView::OnLButtonUp(nFlags, point);
}
