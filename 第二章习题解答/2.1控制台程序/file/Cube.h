#include "Rect.h"
class CCube:public CRect//���м̳�������
{
public:
	CCube(double,double,double);
	~CCube();
	double volume();//���������Ա����
private:
	double height; //�����߶����ݳ�Ա
};
