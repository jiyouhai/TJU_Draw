#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

// DialogScale dialog

class DialogScale : public CDialogEx
{
	DECLARE_DYNAMIC(DialogScale)

public:
	DialogScale(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogScale();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCALE };
#endif

protected:
	CDrawDoc* m_Doc = NULL;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonScaleOk();
private:
//	double s_rate;
public:
//	CString str;
};
