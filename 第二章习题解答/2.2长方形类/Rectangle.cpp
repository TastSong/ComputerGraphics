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
	CInputDlg Dlg;//����Ի��������
	if(IDOK==Dlg.DoModal())//�����OK��ť
	{
		length=Dlg.m_len;//����Ի���������ĳ���
		width=Dlg.m_wid;
	}
}
double CRectangle::circum()//�����ܳ�����
{
	return 2*(length+width);
}
double CRectangle::area()//�����������
{
	return length*width;
}
