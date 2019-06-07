// Rectangle.cpp: implementation of the CRectangle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Rectangle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRectangle::CRectangle()
{

}

CRectangle::~CRectangle()
{

}
void CRectangle::input()
{
	CInputDlg Dlg;//定义对话框类对象
	if(IDOK==Dlg.DoModal())//点击了OK按钮
	{
		length=Dlg.m_len;//读入对话框里输入的长度
		width=Dlg.m_wid;
	}
}
double CRectangle::circum()//定义周长函数
{
	return 2*(length+width);
}
double CRectangle::area()//定义面积函数
{
	return length*width;
}
