#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogCircle dialog

class DialogCircle : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCircle)

public:
	DialogCircle(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogCircle();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CIRCLE };
#endif

protected:
	CDrawDoc* m_Doc = NULL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CMFCColorButton circle_color;
	afx_msg void OnBnClickedButtonDrawCircle();
	afx_msg void OnBnClickedMfccolorbutton1();
};
