// RGB.h: interface for the CRGB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGB_H__8D4978C3_A3C1_4D83_89B4_BEF9084AD97B__INCLUDED_)
#define AFX_RGB_H__8D4978C3_A3C1_4D83_89B4_BEF9084AD97B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRGB  //��ɫ��
{
public:
	CRGB();
	CRGB(double,double,double);//���ع��캯��
	friend CRGB operator+(CRGB&,CRGB&);//����+
	friend CRGB operator*(double,CRGB&);//����*
	virtual ~CRGB();
public:
	double red;//RGB������
	double green;
	double blue;
};

#endif // !defined(AFX_RGB_H__8D4978C3_A3C1_4D83_89B4_BEF9084AD97B__INCLUDED_)
