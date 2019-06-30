// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#define ROUND(a) long(a+0.5)//四舍五入
#include "math.h"//数学头文件
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
	ON_COMMAND(ID_MENUDrawCardinal, OnMENUDrawCardinal)
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
	//9个型值点的初始化
	p[0][0]=336;p[0][1]=327;
	p[1][0]=110;p[1][1]=353;
	p[2][0]=339;p[2][1]=84;
	p[3][0]=434;p[3][1]=246;
	p[4][0]=712;p[4][1]=246;
	p[5][0]=938;p[5][1]=31;
	p[6][0]=816;p[6][1]=509;
	p[7][0]=336;p[7][1]=509;
	p[8][0]=336;p[8][1]=327;
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
	CPen NewPen,*OldPen;
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0));//黑色笔绘制特征多边形
	OldPen=pDC->SelectObject(&NewPen);	
	pDC->MoveTo(p[0][0],p[0][1]);
	pDC->Ellipse(p[0][0]-2,p[0][1]-2,p[0][0]+2,p[0][1]+2);//绘制特征多边形顶点
	for(int i=1;i<9;i++)
	{
		pDC->LineTo(p[i][0],p[i][1]);
		pDC->Ellipse(p[i][0]-2,p[i][1]-2,p[i][0]+2,p[i][1]+2);
	}
	pDC->SelectObject(OldPen);
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
void CTestView::Cardinal(CDC *pDC)//绘制Cardinal三次插值样条
{
	double s,u=0.1;
	s=(1-u)/2;
	double a[4][4] ={{-s,2-s,s-2,s},{2*s,s-3,3-2*s,-s},{-s,0,s,0},{0,1,0,0}};//Mc矩阵系数
	double b[4][2];//边界点 
	for(int i=0;i<8;i++)//计算Pk-1、Pk、Pk+1、Pk+2
	{
		if(i==0)
		{
			b[0][0]=p[8][0];b[0][1]=p[8][1];
			b[1][0]=p[0][0];b[1][1]=p[0][1];
			b[2][0]=p[1][0];b[2][1]=p[1][1];
		}
		else
		{
			b[0][0]=p[i-1][0];b[0][1]=p[i-1][1];
			b[1][0]=p[i][0];b[1][1]=p[i][1];
			b[2][0]=p[i+1][0];b[2][1]=p[i+1][1];
		}
		if (i<7)
		{
			b[3][0]=p[i+2][0];b[3][1]=p[i+2][1];
		}
		else
		{
			b[3][0]=p[1][0];b[3][1]=p[1][1];
		}
		MultiMatrix(a,b);
		CPen NewPen,*OldPen;
		NewPen.CreatePen(PS_SOLID,1,RGB(0,0,255));//蓝色笔绘制样条曲线
		OldPen=pDC->SelectObject(&NewPen);
		pDC->MoveTo(p[i][0],p[i][1]);
		for(double t=0.0;t<=1.0;t+=1.0/100)
		{
			int x=ROUND(pow(t,3)*result[0][0]+pow(t,2)*result[1][0]
			+ t*result[2][0]+result[3][0]);
			int y=ROUND(pow(t,3)*result[0][1]+pow(t,2)*result[1][1]
			+ t*result[2][1]+result[3][1]);		
			pDC->LineTo(x,y);
		}
		pDC->SelectObject(OldPen);
		NewPen.DeleteObject();
	}
}

void CTestView::MultiMatrix(double a[4][4],double b[4][2])//矩阵相乘
{
	int i,j,k;
	for(i=0;i<4;i++)
		for(j=0;j<2;j++)
			result[i][j]=0;//矩阵清零
	for(i=0;i<2;i++)
		for(j=0;j<4;j++)
			for(k=0;k<4;k++)
				result[j][i]+=a[j][k]*b[k][i]; 
}

void CTestView::OnMENUDrawCardinal() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);
	Cardinal(&dc);
}
