#include"Rect.h"
CRect::CRect(double len,double wid)//������ι��캯��
{
	length=len;
	width=wid;
	cout<<"�����������"<<endl;
}
CRect::~CRect()//������������
{
	cout<<"�����������"<<endl;
}
double CRect::area()//�����������
{
	return length*width;
}
double CRect::circum()//�����ܳ�����
{
	return 2*(length+width);
}