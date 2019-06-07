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

BOOL CRGBDlg::OnInitDialog()//初始化对话框 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_ScrollBarRed.SetScrollRange(0,255);//设置滚动条的范围0-255
	m_ScrollBarGreen.SetScrollRange(0,255);
	m_ScrollBarBlue.SetScrollRange(0,255);
	SetWindowText("RGB演示[博创研究所@2009]");	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CRGBDlg::OnButtonred()//红色按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=0;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtongreen()//绿色按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=255;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtonblue()//蓝色按钮  
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=0;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonblack()//黑色按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=0;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtonmegenta()//品红按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=0;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonyellow()//黄色按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=255;
	m_EditBlue=0;
	ShowColor();
}
void CRGBDlg::OnButtoncyan()//青色按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=0;
	m_EditGreen=255;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonwhite()//白色按钮 
{
	// TODO: Add your control notification handler code here
	m_EditRed=255;
	m_EditGreen=255;
	m_EditBlue=255;
	ShowColor();
}
void CRGBDlg::OnButtonpalette()//调色板 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDlg(RGB(m_EditRed,m_EditGreen,m_EditBlue),CC_FULLOPEN);
	if(ColorDlg.DoModal()==IDOK)
	{
		COLORREF c=ColorDlg.GetColor();
		m_EditRed=GetRValue(c);//获得颜色的红色分量
		m_EditGreen=GetGValue(c);//获得颜色的绿色分量
		m_EditBlue=GetBValue(c);//获得颜色的蓝色分量
		ShowColor();
	}
}
void CRGBDlg::OnChangeEditred()//红色编辑框  
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
void CRGBDlg::OnChangeEditgreen()//绿色编辑框  
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
void CRGBDlg::OnChangeEditblue()//蓝色编辑框  
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
	int		OrgPos=0;//滚动块原始位置
	CString	Flag="";//滚动条选择标志	
	if(IDC_SCROLLBARRED==pScrollBar->GetDlgCtrlID())
	{
		OrgPos=m_ScrollBarRed.GetScrollPos();//红色滚动条的值
		Flag="Red";
	}
	else if(IDC_SCROLLBARGREEN==pScrollBar->GetDlgCtrlID())
	{
		OrgPos=m_ScrollBarGreen.GetScrollPos();//绿色滚动条的值
		Flag="Green";
	}
	else if(IDC_SCROLLBARBLUE==pScrollBar->GetDlgCtrlID())
	{
		OrgPos=m_ScrollBarBlue.GetScrollPos();//蓝色滚动条的值
		Flag="Blue";	
	}
	else
	{
		return;
	}
	switch(nSBCode)//根据不同的动作产生不同的结果
	{
		case SB_LINELEFT://鼠标单击滚动条左箭头
			CurrentPos=OrgPos-1;break;
		case SB_LINERIGHT://鼠标单击滚动条右箭头
			CurrentPos=OrgPos+1;break;
		case SB_PAGELEFT://单击滚动块和左箭头中间空白处
			CurrentPos=OrgPos-10;break;
		case SB_PAGERIGHT://单击滚动块和右箭头中间空白处
			CurrentPos=OrgPos+10;break;
		case SB_THUMBTRACK://拖动滚动块
			CurrentPos=nPos;break;
		default:
			break;
	}
	if(CurrentPos>255)//判断大于255越界
		CurrentPos=255;
	if(CurrentPos<0)//判断小于0越界
		CurrentPos=0;
	pScrollBar->SetScrollPos(CurrentPos);//设置滚动块位置
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
	m_Hex=RGBToHex(m_EditRed,m_EditGreen,m_EditBlue);//输出十六进制值
	m_Hex.MakeUpper();
	UpdateData(FALSE);//实质上是调用SetDlgItemText(),把m_Edit的值表现出来
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
//当修改了变量的值，而希望对话框控件更新显示，就应该在修改变量后调用UpdateData(FALSE)；
//如果希望知道用户在对话框中到底输入了什么，就应该在访问变量前调用UpdateData(TRUE)。

//在这里UpdateData函数起到控制EditBox 显示内容的作用。当调用UpdataData (TRUE)的时候，程序会对控件对应的变量值进行刷新，也就是说会把控件中的输入值赋给对应的变量。而调用UpdataData (FALSE)的时候，程序则会把相应变量的值显示在对应的控件上面。

void CRGBDlg::OnPaint() //重绘窗口
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	ShowColor();
	// Do not call CDialog::OnPaint() for painting messages
}
