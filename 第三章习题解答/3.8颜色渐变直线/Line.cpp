// Line.cpp: implementation of the CLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Line.h"
#define   ROUND(a) int(a+0.5) //四舍五入
#include "cmath"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLine::CLine()
{ 

}

CLine::~CLine()
{
	
}

void CLine::MoveTo(CDC *pDC,CP2 p0)
{	
	P0=p0;
}

void CLine::MoveTo(CDC *pDC,double x0,double y0,CRGB c0)//重载函数
{	
	P0.x=x0,P0.y=y0;P0.c=c0;
}

void CLine::LineTo(CDC *pDC,CP2 p1)
{
	P1=p1;
	CP2 p,t;
	if(fabs(P0.x-P1.x)<1e-6)//绘制垂线
	{
		if(P0.y>P1.y)//交换顶点,使得起始点低于终点顶点
		{
			t=P0;P0=P1;P1=t;
		}
		for(p=P0;p.y<P1.y;p.y++)
		{
			p.c=Interpolation(p.y,P0.y,P1.y,P0.c,P1.c);
			pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(p.c.red*255,p.c.green*255,p.c.blue*255));	
		}
	}
	else
	{
		double k,d;
		k=(P1.y-P0.y)/(P1.x-P0.x);
		if(k>1)//绘制k>1
		{
			if(P0.y>P1.y)
			{
				t=P0;P0=P1;P1=t;
			}
			d=1-0.5*k;
			for(p=P0;p.y<P1.y;p.y++)
			{
				p.c=Interpolation(p.y,P0.y,P1.y,P0.c,P1.c);
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(p.c.red*255,p.c.green*255,p.c.blue*255));
                if(d>=0)
				{
					p.x++;
					d+=1-k;
				}
				else 
                    d+=1;       
			}
		}
		if(0<=k && k<=1)//绘制0<=k<=1
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}
			d=0.5-k; 
			for(p=P0;p.x<P1.x;p.x++)
			{
				p.c=Interpolation(p.x,P0.x,P1.x,P0.c,P1.c);
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(p.c.red*255,p.c.green*255,p.c.blue*255));
                if(d<0)
				{
					p.y++;
					d+=1-k;
				}
				else 
					d-=k;		
			}
		}		
		if(k>=-1 && k<0)//绘制-1<=k<0
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}
			d=-0.5-k;
            for(p=P0;p.x<P1.x;p.x++)
			{
				p.c=Interpolation(p.x,P0.x,P1.x,P0.c,P1.c);
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(p.c.red*255,p.c.green*255,p.c.blue*255));
                if(d>0)
				{
					p.y--;
					d-=1+k;
				}
				else 
					d-=k;		
			}
		}
		if(k<-1)//绘制k<-1 
		{
			if(P0.y<P1.y)
			{
				t=P0;P0=P1;P1=t;
			}
			d=-1-0.5*k;
			for(p=P0;p.y>P1.y;p.y--)
			{
				p.c=Interpolation(p.y,P0.y,P1.y,P0.c,P1.c);
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(p.c.red*255,p.c.green*255,p.c.blue*255));
                if(d<0)
				{
					p.x++;
					d-=1+k;
				}
				else 
					d-=1;           
			}
		}
	}
	P0=p1;
}

void CLine::LineTo(CDC *pDC,double x1,double y1,CRGB c1)//重载
{
	LineTo(pDC,CP2(x1,y1,c1));
}

CRGB CLine::Interpolation(double t,double t1,double t2,CRGB c1,CRGB c2)//线性插值函数
{
	CRGB c;
	c=(t-t2)/(t1-t2)*c1+(t-t1)/(t2-t1)*c2;
	return c;
}

