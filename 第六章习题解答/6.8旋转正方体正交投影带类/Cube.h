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

class CCube  //立方体类
{
public:
	CCube();
	virtual ~CCube();
	void SetPoint();//点表
	void SetFace();//面表
	void Multiply(CTransform matrix);//顶点的齐次矩阵乘以变换矩阵
	void VertexToHomogen();//CP3顶点数组的齐次矩阵 
	void HomogenToVertex();//齐次矩阵转换为CP3顶点数组
public:
	CP3 Vertex[9];//点表
	CFace Face[7];//面表
	double H[9][5];//点表的齐次矩阵
private:
	void ClearH();//点表的齐次矩阵清零
};

#endif // !defined(AFX_CUBE_H__94DB34D3_98C9_4C95_BBE5_CAF5BFEC50FC__INCLUDED_)
