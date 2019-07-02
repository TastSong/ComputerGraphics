// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//数学头文件
#define PI 3.1415926//PI的宏定义
#define ROUND(x) int(x+0.5)
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
		ON_COMMAND(ID_MENUMaple, OnMENUMaple)
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

void CTestView::GetMaxX()//求屏幕最大x值
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxX=Rect.right;
}
void CTestView::GetMaxY()//求屏幕最大y值
{
	CRect Rect;
	GetClientRect(&Rect);
    MaxY=Rect.bottom;
}
void CTestView::IFSCode()//IFS编码
{
	CClientDC dc(this);
	Code[0][0]=0.6;Code[0][1]=0;Code[0][2]=0;Code[0][3]=0.6;Code[0][4]=0.18;Code[0][5]=0.36;Code[0][6]=0.25;
	Code[1][0]=0.6;Code[1][1]=0;Code[1][2]=0;Code[1][3]=0.6;Code[1][4]=0.18;Code[1][5]=0.12;Code[1][6]=0.25;
	Code[2][0]=0.4;Code[2][1]=0.3;Code[2][2]=-0.3;Code[2][3]=0.4;Code[2][4]=0.27;Code[2][5]=0.36;Code[2][6]=0.25;
	Code[3][0]=0.4;Code[3][1]=-0.3;Code[3][2]=0.3;Code[3][3]=0.4;Code[3][4]=0.27;Code[3][5]=0.09;Code[3][6]=0.25;
	//'循环迭代，在不同的概率空间下，赋不同的IFS码值
	for(int k=1000000;k>0;k--)//分形图的浓度
	{
		double R=double(rand())/RAND_MAX;//随机数的最大值
		if(R<=Code[0][6]) 
		{
			a=Code[0][0];b=Code[0][1];c=Code[0][2];d=Code[0][3];e=Code[0][4];f=Code[0][5];
		} 
		else if(R<=Code[0][6]+Code[1][6])
		{
			a=Code[1][0];b=Code[1][1];c=Code[1][2];d=Code[1][3];e=Code[1][4];f=Code[1][5];
		}
		else if(R<=Code[0][6]+Code[1][6]+Code[2][6])
		{
			a=Code[2][0];b=Code[2][1];c=Code[2][2];d=Code[2][3];e=Code[2][4];f=Code[2][5];
		} 
		else 
		{
			a=Code[3][0];b=Code[3][1];c=Code[3][2];d=Code[3][3];e=Code[3][4];f=Code[3][5];
		}
		x1=(a*x)+(b*y)+e;y1=(c*x)+(d*y)+f;//仿射变换		
		x=x1;y=y1;
		dc.SetPixel((MaxX/2-300+ROUND(600*x)),(MaxY/2+400-ROUND(600*y)),RGB(x*500*R,R*50,y*30*R));      
	}
}


void CTestView::OnMENUMaple() 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("IFS模型:枫叶");
	RedrawWindow();
	GetMaxX();GetMaxY();
	IFSCode();
}
