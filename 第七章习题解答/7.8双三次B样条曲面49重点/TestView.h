// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"//三维坐标点头文件
#define N 7//曲面顶点数


class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument();

// Operations
public:
	void Project1();//三维点变换为二维点的轴侧投影4*4
	void Project2();//三维点变换为二维点的轴侧投影7*7
	void DrawCtrP1(CDC *);//从左到右的画控制多边形
	void DrawCtrP2(CDC *);//从前到后画控制多边形
	void Line(CDC *,CPoint p[]);//绘制控制多边形
	void DrawBFace(CDC *);//绘制双3次Bezier曲面
	void MultiMatrix1(double M0[][4],CP3 P0[][4]);//矩阵M*P
	void MultiMatrix2(CP3 P0[][4],double M0[][4]);//矩阵P*M
	void KeepOriginalMatrix(CP3 Orig[][4],CP3 Dest[][4]);//保留原矩阵
	void SignCtrPoint(CDC *);//标注控制点
	void MatrixRotate(double M[][4]);//矩阵转置
	void BlockMatrix(CDC *);//矩阵分块
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CP3 P3[4][4];//矩阵的三维顶点
	CP2 P2[4][4];//二维顶点
	double M[4][4];//变换矩阵
	CP3 T[4][4];//临时矩阵
	double Mz[4][4];//M的转置矩阵	
	CP3 Ori[N][N];//控制点三维坐标
	CP2 Ori1[N][N];//控制点二维坐标
	CRect Rect;//声明矩形
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnMENUPolygon();
	afx_msg void OnMENUBSurface();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument()
   { return (CTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
