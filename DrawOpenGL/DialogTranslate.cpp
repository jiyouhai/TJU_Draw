// DialogTranslate.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogTranslate.h"
#include "afxdialogex.h"


// DialogTranslate dialog

IMPLEMENT_DYNAMIC(DialogTranslate, CDialogEx)

DialogTranslate::DialogTranslate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TRANSLATE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogTranslate::~DialogTranslate()
{
	m_Doc = NULL;
}

void DialogTranslate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogTranslate, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TRANSLATE_OK, &DialogTranslate::OnBnClickedButtonTranslateOk)
END_MESSAGE_MAP()


// DialogTranslate message handlers


void DialogTranslate::OnBnClickedButtonTranslateOk()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 101;
	
	m_Doc->rl_move = GetDlgItemInt(IDC_EDIT1);
	m_Doc->ud_move = GetDlgItemInt(IDC_EDIT2);

	EndDialog(0);
}
