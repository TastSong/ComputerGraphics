// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#include "cmath"//数学头文件
#define  PI 3.1415926//圆周率
#define  ROUND(x)  int(x+0.5)
#define WIDTH 512
#define HEIGHT 256
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
	ON_WM_ERASEBKGND()
	ON_UPDATE_COMMAND_UI(ID_MENUPlay, OnUpdateMENUPlay)
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
	R=1000,d=800,Phi=100.0,Theta=-90;	
	LightNum=1;//光源个数
	pLight=new CLighting(LightNum);//一维光源动态数组
	pLight->Light[0].SetGlobal(1200,50,60);//设置第一个光源球坐标
	for(int i=0;i<LightNum;i++)
	{
		pLight->Light[i].L_Diffuse=CRGB(0.9,0.9,0.9);//光源的漫反射颜色	
		pLight->Light[i].L_Specular=CRGB(0.9,0.9,0.9);//光源镜面高光颜色
		pLight->Light[i].L_C0=1.0;//常数衰减系数
		pLight->Light[i].L_C1=0.0000001;//线性衰减系数
		pLight->Light[i].L_C2=0.00000001;//二次衰减系数
		pLight->Light[i].L_OnOff=TRUE;//光源开启
	}
 	pMaterial=new CMaterial;//一维材质动态数组
	pMaterial->M_Ambient=CRGB(0.5,0.5,0.5);//材质对环境光的反射率
	pMaterial->M_Diffuse=CRGB(1.0,1.0,1.0);//材质对漫反射光的反射率
	pMaterial->M_Specular=CRGB(1.0,1.0,1.0);//材质对镜面反射光的反射率
	pMaterial->M_Exp=50.0;//高光指数
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
	ReadImage();
	ReadPoint();
	ReadFace();
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
void CTestView::ReadImage()//读入BMP图片（为提高效率，采用500*500的图片）
{
	CBitmap m_bmp;
	m_bmp.LoadBitmap(IDB_EARTH);//调入位图资源
	BITMAP bm;//定义一个BITMAP结构变量，以便获取位图参数
	m_bmp.GetObject(sizeof(BITMAP),&bm);
	CDC *pDC=GetDC();
	CDC dcMem;//定义并创建一个内存设备环境
	dcMem.CreateCompatibleDC(pDC);
	CBitmap *Oldbitmap=dcMem.SelectObject(&m_bmp);//将位图选入内存设备环境中
	
	Image=new COLORREF*[WIDTH];
	for(int i=0;i<WIDTH;i++)//Height
	{
		Image[i]=new COLORREF[HEIGHT];
		for(int j=0;j<HEIGHT;j++)//Width
		{
			Image[i][j]=dcMem.GetPixel(i,j);
		}
	}
	dcMem.SelectObject(Oldbitmap);
}

void CTestView::ReadPoint()//读入点坐标
{
	afa=beta=10;//面片夹角
	N1=180/afa,N2=360/beta;//N1为纬度区间,N2为经度区间
	P=new CP3[(N1-1)*N2+2];//纬度方向除南北极点外有“N1－1”个点，“2”代表南北极两点
	double afa1,beta1;
	r=300;//r为球半径
	//计算北极点
	P[0].x=0,P[0].y=0,P[0].z=r;//北极点坐标
	//计算球体上的点
	for(int i=0;i<=N1-2;i++)
	{
		afa1=(i+1)*afa*PI/180;
		for(int j=0;j<N2;j++)
	    {
			beta1=j*beta*PI/180;		
			P[i*N2+j+1].x=r*sin(afa1)*cos(beta1);
			P[i*N2+j+1].y=r*sin(afa1)*sin(beta1);
			P[i*N2+j+1].z=r*cos(afa1);				
		}
	}
	//计算南极点
	P[(N1-1)*N2+1].x=0,P[(N1-1)*N2+1].y=0,P[(N1-1)*N2+1].z=-r;	
}

void CTestView::ReadFace()//读入面坐标
{
	//面的二维动态数组
	F=new CFace *[N1];
	for(int n=0;n<N1;n++)
	{
		F[n]=new CFace[N2];
	}
	//构造北极三角形面片
	for(int j=0;j<N2;j++)
	{
		int tempj=j+1;
		if(tempj==N2) tempj=0;//面片的首尾连接
		int NorthIndex[3];//北极三角形面片索引号数组
		NorthIndex[0]=0;
		NorthIndex[1]=j+1;
		NorthIndex[2]=tempj+1;
		F[0][j]=CFace(NorthIndex,3);
		F[0][j].SetNormal(P[NorthIndex[0]],P[NorthIndex[1]],P[NorthIndex[2]]);//计算小面片法矢量
	}
	//构造球体四边形面片
	for(int i=1;i<N1-1;i++)
	{
		for(int j=0;j<N2;j++)
	    {
			int tempi=i+1;
			int tempj=j+1;
			if(tempj==N2) tempj=0;
			int BodyIndex[4];//球体四边形面片索引号数组
			BodyIndex[0]=(i-1)*N2+j+1;
			BodyIndex[1]=(tempi-1)*N2+j+1;
			BodyIndex[2]=(tempi-1)*N2+tempj+1;
			BodyIndex[3]=(i-1)*N2+tempj+1;
			F[i][j]=CFace(BodyIndex,4);
			F[i][j].SetNormal(P[BodyIndex[0]],P[BodyIndex[1]],P[BodyIndex[2]]);//计算小面片法矢量
		}
	}
	//构造南极三角形面片
	for(j=0;j<N2;j++)
	{
		int tempj=j+1;
		if(tempj==N2) tempj=0;
		int SouthIndex[3];//南极三角形面片索引号数组
		SouthIndex[0]=(N1-2)*N2+j+1;
		SouthIndex[1]=(N1-1)*N2+1;
		SouthIndex[2]=(N1-2)*N2+tempj+1;
		F[N1-1][j]=CFace(SouthIndex,3);	
		F[N1-1][j].SetNormal(P[SouthIndex[0]],P[SouthIndex[1]],P[SouthIndex[2]]);//计算小面片法矢量
	}
}

void CTestView::InitParameter()//透视变换常数
{
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[3]*k[2];
	k[6]=k[1]*k[2];
	k[7]=k[3]*k[4];
	k[8]=k[1]*k[4];
	ViewPoint.x=R*k[5];//用户坐标系的视点球坐标
	ViewPoint.y=R*k[6];
	ViewPoint.z=R*k[4];
}

void CTestView::PerProject(CP3 P)//透视变换
{
	CP3 ViewP;
	ViewP.x=-k[1]*P.x+k[3]*P.y;//观察坐标系三维坐标
	ViewP.y=-k[7]*P.x-k[8]*P.y+k[2]*P.z;
	ViewP.z=-k[5]*P.x-k[6]*P.y-k[4]*P.z+R;
	ViewP.c=P.c;
	ScreenP.x=d*ViewP.x/ViewP.z;//屏幕坐标系二维坐标
	ScreenP.y=d*ViewP.y/ViewP.z;
	ScreenP.z=d*(d-ViewP.z)/ViewP.z;
	ScreenP.c=ViewP.c;
}

void CTestView::DoubleBuffer()//双缓冲
{
	CRect Rect;
	GetClientRect(&Rect);
	CDC *pDC=GetDC();
	pDC->SetMapMode(MM_ANISOTROPIC);//自定义坐标系
	pDC->SetWindowExt(Rect.Width(),Rect.Height());
	pDC->SetViewportExt(Rect.Width(),-Rect.Height());//x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(Rect.Width()/2,Rect.Height()/2);//屏幕中心为原点	
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
    DrawObject(&MemDC);	
	pDC->BitBlt(-Rect.Width()/2,-Rect.Height()/2,Rect.Width(),Rect.Height(),&MemDC,-Rect.Width()/2,-Rect.Height()/2,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(OldBitmap);	
	NewBitmap.DeleteObject();	
}
void CTestView::PointColor()//计算顶点颜色
{
	for(int i=0;i<(N1-1)*N2+2;i++)//遍历所有点
	{
		CVector PNormal(P[i]);//点的法矢量代表共享该点的所有面的平均法矢量
		P[i].c=pLight->Lighting(ViewPoint,P[i],PNormal,pMaterial);//调用光照函数
	}
}

void CTestView::DrawObject(CDC *pDC)//绘制球面
{
	CPi3 Point3[3];//南北极顶点数组
	double u3[3],v3[3];
	CVector Normal3[3];
	CPi3 Point4[4];//球体顶点数组
	double u4[4],v4[4];
	CVector Normal4[4];
	for(int i=0;i<N1;i++)
	{
		for(int j=0;j<N2;j++)
		{
			CVector VS(P[F[i][j].pIndex[1]],ViewPoint);//面的视矢量
			if(Dot(VS,F[i][j].Normal)>=0)
			{
				if(F[i][j].En==3)
				{
					for(int m=0;m<F[i][j].En;m++)
					{
						PerProject(P[F[i][j].pIndex[m]]);
						Point3[m].x=ScreenP.x;
						Point3[m].y=ROUND(ScreenP.y);
						Point3[m].z=ScreenP.z;
						Normal3[m]=CVector(P[F[i][j].pIndex[m]]);
						CP3 p=P[F[i][j].pIndex[m]];
						int u,v;
						double theta,phi;
						//利用空间坐标系下的点坐标来求对应二维平面的纹理坐标
						if(p.y>=0)
						{
							theta=360*acos(p.x/sqrt(r*r-p.z*p.z))/(2*PI);
						}
						else
						{
						   theta=360-360*acos(p.x/sqrt(r*r-p.z*p.z))/(2*PI);
						}
						if(m==0&&i==0)
						{
							theta=(j+0.5)*360/N2;
						}
						if(m==1&&i==(N1-1))
							theta=(j+0.5)*360/N2;
						if(j==(N2-1)&&m==2)
							theta=360;
						phi=acos(p.z/r)*180/PI;
						u=ROUND(theta/360*WIDTH);
						v=ROUND(phi/180*HEIGHT);
						u3[m]=u;
						v3[m]=v;
					}			
					zbuf.SetPoint(Point3,Normal3,u3,v3,3);//初始化南北极的CZBuffer对象
					zbuf.CreateBucket();//建立桶表
					zbuf.CreateEdge();//建立边表
					zbuf.Fill(pDC,Image,ViewPoint,pLight,pMaterial);//颜色渐变填充三角形
				}
				else
				{
					for(int m=0;m<F[i][j].En;m++)
					{
						PerProject(P[F[i][j].pIndex[m]]);
						Point4[m].x=ScreenP.x;
						Point4[m].y=ROUND(ScreenP.y);
						Point4[m].z=ScreenP.z;
						Normal4[m]=CVector(P[F[i][j].pIndex[m]]);
						CP3 p=P[F[i][j].pIndex[m]];
						int u,v;
						double theta,phi;
						//利用空间坐标系下的点坐标来求对应二维平面的纹理坐标
						if(p.y>=0)
						{   
							theta=360*acos(p.x/sqrt(r*r-p.z*p.z))/(2*PI);					
						}
						else
						{
						   theta=360-360*acos(p.x/sqrt(r*r-p.z*p.z))/(2*PI);
						}
						if((m==2||m==3)&&j==(N2-1))
							theta=360;

						phi=acos(p.z/r)*180/PI;

						u=ROUND(theta/360*WIDTH);
						v=ROUND(phi/180*HEIGHT);
						u4[m]=u;
						v4[m]=v;
					}
					zbuf.SetPoint(Point4,Normal4,u4,v4,4);//初始化CZBuffer对象
					zbuf.CreateBucket();//建立桶表
					zbuf.CreateEdge();//建立边表
					zbuf.Fill(pDC,Image,ViewPoint,pLight,pMaterial);//颜色渐变填充四边形
				}
			} 	
		}	
	}		
}
	
void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(!Play)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi-=5;//设定步长
			break;
		case VK_DOWN:
			Phi+=5;
			break;
		case VK_LEFT:
			Theta-=5;
			break;
		case VK_RIGHT:
		    Theta+=5;
			break;
		default:
			break;			
		}
		InitParameter();
		DoubleBuffer();		
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnMENUPlay() 
{
	// TODO: Add your command handler code here
	Play=Play?FALSE:TRUE;
	if (Play)//设置动画的时间步
		SetTimer(1,15,NULL);	
	else
		KillTimer(1);
}

void CTestView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Phi-=5;//设定步长
	Theta-=5;
	InitParameter();
	DoubleBuffer();	
	CView::OnTimer(nIDEvent);
}


BOOL CTestView::OnEraseBkgnd(CDC* pDC)//设置背景函数 
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;   
	GetClientRect(&Rect);   
	pDC->FillSolidRect(Rect,RGB(0,0,0));
	return true;
}

void CTestView::OnUpdateMENUPlay(CCmdUI* pCmdUI)//动画按钮状态函数  
{
	// TODO: Add your command update UI handler code here
	if(Play)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}
