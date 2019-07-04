// Pi3.h: interface for the CPi3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PI3_H__1DC85C9B_C92E_4165_9851_4C61236BF305__INCLUDED_)
#define AFX_PI3_H__1DC85C9B_C92E_4165_9851_4C61236BF305__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "RGB.h"

class CPi3  //三维点类，y坐标取整数
{
public:
	CPi3();
	virtual ~CPi3();
	double x;
	int y;
	double z;
	CRGB c;
};

#endif // !defined(AFX_PI3_H__1DC85C9B_C92E_4165_9851_4C61236BF305__INCLUDED_)
