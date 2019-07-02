// P2.cpp: implementation of the CP2 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "P2.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CP2::CP2()
{

}

CP2::~CP2()
{

}
CP2::CP2(double x0,double y0)
{
	this->x=x0;
	this->y=y0;
}
CP2 operator +(CP2 &p1,CP2 &p2)//ºÍ
{	
	CP2 p;
	p.x=p1.x+p2.x;
	p.y=p1.y+p2.y;
	return p;
}

CP2 operator /(CP2 &p0,double m)//Êý³ý
{
	CP2 p;
	p.x=p0.x/m;
	p.y=p0.y/m;
	return p;
}