// Point3D.h: interface for the Point3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POINT3D_H__7A73AE23_EF21_4B23_871C_ADB37881A13B__INCLUDED_)
#define AFX_POINT3D_H__7A73AE23_EF21_4B23_871C_ADB37881A13B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Point3D  
{
public:
	Point3D();
	virtual ~Point3D();
	double x;
	double y;
	double z;
	double h;
};

#endif // !defined(AFX_POINT3D_H__7A73AE23_EF21_4B23_871C_ADB37881A13B__INCLUDED_)
