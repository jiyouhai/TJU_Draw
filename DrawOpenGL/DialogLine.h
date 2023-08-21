#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogLine dialog

class DialogLine : public CDialogEx
{
	DECLARE_DYNAMIC(DialogLine)

public:
	DialogLine(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogLine();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LINE };
#endif

protected:
	CDrawDoc* m_Doc = NULL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedMfccolorbutton1();
	afx_msg void OnClickedButtonDrawLine();
	CMFCColorButton line_color;
};
