#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogFill dialog

class DialogFill : public CDialogEx
{
	DECLARE_DYNAMIC(DialogFill)

public:
	DialogFill(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogFill();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FILL };
#endif

protected:

	CDrawDoc* m_Doc = NULL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMFCColorButton fill_color;
	afx_msg void OnClickedMfccolorbutton1();
	afx_msg void OnBnClickedButtonOk();
};
