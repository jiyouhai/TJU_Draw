// DialogLine.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogLine.h"
#include "afxdialogex.h"


// DialogLine dialog

IMPLEMENT_DYNAMIC(DialogLine, CDialogEx)

DialogLine::DialogLine(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LINE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogLine::~DialogLine()
{
	m_Doc = NULL;
}

void DialogLine::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, line_color);
}


BEGIN_MESSAGE_MAP(DialogLine, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogLine::OnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_LINE, &DialogLine::OnClickedButtonDrawLine)
END_MESSAGE_MAP()


// DialogLine message handlers


void DialogLine::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = line_color.GetColor();
}


void DialogLine::OnClickedButtonDrawLine()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 2;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}
