#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogTriangle dialog

class DialogTriangle : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTriangle)

public:
	DialogTriangle(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogTriangle();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRIANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDrawDoc* m_Doc = NULL;
	afx_msg void OnClickedButtonRandomTriangle();
	afx_msg void OnClickedMfccolorbutton1();
	CMFCColorButton line_color;
	afx_msg void OnClickedButtonRightTriangle();
	afx_msg void OnClickedButtonIsoscelesTriangle();
	afx_msg void OnClickedButtonEquilateralTriangle();
};
