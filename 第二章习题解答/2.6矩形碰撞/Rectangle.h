// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _CRECTANGLE_H
#define _CRectangle_H

class CRectangle//定义长方形类  
{
public:
	CRectangle();
	CRectangle(double,double,double,double,double,double);//长方形构造函数
	virtual ~CRectangle();
	void DrawRectangle(CDC*);//绘制长方形
	void MoveRectangle();//移动长方形
	void SetSpeed(double,double);//设置长方形移动速度
public:
	double X;//矩形中心点X坐标
	double Y;//矩形中心点Y坐标
	double SpeedX;//矩形X方向移动速度
	double SpeedY;//矩形Y方向移动速度
	double Width;//矩形宽度
	double Height;//矩形高度
};

#endif 
