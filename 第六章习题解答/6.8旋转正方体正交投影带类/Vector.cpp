// Vector.cpp: implementation of the CVector class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Vector.h"
#include "Cmath"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVector::CVector()
{

}

CVector::~CVector()
{

}
CVector::CVector(CP3 &p)
{
	this->x=p.x;
	this->y=p.y;
	this->z=p.z;	
}

CVector::CVector(double x,double y,double z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}
double CVector::X()
{
	return this->x;
}

double CVector::Y()
{
	return this->y;
}
double CVector::Z()
{
	return this->z;
}

CVector CVector::Unit()//��λʸ��
{
	CVector vector;
	double product=sqrt(x*x+y*y+z*z);
	if(product<1e-5)
		product=1.0;
	vector.x=x/product;
	vector.y=y/product;
	vector.z=z/product;
	return vector;
}

double CVector::Mold(CVector &v)//ʸ����ģ
{
	double product=fabs(sqrt(v.x*v.x+v.y*v.y+v.z*v.z));
	return product;
}

double Dot(CVector &v1,CVector &v2)//ʸ���ĵ��
{
	return(v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}

CVector operator +(CVector &v1,CVector &v2)//ʸ���ĺ�
{	
	CVector vector;
	vector.x=v1.x+v2.x;
	vector.y=v1.y+v2.y;
	vector.z=v1.z+v2.z;
	return vector;
}
CVector operator -(CVector &v1,CVector &v2)//ʸ���Ĳ�
{	
	CVector vector;
	vector.x=v1.x-v2.x;
	vector.y=v1.y-v2.y;
	vector.z=v1.z-v2.z;
	return vector;
}

CVector operator *(CVector &v,double k)//ʸ���ͳ����Ļ�
{	
	CVector vector;
	vector.x=v.x*k;
	vector.y=v.y*k;
	vector.z=v.z*k;
	return vector;
}

CVector operator * (CVector &v1,CVector &v2)//ʸ���Ĳ��
{
	CVector vector;
	vector.x=v1.y*v2.z-v1.z*v2.y;
	vector.y=v1.z*v2.x-v1.x*v2.z;
	vector.z=v1.x*v2.y-v1.y*v2.x;
	return vector;
}

CVector NormalVector(CVector &v0,CVector &v1,CVector &v2)//����淨����
{
	CVector vector,vector1,vector2;
	vector1=v1-v0;
	vector2=v2-v0;
	vector=vector1*vector2;
	return vector;
}