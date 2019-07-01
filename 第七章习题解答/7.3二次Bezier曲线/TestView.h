// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)
// Attributes
public:
	CTestDoc* GetDocument();
	void Bezier2_curves(int P[][2],CDC*pDC);//绘制二次Bezier曲线
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
	BOOL	AbleToLeftBtn;//左键按下与否
	BOOL	AbleToMove;//鼠标移动与否
	int		Number;//当前点控制参数
	int  	P[3][2];//顶点数组
// Generated message map functions
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnMenuB();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
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
