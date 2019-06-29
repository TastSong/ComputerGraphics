// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "vector"
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
	ON_COMMAND(ID_MENUFill, OnMENUFill)
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
	Fillcolor=RGB(0,0,255);
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
	GetClientRect(&Rect);
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);	
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);
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

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//������º��� 
{
	// TODO: Add your message handler code here and/or call default
	Seed=point;//ѡ������λ��
	CharFill();//�������
	CView::OnLButtonDown(nFlags, point);
}
void CTestView::CharFill()//������亯��
{
	CRect Rect;
	GetClientRect(&Rect);
	CClientDC dc(this);
	COLORREF BoundColor;//�߽�ɫ
	int Width=Rect.right-Rect.left;
	int Hight=Rect.bottom-Rect.top ;
	int Flag;
	int x0,y0,x,y;
	CPoint Point;
	std::vector<CPoint> FillBuffle;//����CPoint���͵��������ж���
	FillBuffle.reserve(10);//�����������еĴ�С
	FillBuffle.push_back(CPoint(Seed)); //�����ӽ��ѹ����������
	BoundColor=RGB(0,0,0);//����߽�ɫΪ��ɫ
	while(!FillBuffle.empty())//����������зǿ�
	{
      	Point=FillBuffle.front();//������������ͷԪ��
		x=Point.x;y=Point.y;
		FillBuffle.erase(FillBuffle.begin());//������������ڵ�Ԫ��
		dc.SetPixel(Point,Fillcolor);//��������
		//�ж����ص�λ���Ƿ���ͼ���ڲ�
		x0=x+1;//�ҷ��ж�
		while(dc.GetPixel(x0,y)!=BoundColor&&dc.GetPixel(x0,y)!=Fillcolor)
		{
			x0=x0+1;
			if(x0>=Width)//������Ļ���Ҷ�
			{
				MessageBox("���ӳ�����Χ","����");
			    RedrawWindow();
				return;
			}
		}
		y0=y+1;//�·��ж�
        while(dc.GetPixel(x,y0)!=BoundColor&&dc.GetPixel(x,y0)!=Fillcolor)
		{
			y0=y0+1;
			if(y0>=Hight)//������Ļ���¶�
			{
				MessageBox("���ӳ�����Χ","����");
				RedrawWindow();
				return;
			}
		}
		RightPoint.x=x0;//�ұ߽��ڵ����ڵ�
		x0=x-1;
		while(dc.GetPixel(x0,y)!=Fillcolor&&dc.GetPixel(x0,y)!=BoundColor)
		{
			dc.SetPixel(x0,y,Fillcolor);
			x0=x0-1;
			if(x0<=0)//������Ļ�����
			{
				MessageBox("���ӳ�����Χ","����");
				RedrawWindow();
				return;
			}
		}
		y0=y-1;
        while(dc.GetPixel(x,y0)!=BoundColor&&dc.GetPixel(x,y0)!=Fillcolor)
		{
			y0=y0-1;
			if(y0<=0)//������Ļ���϶�
			{
				MessageBox("���ӳ�����Χ","����");
				RedrawWindow();
				return;
			}
		}
		LeftPoint.x=x0+1;//��߽��ڵ����ڵ�
		x0=LeftPoint.x;
		y=y+1;//��һ��ɨ����
		while(x0<RightPoint.x)
		{
			Flag=0;
			while((dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor))
			{
				if(Flag==0)
					Flag=1;
				x0++ ;
			}
			if(Flag==1)
			{
				if((x0==RightPoint.x)&&(dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor))
					FillBuffle.push_back(CPoint(x0,y));//������������
				else
				{
					
					FillBuffle.push_back(CPoint(x0-1,y));
				}
				Flag=0;
			}
			PointNext.x=x0;
			while(((dc.GetPixel(x0,y)==Fillcolor)&&(x0<RightPoint.x))||((dc.GetPixel(x0,y)==BoundColor)&&(x0<RightPoint.x)))
			{
				x0 ++;
			}
		}
        x0=LeftPoint.x;
		y=y-2;
		while(x0<RightPoint.x)
		{
			Flag=0;
			while((dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor)&&(x0<RightPoint.x))
			{
				if(Flag==0)
					Flag=1;
				x0++ ;
			}
			if(Flag==1)
			{
				if((x0==RightPoint.x)&&(dc.GetPixel(x0,y)!=Fillcolor)&&(dc.GetPixel(x0,y)!=BoundColor))
					FillBuffle.push_back(CPoint(x0,y));
				else
				{
					
					FillBuffle.push_back(CPoint(x0-1,y));
				}
				Flag=0;
			}
			PointNext.x=x0;
			while((dc.GetPixel(x0,y)==Fillcolor&&x0<RightPoint.x)||(dc.GetPixel(x0,y)==BoundColor&&x0<RightPoint.x))
			{
				x0++;
			}
		}
	}
	FillBuffle.clear();
	return;
}

void CTestView::OnMENUFill() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	MessageBox("���ڿ��������ڲ�����������!","��ʾ");
}
