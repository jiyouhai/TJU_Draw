// SettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "Draw.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialog)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DLG_SETTING, pParent)
	, m_nLineWidth(0)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LINE_WIDTH, m_nLineWidth);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO1, &CSettingDlg::OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CSettingDlg::OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CSettingDlg::OnRadio3)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_LINE_WIDTH, &CSettingDlg::OnChangeLineWidth)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	Invalidate();
}


void CSettingDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here
	UpdateData();
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	dc.SelectObject(&pen);

	CRect rect;
	GetDlgItem(IDM_SAMPLE)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	dc.MoveTo(rect.left + 20, rect.top + rect.Height() / 2);
	dc.LineTo(rect.right - 20, rect.top + rect.Height() / 2); // 不为绘图消息调用 CDialog::OnPaint()
}


void CSettingDlg::OnChangeLineWidth()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	Invalidate();
}
