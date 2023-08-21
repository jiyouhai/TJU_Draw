// DialogBorderColor.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogBorderColor.h"
#include "afxdialogex.h"


// DialogBorderColor dialog

IMPLEMENT_DYNAMIC(DialogBorderColor, CDialogEx)

DialogBorderColor::DialogBorderColor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BORDER_COLOR, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogBorderColor::~DialogBorderColor()
{
	m_Doc = NULL;
}

void DialogBorderColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_newcolor);
}


BEGIN_MESSAGE_MAP(DialogBorderColor, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogBorderColor::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &DialogBorderColor::OnBnClickedButtonChange)
END_MESSAGE_MAP()


// DialogBorderColor message handlers


void DialogBorderColor::OnBnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_newcolor = m_newcolor.GetColor();
	
}


void DialogBorderColor::OnBnClickedButtonChange()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 500;

	EndDialog(0);
}
