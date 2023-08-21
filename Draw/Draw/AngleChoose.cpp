// AngleChoose.cpp: 实现文件
//

#include "pch.h"
#include "Draw.h"
#include "AngleChoose.h"
#include "afxdialogex.h"


// CAngleChoose 对话框

IMPLEMENT_DYNAMIC(CAngleChoose, CDialogEx)

CAngleChoose::CAngleChoose(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAngleChoose, pParent)
	, m_nAngle(0)
{

}

CAngleChoose::~CAngleChoose()
{
}

void CAngleChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nAngle);
}


BEGIN_MESSAGE_MAP(CAngleChoose, CDialogEx)
END_MESSAGE_MAP()


// CAngleChoose 消息处理程序
