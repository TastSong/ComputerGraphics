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
	m_x0 =-400.0;
	m_y0 =-100.0;
	m_x1 =400.0;
	m_y1 =100.0;
	//}}AFX_DATA_INIT
}


void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg)
	DDX_Text(pDX, IDC_EDIT1, m_x0);
	DDV_MinMaxDouble(pDX, m_x0, -510., 510.);
	DDX_Text(pDX, IDC_EDIT2, m_y0);
	DDV_MinMaxDouble(pDX, m_y0, -314., 314.);
	DDX_Text(pDX, IDC_EDIT3, m_x1);
	DDV_MinMaxDouble(pDX, m_x1, -510., 510.);
	DDX_Text(pDX, IDC_EDIT4, m_y1);
	DDV_MinMaxDouble(pDX, m_y1, -314., 314.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg message handlers




