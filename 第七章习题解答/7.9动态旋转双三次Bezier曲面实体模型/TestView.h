// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"//包含三维坐标点类

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
	void ReadPoint();//读入特征多边形的顶点
	void Project(CP3 S[][4],CP2 D[][4]);//将目标三维点变换为二维点
	void DrawCtrP1(CDC* pDC);//从左到右的画控制多边形
	void DrawCtrP2(CDC* pDC);//从前到后画控制多边形
	void Line(CDC* pDC,CPoint p[]);//绘制特征多边形
	void DrawBezier(CDC* pDC);//绘制Bezier曲面
	void MultiMatrix1(double M0[][4],CP3 P0[][4],CP3 D[][4]);//矩阵相乘
	void MultiMatrix2(CP3 P0[][4],double M0[][4],CP3 D[][4]);//矩阵相乘
	void MatrixRotate(double M0[][4]);//矩阵转置
	void SignCtrPoint(CDC* pDC);//标注点
	void DoubleBuffer();//双缓冲
	void Rotate();//旋转变换
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
	CP3 P3New[4][4];//三维顶点
	CP3 P3Old[4][4];//初始的三维顶点
	CP2 P2[4][4];//二维顶点
	CP2 P2Ctr[4][4];//二维标志顶点
	BOOL Play;//动画开关
	double MT[4][4];//M的转置矩阵
	double Afa,Beta;//x方向旋转Afa,y方向旋转Beta
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnMENUBezierSurface();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateMENUBezierSurface(CCmdUI* pCmdUI);
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
