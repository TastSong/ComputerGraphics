// AET.h: interface for the CAET class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CAET_H__D7F2123F_A3AE_40D6_81D8_E403C7E50447__INCLUDED_)
#define AFX_CAET_H__D7F2123F_A3AE_40D6_81D8_E403C7E50447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi2.h"

class CAET  //有效边表类
{
public:
	CAET();
	virtual ~CAET();
public:
	double x;
	int    yMax;
	double k;//代表/1k
	CPi2   pb;//起点
	CPi2   pe;//终点
	CAET   *next;
};

#endif // !defined(AFX_CAET_H__D7F2123F_A3AE_40D6_81D8_E403C7E50447__INCLUDED_)
