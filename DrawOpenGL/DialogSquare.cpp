// DialogSquare.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogSquare.h"
#include "afxdialogex.h"


// DialogSquare dialog

IMPLEMENT_DYNAMIC(DialogSquare, CDialogEx)

DialogSquare::DialogSquare(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SQUARE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogSquare::~DialogSquare()
{
	m_Doc = NULL;
}

void DialogSquare::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, square_color);
}


BEGIN_MESSAGE_MAP(DialogSquare, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogSquare::OnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_SQUARE, &DialogSquare::OnClickedButtonDrawSquare)
END_MESSAGE_MAP()


// DialogSquare message handlers


void DialogSquare::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = square_color.GetColor();
}


void DialogSquare::OnClickedButtonDrawSquare()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 8;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}
