#include "Cube.h"
void main()
{
	CCube *p=new CCube(30,20,100);
	cout<<"����������Ϊ��"<<p->volume()<<endl;
	delete p;
}
