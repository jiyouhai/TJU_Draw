#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogTranslate dialog

class DialogTranslate : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTranslate)

public:
	DialogTranslate(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogTranslate();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TRANSLATE };
#endif

protected:
	CDrawDoc* m_Doc = NULL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTranslateOk();
};
