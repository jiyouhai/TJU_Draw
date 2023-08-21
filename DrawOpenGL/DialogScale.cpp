// DialogScale.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogScale.h"
#include "afxdialogex.h"


// DialogScale dialog

IMPLEMENT_DYNAMIC(DialogScale, CDialogEx)

DialogScale::DialogScale(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SCALE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogScale::~DialogScale()
{
	m_Doc = NULL;
}

void DialogScale::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, s_rate);
	//  DDX_Text(pDX, IDC_EDIT1, str);
}


BEGIN_MESSAGE_MAP(DialogScale, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SCALE_OK, &DialogScale::OnBnClickedButtonScaleOk)
END_MESSAGE_MAP()


// DialogScale message handlers


void DialogScale::OnBnClickedButtonScaleOk()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 301; 
	CString str;
	GetDlgItemText(IDC_EDIT1, str);


	m_Doc->s_rate = _wtof(str.GetBuffer());

	EndDialog(0);
}
