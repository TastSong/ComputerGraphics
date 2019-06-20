// ALine.h: interface for the CAnTLine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALINE_H__A51218DC_20B4_4EEE_AE3F_0723B4FBEECB__INCLUDED_)
#define AFX_ALINE_H__A51218DC_20B4_4EEE_AE3F_0723B4FBEECB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"P2.h"
#include "cmath"
#include "RGB.h"
class CALine  
{
public:
	CALine();
	CALine(COLORREF bkcolor);
	virtual ~CALine();
	void AMoveTo(CDC *,CP2);
	void AMoveTo(CDC *,double,double,CRGB);
	void ALineTo(CDC *,CP2);
	void ALineTo(CDC *,double,double,CRGB);
    CRGB Interpolation(double,double,double,CRGB,CRGB);//线性插值
public:
	CP2 P0;//起点
	CP2 P1;//终点
	CRGB Bc;//背景色
};

#endif // !defined(AFX_ALINE_H__A51218DC_20B4_4EEE_AE3F_0723B4FBEECB__INCLUDED_)
