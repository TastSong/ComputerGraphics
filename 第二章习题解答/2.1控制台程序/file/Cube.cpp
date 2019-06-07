#include "Cube.h"
CCube::CCube(double len,double wid,double hei):CRect(len,wid) //派生类构造函数
{
	height=hei;
	cout<<"建立派生类对象"<<endl;
} 
CCube::~CCube()//派生类析构函数
{
	cout<<"撤销派生类对象"<<endl;
}
double CCube::volume()//派生类体积函数
{
	return length*width*height;
}
