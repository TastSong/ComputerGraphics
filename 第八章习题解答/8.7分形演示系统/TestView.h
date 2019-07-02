// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_)
#define AFX_TESTVIEW_H__7B09737C_A6B6_4402_B2B8_087738721CF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InputDlg.h"

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
	void GetMaxY();//获得屏幕x方向最大值
	void GetMaxX();//获得屏幕y方向最大值
	void Cantor(int n,double ax,double ay,double bx,double by);//Cantor函数
	void Koch(int n,double theta);//Koch函数
	void Koch1(int n);//雪花函数1
	void Koch2(int n);//雪花函数2
	void Koch3(int n);//雪花函数3
	void Peano(int n,int s,double x1,double y1,double  x2,double y2);//Peano曲线
	void Gasket(int n,double x1,double y1,double x2,double y2,double x3,double y3);//Gasket垫片
	void Carpet(int n,double x1,double y1,double x2,double y2);//Carpet地毯
	void CubicR(double x,double y,double d);//绘制海绵的右面
	void CubicT(double x,double y,double d);//绘制海绵的顶面
	void CubicF(double x,double y,double d);//绘制海绵的前面
	void Sponge(int n,double x,double y,double d);//绘制海绵函数
	void C(int n,double x1,double y1,double x2,double y2);//C字曲线函数
	void Caley(int n,double x,double y,double len,double theta);//Caley函数
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
	int MaxX,MaxY;//屏幕最大值
	int Flag,n;
	COLORREF Color,BKColor;
	BOOL Add_Flag,Sub_Flag;//工具条“增加”和“减少”按钮状态控制参数	
protected:
	double Koch_Theta,ax,ay,bx,by,d,alpha;//koch曲线参数
	double x,y,x1,y1,x2,y2,x3,y3;//Peano曲线参数
	int Peano_s;
	double carpet_x1,carpet_y1,carpet_x2,carpet_y2;//Carpet曲线参数
	double sponge_x,sponge_y,sponge_d;//海绵参数
	double c_x1,c_y1,c_x2,c_y2;//C字曲线参数
	double caley_th,caley_len,caley_x0,caley_y0;//Caley参数		
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnMenuCantor();
	afx_msg void OnMenuKoch();
	afx_msg void OnUpdateBtnAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnSub(CCmdUI* pCmdUI);
	afx_msg void OnBtnAdd();
	afx_msg void OnBtnSub();
	afx_msg void OnMenuKochsnow();
	afx_msg void OnMenuPeano();
	afx_msg void OnMenuGasket();
	afx_msg void OnMenuCarpet();
	afx_msg void OnMenuC();
	afx_msg void OnMenuCaley();
	afx_msg void OnMenuSponge();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
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
