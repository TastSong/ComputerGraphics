// Cube.cpp: implementation of the CCube class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Cube.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCube::CCube()
{

}

CCube::~CCube()
{

}
void CCube::SetPoint()//点表
{
	double a=300;//正方体边长
	//顶点的三维坐标(x,y,z)
	Vertex[1].x=-a/2;Vertex[1].y=-a/2;Vertex[1].z=-a/2;
	Vertex[2].x=a/2; Vertex[2].y=-a/2;Vertex[2].z=-a/2;
	Vertex[3].x=a/2; Vertex[3].y=a/2; Vertex[3].z=-a/2;
	Vertex[4].x=-a/2;Vertex[4].y=a/2; Vertex[4].z=-a/2;
	Vertex[5].x=-a/2;Vertex[5].y=-a/2;Vertex[5].z=a/2;
	Vertex[6].x=a/2; Vertex[6].y=-a/2;Vertex[6].z=a/2;
	Vertex[7].x=a/2; Vertex[7].y=a/2; Vertex[7].z=a/2;
	Vertex[8].x=-a/2;Vertex[8].y=a/2; Vertex[8].z=a/2;
}
void CCube::SetFace()//面表
{
	//面的边数、面的顶点编号和面的颜色
	Face[1].En=4;Face[1].p[1]=1;Face[1].p[2]=4;Face[1].p[3]=3;Face[1].p[4]=2;Face[1].c=CRGB(255,0,0);//后面红色
	Face[2].En=4;Face[2].p[1]=5;Face[2].p[2]=6;Face[2].p[3]=7;Face[2].p[4]=8;Face[2].c=CRGB(0,255,0);//前面绿色
	Face[3].En=4;Face[3].p[1]=1;Face[3].p[2]=5;Face[3].p[3]=8;Face[3].p[4]=4;Face[3].c=CRGB(0,0,255);//左面蓝色
	Face[4].En=4;Face[4].p[1]=2;Face[4].p[2]=3;Face[4].p[3]=7;Face[4].p[4]=6;Face[4].c=CRGB(255,255,0);//右面黄色
	Face[5].En=4;Face[5].p[1]=4;Face[5].p[2]=8;Face[5].p[3]=7;Face[5].p[4]=3;Face[5].c=CRGB(255,0,255);//顶面品红
	Face[6].En=4;Face[6].p[1]=1;Face[6].p[2]=2;Face[6].p[3]=6;Face[6].p[4]=5;Face[6].c=CRGB(0,255,255);//底面青色
}
void CCube::VertexToHomogen()//CP3顶点数组的齐次矩阵
{
	for(int i=1;i<=8;i++)
	{
		H[i][1]=Vertex[i].x;H[i][2]=Vertex[i].y;
		H[i][3]=Vertex[i].z;
		H[i][4]=1;
	}
}
void CCube::Multiply(CTransform Tran)//H×T
{
	VertexToHomogen();
	CCube cube;
	for(int i=1;i<=8;i++)
		for(int j=1;j<=4;j++)
			cube.H[i][j]=H[i][j];
	ClearH();
	for(i=1;i<=8;i++)
		for(int j=1;j<=4;j++)
			for(int k=1;k<=4;k++)
				H[i][j]+=cube.H[i][k]*Tran.T[k][j];	
	HomogenToVertex();
}

void CCube::ClearH()//齐次矩阵置零
{
	for(int i=1;i<=8;i++)
		for(int j=1;j<=4;j++)
			H[i][j]=0;	
}

void CCube::HomogenToVertex()//齐次矩阵转换为CP3顶点数组
{
	for(int i=1;i<=8;i++)
	{
		Vertex[i].x=H[i][1];
		Vertex[i].y=H[i][2];
		Vertex[i].z=H[i][3];
	}
}