// MyRect.cpp: implementation of the CMyRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "MyRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyRect::CMyRect()
{
	length=0.0;
	width=0.0;
}

CMyRect::~CMyRect()
{

}

void CMyRect::input()
{
	CInputDlg Dlg;//定义对话框类对象
	if(IDOK==Dlg.DoModal())//点击了OK按钮
	{
		length=Dlg.m_len;//读入对话框里输入的长度
		width=Dlg.m_wid;
	}
}
double CMyRect::area()
{
	return length*width;
}
double CMyRect::circum()
{
	return 2*(length+width);
}