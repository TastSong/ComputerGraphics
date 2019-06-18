// Line.h: interface for the CLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_)
#define AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"

class CLine  //直线类
{
public:
	CLine();
	virtual ~CLine();
    void MoveTo(CDC *,CP2);//移动到指定位置函数
	void MoveTo(CDC *,double,double,CRGB);
	void LineTo(CDC *,CP2);//绘制直线函数，不画端点
	void LineTo(CDC *,double,double,CRGB);
	CRGB Interpolation(double,double,double,CRGB,CRGB);//线性插值函数
public:
	CP2 P0;//起点
	CP2 P1;//终点
};

#endif // !defined(AFX_LINE_H__4F2B9CBA_79F9_412F_8E9F_4A7D0B14C66C__INCLUDED_)
