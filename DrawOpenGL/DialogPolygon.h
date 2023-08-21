#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogPolygon dialog

class DialogPolygon : public CDialogEx
{
	DECLARE_DYNAMIC(DialogPolygon)

public:
	DialogPolygon(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogPolygon();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_POLYGON };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDrawDoc* m_Doc = NULL;
	afx_msg void OnClickedMfccolorbutton1();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CMFCColorButton line_color;
	afx_msg void OnClickedButtonDrawPolygon();
};
