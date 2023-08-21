#pragma once


// DialogSquare dialog

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"


class DialogSquare : public CDialogEx
{
	DECLARE_DYNAMIC(DialogSquare)

public:
	DialogSquare(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogSquare();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SQUARE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDrawDoc* m_Doc = NULL;
	CMFCColorButton square_color;
	afx_msg void OnClickedMfccolorbutton1();
	afx_msg void OnClickedButtonDrawSquare();
};
