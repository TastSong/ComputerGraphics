// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rectangle.h"
#include "Test.h"
#define ROUND(a) int(a+0.5)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle()
{

}

CRectangle::CRectangle(double X,double Y,double Width,double Height,double SpeedX,double SpeedY)
{
	this->X=X;
	this->Y=Y;
	this->SpeedX=SpeedX;
	this->SpeedY=SpeedY;
	this->Width=Width;
	this->Height=Height;
}

CRectangle::~CRectangle()
{

}

void CRectangle::SetSpeed(double spx,double spy)
{
	SpeedX=spx;
	SpeedY=spy;
}

void CRectangle::MoveRectangle()
{
	X+=SpeedX;
	Y+=SpeedY;
}

void CRectangle::DrawRectangle(CDC* pDC)
{
	pDC->Rectangle(ROUND((X-Width/2)),ROUND((Y-Height/2)),ROUND((X+Width/2)),ROUND((Y+Height/2)));
}