// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_)
#define AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Vector.h"
#include "Face.h"
#include "PTable.h"


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
	void ReadPoint(CP3,double);//读入顶点表
	void ReadFace();//读入面表
	void DoubleBuffer();//双缓冲
	void DrawObject(CDC*,int,CP3,double);//绘制物体
	void DrawCube(CDC*,CP3,double);//绘制正方体
	void Rotate();//旋转变换
    void Max_d(CP3);//移动视点和立方体的最大距离
	void SortCube(CP3 *pt);//立方体排序
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
	CP3 MoveView;//移动视点坐标
	CP3 Viewvector;//移动视矢量
	int a,b,c;//标识最远的立方体
	PTable ptable[3][3][3];
	CP3 POld[8],PNew[9];//点表
	CFace F[6];//面表
	CP2 ScreenP;//屏幕坐标系的二维坐标点
	BOOL Play;//动画开关
	int n;//递归深度
	CP3 OrignPoint;
	double CubeEdgeLength;//立方体的边长
	double Afa,Beta;//x方向旋转Afa,y方向旋转Beta
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnMENUPlay();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnUpdateMENUPlay(CCmdUI* pCmdUI);
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnUpdateButton1(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButton2(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButton3(CCmdUI* pCmdUI);
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
