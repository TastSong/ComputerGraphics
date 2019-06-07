#if !defined(AFX_RGBDLG_H__9AB19A3A_846E_432F_82DB_61F68C12BA0D__INCLUDED_)
#define AFX_RGBDLG_H__9AB19A3A_846E_432F_82DB_61F68C12BA0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RGBDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRGBDlg dialog

class CRGBDlg : public CDialog
{
// Construction
public:
	void  ShowColor();//显示颜色
	CString  RGBToHex(UINT,UINT,UINT);//16进制颜色
	CRGBDlg(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CRGBDlg)
	enum { IDD = IDD_DIALOG1 };
	CScrollBar	m_ScrollBarBlue;
	CScrollBar	m_ScrollBarGreen;
	CScrollBar	m_ScrollBarRed;
	UINT	m_EditRed;
	UINT	m_EditGreen;
	UINT	m_EditBlue;
	CString	m_Hex;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRGBDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		  CurrentPos;//滚动条当前位置
	// Generated message map functions
	//{{AFX_MSG(CRGBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnButtonred();
	afx_msg void OnButtongreen();
	afx_msg void OnButtonblue();
	afx_msg void OnButtonblack();
	afx_msg void OnButtonmegenta();
	afx_msg void OnButtonyellow();	
	afx_msg void OnButtoncyan();
	afx_msg void OnButtonwhite();
	afx_msg void OnButtonpalette();
	afx_msg void OnChangeEditred();
	afx_msg void OnChangeEditgreen();
	afx_msg void OnChangeEditblue();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RGBDLG_H__9AB19A3A_846E_432F_82DB_61F68C12BA0D__INCLUDED_)
