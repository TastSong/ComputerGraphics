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
	CInputDlg Dlg;//����Ի��������
	if(IDOK==Dlg.DoModal())//�����OK��ť
	{
		length=Dlg.m_len;//����Ի���������ĳ���
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