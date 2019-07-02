// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "math.h"//数学头文件
#define PI 3.1415926//PI的宏定义
#include "InputDlg.h"//对话框
#define ROUND(x) int(x+0.5)//四舍五入
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
	ON_COMMAND(ID_MENUGrass, OnMENUGrass)
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

void CTestView::GrammarModel(int n)//文法模型
{	
	StackPushPos=0;
	NewRule=Rule[0];
	NewRuleTemp.Empty();
	int Length=NewRule.GetLength();
	for(int i=1;i<=n;i++)
	{		
		int Pos=0;
		for(int j=0;j<Length;j++)//规则替换
		{
			if(NewRule[j]==Axiom[1])
			{
				NewRuleTemp+=Rule[1];
				Pos=NewRuleTemp.GetLength()-1 ;
			}
			else if(NewRule[j]==Axiom[2])
			{
				NewRuleTemp+=Rule[2];
				Pos=NewRuleTemp.GetLength()-1 ;
			}
			else
			{
				NewRuleTemp+=NewRule[j];
				Pos++;
			}
		}
		NewRule=NewRuleTemp;
		NewRuleTemp.Empty();
		Length=NewRule.GetLength();
	}	
}
	
void CTestView::GrammarExplanation(double theta,double lenth)//文法解释
{
	CClientDC dc(this);
	if(NewRule.IsEmpty ())//字符串空返回
		return ;
	else 
	{
		CStateNode CurrentNode,NextNode;
  		CurrentNode.x=ax;CurrentNode.y=ay;CurrentNode.afa=90;
		int Len=NewRule.GetLength();
		StackPushPos=0;
		dc.MoveTo(ROUND(ax),ROUND(MaxY-ay));
		for(int i=0;i<Len;i++)
		{
			switch(NewRule[i])//访问字符串中的某个位置的字符
			{
				case 'F'://取出"F"字符的操作
		 			NextNode.x=CurrentNode.x+lenth*cos(CurrentNode.afa*PI/180);
					NextNode.y=CurrentNode.y+lenth*sin(CurrentNode.afa*PI/180);
					NextNode.afa=CurrentNode.afa;
					dc.LineTo (ROUND(NextNode.x),ROUND(MaxY-NextNode.y));
					CurrentNode=NextNode;
					break ;			
				case '['://取出"["字符的操作
					Stack[StackPushPos]=CurrentNode;
					StackPushPos ++;
					break;
				case ']'://取出"]"字符的操作
					CurrentNode=Stack[StackPushPos-1]; 
					StackPushPos -- ;
					dc.MoveTo (ROUND(CurrentNode.x),ROUND(MaxY-CurrentNode.y));
					break;
				case '+'://取出"+"字符的操作
					CurrentNode.afa=CurrentNode.afa+theta;
					break;
				case '-'://取出"-"字符的操作
					CurrentNode.afa=CurrentNode.afa-theta;
					break;
				default:
					;
			}			
		}
	}
}

void CTestView::OnMENUGrass()//菜单操作函数  
{
	// TODO: Add your command handler code here
	GetMaxX();GetMaxY();
	CInputDlg dlg;
	int n;
	double len,th;
	if (dlg.DoModal()==IDOK)
	{
		n=dlg.m_n;
	}
	else
	{
		return;
	}	
	RedrawWindow();
	ax=MaxX/2-150;ay=MaxY-600;//起点坐标
	Rule[0]="Y";
	Axiom[1]="Y";
	Rule[1]="YFX[+++++YFY][-----YFY]";
	Axiom[2]="X";
	Rule[2]="F-XF";	
	GrammarModel(n);	
	len=13;th=7;
	GrammarExplanation(th,len);	
}
