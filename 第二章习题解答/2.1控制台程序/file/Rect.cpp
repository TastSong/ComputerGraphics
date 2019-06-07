#include"Rect.h"
CRect::CRect(double len,double wid)//基类带参构造函数
{
	length=len;
	width=wid;
	cout<<"建立基类对象"<<endl;
}
CRect::~CRect()//基类析构函数
{
	cout<<"撤销基类对象"<<endl;
}
double CRect::area()//基类面积函数
{
	return length*width;
}
double CRect::circum()//基类周长函数
{
	return 2*(length+width);
}