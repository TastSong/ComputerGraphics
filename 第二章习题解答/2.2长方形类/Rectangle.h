// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__94FC0B8E_D5C7_4306_A30C_E0FA89A3CD94__INCLUDED_)
#define AFX_RECTANGLE_H__94FC0B8E_D5C7_4306_A30C_E0FA89A3CD94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InputDlg.h"//包含对话框头文件

class CRectangle  //长方形类
{
public:
	CRectangle();
	virtual ~CRectangle();
	void input();
	double circum();//周长函数
	double area();//面积函数
private:
	double length;//长方形的长度
	double width;//长方形的宽度
};

#endif // !defined(AFX_RECTANGLE_H__94FC0B8E_D5C7_4306_A30C_E0FA89A3CD94__INCLUDED_)
