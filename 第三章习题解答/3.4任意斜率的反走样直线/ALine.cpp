// ALine.cpp: implementation of the CALine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "ALine.h"
#define  ROUND(x)  int(x+0.5)
#include "math.h"
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

}

CALine::~CALine()
{

}
void CALine::AMoveTo(CDC* pDC,CP2 p0)
{
		P0=p0;
}
void CALine::AMoveTo(CDC *pDC,double x,double y)
{
		P0.x=x;
		P0.y=y;
}
void CALine::ALineTo(CDC* pDC,double x,double y)
{
   ALineTo(pDC,CP2(x,y));
}
void CALine::ALineTo(CDC* pDC,CP2 P1)  //�յ�
{   //�����Ȩ�������㷨��������б�ʷ�����ֱ��
	this->P1=P1;
	CP2  p,t;                                                   //�������
	if(fabs(P0.x-P1.x)<1e-6)                                    //����
	{
	  if(P0.y>P1.y)
	  {
		  t=P0;P0=P1;P1=t;
	  }	  
	  for(p.x=P0.x,p.y=P0.y;p.y<P1.y;p.y++)
	  	  pDC->SetPixel(ROUND(p.x),ROUND(p.y),RGB(0,0,0));       //���߲�������������
	}
	else
	{
		double k,e;
		k=(P1.y-P0.y)/(P1.x-P0.x);                              //ֱ��б��
		if(k>1)                                                 //����k>1
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
		if(0<=k && k<=1)                                        //����0<=k<=1
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
		if(k>=-1 && k<0)                                       //����-1<=k<0
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
		if(k<-1)                                               //����k<-1 
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
	P0=P1;
}
