// MyRect.h: interface for the CMyRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYRECT_H__3F082811_98D7_4AD1_A827_1F111763BFBA__INCLUDED_)
#define AFX_MYRECT_H__3F082811_98D7_4AD1_A827_1F111763BFBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InputDlg.h"//包含对话框头文件

class CMyRect  
{
public:
	CMyRect();
	virtual ~CMyRect();
	void input();
	double circum();
	double area();
private:
	double length,width;
};

#endif // !defined(AFX_MYRECT_H__3F082811_98D7_4AD1_A827_1F111763BFBA__INCLUDED_)
