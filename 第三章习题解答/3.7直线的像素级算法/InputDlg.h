#if !defined(AFX_INPUTDLG_H__C3D2E7F5_F5A4_4822_A78B_7EA0347A2611__INCLUDED_)
#define AFX_INPUTDLG_H__C3D2E7F5_F5A4_4822_A78B_7EA0347A2611__INCLUDED_

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
	int		m_x0;
	int		m_y0;
	int		m_x1;
	int		m_y1;
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
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTDLG_H__C3D2E7F5_F5A4_4822_A78B_7EA0347A2611__INCLUDED_)
