// ZBuffer.h: interface for the CZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
#define AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi3.h"//三维点头文件
#include "Bucket.h"//桶头文件
#include "Vector.h"

class CZBuffer  //深度缓冲类
{
public:
	CZBuffer();
	CZBuffer(CPi3 *,int);//重载构造函数
    virtual ~CZBuffer();
	void CreateBucket();//创建桶
	void CreateEdge();//边表
	void AddEt(CAET *);//合并ET表
	void EtOrder();//ET表排序
	void Gouraud(CDC *);//填充
	void InitDeepBuffer(int,int,double);//初始化深度缓存
    CRGB Interpolation(double,double,double,CRGB,CRGB);//线性插值
	void SetPoint(CPi3 *,int);
protected:
	int PNum;//顶点个数
	CPi3 *P;//顶点数组
	CAET *CurrentE,*HeadE,*Edge;//有效边表结点指针
	CBucket *CurrentB,*HeadB;//桶表结点指针
	double **ZB;
	int Width,Height;//深度缓冲大小参数
};

#endif // !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
