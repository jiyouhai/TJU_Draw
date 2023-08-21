// RatioDlg.cpp: 实现文件
//

#include "pch.h"
#include "Draw.h"
#include "RatioDlg.h"
#include "afxdialogex.h"


// CRatioDlg 对话框

IMPLEMENT_DYNAMIC(CRatioDlg, CDialogEx)

CRatioDlg::CRatioDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_RATIO, pParent)
	, ratio(0)
{

}

CRatioDlg::~CRatioDlg()
{
}

void CRatioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RATIO, ratio);
}


BEGIN_MESSAGE_MAP(CRatioDlg, CDialogEx)
	ON_EN_CHANGE(IDC_RATIO, &CRatioDlg::OnEnChangeRatio)
END_MESSAGE_MAP()


// CRatioDlg 消息处理程序


void CRatioDlg::OnEnChangeRatio()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
