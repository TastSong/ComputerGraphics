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
	void GetMaxY();//�����Ļx�������ֵ
	void GetMaxX();//�����Ļy�������ֵ
	void Cantor(int n,double ax,double ay,double bx,double by);//Cantor����
	void Koch(int n,double theta);//Koch����
	void Koch1(int n);//ѩ������1
	void Koch2(int n);//ѩ������2
	void Koch3(int n);//ѩ������3
	void Peano(int n,int s,double x1,double y1,double  x2,double y2);//Peano����
	void Gasket(int n,double x1,double y1,double x2,double y2,double x3,double y3);//Gasket��Ƭ
	void Carpet(int n,double x1,double y1,double x2,double y2);//Carpet��̺
	void CubicR(double x,double y,double d);//���ƺ��������
	void CubicT(double x,double y,double d);//���ƺ���Ķ���
	void CubicF(double x,double y,double d);//���ƺ����ǰ��
	void Sponge(int n,double x,double y,double d);//���ƺ��ຯ��
	void C(int n,double x1,double y1,double x2,double y2);//C�����ߺ���
	void Caley(int n,double x,double y,double len,double theta);//Caley����
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
	int MaxX,MaxY;//��Ļ���ֵ
	int Flag,n;
	COLORREF Color,BKColor;
	BOOL Add_Flag,Sub_Flag;//�����������ӡ��͡����١���ť״̬���Ʋ���	
protected:
	double Koch_Theta,ax,ay,bx,by,d,alpha;//koch���߲���
	double x,y,x1,y1,x2,y2,x3,y3;//Peano���߲���
	int Peano_s;
	double carpet_x1,carpet_y1,carpet_x2,carpet_y2;//Carpet���߲���
	double sponge_x,sponge_y,sponge_d;//�������
	double c_x1,c_y1,c_x2,c_y2;//C�����߲���
	double caley_th,caley_len,caley_x0,caley_y0;//Caley����		
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
