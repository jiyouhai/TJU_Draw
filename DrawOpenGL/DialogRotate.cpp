// DialogRotate.cpp : implementation file
//

#include "pch.h"
#include "Draw.h"
#include "DialogRotate.h"
#include "afxdialogex.h"


// DialogRotate dialog

IMPLEMENT_DYNAMIC(DialogRotate, CDialogEx)

DialogRotate::DialogRotate(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ROTATE, pParent)
{
	m_Doc = (CDrawDoc*)((CDrawView*)((CMainFrame*)AfxGetApp()->GetMainWnd())->GetActiveView())->GetDocument();
}

DialogRotate::~DialogRotate()
{
	m_Doc = NULL;
}

void DialogRotate::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DialogRotate, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &DialogRotate::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_ROTATE_OK, &DialogRotate::OnBnClickedButtonRotateOk)
END_MESSAGE_MAP()


// DialogRotate message handlers


void DialogRotate::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}





void DialogRotate::OnBnClickedButtonRotateOk()
{
	// TODO: Add your control notification handler code here
	m_Doc->m_type = 201;
	m_Doc->r_angle = GetDlgItemInt(IDC_EDIT1);

	EndDialog(0);
}
