#include "Rect.h"
class CCube:public CRect//公有继承派生类
{
public:
	CCube(double,double,double);
	~CCube();
	double volume();//新增面积成员函数
private:
	double height; //新增高度数据成员
};
