// Aet.h: interface for the Aet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AET_H__3919964E_FE9E_4BCC_B7B4_325B1517ACC2__INCLUDED_)
#define AFX_AET_H__3919964E_FE9E_4BCC_B7B4_325B1517ACC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Aet  
{
public:
	Aet();
	virtual ~Aet();
	double x;
	double yMax;
	double k;//´ú±í1/k
	Aet *next;
};

#endif // !defined(AFX_AET_H__3919964E_FE9E_4BCC_B7B4_325B1517ACC2__INCLUDED_)
