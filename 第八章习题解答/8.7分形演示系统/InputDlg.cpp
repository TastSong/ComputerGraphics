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
	m_KochTheta = 60.0;
	m_carpetX1 = 0.0;
	m_carpetY1 = 0.0;
	m_carpetX2 = 1020.0;
	m_carpetY2 = 628.0;
	m_spongeD = 300.0;	
	m_spongeX = 250.0;
	m_spongeY = 250.0;
	m_cX1 = 300;
	m_cY1 = 150;
	m_cX2 = 720;
	m_cY2 = 150;
	m_caleyLEN =180.0;
	m_caleyTH = 90.0;
	m_color=RGB(255,255,255);
	m_peanoS = 1;
	//}}AFX_DATA_INIT
}


void CInputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputDlg)
	DDX_Control(pDX, IDC_PaintColor, m_PaintColor);
	DDX_Control(pDX, IDC_BTN_MORE, m_BtnMore);
	DDX_Control(pDX, IDC_COMBO1, m_Combo);
	DDX_Text(pDX, IDC_KOCH_EDITTH, m_KochTheta);
	DDV_MinMaxDouble(pDX, m_KochTheta, 0., 89.);
	DDX_Text(pDX, IDC_CARPET_EDITSX, m_carpetX1);
	DDX_Text(pDX, IDC_CARPET_EDITSY, m_carpetY1);
	DDX_Text(pDX, IDC_CARPET_EDITEX, m_carpetX2);
	DDX_Text(pDX, IDC_CARPET_EDITEY, m_carpetY2);
	DDX_Text(pDX, IDC_SPONGE_EDITD, m_spongeD);
	DDX_Text(pDX, IDC_SPONGE_EDITX, m_spongeX);
	DDX_Text(pDX, IDC_SPONGE_EDITY, m_spongeY);
	DDX_Text(pDX, IDC_C_EDITSX, m_cX1);
	DDX_Text(pDX, IDC_C_EDITSY, m_cY1);
	DDX_Text(pDX, IDC_C_EDITEX, m_cX2);
	DDX_Text(pDX, IDC_C_EDITEY, m_cY2);
	DDX_Text(pDX, IDC_CALEY_EDITLEN, m_caleyLEN);
	DDX_Text(pDX, IDC_CALEY_EDITTH, m_caleyTH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputDlg, CDialog)
	//{{AFX_MSG_MAP(CInputDlg)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
	ON_BN_CLICKED(IDC_PaintColor, OnPaintColor)
	ON_BN_CLICKED(IDC_PEANO_LEFT, OnPeanoLeft)
	ON_BN_CLICKED(IDC_PEANO_UP, OnPeanoUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputDlg message handlers

void CInputDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	m_Combo.SetWindowText("0");
	int i;
	switch(m_flag)
	{
	case 1://Cantor
		for(i=0;i<=10;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		m_BtnMore.EnableWindow(FALSE);
		break;
	case 2://Koch
		for(i=0;i<=8;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		GetDlgItem(IDC_KOCH_LABTH)->ShowWindow(TRUE);//¿Ø¼þ¿É¼û
		GetDlgItem(IDC_KOCH_EDITTH)->ShowWindow(TRUE);
		break;
	case 3://Snow
		for(i=0;i<=8;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		m_BtnMore.EnableWindow(FALSE);
		break;
	case 4://Peano
		for(i=0;i<=10;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		GetDlgItem(IDC_PEANO_LABWAY)->ShowWindow(TRUE);
		GetDlgItem(IDC_PEANO_UP)->ShowWindow(TRUE);
		GetDlgItem(IDC_PEANO_LEFT)->ShowWindow(TRUE);
		break;
	case 5://Gasket
		for(i=0;i<=4;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		m_BtnMore.EnableWindow(FALSE);
		break;
	case 6://Carpet
		for(i=1;i<=4;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
			m_Combo.SetWindowText("1");
		}
		GetDlgItem(IDC_CARPET_LABSX)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_LABSY)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_LABEX)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_LABEY)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_EDITSX)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_EDITSY)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_EDITEX)->ShowWindow(TRUE);
		GetDlgItem(IDC_CARPET_EDITEY)->ShowWindow(TRUE);
		break;
	case 7://Sponge
		for(i=0;i<=4;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		m_PaintColor.EnableWindow(FALSE);
		GetDlgItem(IDC_SPONGE_LABX)->ShowWindow(TRUE);
		GetDlgItem(IDC_SPONGE_LABY)->ShowWindow(TRUE);
		GetDlgItem(IDC_SPONGE_EDITX)->ShowWindow(TRUE);
		GetDlgItem(IDC_SPONGE_EDITY)->ShowWindow(TRUE);
		GetDlgItem(IDC_SPONGE_LABD)->ShowWindow(TRUE);
		GetDlgItem(IDC_SPONGE_EDITD)->ShowWindow(TRUE);
		break;
	case 8://C
		for(i=0;i<=13;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i,str);
		}
		GetDlgItem(IDC_C_LABSX)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_LABSY)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_LABEX)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_LABEY)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_EDITSX)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_EDITSY)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_EDITEX)->ShowWindow(TRUE);
		GetDlgItem(IDC_C_EDITEY)->ShowWindow(TRUE);
		break;
	case 9://Caley
		for(i=1;i<=20;i++)
		{
			CString str;
			str.Format("%d",i);
			m_Combo.InsertString(i-1,str);
			m_Combo.SetWindowText("1");
		}
		GetDlgItem(IDC_CALEY_TH)->ShowWindow(TRUE);
		GetDlgItem(IDC_CALEY_LEN)->ShowWindow(TRUE);
		GetDlgItem(IDC_CALEY_EDITTH)->ShowWindow(TRUE);
		GetDlgItem(IDC_CALEY_EDITLEN)->ShowWindow(TRUE);
		break;
	}
}

void CInputDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_n=GetDlgItemInt(IDC_COMBO1);
	CDialog::OnOK();
}

BOOL CInputDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CenterWindow();
	// TODO: Add extra initialization here
	GetWindowRect(&m_fullRect);
	m_halfRect=m_fullRect;
	CRect Rect;
	m_BtnMore.GetWindowRect(&Rect);
	m_halfRect.bottom=Rect.bottom+10;
	ToggleSize();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInputDlg::OnBtnMore() 
{
	// TODO: Add your control notification handler code here
	ToggleSize();
	if(m_flag==4)
		CheckRadioButton(IDC_PEANO_UP,IDC_PEANO_LEFT,IDC_PEANO_UP);
}
void CInputDlg::ToggleSize()
{
	CRect Rect;
	CString str;
	if(!m_bToggleSize)
	{
		str="<<&Less";
		Rect=m_fullRect;
	}
	else
	{
		str=">>&More";
		Rect=m_halfRect;
	}
	SetWindowPos(NULL,0,0,Rect.Width(),Rect.Height(),SWP_NOZORDER|SWP_NOMOVE);
	m_BtnMore.SetWindowText(str);
	m_bToggleSize=!m_bToggleSize;
}

void CInputDlg::OnPaintColor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog colorDlg(m_color,CC_FULLOPEN);
	if(colorDlg.DoModal()==IDOK)
	{
		m_color=colorDlg.GetColor();
	}
}
void CInputDlg::OnPeanoUp() 
{
	// TODO: Add your control notification handler code here
	m_peanoS=1;
}
void CInputDlg::OnPeanoLeft() 
{
	// TODO: Add your control notification handler code here
	m_peanoS=-1;
}


