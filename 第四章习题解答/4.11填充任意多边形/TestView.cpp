// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "MainFrm.h"//����ͷ�ļ�������״̬����ʾ�������λ��
#define   ROUND(a) long(a+0.5) //��������
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
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_MENUDrawPolygon, OnMENUDrawPolygon)
	ON_WM_RBUTTONDOWN()
	ON_UPDATE_COMMAND_UI(ID_MENUFillPolygon, OnUpdateMENUFillPolygon)
	ON_COMMAND(ID_MENUFillPolygon, OnMENUFillPolygon)
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
	Number=0;
	Flag=LBDown=Attach=MState=FALSE;
	Arrow=TRUE;
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
	CRect Rect;//����ͻ���
	GetClientRect(&Rect);//��ÿͻ����Ĵ�С
	CDC MemDC;//����һ���ڴ��豸������
	CBitmap NewBitmap,*OldBitmap;//����һ��CBitmap�����һ��ָ��
	NewBitmap.LoadBitmap(IDB_BITMAP2);//����Դ�е���ͼƬ
	MemDC.CreateCompatibleDC(pDC);///������pDC���ݵ��ڴ��豸������
	OldBitmap=MemDC.SelectObject(&NewBitmap);//���ڴ��豸�����Ļ���λͼͼ��
	MemDC.BitBlt(0,0,Rect.Width(),Rect.Height(),&Picture,0,0,SRCCOPY);//��λͼ���ݴ��͵��ڴ�
	CPen NewPen,*OldPen; 
	NewPen.CreatePen(PS_SOLID,3,RGB(0,0,0)); 
	OldPen=MemDC.SelectObject(&NewPen);	
	MemDC.MoveTo(p[0]);
	for(int i=1;i<Number;i++)
	{
		MemDC.LineTo(p[i]);
	}
	if(Flag==FALSE)
	{
		MemDC.LineTo(p[0]);		
	}
	MemDC.SelectObject(OldPen);
	NewPen.DeleteObject();
	pDC->BitBlt(0,0,Rect.Width(),Rect.Height(),&MemDC,0,0,SRCCOPY);//���ڴ����ݴ��͵���Ļ
	MemDC.SelectObject(OldBitmap);//���ڴ��豸���������ͷ�λͼͼ��
	NewBitmap.DeleteObject();//���ڴ��豸��������ɾ��λͼͼ��
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
void CTestView::OnMENUDrawPolygon()//���Ʋ˵��������� 
{
	// TODO: Add your command handler code here
	Arrow=FALSE;
	Flag=TRUE;
	Number=0;
	MState=FALSE;
	if(FALSE==Attach)
	{
		CClientDC dc(this);
		Picture.CreateCompatibleDC(&dc);		
		MessageBox("��ʹ���������Ļ�ϻ��ƶ����","��ʾ", MB_ICONINFORMATION);	
	}
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=Picture.SelectObject(&NewBitmap);
	Attach=TRUE;
	Invalidate(FALSE);	
}
void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//������º��� 
{
	// TODO: Add your message handler code here and/or call default
	if(Flag==TRUE)
	{
		if(Number<50)
		{
			LBDown=TRUE;
			p[Number]=point;
			if(!Number)
			{				
				Number++;
			}
			Number++;
		}
	}
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnMouseMove(UINT nFlags, CPoint point)//����ƶ����� 
{
	// TODO: Add your message handler code here and/or call default
	if(Arrow)
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
	CString Str;//״̬����ʾ���λ��
	CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;//����MainFrm.hͷ�ļ�
	CStatusBar *pStatus=&pFrame->m_wndStatusBar;//��Ҫ��m_wndStatusBar�����޸�Ϊ����
	if(pStatus)
	{
		Str.Format("%d,%d",point.x,point.y);
		pStatus->SetPaneText(2,Str);//״̬����ʾ�����λ��ֵ
	}
	if(LBDown)
	{
		p[Number-1]=point;
		if(nFlags==MK_SHIFT)//Լ��:���԰�����Shift��
		{
			if(abs(p[Number-1].x-p[Number-2].x)>=abs(p[Number-1].y-p[Number-2].y))
			{
				p[Number-1].y=p[Number-2].y;//x����Ĵ���
			}
			else
			{
				p[Number-1].x=p[Number-2].x;//y����Ĵ���
			}
		}
	}
	if(Number-1>=3)
	{
		if((abs(p[Number-1].x-p[0].x)<=5) && (abs(p[Number-1].y-p[0].y)<=5))//������:�߳�Ϊ10��������
		{
			p[Number-1]=p[0];
			Arrow=TRUE;
			LBDown=FALSE;
			MState=TRUE;
		}
	}
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}
void CTestView::OnRButtonDown(UINT nFlags, CPoint point)//�Ҽ����º��� 
{
	// TODO: Add your message handler code here and/or call default
	Arrow=TRUE;
	LBDown=FALSE;
	Flag=FALSE;
	MState=TRUE;
	CView::OnRButtonDown(nFlags, point);
}
void CTestView::OnMENUFillPolygon()//���˵��������� 
{
	// TODO: Add your command handler code here
	COLORREF FColor;//�����ɫ
	CColorDialog ccd(RGB(0,0,255));
	if(ccd.DoModal()==IDOK)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
		FColor=ccd.GetColor();
		CPoint BPoint,EPoint;//�ߵ������յ�
		long MaxX=p[0].x;//����ε�x�������ֵ
		for(long Num=0;Num<Number;Num++)//�����ε����xֵ
		{	
			BPoint.x=p[Num].x;
			EPoint.x=p[(Num+1)%Number].x;
			//����������Ƿ�ն���Σ����Number��4����ôѭ��(Num+1)%Number�ĵ���1��2��3��0
			if(EPoint.x>MaxX)
				MaxX=EPoint.x;			
		}			
		for(Num=0;Num<Number;Num++)//����ÿ����
		{
			BPoint.x=p[Num].x,BPoint.y=p[Num].y;
			EPoint.x=p[(Num+1)%Number].x,EPoint.y=p[(Num+1)%Number].y;			
			if(BPoint.y>EPoint.y)//ȷ������yֵС���յ��yֵ
			{
				CPoint t;//��ʱ����
				t=BPoint;
				BPoint=EPoint;
				EPoint=t;				
			}
			double k=double(BPoint.x-EPoint.x)/(BPoint.y-EPoint.y);//����1/k
			for(long y=BPoint.y;y<EPoint.y;y++)//��Ե����㷨
			{
				long x=ROUND(double(BPoint.x)+(double(y)-double(BPoint.y))*k);//����һ�����ϸ������x��ʼ����
				for(;x<MaxX;x++)
				{
					if(Picture.GetPixel(x,y)==FColor)
					{
						Picture.SetPixel(x,y,RGB(255,255,255));
					}
					else
					{
						Picture.SetPixel(x,y,FColor);
					}
				}
			}
		}
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
	}
}
void CTestView::OnUpdateMENUFillPolygon(CCmdUI* pCmdUI)//���˵�״̬���ƺ���  
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((MState)?TRUE:FALSE);
}
