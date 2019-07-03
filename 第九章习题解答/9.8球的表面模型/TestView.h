// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi2.h"//包含二维点类
#include "Face.h"//包含面类
#include "Vector.h"//包含矢量类
#include "Fill.h"//包含填充类


class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument();
	void ReadPoint();//读入顶点坐标
	void ReadFace();//读入面坐标
	void InitParameter();//变换参数
	void PerProject(CP3);//透视投影
	void DoubleBuffer();//双缓冲
	void GlobeNorth(CDC *);//画北极
	void GlobeBodyUp(CDC *);//画球体四边形面片的上半部分
	void GlobeBodyDown(CDC *);//画球体四边形面片的下半部分
	void GlobeSouth(CDC *);//画南极
	void DrawObject(CDC *);//绘制球
	void PointColor();//计算各点的颜色 
// Operations
public:
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
	double R,Theta,Phi,d;//视点在用户坐标系中的球坐标
	double k[9];//透视变换常量
	CP3 ViewPoint;//视点球坐标位置
	CP2 ScreenP;//屏幕坐标系的二维坐标点
	CP3 *P;//球的顶点一维数组
	CFace **F;//面的二维数组
	int afa,beta,N1,N2;//球参数
	BOOL Play;//动画开关
	CFill fill;//类对象
// Generated message map functions
public:
	//{{AFX_MSG(CTestView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMENUPlay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateMENUPlay(CCmdUI* pCmdUI);
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
