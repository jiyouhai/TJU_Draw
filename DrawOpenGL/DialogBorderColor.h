#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogBorderColor dialog

class DialogBorderColor : public CDialogEx
{
	DECLARE_DYNAMIC(DialogBorderColor)

public:
	DialogBorderColor(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogBorderColor();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BORDER_COLOR };
#endif

protected:
	CDrawDoc* m_Doc = NULL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CMFCColorButton m_newcolor;
	afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnBnClickedButtonChange();
};
