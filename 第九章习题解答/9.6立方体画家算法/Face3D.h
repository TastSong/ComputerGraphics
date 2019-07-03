// Face3D.h: interface for the Face3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACE3D_H__B12C0420_8528_4F39_AD8C_663FE6EDC917__INCLUDED_)
#define AFX_FACE3D_H__B12C0420_8528_4F39_AD8C_663FE6EDC917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Face3D  
{
public:
	Face3D();
	virtual ~Face3D();
	int num;
	int first;
	int second;
	int third;
	int fourth;
};

#endif // !defined(AFX_FACE3D_H__B12C0420_8528_4F39_AD8C_663FE6EDC917__INCLUDED_)
