// TestView.h : interface of the CTestView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_)
#define AFX_TESTVIEW_H__A75FDCFB_621C_4E38_A154_C344803E6372__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"//��ά�����ͷ�ļ�
#define N 7//���涥����


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
	void Project1();//��ά��任Ϊ��ά������ͶӰ4*4
	void Project2();//��ά��任Ϊ��ά������ͶӰ7*7
	void DrawCtrP1(CDC *);//�����ҵĻ����ƶ����
	void DrawCtrP2(CDC *);//��ǰ���󻭿��ƶ����
	void Line(CDC *,CPoint p[]);//���ƿ��ƶ����
	void DrawBFace(CDC *);//����˫3��Bezier����
	void MultiMatrix1(double M0[][4],CP3 P0[][4]);//����M*P
	void MultiMatrix2(CP3 P0[][4],double M0[][4]);//����P*M
	void KeepOriginalMatrix(CP3 Orig[][4],CP3 Dest[][4]);//����ԭ����
	void SignCtrPoint(CDC *);//��ע���Ƶ�
	void MatrixRotate(double M[][4]);//����ת��
	void BlockMatrix(CDC *);//����ֿ�
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
	CP3 P3[4][4];//�������ά����
	CP2 P2[4][4];//��ά����
	double M[4][4];//�任����
	CP3 T[4][4];//��ʱ����
	double Mz[4][4];//M��ת�þ���	
	CP3 Ori[N][N];//���Ƶ���ά����
	CP2 Ori1[N][N];//���Ƶ��ά����
	CRect Rect;//��������
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
