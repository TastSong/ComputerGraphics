// TransForm.cpp: implementation of the CTransForm class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Transform.h"
#include "Cmath"
#define PI 3.1415926
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransform::CTransform()
{

}

CTransform::~CTransform()//�任��������
{

}
void CTransform::ClearMatrix()//ƽ�Ʊ任
{
	for(int i=1;i<=4;i++)
		for(int j=1;j<=4;j++)
			T[i][j]=0;
}

void CTransform::Translate(double x,double y,double z)//ƽ�Ʊ任
{
	ClearMatrix();
	T[1][1]=1;
	T[2][2]=1;
	T[3][3]=1;
	T[4][1]=x;
	T[4][2]=y;
	T[4][3]=z;
	T[4][4]=1;	
}

void CTransform::Scale(double sx,double sy,double sz)//�����任
{
	ClearMatrix();
	T[1][1]=sx;
	T[2][2]=sy;
    T[3][3]=sz;
	T[4][4]=1;	
}

void CTransform::RotateX(double angle)//��X����ת�任
{
	ClearMatrix();
	T[1][1]=1;
	T[2][2]=cos(angle*PI/180);
	T[2][3]=sin(angle*PI/180);
	T[3][2]=-sin(angle*PI/180);
	T[3][3]=cos(angle*PI/180);	
	T[4][4]=1;
}

void CTransform::RotateY(double angle)//��Y����ת�任
{
	ClearMatrix();
	T[1][1]=cos(angle*PI/180);
	T[1][3]=-sin(angle*PI/180);
	T[2][2]=1;
	T[3][1]=sin(angle*PI/180);
	T[3][3]=cos(angle*PI/180);		
	T[4][4]=1;
}


void CTransform::RotateZ(double angle)//��Z����ת�任
{
	ClearMatrix();
	T[1][1]=cos(angle*PI/180);
	T[1][2]=sin(angle*PI/180);
	T[2][1]=-sin(angle*PI/180);
	T[2][2]=cos(angle*PI/180);
	T[3][3]=1;	
	T[4][4]=1;
}

void CTransform::ReflexXOY()//XOY�淴��任
{
	ClearMatrix();
	T[1][1]=1;
	T[2][2]=1;
	T[3][3]=-1;
	T[4][4]=1;
}

void CTransform::ReflexYOZ()//YOZ�淴��任
{
	ClearMatrix();
	T[1][1]=-1;
	T[2][2]=1;
	T[3][3]=1;
	T[4][4]=1;
}

void CTransform::ReflexZOX()//ZOX�淴��任
{
	ClearMatrix();
	T[1][1]=1;
	T[2][2]=-1;
	T[3][3]=1;
	T[4][4]=1;
}

void CTransform::Shear(double b,double c,double d,double f,double g,double h)//���б任
{
	ClearMatrix();
	T[1][1]=1;
	T[1][2]=b;
	T[1][3]=c;
	T[2][1]=d;
	T[2][2]=1;
	T[2][3]=f;
	T[3][1]=g;
	T[3][2]=h;
	T[3][3]=1;
	T[4][4]=1;
}

