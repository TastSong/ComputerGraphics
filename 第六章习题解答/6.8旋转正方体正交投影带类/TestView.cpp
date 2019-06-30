// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//四舍五入
#include "cmath"//数学头文件
#define PI 3.1415926//圆周率
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
	ON_COMMAND(ID_MENUPlay, OnMENUPlay)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENUPlay, OnUpdateMENUPlay)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
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
	Play=FALSE;
	Afa=0;
	Beta=0;
	Gama=0;
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
	ReadPoint();
	ReadFace();
	RotateX();
	RotateY();
	RotateZ();
	DoubleBuffer();	
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

void CTestView::ReadPoint()//读入点表
{
	Cube.SetPoint();	
}
void CTestView::ReadFace()//读入面表
{
	Cube.SetFace();
}

void CTestView::RotateX()//绕x轴旋转Afa
{
	Tran.RotateX(Afa);
	Cube.Multiply(Tran);	
}

void CTestView::RotateY()//绕y轴旋转Beta
{
	Tran.RotateY(Beta);
	Cube.Multiply(Tran);
}
void CTestView::RotateZ()//绕z轴旋转Gama
{
	Tran.RotateZ(Gama);
	Cube.Multiply(Tran);
}
void CTestView::DoubleBuffer()//双缓冲绘图
{
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(Rect.right/2,Rect.bottom/2);//屏幕中心为原点	
	CDC	MemDC,Picture;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SetMapMode(MM_ANISOTROPIC);
	MemDC.SetWindowExt(Rect.Width(),Rect.Height());
	MemDC.SetViewportExt(Rect.right,-Rect.bottom);
	MemDC.SetViewportOrg(Rect.right/2,Rect.bottom/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.Width(),Rect.Height(),&Picture,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	for(int nFace=1;nFace<=6;nFace++)
	{
		CVector VS(0,0,1);//Z轴方向视矢量
		int n1=Cube.Face[nFace].p[1];
		int n2=Cube.Face[nFace].p[2];
		int n3=Cube.Face[nFace].p[3];
		CVector V1(Cube.Vertex[n1]);//面的第一个顶点矢量
		CVector V2(Cube.Vertex[n2]);//面的第二个顶点矢量
		CVector V3(Cube.Vertex[n3]);//面的第三个顶点矢量
		CVector V21=V2-V1;//面的一个边矢量
		CVector V32=V3-V2;//面的另一个边矢量				
		CVector VN=V21*V32;//面的法矢量					
		if(Dot(VS,VN)>=0)//凸多面体消隐
			DrawObject(&MemDC,nFace);//视矢量和法矢量的数量积大于零，表面画出
	}		
	pDC->BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.right,Rect.bottom,&MemDC,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
}
void CTestView::DrawObject(CDC* pDC,int nface)//绘制正方体
{
	CP3 Point,TempPoint;	
	CRGB Color=Cube.Face[nface].c;
	NewBbrush[nface].CreateSolidBrush(RGB(Color.red,Color.green,Color.blue));	
	CBrush *OldBrush=pDC->SelectObject(&NewBbrush[nface]);
	pDC->BeginPath();
	for(int nEdge=1;nEdge<=Cube.Face[nface].En;nEdge++)//边循环
	{
		Point=Cube.Vertex[Cube.Face[nface].p[nEdge]];
		if(nEdge==1)
		{
			pDC->MoveTo(ROUND(Point.x),ROUND(Point.y));
			TempPoint=Point;
		}
		else
		{
			pDC->LineTo(ROUND(Point.x),ROUND(Point.y));
		}		
	}
	pDC->LineTo(ROUND(TempPoint.x),ROUND(TempPoint.y));//闭合四边形
	pDC->EndPath();
	pDC->FillPath();//填充四边形
	pDC->SelectObject(OldBrush);
	NewBbrush[nface].DeleteObject();
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(!Play)
	{
		switch(nChar)
		{
		case VK_UP:
			Afa=-5;//设定步长
			RotateX();
			break;
		case VK_DOWN:
			Afa=+5;
			RotateX();
			break;
		case VK_LEFT:
			Beta=-5;
			RotateY();
			break;
		case VK_RIGHT:
			Beta=+5;
			RotateY();
			break;
		default:
			break;			
		}		
	}
	DoubleBuffer();		
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnMENUPlay()//动画按钮函数 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;//按钮状态开关
	if (Play)//设置动画的时间步		
		SetTimer(1,150,NULL);
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent)//动画时间函数 
{
	// TODO: Add your message handler code here and/or call default
	Afa=-5;
	Beta=-5;
	RotateX();
	RotateY();
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI) //动画按钮状态函数 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;   
	GetClientRect(&Rect);   
	pDC->FillSolidRect(Rect,RGB(0,0,0));
	return true;
}
