// DialogEllipse.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogEllipse.h"
#include "afxdialogex.h"


// DialogEllipse dialog

IMPLEMENT_DYNAMIC(DialogEllipse, CDialogEx)

DialogEllipse::DialogEllipse(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ELLIPSE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogEllipse::~DialogEllipse()
{
	m_Doc = NULL;
}

void DialogEllipse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, ellipse_color);
}


BEGIN_MESSAGE_MAP(DialogEllipse, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_ELLIPSE, &DialogEllipse::OnClickedButtonDrawEllipse)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogEllipse::OnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// DialogEllipse message handlers


void DialogEllipse::OnClickedButtonDrawEllipse()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 6;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}


void DialogEllipse::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = ellipse_color.GetColor();
}
