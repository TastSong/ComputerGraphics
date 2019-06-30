// Cube.h: interface for the CCube class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBE_H__94DB34D3_98C9_4C95_BBE5_CAF5BFEC50FC__INCLUDED_)
#define AFX_CUBE_H__94DB34D3_98C9_4C95_BBE5_CAF5BFEC50FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"
#include "Face.h"
#include "TransForm.h"

class CCube  //��������
{
public:
	CCube();
	virtual ~CCube();
	void SetPoint();//���
	void SetFace();//���
	void Multiply(CTransform matrix);//�������ξ�����Ա任����
	void VertexToHomogen();//CP3�����������ξ��� 
	void HomogenToVertex();//��ξ���ת��ΪCP3��������
public:
	CP3 Vertex[9];//���
	CFace Face[7];//���
	double H[9][5];//������ξ���
private:
	void ClearH();//������ξ�������
};

#endif // !defined(AFX_CUBE_H__94DB34D3_98C9_4C95_BBE5_CAF5BFEC50FC__INCLUDED_)
