// DialogRectangle.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogRectangle.h"
#include "afxdialogex.h"


// DialogRectangle dialog

IMPLEMENT_DYNAMIC(DialogRectangle, CDialogEx)

DialogRectangle::DialogRectangle(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RECTANGLE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogRectangle::~DialogRectangle()
{
	m_Doc = NULL;
}

void DialogRectangle::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, rectangle_color);
}


BEGIN_MESSAGE_MAP(DialogRectangle, CDialogEx)
//	ON_WM_LBUTTONDBLCLK()
ON_BN_CLICKED(IDC_BUTTON_DRAW_RECTANGLE, &DialogRectangle::OnClickedButtonDrawRectangle)
ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogRectangle::OnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// DialogRectangle message handlers


//void DialogRectangle::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	CDialogEx::OnLButtonDblClk(nFlags, point);
//}


void DialogRectangle::OnClickedButtonDrawRectangle()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 7;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}


void DialogRectangle::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = rectangle_color.GetColor();
}
