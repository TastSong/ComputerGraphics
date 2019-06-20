// ALine.cpp: implementation of the CALine class.
//
//////////////////////////////////////////////////////////////////////

#include"stdafx.h"
#include "ALine.h"
#define  ROUND(x)  int(x+0.5)
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CALine::CALine()
{ 
	Bc=CRGB(1,1,1);//屏幕背景色
}

CALine::CALine(COLORREF bkcolor)
{
	Bc=CRGB(GetRValue(bkcolor)*255,GetGValue(bkcolor)*255,GetBValue(bkcolor)*255);
}

CALine::~CALine()
{

}

void CALine::AMoveTo(CDC* pDC,CP2 p0)
{
	this->P0=p0;
}
void CALine::AMoveTo(CDC *pDC,double x,double y,CRGB c)
{
	this->P0.x=x;
	this->P0.y=y;
	this->P0.c=c;
}

void CALine::ALineTo(CDC* pDC,double x,double y,CRGB c)
{
   this->ALineTo(pDC,CP2(x,y,c));
}

void CALine::ALineTo(CDC* pDC,CP2 P1)  //终点
{   //距离加权反走样算法绘制任意斜率反走样直线
	this->P1=P1;
	CP2  p,t;                                                   //点的坐标
	if(fabs(P0.x-P1.x)<1e-6)                                    //垂线
	{
	  if(P0.y>P1.y)
	  {
		  t=P0;P0=P1;P1=t;
	  }	  
	  for(p.x=P0.x,p.y=P0.y;p.y<P1.y;p.y++)
	  	  pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(0,0,0));       //垂线不存在走样问题
	}
	else
	{
		double k,e;
		k=(P1.y-P0.y)/(P1.x-P0.x);                              //直线斜率
		if(k>1)                                                 //绘制k>1
		{
			if(P0.y>P1.y)
			{
				t=P0;P0=P1;P1=t;
			}	  		
			for(p.x=P0.x,p.y=P0.y,e=1/k;p.y<P1.y;p.y++)
			{
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(e*255,e*255,e*255));
				pDC->SetPixel(ROUND(p.x+1),ROUND(p.y),RGB((1-e)*255,(1-e)*255,(1-e)*255));
				e=e+1/k;
                if(e>=1.0)
				{
					p.x++;
					e--;
				}				     
			}
		}
		if(0<=k && k<=1)                                        //绘制0<=k<=1
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}	  
			for(p.y=P0.y,p.x=P0.x,e=k;p.x<P1.x;p.x++)
			{
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(e*255,e*255,e*255));
				pDC->SetPixel(ROUND(p.x),ROUND(p.y+1),RGB((1-e)*255,(1-e)*255,(1-e)*255));					
				e=e+k;
                if(e>=1.0)
				{
					p.y++;
					e--;
				}				     
			}
		}
		if(k>=-1 && k<0)                                       //绘制-1<=k<0
		{
			if(P0.x>P1.x)
			{
				t=P0;P0=P1;P1=t;
			}	 
			for(p.y=P0.y,p.x=P0.x,e=-k;p.x<P1.x;p.x++)
			{
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(e*255,e*255,e*255));
				pDC->SetPixel(ROUND(p.x),ROUND(p.y-1),RGB((1-e)*255,(1-e)*255,(1-e)*255));
				e=e-k;
                if(e>=1.0)
				{
					p.y--;
					e--;
				}				
			}
		}
		if(k<-1)                                               //绘制k<-1 
		{
			if(P0.y<P1.y)
			{
				t=P0;P0=P1;P1=t;
			}	  
			for(p.x=P0.x,p.y=P0.y,e=-1/k;p.y>P1.y;p.y--)
			{
				pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(e*255,e*255,e*255));
				pDC->SetPixel(ROUND(p.x+1),ROUND(p.y),RGB((1-e)*255,(1-e)*255,(1-e)*255));
				e=e-1/k;
                if(e>=1.0)
				{
					p.x++;
					e--;
				}				   
			}
		}
	}
	this->P0=P1;
}


CRGB CALine::Interpolation(double t,double t1,double t2,CRGB c1,CRGB c2)//线性插值
{
	CRGB c;
	c=(t-t2)/(t1-t2)*c1+(t-t1)/(t2-t1)*c2;
	return c;
}
