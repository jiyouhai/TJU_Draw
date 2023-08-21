#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogRectangle dialog

class DialogRectangle : public CDialogEx
{
	DECLARE_DYNAMIC(DialogRectangle)

public:
	DialogRectangle(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogRectangle();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RECTANGLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDrawDoc* m_Doc = NULL;
	CMFCColorButton rectangle_color;
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnClickedButtonDrawRectangle();
	afx_msg void OnClickedMfccolorbutton1();
};
