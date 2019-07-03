// Material.cpp: implementation of the CMaterial class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Material.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaterial::CMaterial()
{
	M_Ambient=CRGB(0.192,0.192,0.192);//���ʶԻ�����ķ�����
	M_Diffuse=CRGB(0.0,1.0,0.0);//���ʶ��������ķ�����
	M_Specular=CRGB(1.0,1.0,1.0);//���ʶԾ��淴���ķ�����
	M_Exp=5;//�߹�ָ��
}

CMaterial::~CMaterial()
{

}

void CMaterial::SetExp(double Exp)
{
	this->M_Exp=Exp;
}

void CMaterial::SetAmbient(CRGB c)
{
	this->M_Ambient=c;
}

void CMaterial::SetDiffuse(CRGB c)
{
	this->M_Diffuse=c;
}

void CMaterial::SetSpecular(CRGB c)
{
	M_Specular=c;
}