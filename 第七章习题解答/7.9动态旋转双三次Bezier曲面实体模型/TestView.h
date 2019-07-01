// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"//������ά�������

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
	void ReadPoint();//������������εĶ���
	void Project(CP3 S[][4],CP2 D[][4]);//��Ŀ����ά��任Ϊ��ά��
	void DrawCtrP1(CDC* pDC);//�����ҵĻ����ƶ����
	void DrawCtrP2(CDC* pDC);//��ǰ���󻭿��ƶ����
	void Line(CDC* pDC,CPoint p[]);//�������������
	void DrawBezier(CDC* pDC);//����Bezier����
	void MultiMatrix1(double M0[][4],CP3 P0[][4],CP3 D[][4]);//�������
	void MultiMatrix2(CP3 P0[][4],double M0[][4],CP3 D[][4]);//�������
	void MatrixRotate(double M0[][4]);//����ת��
	void SignCtrPoint(CDC* pDC);//��ע��
	void DoubleBuffer();//˫����
	void Rotate();//��ת�任
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
	CP3 P3New[4][4];//��ά����
	CP3 P3Old[4][4];//��ʼ����ά����
	CP2 P2[4][4];//��ά����
	CP2 P2Ctr[4][4];//��ά��־����
	BOOL Play;//��������
	double MT[4][4];//M��ת�þ���
	double Afa,Beta;//x������תAfa,y������תBeta
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
