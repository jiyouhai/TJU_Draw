
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "Draw.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_SHAPE_LINE, &CMainFrame::OnShapeLine)
	ON_COMMAND(ID_SHAPE_CIRCLE, &CMainFrame::OnShapeCircle)
	ON_COMMAND(ID_SHAPE_TRIANGLE, &CMainFrame::OnShapeTriangle)
	ON_COMMAND(ID_SHAPE_POLYGON, &CMainFrame::OnShapePolygon)
	ON_COMMAND(ID_SHAPE_ELLIPSE, &CMainFrame::OnShapeEllipse)
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CMainFrame::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_SQUARE, &CMainFrame::OnShapeSquare)
	ON_COMMAND(ID_BUTTON_CLEAR, &CMainFrame::OnButtonClear)
	ON_COMMAND(ID_BUTTON_MOUSE, &CMainFrame::OnButtonMouse)
	ON_COMMAND(ID_BUTTON_TRANSLATE, &CMainFrame::OnButtonTranslate)
	ON_COMMAND(ID_BUTTON_ROTATE, &CMainFrame::OnButtonRotate)
	ON_COMMAND(ID_BUTTON_SCALE, &CMainFrame::OnButtonScale)
	ON_COMMAND(ID_BUTTON_SYM_LR, &CMainFrame::OnButtonSymLr)
	ON_COMMAND(ID_BUTTON_SYM_UD, &CMainFrame::OnButtonSymUd)
	ON_COMMAND(ID_BUTTON_FILL, &CMainFrame::OnButtonFill)
	ON_COMMAND(ID_TRANSFORM_ROTATE, &CMainFrame::OnTransformRotate)
	ON_COMMAND(ID_TRANSFORM_SCALE, &CMainFrame::OnTransformScale)
	ON_COMMAND(ID_TRANSFORM_TRANLATE, &CMainFrame::OnTransformTranlate)
	ON_COMMAND(ID_CHANGEBORDERCOLOR_CHANGEBORDERCOLOR, &CMainFrame::OnChangebordercolorChangebordercolor)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers



void CMainFrame::OnShapeLine()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogLine dlg;
	dlg.DoModal();
}


void CMainFrame::OnShapeCircle()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogCircle dlg;
	dlg.DoModal();
}


void CMainFrame::OnShapeTriangle()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogTriangle dlg;
	dlg.DoModal();
}




void CMainFrame::OnShapePolygon()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogPolygon dlg;
	dlg.DoModal();
}


void CMainFrame::OnShapeEllipse()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogEllipse dlg;
	dlg.DoModal();
}


void CMainFrame::OnShapeRectangle()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogRectangle dlg;
	dlg.DoModal();
}


void CMainFrame::OnShapeSquare()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogSquare dlg;
	dlg.DoModal();
}


void CMainFrame::OnButtonClear()
{
	// TODO: Add your command handler code here
	if (!m_Doc)
		m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->v_line.clear();
	m_Doc->v_circle.clear();
	m_Doc->v_ellipse.clear();
	m_Doc->v_polygon.clear();
	((CDrawView*)GetActiveView())->Invalidate(TRUE);
	m_Doc->selected_point = -1;
	m_Doc->selected_line = -1;
	m_Doc->selected_circle = -1;
	m_Doc->selected_ellipse = -1;
	m_Doc->selected_polygon = -1;
}


void CMainFrame::OnButtonMouse()
{
	// TODO: Add your command handler code here
	if (!m_Doc)
		m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_type = 0;
	m_Doc->m_color = RGB(0, 0, 0);
	m_Doc->is_d_polygon = FALSE;
}


void CMainFrame::OnButtonTranslate()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_type = 100;
}


void CMainFrame::OnButtonRotate()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_type = 200;
}


void CMainFrame::OnButtonScale()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_type = 300;
}


void CMainFrame::OnButtonSymLr()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_type = 401;
}


void CMainFrame::OnButtonSymUd()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_type = 402;
}


void CMainFrame::OnButtonFill()
{
	// TODO: Add your command handler code here
	if (!m_Doc)
		m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogFill dlg;
	dlg.DoModal();
}


void CMainFrame::OnTransformRotate()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogRotate dlg;
	dlg.DoModal();
}


void CMainFrame::OnTransformScale()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogScale dlg;
	dlg.DoModal();
}


void CMainFrame::OnTransformTranlate()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogTranslate dlg;
	dlg.DoModal();
}


void CMainFrame::OnChangebordercolorChangebordercolor()
{
	// TODO: Add your command handler code here
	if (!m_Doc) m_Doc = (CDrawDoc*)((CDrawView*)GetActiveView())->GetDocument();

	m_Doc->m_color = RGB(0, 0, 0);
	DialogBorderColor dlg;
	dlg.DoModal();
}
