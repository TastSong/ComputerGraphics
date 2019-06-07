// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define Xhit	0;//x������ײ��־
#define Yhit	1;//y������ײ��־
#define Allhit	2;//x��y������ײ��־
#define Nohit	3;//δ������ײ��־
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
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_PLAY, OnMenuPlay)
	ON_UPDATE_COMMAND_UI(ID_MENU_PLAY, OnUpdateMenuPlay)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()//���캯��
{
	// TODO: add construction code here
	Play=FALSE;
	RGB[0]=RGB(255,0,0);//��ɫ
	RGB[1]=RGB(0,255,0);//��ɫ
	RGB[2]=RGB(0,0,255);//��ɫ
	RGB[3]=RGB(255,255,0);//��ɫ
	RGB[4]=RGB(255,0,255);//Ʒ��
	RGB[5]=RGB(0,255,255);//��ɫ
	pRect[0]=new CRectangle(-200,150,200,300,-1.65,1.5);
	pRect[1]=new CRectangle(300,-200,200,200,0.0,0.8);
	pRect[2]=new CRectangle(80,-50,100,200,0.65,0.5);
	pRect[3]=new CRectangle(300,200,50,50,0.16,0.8);
	pRect[4]=new CRectangle(-250,-200,200,100,0.16,0.8);
	pRect[5]=new CRectangle(250,100,200,60,0.4,0.2);
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

void CTestView::DoubleBuffer()//˫����
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
	MemDC.SetWindowExt(Rect.right,Rect.bottom);
	MemDC.SetViewportExt(Rect.right,-Rect.bottom);
	MemDC.SetViewportOrg(Rect.right/2,Rect.bottom/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.Width(),Rect.Height(),&Picture,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
    DrawScene(&MemDC);	
	pDC->BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.right,Rect.bottom,&MemDC,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();	
}

void CTestView::DrawScene(CDC *pDC)//���Ƴ���
{
	CRect Rect;
	GetClientRect(&Rect);
	CBrush  NewBrush[6],*OldBrush;
	//���ƾ��ο�
	for(int i=0;i<6;i++)
	{  		
		NewBrush[i].CreateSolidBrush(RGB[i]);
		OldBrush=pDC->SelectObject(&NewBrush[i]);
		pRect[i]->DrawRectangle(pDC);
		int flagB,flagS;
		flagB=TestB(*pRect[i],Rect.right,Rect.bottom);//���Ա߽���ײ
		HitB(*pRect[i],flagB);//�߽���ײ�ٶȼ���
		for(int j=0;j<6;j++)//���Ծ��ο�֮�����ײ
		{
			if(j!=i)//����������м��
			{
				flagS=TestS(*pRect[i],*pRect[j]);//���ο�֮�����
				HitS(*pRect[i],*pRect[j],flagS);//�ٶȼ���
			}
		}
		pRect[i]->MoveRectangle();
	    pDC->SelectObject(OldBrush);
	    NewBrush[i].DeleteObject();
	}
}
int CTestView::TestB(CRectangle rect,double width,double height)//���Ա߽���ײ 
{
	double halfBW=width/2;//��߽�Ŀ�� 
	double halfBH=height/2;//��߽�ĸ߶�
	double halfRW=rect.Width/2;//���ο���
	double halfRH=rect.Height/2;//���ο���
	if(fabs(rect.X)+halfRW >= halfBW && fabs(rect.Y)+halfRH >= halfBH)//���ο�λ�ڿͻ������ĸ��Խ�
		return Allhit;
	if(fabs(rect.X)+halfRW >= halfBW)//���ο�λ�ڿͻ������ұ߽�
		return Xhit;
	if(fabs(rect.Y)+halfRH >= halfBH)//���ο�λ�ڿͻ������±߽�
		return Yhit;
	return Nohit;
}
int CTestView::TestS(CRectangle rect1,CRectangle rect2)//���Ծ��ο�֮����ײ
{
	double DX=fabs(rect1.X-rect2.X);//�������ο����ĵ��x����ľ���
	double DY=fabs(rect1.Y-rect2.Y);//�������ο����ĵ��Y����ľ���
	double halfRW12=(rect1.Width+rect2.Width)/2;//�������ο����ĵ��x�������С����
	double halfRH12=(rect1.Height+rect2.Height)/2;//�������ο����ĵ��Y�������С����
	if(DX <= halfRW12 && DY <= halfRH12)//������ײ
	{
		double PreDX,PreDY,SpdX,SpdY;//��һ��ʱ�������ľ��룬�����˶��ĺ��ٶ�
		PreDX=fabs((rect1.X-rect1.SpeedX)-(rect2.X-rect2.SpeedX));
		PreDY=fabs((rect1.Y-rect1.SpeedY)-(rect2.Y-rect2.SpeedY));
		//����X�����ϵĺ��ٶȷ���
		if( rect1.SpeedX * rect2.SpeedX < 0 )		//�������ο��ƶ������෴�����
		{
			SpdX=fabs(rect1.SpeedX)+fabs(rect2.SpeedX);
		}
		else							    	//�������ο��ƶ�������ͬ�����
		{
			if(fabs(rect1.SpeedX) >= fabs(rect2.SpeedX))	//���ٶȴ�ļ�ȥ�ٶ�С��
				SpdX=fabs(rect1.SpeedX)-fabs(rect2.SpeedX);
			else
				SpdX=fabs(rect2.SpeedX)-fabs(rect1.SpeedX);
		}
		//����Y�����ϵĺ��ٶȷ���
		if( rect1.SpeedY * rect2.SpeedY < 0 )
		{
			SpdY=fabs(rect1.SpeedY)+fabs(rect2.SpeedY);
		}
		else
		{
			if(fabs(rect1.SpeedY) >= fabs(rect2.SpeedY))
				SpdY=fabs(rect1.SpeedY)-fabs(rect2.SpeedY);
			else
				SpdY=fabs(rect2.SpeedY)-fabs(rect1.SpeedY);
		}
		//�ж���ײʱ������X�����ϻ���Y������
		if(PreDX > halfRW12 && PreDY <= halfRH12)
			return Xhit;
		if(PreDX <= halfRW12 && PreDY > halfRH12)
			return Yhit;
		if(PreDX > halfRW12 && PreDY > halfRH12)
		{
			double SX=fabs(PreDX-halfRW12);
			double SY=fabs(PreDY-halfRH12);
			double TX=SX/SpdX;
			double TY=SY/SpdY;
			if(TX>TY)
			{
				return Yhit;
			}
			else if(TX<TY)
			{
				return Xhit;
			}
			else if(TX==TY)
				return Allhit;
		}
	}
	return Nohit;
}

void CTestView::HitB(CRectangle &rect,int flag)//�ٶȼ��� 
{
	if(flag==3)//���û�з�����ײ����ֱ�ӷ���������
		return ;
	//���������ײ
	if(flag==0)//x������ײ
	{
		rect.SpeedX=-rect.SpeedX;
	}
	if(flag==1)//y������ײ
	{
		rect.SpeedY=-rect.SpeedY;
	}
	if(flag==2)//x��y������ײ
	{
		rect.SpeedX=-rect.SpeedX;
		rect.SpeedY=-rect.SpeedY;
	}
}

void CTestView::HitS(CRectangle &rect1,CRectangle &rect2,int flag)//�ٶȼ���
{
	if(flag==3)//���û�з�����ײ����ֱ�ӷ���������
		return ;
	//���������ײ
	double m1=rect1.Width*rect1.Height;//������ο���������ģ������
	double m2=rect2.Width*rect2.Height;//������ο���������ģ������
	double v1x,v2x,v1y,v2y;//���ο��ƶ��ٶ�
	if(flag==0)//x������ײ
	{
		v2x=(2*m1*rect1.SpeedX+(m2-m1)*rect2.SpeedX)/(m1+m2);//�ٶȼ��㹫ʽ
		v1x=v2x+rect2.SpeedX-rect1.SpeedX;//�ٶȼ��㹫ʽ
		rect1.SpeedX=v1x;
		rect2.SpeedX=v2x;
	}
	if(flag==1)//y������ײ
	{
		v2y=(2*m1*rect1.SpeedY+(m2-m1)*rect2.SpeedY)/(m1+m2);
		v1y=v2y+rect2.SpeedY-rect1.SpeedY;
		rect1.SpeedY=v1y;
		rect2.SpeedY=v2y;
	}
	if(flag==2)//x��y������ײ
	{
		v2x=(2*m1*rect1.SpeedX+(m2-m1)*rect2.SpeedX)/(m1+m2);
		v1x=v2x+rect2.SpeedX-rect1.SpeedX;
		v2y=(2*m1*rect1.SpeedY+(m2-m1)*rect2.SpeedY)/(m1+m2);
		v1y=v2y+rect2.SpeedY-rect1.SpeedY;
		rect1.SpeedX=v1x;
		rect2.SpeedX=v2x;
		rect1.SpeedY=v1y;
		rect2.SpeedY=v2y;
	}
}

void CTestView::OnTimer(UINT nIDEvent)//���ö�ʱ�� 
{
	// TODO: Add your message handler code here and/or call default
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}

void CTestView::OnMenuPlay()//������ť 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//���ö�����ʱ�䲽
		SetTimer(1,1,NULL);	
	else
		KillTimer(1);
	
}

void CTestView::OnUpdateMenuPlay(CCmdUI* pCmdUI)//������ť״̬ 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
