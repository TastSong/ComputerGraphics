// TransForm.h: interface for the CTransForm class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORM_H__19CEF13B_67A6_43B5_8E35_9A523CFF75F5__INCLUDED_)
#define AFX_TRANSFORM_H__19CEF13B_67A6_43B5_8E35_9A523CFF75F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTransform  //�任��
{
public:
	CTransform();
	virtual ~CTransform();
	void Translate(double,double,double);                 //ƽ�Ʊ任
	void Scale(double,double,double);                     //�����任
	void RotateX(double);		                          //��X����ת�任
	void RotateY(double);			                      //��Y����ת�任
	void RotateZ(double);			                      //��Z����ת�任
	void ReflexXOY();					                  //XOY�淴��任
	void ReflexYOZ();					                  //YOZ�淴��任
	void ReflexZOX();					                  //ZOX�淴��任
	void Shear(double,double,double,double,double,double);//���б任
public:
	double T[5][5];
private:
	void ClearMatrix();//�任��������
};

#endif // !defined(AFX_TRANSFORM_H__19CEF13B_67A6_43B5_8E35_9A523CFF75F5__INCLUDED_)
