// DialogFill.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogFill.h"
#include "afxdialogex.h"


// DialogFill dialog

IMPLEMENT_DYNAMIC(DialogFill, CDialogEx)

DialogFill::DialogFill(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FILL, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogFill::~DialogFill()
{
	m_Doc = NULL;
}

void DialogFill::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, fill_color);
}


BEGIN_MESSAGE_MAP(DialogFill, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogFill::OnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_BUTTON_OK, &DialogFill::OnBnClickedButtonOk)
END_MESSAGE_MAP()


// DialogFill message handlers


void DialogFill::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = fill_color.GetColor();
}


void DialogFill::OnBnClickedButtonOk()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 50;
	EndDialog(0);
}
