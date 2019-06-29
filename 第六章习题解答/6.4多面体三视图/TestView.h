// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Face.h"//包含面头文件

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
	void GetMaxY();//获得屏幕的最大y值函数
	void GetMaxX();//获得屏幕的最大x值函数
	void ReadPoint();//读入顶点函数
	void ReadFace();//读入面函数
	void DrawPolygon();//绘制多面体函数
	void Project(const double P3[][4],double P2[][3],const int);//斜等侧投影变换
	void MultiMatrix(double P[][4],int T[][4]);//矩阵相乘
	void Line(CDC *,CPoint p[],int num);//绘制多边形边线函数
	void ClearMatrix(int A[4][4]);//清除矩阵函数
	void DrawVView();//绘制主视图函数
	void DrawHView();//绘制俯视图函数
	void DrawWView();//绘制左视图函数
	void DrawTriView();//绘制三视图函数
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
	int MaxX,MaxY;//屏幕x和y的最大坐标
	double P3[10][4];//三维顶点
	double P2[10][3];//二维顶点
	CFace F[7];//面表
	int TV[4][4];//主视图变换矩阵
	int TH[4][4];//俯视图变换矩阵
	int TW[4][4];//左视图变换矩阵
	double Tri[10][4];//三视图变换后的矩阵
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnMENUTriView();
	afx_msg void OnUpdateMENUTriView(CCmdUI* pCmdUI);
	afx_msg void OnMENUPlygon();
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
