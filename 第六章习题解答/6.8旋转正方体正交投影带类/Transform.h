// TransForm.h: interface for the CTransForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORM_H__19CEF13B_67A6_43B5_8E35_9A523CFF75F5__INCLUDED_)
#define AFX_TRANSFORM_H__19CEF13B_67A6_43B5_8E35_9A523CFF75F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTransform  //变换类
{
public:
	CTransform();
	virtual ~CTransform();
	void Translate(double,double,double);                 //平移变换
	void Scale(double,double,double);                     //比例变换
	void RotateX(double);		                          //绕X轴旋转变换
	void RotateY(double);			                      //绕Y轴旋转变换
	void RotateZ(double);			                      //绕Z轴旋转变换
	void ReflexXOY();					                  //XOY面反射变换
	void ReflexYOZ();					                  //YOZ面反射变换
	void ReflexZOX();					                  //ZOX面反射变换
	void Shear(double,double,double,double,double,double);//错切变换
public:
	double T[5][5];
private:
	void ClearMatrix();//变换矩阵置零
};

#endif // !defined(AFX_TRANSFORM_H__19CEF13B_67A6_43B5_8E35_9A523CFF75F5__INCLUDED_)
