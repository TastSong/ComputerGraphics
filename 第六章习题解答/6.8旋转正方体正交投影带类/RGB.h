// RGB.h: interface for the CRGB class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RGB_H__8D4978C3_A3C1_4D83_89B4_BEF9084AD97B__INCLUDED_)
#define AFX_RGB_H__8D4978C3_A3C1_4D83_89B4_BEF9084AD97B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CRGB  //颜色类
{
public:
	CRGB();
	CRGB(double,double,double);//重载构造函数
	friend CRGB operator+(CRGB&,CRGB&);//重载+
	friend CRGB operator*(double,CRGB&);//重载*
	virtual ~CRGB();
public:
	double red;//RGB三分量
	double green;
	double blue;
};

#endif // !defined(AFX_RGB_H__8D4978C3_A3C1_4D83_89B4_BEF9084AD97B__INCLUDED_)
