#if !defined(AFX_INPUTDLG_H__8014D7FC_38F6_43BC_9310_C5EACBF8B1E9__INCLUDED_)
#define AFX_INPUTDLG_H__8014D7FC_38F6_43BC_9310_C5EACBF8B1E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg.h : header file
//
#include "ColorButton.h"
/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog

class CInputDlg : public CDialog
{
// Construction
public:
	CInputDlg(CWnd* pParent = NULL);   // standard constructor
	COLORREF  cc0,cc1;//起点和终点的颜色
// Dialog Data
	//{{AFX_DATA(CInputDlg)
	enum { IDD = IDD_DIALOG1 };
	CColorButton	m_Button1;
	CColorButton	m_Button2;
	double	m_x0;
	double	m_y0;
	double	m_x1;
	double	m_y1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_H__8014D7FC_38F6_43BC_9310_C5EACBF8B1E9__INCLUDED_)
