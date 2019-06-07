#include "iostream.h"
class CRect//»ùÀà  
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
