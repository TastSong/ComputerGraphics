// InputDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "InputDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputDlg dialog


CInputDlg::CInputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInputDlg)
	m_x0 = 2;
	m_y0 = 3;
	m_x1 = 38;
	m_y1 = 27;
	//}}AFX_DATA_INIT
}


void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg)
	DDX_Text(pDX, IDC_EDIT1, m_x0);
	DDV_MinMaxInt(pDX, m_x0, 0, 40);
	DDX_Text(pDX, IDC_EDIT2, m_y0);
	DDV_MinMaxInt(pDX, m_y0, 0, 30);
	DDX_Text(pDX, IDC_EDIT3, m_x1);
	DDV_MinMaxInt(pDX, m_x1, 0, 40);
	DDX_Text(pDX, IDC_EDIT4, m_y1);
	DDV_MinMaxInt(pDX, m_y1, 0, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDlg)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg message handlers

void CInputDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	GetDlgItem(IDC_EDIT3)->SetFocus();
	((CEdit *)GetDlgItem(IDC_EDIT3))->SetSel(0,-1);
}
