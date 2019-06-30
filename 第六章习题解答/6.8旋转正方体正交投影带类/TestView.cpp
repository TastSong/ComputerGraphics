// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(a) int(a+0.5)//��������
#include "cmath"//��ѧͷ�ļ�
#define PI 3.1415926//Բ����
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

void CTestView::ReadPoint()//������
{
	Cube.SetPoint();	
}
void CTestView::ReadFace()//�������
{
	Cube.SetFace();
}

void CTestView::RotateX()//��x����תAfa
{
	Tran.RotateX(Afa);
	Cube.Multiply(Tran);	
}

void CTestView::RotateY()//��y����תBeta
{
	Tran.RotateY(Beta);
	Cube.Multiply(Tran);
}
void CTestView::RotateZ()//��z����תGama
{
	Tran.RotateZ(Gama);
	Cube.Multiply(Tran);
}
void CTestView::DoubleBuffer()//˫�����ͼ
{
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//�Զ�������ϵ
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(Rect.right/2,Rect.bottom/2);//��Ļ����Ϊԭ��	
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
		CVector VS(0,0,1);//Z�᷽����ʸ��
		int n1=Cube.Face[nFace].p[1];
		int n2=Cube.Face[nFace].p[2];
		int n3=Cube.Face[nFace].p[3];
		CVector V1(Cube.Vertex[n1]);//��ĵ�һ������ʸ��
		CVector V2(Cube.Vertex[n2]);//��ĵڶ�������ʸ��
		CVector V3(Cube.Vertex[n3]);//��ĵ���������ʸ��
		CVector V21=V2-V1;//���һ����ʸ��
		CVector V32=V3-V2;//�����һ����ʸ��				
		CVector VN=V21*V32;//��ķ�ʸ��					
		if(Dot(VS,VN)>=0)//͹����������
			DrawObject(&MemDC,nFace);//��ʸ���ͷ�ʸ���������������㣬���滭��
	}		
	pDC->BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.right,Rect.bottom,&MemDC,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
}
void CTestView::DrawObject(CDC* pDC,int nface)//����������
{
	CP3 Point,TempPoint;	
	CRGB Color=Cube.Face[nface].c;
	NewBbrush[nface].CreateSolidBrush(RGB(Color.red,Color.green,Color.blue));	
	CBrush *OldBrush=pDC->SelectObject(&NewBbrush[nface]);
	pDC->BeginPath();
	for(int nEdge=1;nEdge<=Cube.Face[nface].En;nEdge++)//��ѭ��
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
	pDC->LineTo(ROUND(TempPoint.x),ROUND(TempPoint.y));//�պ��ı���
	pDC->EndPath();
	pDC->FillPath();//����ı���
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
			Afa=-5;//�趨����
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

void CTestView::OnMENUPlay()//������ť���� 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;//��ť״̬����
	if (Play)//���ö�����ʱ�䲽		
		SetTimer(1,150,NULL);
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent)//����ʱ�亯�� 
{
	// TODO: Add your message handler code here and/or call default
	Afa=-5;
	Beta=-5;
	RotateX();
	RotateY();
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI) //������ť״̬���� 
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
