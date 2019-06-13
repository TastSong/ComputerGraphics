// ALine.h: interface for the ALine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALINE_H__1B2064DE_2D47_4EA8_AEA2_7D959782F70F__INCLUDED_)
#define AFX_ALINE_H__1B2064DE_2D47_4EA8_AEA2_7D959782F70F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P2.h"

class CALine  //反走样直线类
{
public:
	CALine();
	virtual ~CALine();
	void AMoveTo(CDC *,CP2);
	void AMoveTo(CDC *,double,double);
	void ALineTo(CDC *,CP2);
	void ALineTo(CDC *,double,double); 
public:
	CP2 P0;//起点
	CP2 P1;//终点
};

#endif // !defined(AFX_ALINE_H__1B2064DE_2D47_4EA8_AEA2_7D959782F70F__INCLUDED_)
