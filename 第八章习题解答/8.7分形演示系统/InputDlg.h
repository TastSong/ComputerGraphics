#if !defined(AFX_INPUTDLG_H__87B4AD82_19E0_41D0_9700_A6963B003AAD__INCLUDED_)
#define AFX_INPUTDLG_H__87B4AD82_19E0_41D0_9700_A6963B003AAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog

class CInputDlg : public CDialog
{
// Construction
public:
	CInputDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInputDlg)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_PaintColor;
	CButton	m_BtnMore;
	CComboBox	m_Combo;
	double	m_KochTheta;
	double	m_carpetX1;
	double	m_carpetY1;
	double	m_carpetX2;
	double	m_carpetY2;
	double	m_spongeD;
	double	m_spongeX;
	double	m_spongeY;
	long	m_cX1;
	long	m_cY1;
	long	m_cX2;
	long	m_cY2;
	double	m_caleyLEN;
	double	m_caleyTH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CRect m_fullRect;
	CRect m_halfRect;
	BOOL  m_bToggleSize;
	
	// Generated message map functions
	//{{AFX_MSG(CInputDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMore();
	afx_msg void OnPaintColor();
	afx_msg void OnPeanoLeft();
	afx_msg void OnPeanoUp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void ToggleSize();
	int m_flag;
	COLORREF m_color;
	int m_n;
	int m_peanoS;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_H__87B4AD82_19E0_41D0_9700_A6963B003AAD__INCLUDED_)
