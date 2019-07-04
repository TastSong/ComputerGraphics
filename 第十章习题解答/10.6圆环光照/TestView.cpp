// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "cmath"//������ѧͷ�ļ�
#define  PI 3.1415926//Բ����
#define  ROUND(x)  int(x+0.5)//��������
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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_MENUPlay, OnMENUPlay)
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_MENUPlay, OnUpdateMENUPlay)
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
	R=1000,d=800,Phi=0.0,Theta=0.0;
	LightNum=1;
	pLight=new CLighting(LightNum);
	pLight->Light[0].SetGlobal(1000,-40,0);
	for(int i=0;i<LightNum;i++)
	{
		pLight->Light[i].L_Diffuse=CRGB(1.0,1.0,1.0);//��Դ����������ɫ	
		pLight->Light[i].L_Specular=CRGB(0.828,0.636,0.366);//��Դ����߹���ɫ
		pLight->Light[i].L_C0=1.1;//����˥��ϵ��
		pLight->Light[i].L_C1=0.0000001;//����˥��ϵ��
		pLight->Light[i].L_C2=0.00000003;//����˥��ϵ��
		pLight->Light[i].L_OnOff=TRUE;//��Դ����	
	}
 	pMaterial=new CMaterial;//һά���ʶ�̬����
	pMaterial->M_Ambient=CRGB(0.547,0.400,0.075);//���ʶԻ�����ķ�����
	pMaterial->M_Diffuse=CRGB(0.912,0.616,0.116);//���ʶ��������ķ�����
	pMaterial->M_Specular=CRGB(1.0,1.0,1.0);//���ʶԾ��淴���ķ�����
	pMaterial->M_Exp=80.0;//�߹�ָ��
}

CTestView::~CTestView()
{
	if(pLight)
		delete [] pLight;
	if(pMaterial)
		delete pMaterial;
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
	InitParameter();
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
void CTestView::InitParameter()
{
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[3]*k[2];
	k[6]=k[1]*k[2];
	k[7]=k[3]*k[4];
	k[8]=k[1]*k[4];
	ViewPoint.x=R*k[5];//�û�����ϵ���ӵ�������
	ViewPoint.y=R*k[6];
	ViewPoint.z=R*k[4];
}
void CTestView::PerProject(CP3 P)
{
	CP3 ViewP;
	ViewP.x=-k[1]*P.x+k[3]*P.y;//�۲�����ϵ��ά����
	ViewP.y=-k[7]*P.x-k[8]*P.y+k[2]*P.z;
	ViewP.z=-k[5]*P.x-k[6]*P.y-k[4]*P.z+R;
	ViewP.c=P.c; 
	ScreenP.x=d*ViewP.x/ViewP.z;//��Ļ����ϵ��ά����
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.z=d*(R-ViewP.z)/ViewP.z;
	ScreenP.c=ViewP.c;
}

void CTestView::DoubleBuffer()//˫����
{
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//�Զ�������ϵ
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//��Ļ����Ϊԭ��	
	CDC	MemDC,Picture;
	MemDC.CreateCompatibleDC(pDC);
	MemDC.SetMapMode(MM_ANISOTROPIC);
	MemDC.SetWindowExt(Rect.Width(),Rect.Height());
	MemDC.SetViewportExt(Rect.Width(),-Rect.Height());
	MemDC.SetViewportOrg(Rect.Width()/2,Rect.Height()/2);
	CBitmap NewBitmap,*OldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	OldBitmap=MemDC.SelectObject(&NewBitmap);
	MemDC.BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&Picture,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	DrawObject(&MemDC);//��	
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();	
}

void CTestView::DrawObject(CDC *pDC)
{
	zbuf.InitDeepBuffer(600,600,-600);//��ȳ�ʼ��
	double afa1,afa2,beta1,beta2;
	int afa=9,beta=12;//�ȷֽǶ�
	int NumR1=360/afa,NumR2=360/beta;//��Ƭ����ΪNumR1��NumR2
	R1=200;R2=80;//Բ����Բ��СԲ�뾶
	CP3 **P=new CP3 *[NumR1+1];//��ά��̬����
	for(int n=0;n<NumR1+1;n++)
	{
		P[n]=new CP3[NumR2+1];
	}	
	for(int i=0;i<NumR1;i++)
	{
		for(int j=0;j<NumR2;j++)//���㸳ֵ
		{
			afa1=afa*i*PI/180,afa2=(afa*(i+1))*PI/180;
			beta1=beta*j*PI/180,beta2=(beta*(j+1))*PI/180;
			P[i][j].x=R1*cos(afa1)+R2*sin(beta1)*cos(afa1);//P[0]
			P[i][j].y=R1*sin(afa1)+R2*sin(beta1)*sin(afa1);
			P[i][j].z=R2*cos(beta1);
			P[i][j+1].x=R1*cos(afa1)+R2*sin(beta2)*cos(afa1);//P[1]
			P[i][j+1].y=R1*sin(afa1)+R2*sin(beta2)*sin(afa1);
			P[i][j+1].z=R2*cos(beta2);
			P[i+1][j+1].x=R1*cos(afa2)+R2*sin(beta2)*cos(afa2);//P[2]
			P[i+1][j+1].y=R1*sin(afa2)+R2*sin(beta2)*sin(afa2);
			P[i+1][j+1].z=R2*cos(beta2);
			P[i+1][j].x=R1*cos(afa2)+R2*sin(beta1)*cos(afa2);//P[3]
			P[i+1][j].y=R1*sin(afa2)+R2*sin(beta1)*sin(afa2);
			P[i+1][j].z=R2*cos(beta1);
		}
	}
	for(i=0;i<NumR1;i++)//ѭ������ÿ�������ƽ��ʸ��
	{
		for(int j=0;j<NumR2;j++)
		{
			int beforei=i-1,beforej=j-1;
			int afteri=i+1,afterj=j+1;
			if(i==0) beforei=NumR1-1;
			if(j==0) beforej=NumR2-1;
			if(afteri==NumR1) afteri=0;
			if(afterj==NumR2) afterj=0;
			CVector VN0,VN1,VN2,VN3,VN;//�ĸ���Ƭ�ķ�ʸ����ƽ��ʸ��	
			CVector edge00(P[beforei][beforej],P[beforei][j]);
			CVector edge01(P[beforei][j],P[i][j]);
			VN0=edge00*edge01;
			CVector edge10(P[beforei][j],P[beforei][afterj]);
			CVector edge11(P[beforei][afterj],P[i][afterj]);
			VN1=edge10*edge11;
			CVector edge20(P[i][j],P[i][afterj]);
			CVector edge21(P[i][afterj],P[afteri][afterj]);
			VN2=edge20*edge21;
			CVector edge30(P[i][beforej],P[i][j]);
			CVector edge31(P[i][j],P[afteri][j]);
			VN3=edge30*edge31;
			VN=VN0+VN1+VN2+VN3;
			VN=VN/VN.Mold();
			P[i][j].c=pLight->Lighting(ViewPoint,P[i][j],VN,pMaterial);
		}
	}
	for( i=0;i<NumR1;i++)
	{
		for(int j=0;j<NumR2;j++)
		{
			int afteri=i+1,afterj=j+1;
			if(afteri==NumR1)	afteri=0;
			if(afterj==NumR2)	afterj=0;
			CP3 Pt[4];
			Pt[0]=P[i][j];Pt[1]=P[i][afterj];
			Pt[2]=P[afteri][afterj];Pt[3]=P[afteri][j];
			CVector VS(Pt[1],ViewPoint);//�����ʸ��
			CVector V10(Pt[0],Pt[1]);//���һ����ʸ��
			CVector V21(Pt[1],Pt[2]);//�����һ����ʸ��				
			CVector VN=V10*V21;//��ķ�ʸ��		
			CPi3 Point[4];
			for(int i=0;i<4;i++)
			{
				PerProject(Pt[i]);
				Point[i].x=ScreenP.x;
				Point[i].y=ROUND(ScreenP.y);
				Point[i].z=ScreenP.z;
				Point[i].c=ScreenP.c;
			}
			if(Dot(VS,VN)>=0)//͹����������
			{
				zbuf.SetPoint(Point,4);			
				zbuf.CreateBucket();//����Ͱ��
				zbuf.CreateEdge();//�����߱�
				zbuf.Gouraud(pDC);//��ɫ��������ı���	
			}
		}
	}
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	int j=0; 
	switch(nChar)
	{
	case VK_UP:
		Phi-=5;
		for(j=0;j<LightNum;j++)
		{
			pLight->Light[j].L_Phi-=5;
		}
		break;
	case VK_DOWN:
		Phi+=5;
		for(j=0;j<LightNum;j++)
		{
			pLight->Light[j].L_Phi+=5;
		}		
		break;
	case VK_LEFT:
		Theta-=5;
		for(j=0;j<LightNum;j++)
		{
			pLight->Light[j].L_Theta-=5;
		}	
		break;
	case VK_RIGHT:
		Theta+=5;
		for(j=0;j<LightNum;j++)
		{
			pLight->Light[j].L_Theta+=5;
		}		
		break;
	default:
		break;
	}
	InitParameter();
	DoubleBuffer();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnMENUPlay() 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//���ö�����ʱ�䲽
		SetTimer(1,15,NULL);		
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Phi-=5;
	Theta-=5;
	for(int j=0;j<LightNum;j++)
	{
		pLight->Light[j].L_Phi-=5;
		pLight->Light[j].L_Theta-=5;
	}	
	InitParameter();
	DoubleBuffer();
	CView::OnTimer(nIDEvent);
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI)//������ť״̬���� 
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI ->SetCheck(TRUE);
	else
		pCmdUI ->SetCheck(FALSE);	
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;   
	GetClientRect(&Rect);   
	pDC->FillSolidRect(Rect,RGB(0,0,0));
	return true;
}


