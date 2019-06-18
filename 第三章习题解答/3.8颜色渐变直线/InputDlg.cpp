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
	cc0=RGB(255,0,0);
	cc1=RGB(0,0,255);
	//}}AFX_DATA_INIT
}


void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg)
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
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
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg message handlers

HBRUSH CInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if(pWnd->GetDlgCtrlID()==IDC_EDIT1||pWnd->GetDlgCtrlID()==IDC_EDIT2) 
	{ 			
		pDC->SetTextColor(cc0);
	} 
	if(pWnd->GetDlgCtrlID()==IDC_EDIT3||pWnd->GetDlgCtrlID()==IDC_EDIT4) 
	{ 			
		pDC->SetTextColor(cc1);
	}  	   
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Button1.SetBkColor(cc0);
	m_Button2.SetBkColor(cc1);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputDlg::OnButton1()//起点按钮 
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(cc0);
	if (dlg.DoModal()==IDOK)
	{
	   cc0=dlg.GetColor();	  
	   m_Button1.SetBkColor(cc0);
    }
	Invalidate();
}

void CInputDlg::OnButton2()//终点按钮
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg(cc1);
	if (dlg.DoModal()==IDOK)
	{
	   cc1=dlg.GetColor();	   
	   m_Button2.SetBkColor(cc1);
	}
	Invalidate();
}
