// Face.h: interface for the CFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACE_H__6BDEB84F_A0BC_419C_ACBE_01555468CB0A__INCLUDED_)
#define AFX_FACE_H__6BDEB84F_A0BC_419C_ACBE_01555468CB0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFace  
{
public:
	CFace();
	virtual ~CFace();
	int En;//面的边数
	int p[4];//面的顶点号
};

#endif // !defined(AFX_FACE_H__6BDEB84F_A0BC_419C_ACBE_01555468CB0A__INCLUDED_)
