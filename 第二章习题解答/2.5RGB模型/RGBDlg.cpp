// RGBDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "RGBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRGBDlg dialog


CRGBDlg::CRGBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRGBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRGBDlg)
	m_EditRed = 255;
	m_EditGreen = 0;
	m_EditBlue = 0;
	m_Hex = _T("");
	//}}AFX_DATA_INIT	
}


void CRGBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRGBDlg)
	DDX_Control(pDX, IDC_SCROLLBARBLUE, m_ScrollBarBlue);
	DDX_Control(pDX, IDC_SCROLLBARGREEN, m_ScrollBarGreen);
	DDX_Control(pDX, IDC_SCROLLBARRED, m_ScrollBarRed);
	DDX_Text(pDX, IDC_EDITRED, m_EditRed);
	DDV_MinMaxUInt(pDX, m_EditRed, 0, 255);
	DDX_Text(pDX, IDC_EDITGREEN, m_EditGreen);
	DDV_MinMaxUInt(pDX, m_EditGreen, 0, 255);
	DDX_Text(pDX, IDC_EDITBLUE, m_EditBlue);
	DDV_MinMaxUInt(pDX, m_EditBlue, 0, 255);
	DDX_Text(pDX, IDC_EDITHEX, m_Hex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRGBDlg, CDialog)
	//{{AFX_MSG_MAP(CRGBDlg)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTONRED, OnButtonred)
	ON_BN_CLICKED(IDC_BUTTONGREEN, OnButtongreen)
	ON_BN_CLICKED(IDC_BUTTONBLUE, OnButtonblue)
	ON_BN_CLICKED(IDC_BUTTONBLACK, OnButtonblack)
	ON_BN_CLICKED(IDC_BUTTONMEGENTA, OnButtonmegenta)
	ON_BN_CLICKED(IDC_BUTTONYELLOW, OnButtonyellow)	
	ON_BN_CLICKED(IDC_BUTTONCYAN, OnButtoncyan)
	ON_BN_CLICKED(IDC_BUTTONWHITE, OnButtonwhite)
	ON_BN_CLICKED(IDC_BUTTONPALETTE, OnButtonpalette)
	ON_EN_CHANGE(IDC_EDITRED, OnChangeEditred)
	ON_EN_CHANGE(IDC_EDITGREEN, OnChangeEditgreen)
	ON_EN_CHANGE(IDC_EDITBLUE, OnChangeEditblue)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRGBDlg message handlers

BOOL CRGBDlg::OnInitDialog()//��ʼ���Ի��� 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_ScrollBarRed.SetScrollRange(0,255);//���ù������ķ�Χ0-255
	m_ScrollBarGreen.SetScrollRange(0,255);
	m_ScrollBarBlue.SetScrollRange(0,255);
	SetWindowText("RGB��ʾ[�����о���@2009]");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CRGBDlg::OnButtonred()//��ɫ��ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=0;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtongreen()//��ɫ��ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=255;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtonblue()//��ɫ��ť  
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=0;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonblack()//��ɫ��ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=0;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtonmegenta()//Ʒ�찴ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=0;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonyellow()//��ɫ��ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=255;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtoncyan()//��ɫ��ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=255;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonwhite()//��ɫ��ť 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=255;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonpalette()//��ɫ�� 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDlg(RGB(m_EditRed,m_EditGreen,m_EditBlue),CC_FULLOPEN);
	if(ColorDlg.DoModal()==IDOK)
	{
		COLORREF c=ColorDlg.GetColor();
		m_EditRed=GetRValue(c);//�����ɫ�ĺ�ɫ����
		m_EditGreen=GetGValue(c);//�����ɫ����ɫ����
		m_EditBlue=GetBValue(c);//�����ɫ����ɫ����
		ShowColor();
	}
}
void CRGBDlg::OnChangeEditred()//��ɫ�༭��  
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ScrollBarRed.SetScrollPos(m_EditRed);
	ShowColor();
}
void CRGBDlg::OnChangeEditgreen()//��ɫ�༭��  
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ScrollBarGreen.SetScrollPos(m_EditGreen);
	ShowColor();  
}
void CRGBDlg::OnChangeEditblue()//��ɫ�༭��  
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ScrollBarBlue.SetScrollPos(m_EditBlue);
	ShowColor();
}
void CRGBDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	int		OrgPos=0;//������ԭʼλ��
	CString	Flag="";//������ѡ���־	
	if(IDC_SCROLLBARRED==pScrollBar->GetDlgCtrlID())
	{
		OrgPos=m_ScrollBarRed.GetScrollPos();//��ɫ��������ֵ
		Flag="Red";
	}
	else if(IDC_SCROLLBARGREEN==pScrollBar->GetDlgCtrlID())
	{
		OrgPos=m_ScrollBarGreen.GetScrollPos();//��ɫ��������ֵ
		Flag="Green";
	}
	else if(IDC_SCROLLBARBLUE==pScrollBar->GetDlgCtrlID())
	{
		OrgPos=m_ScrollBarBlue.GetScrollPos();//��ɫ��������ֵ
		Flag="Blue";	
	}
	else
	{
		return;
	}
	switch(nSBCode)//���ݲ�ͬ�Ķ���������ͬ�Ľ��
	{
		case SB_LINELEFT://��굥�����������ͷ
			CurrentPos=OrgPos-1;break;
		case SB_LINERIGHT://��굥���������Ҽ�ͷ
			CurrentPos=OrgPos+1;break;
		case SB_PAGELEFT://��������������ͷ�м�հ״�
			CurrentPos=OrgPos-10;break;
		case SB_PAGERIGHT://������������Ҽ�ͷ�м�հ״�
			CurrentPos=OrgPos+10;break;
		case SB_THUMBTRACK://�϶�������
			CurrentPos=nPos;break;
		default:
			break;
	}
	if(CurrentPos>255)//�жϴ���255Խ��
		CurrentPos=255;
	if(CurrentPos<0)//�ж�С��0Խ��
		CurrentPos=0;
	pScrollBar->SetScrollPos(CurrentPos);//���ù�����λ��
	if(Flag=="Red")
		m_EditRed=CurrentPos;
	else if(Flag=="Green")
		m_EditGreen=CurrentPos;
	else if(Flag=="Blue")
		m_EditBlue=CurrentPos;
	ShowColor();
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CRGBDlg::ShowColor()
{
	CClientDC dc(this);
	m_ScrollBarRed.SetScrollPos(m_EditRed);
	m_ScrollBarGreen.SetScrollPos(m_EditGreen);
	m_ScrollBarBlue.SetScrollPos(m_EditBlue);
	m_Hex=RGBToHex(m_EditRed,m_EditGreen,m_EditBlue);//���ʮ������ֵ
	m_Hex.MakeUpper();
	UpdateData(FALSE);//ʵ�����ǵ���SetDlgItemText(),��m_Edit��ֵ���ֳ���
	CRect Rect=CRect(370,50,470,150);
	CBrush *NewBrush,*OldBrush;
	NewBrush=new CBrush(RGB(m_EditRed,m_EditGreen,m_EditBlue));
	OldBrush=dc.SelectObject(NewBrush);
	dc.Rectangle(Rect);
	dc.SelectObject(OldBrush);
	NewBrush->DeleteObject();
}

CString CRGBDlg::RGBToHex(UINT red,UINT green,UINT blue) 
{ 
	CString  RgbValue="#";
	char Buffer[10];
	if(red<16)
	{
		RgbValue+="0";
		RgbValue+=_itoa(red,Buffer,16);
	}
	else
		RgbValue+=_itoa(red,Buffer,16);
	if(green<16)
	{
		RgbValue+="0";
		RgbValue+=_itoa(green,Buffer,16);
	}
	else
		RgbValue+=_itoa(green,Buffer,16);
	if(blue<16)
	{
		RgbValue+="0";
		RgbValue+=_itoa(blue,Buffer,16);
	}
	else
		RgbValue+=_itoa(blue,Buffer,16);
	return RgbValue;
} 
//���޸��˱�����ֵ����ϣ���Ի���ؼ�������ʾ����Ӧ�����޸ı��������UpdateData(FALSE)��
//���ϣ��֪���û��ڶԻ����е���������ʲô����Ӧ���ڷ��ʱ���ǰ����UpdateData(TRUE)��

//������UpdateData�����𵽿���EditBox ��ʾ���ݵ����á�������UpdataData (TRUE)��ʱ�򣬳����Կؼ���Ӧ�ı���ֵ����ˢ�£�Ҳ����˵��ѿؼ��е�����ֵ������Ӧ�ı�����������UpdataData (FALSE)��ʱ�򣬳���������Ӧ������ֵ��ʾ�ڶ�Ӧ�Ŀؼ����档

void CRGBDlg::OnPaint() //�ػ洰��
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	ShowColor();
	// Do not call CDialog::OnPaint() for painting messages
}
