// DialogCircle.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogCircle.h"
#include "afxdialogex.h"


// DialogCircle dialog

IMPLEMENT_DYNAMIC(DialogCircle, CDialogEx)

DialogCircle::DialogCircle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CIRCLE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogCircle::~DialogCircle()
{
	m_Doc = NULL;
}

void DialogCircle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, circle_color);
}


BEGIN_MESSAGE_MAP(DialogCircle, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_CIRCLE, &DialogCircle::OnBnClickedButtonDrawCircle)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogCircle::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// DialogCircle message handlers


void DialogCircle::OnBnClickedButtonDrawCircle()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 3;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}





void DialogCircle::OnBnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = circle_color.GetColor();
}
