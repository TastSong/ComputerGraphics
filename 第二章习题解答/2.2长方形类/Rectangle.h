// Rectangle.h: interface for the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECTANGLE_H__94FC0B8E_D5C7_4306_A30C_E0FA89A3CD94__INCLUDED_)
#define AFX_RECTANGLE_H__94FC0B8E_D5C7_4306_A30C_E0FA89A3CD94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InputDlg.h"//�����Ի���ͷ�ļ�

class CRectangle  //��������
{
public:
	CRectangle();
	virtual ~CRectangle();
	void input();
	double circum();//�ܳ�����
	double area();//�������
private:
	double length;//�����εĳ���
	double width;//�����εĿ��
};

#endif // !defined(AFX_RECTANGLE_H__94FC0B8E_D5C7_4306_A30C_E0FA89A3CD94__INCLUDED_)
