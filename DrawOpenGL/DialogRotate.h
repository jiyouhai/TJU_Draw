#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogRotate dialog

class DialogRotate : public CDialogEx
{
	DECLARE_DYNAMIC(DialogRotate)

public:
	DialogRotate(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogRotate();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ROTATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CDrawDoc* m_Doc = NULL;

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnEnChangeEdit1();

	afx_msg void OnBnClickedButtonRotateOk();
};
