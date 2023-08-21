// DialogPolygon.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogPolygon.h"
#include "afxdialogex.h"


// DialogPolygon dialog

IMPLEMENT_DYNAMIC(DialogPolygon, CDialogEx)

DialogPolygon::DialogPolygon(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_POLYGON, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogPolygon::~DialogPolygon()
{
	m_Doc = NULL;
}

void DialogPolygon::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, line_color);
}


BEGIN_MESSAGE_MAP(DialogPolygon, CDialogEx)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &DialogPolygon::OnClickedMfccolorbutton1)
//	ON_WM_LBUTTONDBLCLK()
ON_BN_CLICKED(IDC_BUTTON_DRAW_POLYGON, &DialogPolygon::OnClickedButtonDrawPolygon)
END_MESSAGE_MAP()


// DialogPolygon message handlers





void DialogPolygon::OnClickedMfccolorbutton1()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_color = line_color.GetColor();
}





void DialogPolygon::OnClickedButtonDrawPolygon()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 5;
	m_Doc->m_size = GetDlgItemInt(IDC_EDIT1);
	if (m_Doc->m_size <= 0)
	{
		m_Doc->m_size = 1;
	}

	EndDialog(0);
}
