// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_)
#define AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Rectangle.h"//包含矩形类

class CTestView : public CView
{
public:
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument();

// Operations
public:
	int TestS(CRectangle,CRectangle);//测试矩形之间是否发生碰撞
	int TestB(CRectangle,double,double);//测试矩形与边界是否发生碰撞
	void HitS(CRectangle &,CRectangle &,int);//计算矩形碰撞之后的速度
	void HitB(CRectangle &,int);//计算矩形与边界碰撞之后的速度
	void DoubleBuffer();//双缓冲
	void DrawScene(CDC*);//绘制场景	
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
	CRectangle *pRect[6];//矩形指针数组
	bool Play;//动画控制开关
	COLORREF RGB[6];
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMenuPlay();
	afx_msg void OnUpdateMenuPlay(CCmdUI* pCmdUI);
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

#endif // !defined(AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_)
