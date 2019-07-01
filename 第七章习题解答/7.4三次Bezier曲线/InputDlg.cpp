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
// InputDlg dialog


InputDlg::InputDlg(CWnd* pParent /*=NULL*/)
	: CDialog(InputDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(InputDlg)
	m_x0 = 40.0;
	m_y0 = 40.0;
	m_x1 = 500.0;
	m_y1 = 300.0;
	//}}AFX_DATA_INIT
}


void InputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InputDlg)
	DDX_Text(pDX, IDC_EDIT1, m_x0);
	DDX_Text(pDX, IDC_EDIT2, m_y0);
	DDX_Text(pDX, IDC_EDIT3, m_x1);
	DDX_Text(pDX, IDC_EDIT4, m_y1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InputDlg, CDialog)
	//{{AFX_MSG_MAP(InputDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InputDlg message handlers
