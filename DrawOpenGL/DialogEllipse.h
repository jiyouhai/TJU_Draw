#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogEllipse dialog

class DialogEllipse : public CDialogEx
{
	DECLARE_DYNAMIC(DialogEllipse)

public:
	DialogEllipse(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogEllipse();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ELLIPSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDrawDoc* m_Doc = NULL;
	CMFCColorButton ellipse_color;
	afx_msg void OnClickedButtonDrawEllipse();
	afx_msg void OnClickedMfccolorbutton1();
};
