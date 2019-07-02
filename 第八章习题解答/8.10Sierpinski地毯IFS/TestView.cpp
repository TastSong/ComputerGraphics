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
	ON_COMMAND(ID_MENUSierpinski, OnMENUSierpinski)
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
void CTestView::IFSCode()
{
	x=10;y=10;
	CClientDC dc(this);
	Code[1][0]=0.33;Code[1][1]=0;Code[1][2]=0;Code[1][3]=0.33;Code[1][4]=0;Code[1][5]=0.0;Code[1][6]=0.125;
	Code[2][0]=0.33;Code[2][1]=0;Code[2][2]=0;Code[2][3]=0.33;Code[2][4]=0.0;Code[2][5]=0.33;Code[2][6]=0.125;
	Code[3][0]=0.33;Code[3][1]=0;Code[3][2]=0;Code[3][3]=0.33;Code[3][4]=0.0;Code[3][5]=0.66;Code[3][6]=0.125;
	Code[4][0]=0.33;Code[4][1]=0;Code[4][2]=0;Code[4][3]=0.33;Code[4][4]=0.33;Code[4][5]=0.0;Code[4][6]=0.125;
	Code[5][0]=0.33;Code[5][1]=0;Code[5][2]=0;Code[5][3]=0.33;Code[5][4]=0.33;Code[5][5]=0.66;Code[5][6]=0.125;
	Code[6][0]=0.33;Code[6][1]=0;Code[6][2]=0;Code[6][3]=0.33;Code[6][4]=0.66;Code[6][5]=0.0;Code[6][6]=0.125;
	Code[7][0]=0.33;Code[7][1]=0;Code[7][2]=0;Code[7][3]=0.33;Code[7][4]=0.66;Code[7][5]=0.33;Code[7][6]=0.125;
	Code[8][0]=0.33;Code[8][1]=0;Code[8][2]=0;Code[8][3]=0.33;Code[8][4]=0.66;Code[8][5]=0.66;Code[8][6]=0.125;
	for(int k=1000000;k>0;k--)//IFS码赋值
	{
		double R=double(rand())/RAND_MAX;//R是小于1的随机数
		if (R<=Code[1][6]) //0<=R<=0.333
		{
			a=Code[1][0];b=Code[1][1];c=Code[1][2];d=Code[1][3];e=Code[1][4];f=Code[1][5];
		} 
		else if(R<=Code[1][6]+Code[2][6])//0.333<=R<=0.666
		{
			a=Code[2][0];b=Code[2][1];c=Code[2][2];d=Code[2][3];e=Code[2][4];f=Code[2][5];
		}
		else if(R<=Code[1][6]+Code[2][6]+Code[3][6])//0.333<=R<=0.666
		{
			a=Code[3][0];b=Code[3][1];c=Code[3][2];d=Code[3][3];e=Code[3][4];f=Code[3][5];
		}
		else if(R<=Code[1][6]+Code[2][6]+Code[3][6]+Code[4][6])//0.333<=R<=0.666
		{
			a=Code[4][0];b=Code[4][1];c=Code[4][2];d=Code[4][3];e=Code[4][4];f=Code[4][5];
		}
		else if(R<=Code[1][6]+Code[2][6]+Code[3][6]+Code[4][6]+Code[5][6])//0.333<=R<=0.666
		{
			a=Code[5][0];b=Code[5][1];c=Code[5][2];d=Code[5][3];e=Code[5][4];f=Code[5][5];
		}
		else if(R<=Code[1][6]+Code[2][6]+Code[3][6]+Code[4][6]+Code[5][6]+Code[6][6])//0.333<=R<=0.666
		{
			a=Code[6][0];b=Code[6][1];c=Code[6][2];d=Code[6][3];e=Code[6][4];f=Code[6][5];
		}
		else if(R<=Code[1][6]+Code[2][6]+Code[3][6]+Code[4][6]+Code[5][6]+Code[6][6]+Code[7][6])//0.333<=R<=0.666
		{
			a=Code[7][0];b=Code[7][1];c=Code[7][2];d=Code[7][3];e=Code[7][4];f=Code[7][5];
		}
			else //0.666<=R<=1
		{
			a=Code[8][0];b=Code[8][1];c=Code[8][2];d=Code[8][3];e=Code[8][4];f=Code[8][5];
		}
		
		x1=(a*x)+e;//仿射变换
		y1=(d*y)+f;
		x=x1-0.1;y=y1;
		dc.SetPixel((ROUND(MaxX/2-180+500*x)),ROUND((MaxY/2+250-500*y)),RGB(x*400*R,R*400,y*400*R)); 
	}
}

void CTestView::OnMENUSierpinski() 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("IFS模型:Sierpinski地毯");
	RedrawWindow();
	GetMaxX();GetMaxY();
	IFSCode();
}
