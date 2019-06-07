#include "Cube.h"
void main()
{
	CCube *p=new CCube(30,20,100);
	cout<<"立方体的体积为："<<p->volume()<<endl;
	delete p;
}
