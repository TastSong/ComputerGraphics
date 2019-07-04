// Vector.h: interface for the CVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
#define AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi3.h"
#include "P3.h"

class CVector  //矢量类
{
public:
	CVector();	
	CVector(CP3);//重载构造函数
	CVector(CPi3,CPi3);
	CVector(CP3,CP3);//重载构造函数
	virtual ~CVector();
	double X();//矢量的x坐标
	double Y();//矢量的y坐标
	double Z();//矢量的z坐标
	CVector Unit();//单位矢量	
	double Mold();//矢量的模
	friend CVector operator +(CVector &,CVector &);//矢量和
	friend CVector operator -(CVector &,CVector &);//矢量差
	friend CVector operator *(CVector &,double);//矢量积
	friend CVector operator /(CVector &,double);//矢量数除
	friend double Dot(CVector &,CVector &);//矢量点积
	friend CVector operator *(CVector &,CVector &);//矢量叉积
private:
	double x,y,z;
};

#endif // !defined(AFX_VECTOR_H__8C972371_1C22_4E15_A2A8_3CE42319C9CB__INCLUDED_)
