#include "Cube.h"
CCube::CCube(double len,double wid,double hei):CRect(len,wid) //�����๹�캯��
{
	height=hei;
	cout<<"�������������"<<endl;
} 
CCube::~CCube()//��������������
{
	cout<<"�������������"<<endl;
}
double CCube::volume()//�������������
{
	return length*width*height;
}
