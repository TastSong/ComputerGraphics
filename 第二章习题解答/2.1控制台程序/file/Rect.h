#include "iostream.h"
class CRect//����  
{
public:
	CRect(double,double); 
	~CRect();
	double area();
	double circum();
protected:
	double length;
	double width;
};
