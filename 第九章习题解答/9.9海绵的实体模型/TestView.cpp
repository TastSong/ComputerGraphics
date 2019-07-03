// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#define ROUND(x) int(x+0.5)//��������
#define PI 3.1415926//Բ����
#include "math.h"//��ѧͷ�ļ�
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
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_MENUPlay, OnUpdateMENUPlay)
	ON_COMMAND(ID_BUTTON1, OnButton1)
	ON_COMMAND(ID_BUTTON2, OnButton2)
	ON_COMMAND(ID_BUTTON3, OnButton3)
	ON_UPDATE_COMMAND_UI(ID_BUTTON1, OnUpdateButton1)
	ON_UPDATE_COMMAND_UI(ID_BUTTON2, OnUpdateButton2)
	ON_UPDATE_COMMAND_UI(ID_BUTTON3, OnUpdateButton3)
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
	OrignPoint=CP3(0,0,0);//��ά����ϵԭ��
	CubeEdgeLength=300;//�������ʼ�߳�Ϊ200
	n=2;//�ݹ����
	Afa=10,Beta=60;//��ת�Ƕ�	
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

BOOL CTestView::OnPreparePrinting(CPrintInfo*pInfo)
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
void CTestView::Max_d(CP3 pt)//Ѱ����Զ��
{
	double max=0.0f,temp;
	MoveView=pt;
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			for(int k=0;k<3;k++)
			{
				Viewvector.x=MoveView.x-ptable[i][j][k].x;
				Viewvector.y=MoveView.y-ptable[i][j][k].y;
				Viewvector.z=MoveView.z-ptable[i][j][k].z;//��ʸ��
				temp=Viewvector.x*Viewvector.x+Viewvector.y*Viewvector.y+Viewvector.z*Viewvector.z; 
				if(max<temp)
				{
					max=temp;
					a=i;
					b=j;
					c=k;
				}
			}			
}

void CTestView::ReadPoint(CP3 op,double a)//���
{
	//����ϵΪx������,y������,z����ǰ 
	POld[0].x=op.x-a/2;POld[0].y=op.y-a/2;POld[0].z=op.z-a/2;
	POld[1].x=op.x+a/2;POld[1].y=op.y-a/2;POld[1].z=op.z-a/2;
	POld[2].x=op.x+a/2;POld[2].y=op.y+a/2;POld[2].z=op.z-a/2;
	POld[3].x=op.x-a/2;POld[3].y=op.y+a/2;POld[3].z=op.z-a/2;
	POld[4].x=op.x-a/2;POld[4].y=op.y-a/2;POld[4].z=op.z+a/2;
	POld[5].x=op.x+a/2;POld[5].y=op.y-a/2;POld[5].z=op.z+a/2;
	POld[6].x=op.x+a/2;POld[6].y=op.y+a/2;POld[6].z=op.z+a/2;
	POld[7].x=op.x-a/2;POld[7].y=op.y+a/2;POld[7].z=op.z+a/2;
}

void CTestView::ReadFace()//���
{
	//��ı�������Ķ����ź������ɫ
	F[0].En=4;F[0].p[0]=0;F[0].p[1]=3;F[0].p[2]=2;F[0].p[3]=1;F[0].c=CRGB(0.8,0.5,0.2);
	F[1].En=4;F[1].p[0]=4;F[1].p[1]=5;F[1].p[2]=6;F[1].p[3]=7;F[1].c=CRGB(0.8,0.4,0.3);
	F[2].En=4;F[2].p[0]=0;F[2].p[1]=4;F[2].p[2]=7;F[2].p[3]=3;F[2].c=CRGB(0.9,0.5,0.3);
	F[3].En=4;F[3].p[0]=1;F[3].p[1]=2;F[3].p[2]=6;F[3].p[3]=5;F[3].c=CRGB(0.9,0.4,0.2);
	F[4].En=4;F[4].p[0]=3;F[4].p[1]=7;F[4].p[2]=6;F[4].p[3]=2;F[4].c=CRGB(1.0,0.7,0.6);
	F[5].En=4;F[5].p[0]=0;F[5].p[1]=1;F[5].p[2]=5;F[5].p[3]=4;F[5].c=CRGB(1.0,0.5,0.5);
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
	DrawObject(&MemDC,n,OrignPoint,CubeEdgeLength);//���ຯ��	
	pDC->BitBlt(-Rect.right/2,-Rect.bottom/2,Rect.right,Rect.bottom,&MemDC,-Rect.right/2,-Rect.bottom/2,SRCCOPY);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();
	ReleaseDC(pDC);
}

void CTestView::Rotate()//��x����תAfa,��y����תBeta
{
	for(int nVertex=0;nVertex<8;nVertex++)//��������8������
	{
		CP3	PTemp;
		PTemp.x=POld[nVertex].x;
		PTemp.y=POld[nVertex].y*cos(PI*Afa/180)-POld[nVertex].z*sin(PI*Afa/180);
		PTemp.z=POld[nVertex].y*sin(PI*Afa/180)+POld[nVertex].z*cos(PI*Afa/180);		
		PNew[nVertex].x=PTemp.z*sin(PI*Beta/180)+PTemp.x*cos(PI*Beta/180);
		PNew[nVertex].y=PTemp.y;
		PNew[nVertex].z=PTemp.z*cos(PI*Beta/180)-PTemp.x*sin(PI*Beta/180);
	}
}

void CTestView::DrawObject(CDC *pDC,int n,CP3 op,double d)//���ຯ��
{
	CP3 pt[20];
	if(n==0)
	{                                                                                                                                                                                                         
		DrawCube(pDC,op,d);//��������
		return;
	}
	d=d/3;
    //�������ҵ�һ�������干9��
	ptable[0][0][0].x=op.x-d;  ptable[0][0][0].y=op.y+d;	ptable[0][0][0].z=op.z+d;
	ptable[0][0][1].x=op.x-d;  ptable[0][0][1].y=op.y;  	ptable[0][0][1].z=op.z+d;
	ptable[0][0][2].x=op.x-d;  ptable[0][0][2].y=op.y-d;	ptable[0][0][2].z=op.z+d;
	ptable[0][1][0].x=op.x-d;  ptable[0][1][0].y=op.y+d;	ptable[0][1][0].z=op.z ;
	ptable[0][1][1].x=op.x-d;  ptable[0][1][1].y=op.y;	    ptable[0][1][1].z=op.z ;
	ptable[0][1][2].x=op.x-d;  ptable[0][1][2].y=op.y-d;    ptable[0][1][2].z=op.z ;
	ptable[0][2][0].x=op.x-d;  ptable[0][2][0].y=op.y+d;	ptable[0][2][0].z=op.z-d;
	ptable[0][2][1].x=op.x-d;  ptable[0][2][1].y=op.y;	    ptable[0][2][1].z=op.z-d ;
	ptable[0][2][2].x=op.x-d;  ptable[0][2][2].y=op.y-d;	ptable[0][2][2].z=op.z-d;
	//�ڶ��������干9��
	ptable[1][0][0].x=op.x; 	ptable[1][0][0].y=op.y+d;	  ptable[1][0][0].z=op.z+d ;
	ptable[1][0][1].x=op.x;  	ptable[1][0][1].y=op.y;	      ptable[1][0][1].z=op.z+d;
	ptable[1][0][2].x=op.x;  	ptable[1][0][2].y=op.y-d;	  ptable[1][0][2].z=op.z+d;
	ptable[1][1][0].x=op.x;  	ptable[1][1][0].y=op.y+d;     ptable[1][1][0].z=op.z;
	ptable[1][1][1].x=op.x;  	ptable[1][1][1].y=op.y;	      ptable[1][1][1].z=op.z;
	ptable[1][1][2].x=op.x;  	ptable[1][1][2].y=op.y-d;     ptable[1][1][2].z=op.z;
	ptable[1][2][0].x=op.x;  	ptable[1][2][0].y=op.y+d ;    ptable[1][2][0].z=op.z-d;
	ptable[1][2][1].x=op.x; 	ptable[1][2][1].y=op.y ;	  ptable[1][2][1].z=op.z-d ;
	ptable[1][2][2].x=op.x;  	ptable[1][2][2].y=op.y-d;	  ptable[1][2][2].z=op.z-d;
	//�����������干9��	
	ptable[2][0][0].x=op.x+d;  	ptable[2][0][0].y=op.y+d;	ptable[2][0][0].z=op.z+d;
	ptable[2][0][1].x=op.x+d;  	ptable[2][0][1].y=op.y;	    ptable[2][0][1].z=op.z+d;
	ptable[2][0][2].x=op.x+d;  	ptable[2][0][2].y=op.y-d;	ptable[2][0][2].z=op.z+d;
	ptable[2][1][0].x=op.x+d;  	ptable[2][1][0].y=op.y+d;	ptable[2][1][0].z=op.z;
	ptable[2][1][1].x=op.x+d;  	ptable[2][1][1].y=op.y;	    ptable[2][1][1].z=op.z;
	ptable[2][1][2].x=op.x+d;  	ptable[2][1][2].y=op.y-d;	ptable[2][1][2].z=op.z;
	ptable[2][2][0].x=op.x+d;  	ptable[2][2][0].y=op.y+d;	ptable[2][2][0].z=op.z-d;
	ptable[2][2][1].x=op.x+d;  	ptable[2][2][1].y=op.y;	    ptable[2][2][1].z=op.z-d;
	ptable[2][2][2].x=op.x+d;  	ptable[2][2][2].y=op.y-d;	ptable[2][2][2].z=op.z-d;
	//�����������干7��
    ptable[0][1][1].flag=0;    ptable[1][0][1].flag=0;   ptable[1][1][0].flag=0;
    ptable[1][1][1].flag=0;    ptable[1][1][2].flag=0;   ptable[1][2][1].flag=0;
    ptable[2][1][1].flag=0;
	//���������ĵ���ת
	CP3	PTemp1,PTemp2,PTemp,ppt;
	PTemp1.x=op.x;													//��x����ʱ����ת
	PTemp1.y=op.y*cos(PI*Afa/180)-op.z*sin(PI*Afa/180);
	PTemp1.z=op.y*sin(PI*Afa/180)+op.z*cos(PI*Afa/180);		
	PTemp2.x=PTemp1.z*sin(PI*Beta/180)+PTemp1.x*cos(PI*Beta/180);  //��y����ʱ����ת
	PTemp2.y=PTemp1.y;
	PTemp2.z=PTemp1.z*cos(PI*Beta/180)-PTemp1.x*sin(PI*Beta/180);
	PTemp2.z=1000;
	//�ڱ��ָ��27����������Ѱ�Ҿ����ӵ���Զ��һ��
    PTemp.x=-PTemp2.z*sin(PI*Beta/180)+PTemp2.x*cos(PI*Beta/180);//��y��˳ʱ����ת
	PTemp.y=PTemp2.y;
	PTemp.z=PTemp2.z*cos(PI*Beta/180)+PTemp2.x*sin(PI*Beta/180);
	PTemp2.x=PTemp.x;										  // ��x��˳ʱ����ת
	PTemp2.y=PTemp.y*cos(PI*Afa/180)+PTemp.z*sin(PI*Afa/180);
	PTemp2.z=-PTemp.y*sin(PI*Afa/180)+PTemp.z*cos(PI*Afa/180);	
    Max_d(PTemp2);
	SortCube(pt);///����������
	for(int i=0;i<20;i++)
	DrawObject(pDC,n-1,pt[i],d);
}

void CTestView::DrawCube(CDC* pDC,CP3 op,double d)//����������
{
	ReadPoint(op,d);
    ReadFace();
	Rotate();
	CBrush NewBbrush[6],*OldBrush;//����6�������ɫ
	for(int nFace=0;nFace<6;nFace++)
	{
		CVector VS(CP3(0,0,1));//�����ʸ��
    	CVector V01(PNew[F[nFace].p[0]],PNew[F[nFace].p[1]]);//���һ����ʸ��
    	CVector V12(PNew[F[nFace].p[1]],PNew[F[nFace].p[2]]);//�����һ����ʸ��		
		CVector VN=V01*V12;//��ķ�ʸ��						
		if(Dot(VS,VN)>=0)//�����޳�			
		{
			CP3 P,T;
			NewBbrush[nFace].CreateSolidBrush(RGB(F[nFace].c.red*255,F[nFace].c.green*255,F[nFace].c.blue*255));	
			OldBrush=pDC->SelectObject(&NewBbrush[nFace]);
			pDC->BeginPath();
			for(int nEdge=0;nEdge<F[nFace].En;nEdge++)//��ѭ��
			{
				P=PNew[F[nFace].p[nEdge]];
                if(nEdge==0)
				{
					pDC->MoveTo(ROUND(P.x),ROUND(P.y));
					T=P;
				}
				else
				{
					pDC->LineTo(ROUND(P.x),ROUND(P.y));
				}		
			}
			pDC->LineTo(ROUND(T.x),ROUND(T.y));//�պ�������
			pDC->EndPath();
			pDC->FillPath();//���������
			pDC->SelectObject(OldBrush);
			NewBbrush[nFace].DeleteObject();			
		}		
	}	
}

void CTestView::OnMENUPlay()//�˵��������� 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//���ö�����ʱ�䲽
		SetTimer(1,15,NULL);	
	else
		KillTimer(1);
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI)//������ť����  
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);	

}

void CTestView::OnTimer(UINT nIDEvent)//����ʱ�亯�� 
{
	// TODO: Add your message handler code here and/or call default
	Afa+=1,Beta+=1;
	DoubleBuffer();
	CView::OnTimer(nIDEvent);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)//������Ӧ����  
{
	// TODO: Add your message handler code here and/or call default
	if(!Play)
	{
		switch(nChar)
		{
		case VK_UP:
			Afa-=5;//�趨����			
			break;
		case VK_DOWN:
			Afa+=5;
			break;
		case VK_LEFT:
			Beta-=5;
			break;
		case VK_RIGHT:
			Beta+=5;
			break;
		default:
			break;			
		}		
	}
	DoubleBuffer();		
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC)//���ñ�������  
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;   
	GetClientRect(&Rect);   
	pDC->FillSolidRect(Rect,RGB(0,0,0));
	return TRUE;
}

void CTestView::SortCube(CP3 *pt )//����������
{
	
	int A,B,C;
	A=2-a,B=2-b,C=2-c;
	int i,j,k,m=0;
	for(i=a;a>A?i>=A:i<=A;a>A?i--:i++)
		for(j=b;b>B?j>=B:j<=B;b>B?j--:j++)
			for(k=c;c>C?k>=C:k<=C;c>C?k--:k++)
			{
				if(ptable[i][j][k].flag==1)
				{
					pt[m]=CP3(ptable[i][j][k].x,ptable[i][j][k].y,ptable[i][j][k].z);
					m++;
				}
			}
}

void CTestView::OnButton1()//n=0��ť�������� 
{
	// TODO: Add your command handler code here
	n=0;
}

void CTestView::OnButton2()//n=1��ť�������� 
{
	// TODO: Add your command handler code here
	n=1;
}

void CTestView::OnButton3()//n=2��ť�������� 
{
	// TODO: Add your command handler code here
	n=2;
}

void CTestView::OnUpdateButton1(CCmdUI* pCmdUI)//n=0��ť״̬���ƺ��� 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Play?TRUE:FALSE);
}

void CTestView::OnUpdateButton2(CCmdUI* pCmdUI)//n=1��ť״̬���ƺ��� 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Play?TRUE:FALSE);
}

void CTestView::OnUpdateButton3(CCmdUI* pCmdUI)//n=2��ť״̬���ƺ��� 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Play?TRUE:FALSE);
}
