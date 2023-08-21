
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "DrawDoc.h"
#include "DrawView.h"
#include "DialogLine.h"
#include "DialogCircle.h"
#include "DialogTriangle.h"
#include "DialogPolygon.h"
#include "DialogEllipse.h"
#include "DialogRectangle.h"
#include "DialogSquare.h"
#include "DialogFill.h"
#include "DialogRotate.h"
#include "DialogScale.h"
#include "DialogTranslate.h"
#include "DialogBorderColor.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;


	CMFCToolBar m_toolsToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	CDrawDoc* m_Doc = NULL;
	afx_msg void OnShapeLine();
	afx_msg void OnShapeCircle();
	afx_msg void OnShapeTriangle();
	afx_msg void OnShapePolygon();
	afx_msg void OnShapeEllipse();
	afx_msg void OnShapeRectangle();
	afx_msg void OnShapeSquare();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonMouse();
	afx_msg void OnButtonTranslate();
	afx_msg void OnButtonRotate();
	afx_msg void OnButtonScale();
	afx_msg void OnButtonSymLr();
	afx_msg void OnButtonSymUd();
	afx_msg void OnButtonFill();
	afx_msg void OnTransformRotate();
	afx_msg void OnTransformScale();
	afx_msg void OnTransformTranlate();
	afx_msg void OnChangebordercolorChangebordercolor();
};


