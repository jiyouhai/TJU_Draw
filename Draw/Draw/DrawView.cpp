
// DrawView.cpp: CDrawView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "SettingDlg.h"
#include "Graphic.h"
#include "math.h"
#include<cmath>

#ifdef _DEBUG
#define Trans(p1, rect) CPoint(long((p1.x+0.5)/1) - rect.Width()/2, long((p1.y+0.5)/1) - rect.Height()/2)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "AngleChoose.h"



// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(IDM_DOT, &CDrawView::OnDot)
	ON_COMMAND(IDM_LINE, &CDrawView::OnLine)
	ON_COMMAND(IDM_RECTANGLE, &CDrawView::OnRectangle)
	ON_COMMAND(IDM_ELLIPSE, &CDrawView::OnEllipse)
	ON_COMMAND(IDM_TRIANGLE, &CDrawView::OnTriangle)
	ON_COMMAND(IDM_MOVE, &CDrawView::OnMove)
	ON_COMMAND(IDM_ROTATE, &CDrawView::OnRotate)
	ON_COMMAND(IDM_SETTING, &CDrawView::OnSetting)
	ON_COMMAND(IDM_COLOR, &CDrawView::OnColor)
	ON_COMMAND(IDM_FILL, &CDrawView::OnFill)
	ON_COMMAND(IDM_LCOLOR, &CDrawView::OnLcolor)
	ON_COMMAND(IDM_FONT, &CDrawView::OnFont)
	ON_COMMAND(IDM_CLEAR, &CDrawView::OnClear)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_PAINT()
	ON_COMMAND(IDM_ISO, &CDrawView::OnIso)
	ON_COMMAND(IDM_EQUAL, &CDrawView::OnEqual)
	ON_COMMAND(IDM_SETTINGANGLE, &CDrawView::OnSettingangle)
	ON_COMMAND(IDM_GUDINGROTATE, &CDrawView::OnGudingrotate)
	ON_COMMAND(IDM_SQUARE, &CDrawView::OnSquare)
	ON_COMMAND(IDM_CIRCLE, &CDrawView::OnCircle)
	ON_COMMAND(IDM_RIGHT, &CDrawView::OnRight)
	ON_COMMAND(IDM_RIGHT, &CDrawView::OnRight)
	ON_COMMAND(IDM_SQUARE, &CDrawView::OnSquare)
	ON_COMMAND(IDM_CIRCLE, &CDrawView::OnCircle)
END_MESSAGE_MAP()

// CDrawView 构造/析构

CDrawView::CDrawView() noexcept
{
	// TODO: 在此处添加构造代码
	m_nDrawType = 0;//赋初值
	m_ptOrigin = 0;
	m_nLineWidth = 0;
	m_nLineStyle = 0;
	m_clr = RGB(0, 0, 0);
	m_clr2 = RGB(0, 0, 0);
	m_bDraw = FALSE;
	m_ptOld = 0;
	m_ptOld2 = 0;
	m_ptEnd = 0;
	m_strFontName = "";
	m_circle = FALSE;
	m_click = 0;
	m_reDraw = FALSE;
	m_isSelect = FALSE;
	m_SelectOrigin = FALSE;
	m_SelectOld = FALSE;
	m_SelectOrigin2 = FALSE;
	m_SelectEnd2 = FALSE;
	m_SelectTop = FALSE;
	m_SelectBottom = FALSE;
	m_SelectLeft = FALSE;
	m_SelectRight = FALSE;
	m_SelectRatio = FALSE;
	m_ratio = 0;
	vector = 0;
	flag = FALSE;
	m_xForm.eM11 = (float)1.0;
	m_xForm.eM12 = (float)0;
	m_xForm.eM21 = (float)0;
	m_xForm.eM22 = (float)1.0;
	m_xForm.eDx = (float)0;
	m_xForm.eDy = (float)0;
	m_clr3 = m_clr;
	m_isSpin = FALSE;
	m_isRedraw = FALSE;
	m_nAngle = 0;

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDrawView 绘图

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;

	CPoint v1(6, 6);// 圆的半径为6个像素

	CFont* pOldFont = pDC->SelectObject(&m_font);
	pDC->TextOut(0, 0, m_strFontName);
	pDC->SelectObject(pOldFont);

	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//选择画刷
	pDC->SelectObject(pBrush);

	for (int i = 0; i < m_ptrArray.GetSize(); i++)//重绘
	{
		CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//画刷
		pDC->SelectObject(pBrush);
		CPen pen(((CGraphic*)m_ptrArray.GetAt(i))->m_nLineStyle,//画笔
			((CGraphic*)m_ptrArray.GetAt(i))->m_nLineWidth,
			((CGraphic*)m_ptrArray.GetAt(i))->m_clr);
		pDC->SelectObject(&pen);

		CRect rc(((CGraphic*)m_ptrArray.GetAt(i))->point1.x - 6,//设置要判定的矩形区域
			((CGraphic*)m_ptrArray.GetAt(i))->point1.y - 6,
			((CGraphic*)m_ptrArray.GetAt(i))->point2.x + 6,
			((CGraphic*)m_ptrArray.GetAt(i))->point2.y + 6);
		rc.NormalizeRect();//标准化矩形区域

		//九个定位小正方形的判定区域的设定
		CRect rc1(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point1, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point1, rect) + v1));
		CRect rc2(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point2, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point2, rect) + v1));
		CRect rc3(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point3, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point3, rect) + v1));
		CRect rc4(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point4, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point4, rect) + v1));
		CRect rc5(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point5, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point5, rect) + v1));
		CRect rc6(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point6, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point6, rect) + v1));
		CRect rc7(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point7, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point7, rect) + v1));
		CRect rc8(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point8, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point8, rect) + v1));
		CRect rc9(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point9, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(i))->point9, rect) + v1));
		//设置三角形判定区域的外围多边形
		CRgn rgn;
		CPoint ptVertex[8];
		ptVertex[0].x = ((CGraphic*)m_ptrArray.GetAt(i))->point4.x - 6;
		ptVertex[0].y = ((CGraphic*)m_ptrArray.GetAt(i))->point4.y - 6;
		ptVertex[1].x = ((CGraphic*)m_ptrArray.GetAt(i))->point4.x + 6;
		ptVertex[1].y = ((CGraphic*)m_ptrArray.GetAt(i))->point4.y - 6;
		ptVertex[2].x = ((CGraphic*)m_ptrArray.GetAt(i))->point6.x + 6;
		ptVertex[2].y = ((CGraphic*)m_ptrArray.GetAt(i))->point6.y - 6;
		ptVertex[3].x = ((CGraphic*)m_ptrArray.GetAt(i))->point6.x + 6;
		ptVertex[3].y = ((CGraphic*)m_ptrArray.GetAt(i))->point6.y + 6;
		ptVertex[4].x = ((CGraphic*)m_ptrArray.GetAt(i))->point6.x - 6;
		ptVertex[4].y = ((CGraphic*)m_ptrArray.GetAt(i))->point6.y + 6;
		ptVertex[5].x = ((CGraphic*)m_ptrArray.GetAt(i))->point5.x + 6;
		ptVertex[5].y = ((CGraphic*)m_ptrArray.GetAt(i))->point5.y + 6;
		ptVertex[6].x = ((CGraphic*)m_ptrArray.GetAt(i))->point5.x - 6;
		ptVertex[6].y = ((CGraphic*)m_ptrArray.GetAt(i))->point5.y + 6;
		ptVertex[7].x = ((CGraphic*)m_ptrArray.GetAt(i))->point5.x - 6;
		ptVertex[7].y = ((CGraphic*)m_ptrArray.GetAt(i))->point5.y - 6;
		rgn.CreatePolygonRgn(ptVertex, 8, ALTERNATE);

		//判定是否点击在矩形区域或多边形区域中
		BOOL flag1 = rc.PtInRect(m_ptMove1);
		BOOL flag2 = rgn.PtInRegion(m_ptMove1);
		//旋转坐标系
		SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
		SetWorldTransform(pDC->m_hDC, &((CGraphic*)m_ptrArray.GetAt(i))->m_xForm);
		SetGraphicsMode(pDC->m_hDC, GM_COMPATIBLE);
		//重绘每一个图形
		switch (((CGraphic*)m_ptrArray.GetAt(i))->m_nDrawType)
		{
		case 2:
			pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point1);
			pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point2);
			break;
		case 3:
			pDC->Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(i))->point1, ((CGraphic*)m_ptrArray.GetAt(i))->point2));
			break;
		case 4:
			pDC->Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(i))->point1, ((CGraphic*)m_ptrArray.GetAt(i))->point2));
			break;
			//case 5:
		case 6:
			pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point4);
			pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point5);
			pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point4);
			pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point6);
			pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point5);
			pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point6);
			break;
		case 7:
			CBrush pBrush(((CGraphic*)m_ptrArray.GetAt(i))->m_clr2);
			pDC->SelectObject(&pBrush);
			//if(!m_isMove)
			//{
			pDC->ExtFloodFill((((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor).x,
				(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor).y,
				pDC->GetPixel(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor), FLOODFILLSURFACE);
			//}
			//else
			//{
			//	pDC->ExtFloodFill(m_ptMiddle.x,m_ptMiddle.y,pDC->GetPixel(m_ptMiddle),FLOODFILLSURFACE);
			//}
			break;
		}

		if (!m_isRedraw)//判断是否已发生一次重绘
		{
			if (m_reDraw == TRUE)
			{
				CClientDC dc(this);
				CBrush Brush(RGB(0, 0, 0));//设置黑色画刷
				if (((CGraphic*)m_ptrArray.GetAt(i))->m_nDrawType != 6)//填充判定矩形和多边形
					pDC->FillRect(&rc, &Brush);
				else
					pDC->FillRgn(&rgn, &Brush);

				if (m_pixelColor != dc.GetPixel(m_ptMove1))//按顺序重绘到点击的图形颜色是否改变
				{
					num = i;//获得点击的图形			
					m_reDraw = FALSE;
					m_isSelect = TRUE;
					CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
					pDC->SelectObject(pBrush);
					CBrush Brush(RGB(255, 255, 255));//复原画刷
					if (((CGraphic*)m_ptrArray.GetAt(i))->m_nDrawType != 6)//填充判定矩形和多边形
					{
						pDC->FillRect(&rc, &Brush);
					}
					else
						pDC->FillRgn(&rgn, &Brush);
				}
				else//未点击到任何图形
				{
					num = 0;
					m_isSelect = FALSE;
					CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
					pDC->SelectObject(pBrush);
					CBrush Brush(RGB(255, 255, 255));//复原画刷
					if (((CGraphic*)m_ptrArray.GetAt(i))->m_nDrawType != 6)//填充判定矩形和多边形
					{
						pDC->FillRect(&rc, &Brush);
					}
					else
						pDC->FillRgn(&rgn, &Brush);
				}
			}
			switch (((CGraphic*)m_ptrArray.GetAt(i))->m_nDrawType)//重新绘制图形线条
			{
			case 2:
				pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point1);
				pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point2);
				break;
			case 3:
				pDC->Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(i))->point1, ((CGraphic*)m_ptrArray.GetAt(i))->point2));
				break;
			case 4:
				pDC->Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(i))->point1, ((CGraphic*)m_ptrArray.GetAt(i))->point2));
				break;
				//case 5:
			case 6:
				pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point4);
				pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point5);
				pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point4);
				pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point6);
				pDC->MoveTo(((CGraphic*)m_ptrArray.GetAt(i))->point5);
				pDC->LineTo(((CGraphic*)m_ptrArray.GetAt(i))->point6);
				break;
			case 7:
				CBrush pBrush(((CGraphic*)m_ptrArray.GetAt(i))->m_clr2);
				pDC->SelectObject(&pBrush);
				//if(!m_isMove)
				//{
				pDC->ExtFloodFill((((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor).x,
					(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor).y,
					pDC->GetPixel(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor), FLOODFILLSURFACE);
				//}
				//else
				//{
				//	pDC->ExtFloodFill(m_ptMiddle.x,m_ptMiddle.y,pDC->GetPixel(m_ptMiddle),FLOODFILLSURFACE);
				//}
				break;
			}
		}

	}

	// TODO: 在此处为本机数据添加绘制代码
}

// CDrawView 打印

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}
void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}
void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDrawView 诊断

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView 消息处理程序


void CDrawView::OnDot()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 1;
}
void CDrawView::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 2;
}
void CDrawView::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 3;
}
void CDrawView::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 4;
}

void CDrawView::OnCircle()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 32;
}

void CDrawView::OnTriangle()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 6;
}

void CDrawView::OnMove()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 8;
	m_isMove = TRUE;
}
void CDrawView::OnRotate()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 9;
}
void CDrawView::OnSetting()
{
	// TODO: 在此添加命令处理程序代码
	CSettingDlg dlg;
	dlg.m_nLineWidth = m_nLineWidth;
	dlg.m_nLineStyle = m_nLineStyle;
	dlg.m_clr = m_clr;
	if (IDOK == dlg.DoModal())
	{
		m_nLineWidth = dlg.m_nLineWidth;
		m_nLineStyle = dlg.m_nLineStyle;
	};
}
void CDrawView::OnColor()
{
	// TODO: 在此添加命令处理程序代码
	CColorDialog dlg;
	dlg.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg.m_cc.rgbResult = m_clr;
	if (IDOK == dlg.DoModal())
	{
		m_clr = dlg.m_cc.rgbResult;
	}
}
void CDrawView::OnFill()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 7;
	CColorDialog dlg2;//填充色颜色选择对话框
	dlg2.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg2.m_cc.rgbResult = m_clr2;
	if (IDOK == dlg2.DoModal())
	{
		m_clr2 = dlg2.m_cc.rgbResult;
	}
}
void CDrawView::OnLcolor()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 10;
	CColorDialog dlg3;
	dlg3.m_cc.Flags |= CC_RGBINIT | CC_FULLOPEN;
	dlg3.m_cc.rgbResult = m_clr3;
	if (IDOK == dlg3.DoModal())
	{
		m_clr3 = dlg3.m_cc.rgbResult;
	}
}
void CDrawView::OnFont()
{
	// TODO: 在此添加命令处理程序代码
	CFontDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		if (m_font.m_hObject)
			m_font.DeleteObject();
		m_font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		m_strFontName = dlg.m_cf.lpLogFont->lfFaceName;
		Invalidate();
	}
}
void CDrawView::OnClear()
{
	// TODO: 在此添加命令处理程序代码
	//for (int i = 0; i < m_ptrArray.GetSize(); i++)
	//{
	//	delete((CGraphic*)m_ptrArray.GetAt(i));
	//}
	//RedrawWindow();
}
void CDrawView::OnIso()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 15;
}
void CDrawView::OnEqual()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 16;
}
void CDrawView::OnSettingangle()
{
	// TODO: 在此添加命令处理程序代码
	CAngleChoose clg;
	clg.m_nAngle = m_nAngle;
	if (IDOK == clg.DoModal())
	{
		m_nAngle = clg.m_nAngle;
	}

}
void CDrawView::OnGudingrotate()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 20;
}

void CDrawView::OnRight()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 33;
}


void CDrawView::OnSquare()
{
	// TODO: 在此添加命令处理程序代码
	m_nDrawType = 31;
}






void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);//画笔
	dc.SelectObject(pen);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//画刷
	dc.SelectObject(pBrush);
	//::SetCursor(::LoadCursor(NULL,IDC_CROSS));
	if (m_click % 3 == 0)//绘制三角形的准备工作
	{
		m_ptOrigin = m_ptOld = point;
		m_bDraw = TRUE;
	}
	else if (m_click % 3 == 1)//绘制三角形的第三个点并将一三、二三点连线
	{
		m_ptOld2 = point;
		m_bDraw = TRUE;
		m_click++;

		dc.SetROP2(R2_NOTXORPEN);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptOld2);
		dc.MoveTo(m_ptEnd);
		dc.LineTo(m_ptOld2);
	}
	if (m_nDrawType == 2 || m_nDrawType == 3 || m_nDrawType == 4 || m_nDrawType == 6|| m_nDrawType == 21|| m_nDrawType ==22|| m_nDrawType ==23 )//旋转后绘制图形时判断条件更改
		m_isSpin = FALSE;

	if (m_nDrawType == 8 || m_nDrawType == 9 ||m_nDrawType==20)
	{
		if (m_nDrawType == 9 || m_nDrawType==20)//点击旋转后设置判断条件
			m_isSpin = TRUE;

		m_ptMove1 = point;
		m_ptMove3 = point;
		m_pixelColor = dc.GetPixel(m_ptMove1);//保存点下的点的颜色
		m_reDraw = TRUE;

		RedrawWindow();
		m_isRedraw = TRUE;
		RedrawWindow();//防止重叠时互相覆盖
		m_isRedraw = FALSE;

		CRect rect;
		CPoint v1(6, 6);

		SetGraphicsMode(dc.m_hDC, GM_ADVANCED);//更改坐标系
		SetWorldTransform(dc.m_hDC, &((CGraphic*)m_ptrArray.GetAt(num))->m_xForm);
		SetGraphicsMode(dc.m_hDC, GM_COMPATIBLE);

		if (((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 == 0)//若选中图形尚未旋转
			m_isSpin = FALSE;
		else
			m_isSpin = TRUE;
		//图形边界上九个小正方形的判定区域设定
		CRect rc1(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1));
		CRect rc2(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1));
		CRect rc3(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1));
		CRect rc4(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1));
		CRect rc5(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1));
		CRect rc6(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1));
		CRect rc7(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1));
		CRect rc8(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1));
		CRect rc9(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
			CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1));
		if (m_isSelect)
		{
			switch (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType)
			{
			case 2://点击图形选中时直线端点小正方形的绘制
				dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
					CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
				dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
					CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
				break;
			case 3://点击图形选中时矩形边界小正方形的绘制
				if (m_isSpin)
				{
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
				}
				else
				{
					RectLocation(rect);
					m_ptScale = ((CGraphic*)m_ptrArray.GetAt(num))->point1;//记录未移动时原始点位置
					m_ptScale2 = ((CGraphic*)m_ptrArray.GetAt(num))->point2;
				}
				//RotateDC(dc.m_hDC,90,((CGraphic*)m_ptrArray.GetAt(num))->point1);
				break;
			case 4://点击图形选中时椭圆边界小正方形的绘制
				if (m_isSpin)
				{
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
				}
				else
				{
					RectLocation(rect);
					m_ptScale = ((CGraphic*)m_ptrArray.GetAt(num))->point1;//记录未移动时原始点位置
					m_ptScale2 = ((CGraphic*)m_ptrArray.GetAt(num))->point2;
				}
				break;
			case 6://点击图形选中时三角形边界小正方形的绘制
				if (m_isSpin)
				{
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
				}
				else
				{
					TriangleLocation(rect);
					m_ptScale = ((CGraphic*)m_ptrArray.GetAt(num))->point4;//记录未移动时原始点位置
					m_ptScale2 = ((CGraphic*)m_ptrArray.GetAt(num))->point5;
					m_ptSpin = ((CGraphic*)m_ptrArray.GetAt(num))->point6;
				}
				break;
			}
			//判断是否点击在九个定位小正方形内
			flag = (rc1.PtInRect(m_ptMove1) || rc2.PtInRect(m_ptMove1) || rc3.PtInRect(m_ptMove1)
				|| rc4.PtInRect(m_ptMove1) || rc5.PtInRect(m_ptMove1) || rc6.PtInRect(m_ptMove1)
				|| rc7.PtInRect(m_ptMove1) || rc8.PtInRect(m_ptMove1) || rc9.PtInRect(m_ptMove1));
			if (flag)
			{
				//m_isSelect=TRUE;
				if (m_ratio == 0)//确定按比例放大缩小的比例
				{
					m_ratio = abs((((CGraphic*)m_ptrArray.GetAt(num))->point2.x - ((CGraphic*)m_ptrArray.GetAt(num))->point1.x) /
						(((CGraphic*)m_ptrArray.GetAt(num))->point2.y - ((CGraphic*)m_ptrArray.GetAt(num))->point1.y));
				}
				if (rc1.PtInRect(m_ptMove1))
					m_SelectOrigin = TRUE;
				if (rc2.PtInRect(m_ptMove1))
					m_SelectOld = TRUE;
				if (rc3.PtInRect(m_ptMove1))
					m_SelectOld2 = TRUE;
				if (rc4.PtInRect(m_ptMove1))
				{
					m_SelectOrigin2 = TRUE;//点击三角形顶点小正方形
					if (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 6)
					{
						//dc.SetROP2(R2_NOTXORPEN);
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point4);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point5);
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point4);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point6);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
						dc.SetROP2(R2_MASKPEN);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
					}
				}
				if (rc5.PtInRect(m_ptMove1))
				{
					m_SelectEnd2 = TRUE;//点击三角形顶点小正方形
					if (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 6)
					{
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point5);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point4);
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point5);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point6);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
						dc.SetROP2(R2_MASKPEN);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
					}
				}
				if (rc6.PtInRect(m_ptMove1))
				{
					m_SelectTop = TRUE;//点击三角形顶点小正方形
					if (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 6)
					{
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point6);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point4);
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point6);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point5);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
						dc.SetROP2(R2_MASKPEN);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					}
				}
				if (rc7.PtInRect(m_ptMove1))
					m_SelectBottom = TRUE;
				if (rc8.PtInRect(m_ptMove1))
					m_SelectLeft = TRUE;
				if (rc9.PtInRect(m_ptMove1))
					m_SelectRight = TRUE;
			}
		}
	}
	if (m_nDrawType == 10)//改变边框颜色
	{
		m_ptMove1 = point;
		m_pixelColor = dc.GetPixel(m_ptMove1);
		m_reDraw = TRUE;
		RedrawWindow();
	}
	CView::OnLButtonDown(nFlags, point);
}

CPoint m_ptOrigin2, m_ptEnd2, m_ptLeft, m_ptRight, m_ptTop, m_ptBottom;//矩形边界上八个点
CPoint m_ptMid1, m_ptMid2, m_ptMid3;//三角形三边中点

void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int sgn1, sgn2;
	LONG ptWid, ptLen;
	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);
	dc.SelectObject(pen);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.SelectObject(pBrush);
	m_bDraw = FALSE;
	CBrush pBrush2(m_clr2);

	m_ptEnd2.y = m_ptTop.y = m_ptOrigin.y;//矩形边界上的八个点的关系
	m_ptEnd2.x = m_ptRight.x = m_ptOld.x;
	m_ptOrigin2.x = m_ptLeft.x = m_ptOrigin.x;
	m_ptOrigin2.y = m_ptBottom.y = m_ptOld.y;
	m_ptTop.x = (m_ptOrigin.x + m_ptEnd2.x) / 2;
	m_ptBottom.x = (m_ptOrigin2.x + m_ptOld.x) / 2;
	m_ptLeft.y = (m_ptOrigin2.y + m_ptOrigin.y) / 2;
	m_ptRight.y = (m_ptEnd2.y + m_ptOld.y) / 2;
	m_ptMid1.x = (m_ptOrigin.x + m_ptEnd.x) / 2;//三角形边界上六个点的关系
	m_ptMid1.y = (m_ptOrigin.y + m_ptEnd.y) / 2;
	m_ptMid2.x = (m_ptOrigin.x + m_ptOld2.x) / 2;
	m_ptMid2.y = (m_ptOrigin.y + m_ptOld2.y) / 2;
	m_ptMid3.x = (m_ptEnd.x + m_ptOld2.x) / 2;
	m_ptMid3.y = (m_ptEnd.y + m_ptOld2.y) / 2;

	CPoint v1(6, 6);
	CRect rect;

	switch (m_nDrawType)
	{
	case 15:
		dc.SetROP2(R2_NOTXORPEN);
		dc.SetROP2(R2_MASKPEN);
		{
			CRect dengyao = CRect(m_ptOrigin, point);
			CPoint pointd1, pointd2, pointding;
			pointd1.x = dengyao.right;
			pointd1.y = dengyao.bottom;
			pointd2.x = dengyao.left;
			pointd2.y = dengyao.bottom;
			pointding.x = dengyao.left + (dengyao.right - dengyao.left) * 0.5;
			pointding.y = dengyao.top;
			dc.MoveTo(pointd1);
			dc.LineTo(pointding);
			dc.MoveTo(pointd2);
			dc.LineTo(pointd1);
			dc.MoveTo(pointding);
			dc.LineTo(pointd2);
		}
		break;
	case 16:
		dc.SetROP2(R2_NOTXORPEN);
		dc.SetROP2(R2_MASKPEN);
		{
			point.y = point.x - m_ptOrigin.x + m_ptOrigin.y;
			CRect dengbian = CRect(m_ptOrigin, point);
			CPoint pointd1, pointd2, pointding;
			pointd1.x = dengbian.right;
			pointd1.y = dengbian.bottom;
			pointd2.x = dengbian.left;
			pointd2.y = dengbian.bottom;
			pointding.x = dengbian.left + (dengbian.right - dengbian.left) * 0.5;
			pointding.y = dengbian.bottom + (dengbian.top - dengbian.bottom) * 0.86602;
			dc.MoveTo(pointd1);
			dc.LineTo(pointding);
			dc.MoveTo(pointd2);
			dc.LineTo(pointd1);
			dc.MoveTo(pointding);
			dc.LineTo(pointd2);
		}
		break;
	case 1://绘制点
		dc.SetPixel(point, m_clr);
		break;
	case 2://绘制直线
		dc.SetROP2(R2_NOTXORPEN);
		dc.SetROP2(R2_MASKPEN);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		{//保存所绘制的图形及其参数，下同
			CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptOrigin, m_ptOld, NULL, NULL, NULL,
				NULL, NULL, NULL, NULL,
				m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
			m_ptrArray.Add(cgraphic);
		}
		break;
	case 3://绘制矩形、正方形
		dc.SetROP2(R2_NOTXORPEN);
		dc.SetROP2(R2_MASKPEN);
		if (m_circle == TRUE)//绘制正方形
		{
			m_ptOld.y = m_ptOld.x - m_ptOrigin.x + m_ptOrigin.y;
			dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
			point.y = point.x - m_ptOrigin.x + m_ptOrigin.y;
			dc.Rectangle(CRect(m_ptOrigin, point));
			m_circle = FALSE;
		}
		else//绘制矩形
		{
			dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
			dc.Rectangle(CRect(m_ptOrigin, point));
		}

		{
			CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptOrigin, m_ptOld, m_ptOld2, m_ptOrigin2, m_ptEnd2,
				m_ptTop, m_ptBottom, m_ptLeft, m_ptRight,
				m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
			m_ptrArray.Add(cgraphic);
		}
		break;
	case 4://绘制椭圆、圆
		dc.SetROP2(R2_NOTXORPEN);
		dc.SetROP2(R2_MASKPEN);
			dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
			dc.Ellipse(CRect(m_ptOrigin, point));

		{
			CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptOrigin, m_ptOld, m_ptOld2, m_ptOrigin2, m_ptEnd2,
				m_ptTop, m_ptBottom, m_ptLeft, m_ptRight,
				m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
			m_ptrArray.Add(cgraphic);
		}
		break;
	case 6://绘制三角形
		if (m_click % 3 == 2)//绘制第一三、二三点的连线
		{
			dc.SetROP2(R2_NOTXORPEN);
			dc.SetROP2(R2_MASKPEN);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOld2);
			dc.MoveTo(m_ptEnd);
			dc.LineTo(m_ptOld2);
			m_click++;

			{
				CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptMid1, m_ptMid2, m_ptMid3, m_ptOrigin, m_ptOld,
					m_ptOld2, NULL, NULL, NULL,
					m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
				m_ptrArray.Add(cgraphic);
			}
		}
		else if (m_click % 3 == 0)//绘制前两点连成的直线，即三角形的第一条边
		{
			m_ptEnd = point;
			dc.SetROP2(R2_NOTXORPEN);
			dc.SetROP2(R2_MASKPEN);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOld);
			m_click++;
		}
		break;
	case 31:
		ptWid = point.x - m_ptOrigin.x;
		ptLen = point.y - m_ptOrigin.y;
		sgn1 = ptWid / abs(ptWid);
		sgn2 = ptLen / abs(ptLen);
		if (abs(ptWid) >= abs(ptLen));
		else
			ptLen = ptWid;
		point.x = m_ptOrigin.x + (sgn1 * abs(ptLen));
		point.y = m_ptOrigin.y + (sgn2 * abs(ptLen));
		dc.Rectangle(CRect(m_ptOrigin, point));
		{
			CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptOrigin, m_ptOld, m_ptOld2, m_ptOrigin2, m_ptEnd2,
				m_ptTop, m_ptBottom, m_ptLeft, m_ptRight,
				m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
			m_ptrArray.Add(cgraphic);
		}
		break;
	case 32:
		ptLen = long(sqrt((point.x - m_ptOrigin.x) * (point.x - m_ptOrigin.x) + (point.y - m_ptOrigin.y) * (point.y - m_ptOrigin.y)));
		point.x = m_ptOrigin.x + ptLen;
		point.y = m_ptOrigin.y - ptLen;
		m_ptOrigin.x = m_ptOrigin.x - ptLen;
		m_ptOrigin.y = m_ptOrigin.y + ptLen;
		dc.Ellipse(CRect(m_ptOrigin, point));
		{
			CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptOrigin, m_ptOld, m_ptOld2, m_ptOrigin2, m_ptEnd2,
				m_ptTop, m_ptBottom, m_ptLeft, m_ptRight,
				m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
			m_ptrArray.Add(cgraphic);
		}
		break;
	case 33:
		m_ptMid1.y = m_ptOrigin.y;
		m_ptOrigin.y = point.y;
		m_ptMid1.x = m_ptOrigin.x;
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(m_ptMid1);
		dc.MoveTo(m_ptMid1);
		dc.LineTo(point);
		break;

	case 7:
		dc.SelectObject(&pBrush2);//填充色设定
		dc.ExtFloodFill(point.x, point.y, dc.GetPixel(point), FLOODFILLSURFACE);
		m_ptColor = point;
		{
			CGraphic* cgraphic = new CGraphic(m_nDrawType, m_ptOrigin, m_ptOld, m_ptOld2, m_ptOrigin2, m_ptEnd2,
				m_ptTop, m_ptBottom, m_ptLeft, m_ptRight,
				m_ptColor, m_clr, m_clr2, m_nLineStyle, m_nLineWidth, m_xForm);
			m_ptrArray.Add(cgraphic);
		}
		break;
	case 8:
		if (m_isSelect)
		{
			if (m_isSpin)//旋转之后
			{
				RedrawWindow();
				SetGraphicsMode(dc.m_hDC, GM_ADVANCED);//更改坐标系
				SetWorldTransform(dc.m_hDC, &((CGraphic*)m_ptrArray.GetAt(num))->m_xForm);
				SetGraphicsMode(dc.m_hDC, GM_COMPATIBLE);
				//m_isSpin=FALSE;
			}
			{
				vector = point - m_ptMove1;
				CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
				dc.SelectObject(pBrush);
			}
			switch (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType)
			{
			case 2://绘制直线的端点小正方形
				//dc.SetROP2(R2_NOTXORPEN);
				dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
					CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
				dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
					CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
				break;
			case 3:
				if (m_isSpin)//点击旋转后绘制矩形的边界小正方形
				{
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
				}
				else
				{
					CClientDC dc(this);
					CRect rc(m_ptScale.x - 6, m_ptScale.y - 6, m_ptScale2.x + 6, m_ptScale2.y + 6);
					CBrush Brush(RGB(0, 0, 0));
					dc.FillRect(&rc, &Brush);//黑色画刷填充
					for (int i = num; i < m_ptrArray.GetSize(); i++)//找出所选图形填充色保存位置
					{
						if (dc.GetPixel(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor) == RGB(0, 0, 0))
						{
							((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor += (point - m_ptMove3);
							//移动填充点，使得移动填充后的图形不会改变填充色涂色位置
						}
					}
					dc.SetROP2(R2_NOTXORPEN);//绘制矩形及其边界小正方形
					dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
						((CGraphic*)m_ptrArray.GetAt(num))->point2));
					RectLocation(rect);
					dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1 + vector,
						((CGraphic*)m_ptrArray.GetAt(num))->point2 + vector));
					MoveRect();
					RectRelation();
					RectLocation(rect);
					dc.SetROP2(R2_MASKPEN);
					dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
						((CGraphic*)m_ptrArray.GetAt(num))->point2));
					//if(((CGraphic*)m_ptrArray.GetAt(num))->m_clr2!=RGB(0,0,0))
					RedrawWindow();
				}
				if (m_SelectOrigin == TRUE)
				{
					//flag=FALSE;
					m_SelectOrigin = FALSE;
				}
				if (m_SelectOld == TRUE)
					m_SelectOld = FALSE;
				if (m_SelectOrigin2 == TRUE)
					m_SelectOrigin2 = FALSE;
				if (m_SelectEnd2 == TRUE)
					m_SelectEnd2 = FALSE;
				if (m_SelectTop == TRUE)
					m_SelectTop = FALSE;
				if (m_SelectBottom == TRUE)
					m_SelectBottom = FALSE;
				if (m_SelectLeft == TRUE)
					m_SelectLeft = FALSE;
				if (m_SelectRight == TRUE)
					m_SelectRight = FALSE;
				break;
			case 4:
				if (m_isSpin)//点击旋转后绘制椭圆的边界小正方形
				{
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
				}
				else
				{
					CClientDC dc(this);
					CRect rc(m_ptScale.x - 6, m_ptScale.y - 6, m_ptScale2.x + 6, m_ptScale2.y + 6);
					CBrush Brush(RGB(0, 0, 0));//黑色画刷填充
					CBrush* oldbrush;
					oldbrush = dc.SelectObject(&Brush);
					dc.Ellipse(rc);
					dc.SelectObject(oldbrush);
					for (int i = num; i < m_ptrArray.GetSize(); i++)//找出所选图形填充色保存位置
					{
						if (dc.GetPixel(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor) == RGB(0, 0, 0))
						{
							((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor += (point - m_ptMove3);
							//移动填充点，使得移动填充后的图形不会改变填充色涂色位置
						}
					}
					dc.SetROP2(R2_NOTXORPEN);//绘制椭圆及其边界小正方形
					dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
						((CGraphic*)m_ptrArray.GetAt(num))->point2));
					RectLocation(rect);
					dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1 + vector,
						((CGraphic*)m_ptrArray.GetAt(num))->point2 + vector));
					MoveRect();
					RectLocation(rect);
					dc.SetROP2(R2_MASKPEN);
					dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
						((CGraphic*)m_ptrArray.GetAt(num))->point2));
					RedrawWindow();
				}
				if (m_SelectOrigin == TRUE)
					m_SelectOrigin = FALSE;
				if (m_SelectOld == TRUE)
					m_SelectOld = FALSE;
				if (m_SelectOrigin2 == TRUE)
					m_SelectOrigin2 = FALSE;
				if (m_SelectEnd2 == TRUE)
					m_SelectEnd2 = FALSE;
				if (m_SelectTop == TRUE)
					m_SelectTop = FALSE;
				if (m_SelectBottom == TRUE)
					m_SelectBottom = FALSE;
				if (m_SelectLeft == TRUE)
					m_SelectLeft = FALSE;
				if (m_SelectRight == TRUE)
					m_SelectRight = FALSE;
				break;
				//case 5:
			case 6:
				if (m_isSpin)//点击旋转后绘制三角形的边界小正方形
				{
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
					dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
						CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
				}
				else
				{
					CClientDC dc(this);
					CRgn rgn;
					CPoint ptVertex[8];
					ptVertex[0].x = m_ptScale.x - 6;
					ptVertex[0].y = m_ptScale.y - 6;
					ptVertex[1].x = m_ptScale.x + 6;
					ptVertex[1].y = m_ptScale.y - 6;
					ptVertex[2].x = m_ptSpin.x + 6;
					ptVertex[2].y = m_ptSpin.y - 6;
					ptVertex[3].x = m_ptSpin.x + 6;
					ptVertex[3].y = m_ptSpin.y + 6;
					ptVertex[4].x = m_ptSpin.x - 6;
					ptVertex[4].y = m_ptSpin.y + 6;
					ptVertex[5].x = m_ptScale2.x + 6;
					ptVertex[5].y = m_ptScale2.y + 6;
					ptVertex[6].x = m_ptScale2.x - 6;
					ptVertex[6].y = m_ptScale2.y + 6;
					ptVertex[7].x = m_ptScale2.x - 6;
					ptVertex[7].y = m_ptScale2.y - 6;
					rgn.CreatePolygonRgn(ptVertex, 8, ALTERNATE);
					CBrush Brush(RGB(0, 0, 0));//黑色画刷填充
					dc.FillRgn(&rgn, &Brush);
					for (int i = num; i < m_ptrArray.GetSize(); i++)//找出所选图形填充色保存位置
					{
						if (dc.GetPixel(((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor) == RGB(0, 0, 0))
						{
							((CGraphic*)m_ptrArray.GetAt(i))->m_ptColor += (point - m_ptMove3);
							//移动填充点，使得移动填充后的图形不会改变填充色涂色位置
						}
					}
					RedrawWindow();
				}
				if (m_SelectOrigin2 == TRUE)
					m_SelectOrigin2 = FALSE;
				if (m_SelectEnd2 == TRUE)
					m_SelectEnd2 = FALSE;
				if (m_SelectTop == TRUE)
					m_SelectTop = FALSE;
				break;
			case 7://填充色
				CBrush pBrush(((CGraphic*)m_ptrArray.GetAt(num))->m_clr2);
				dc.SelectObject(&pBrush);
				if (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 3 ||
					((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 4)
				{
					m_ptMiddle.x = (((CGraphic*)m_ptrArray.GetAt(num))->point1.x +
						((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2 + vector.x;
					m_ptMiddle.y = (((CGraphic*)m_ptrArray.GetAt(num))->point1.y +
						((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2 + vector.y;
					dc.ExtFloodFill(m_ptMiddle.x, m_ptMiddle.y, dc.GetPixel(m_ptMiddle), FLOODFILLSURFACE);
				}
				break;
			}
			{
				CBrush pBrush2(((CGraphic*)m_ptrArray.GetAt(num))->m_clr2);
			}
		}
		break;

	case 10:
		if (m_isSelect)//改变选中图形的边框颜色
		{
			((CGraphic*)m_ptrArray.GetAt(num))->m_clr = m_clr3;
			RedrawWindow();
		}
		break;
	case 9://旋转
		if (m_isSelect)
		{
			m_ptMiddle.x = (((CGraphic*)m_ptrArray.GetAt(num))->point1.x +//旋转中心
				((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2;
			m_ptMiddle.y = (((CGraphic*)m_ptrArray.GetAt(num))->point1.y +
				((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2;
			//点下去的始点到鼠标弹起的终点及旋转中心三点构成的三角形的三边长
			double a = sqrt(double((point.x - m_ptMiddle.x) * (point.x - m_ptMiddle.x) + (point.y - m_ptMiddle.y) * (point.y - m_ptMiddle.y)));
			double b = sqrt(double((m_ptMove1.x - m_ptMiddle.x) * (m_ptMove1.x - m_ptMiddle.x) + (m_ptMove1.y - m_ptMiddle.y) * (m_ptMove1.y - m_ptMiddle.y)));
			//double c=double ((point.x-m_ptMiddle.x)*(m_ptMove1.x-m_ptMiddle.x)+(point.y-m_ptMiddle.y)*(m_ptMove1.y-m_ptMiddle.y));
			//double theta=acos(c/(a*b));
			double c = sqrt(double((m_ptMove1.x - point.x) * (m_ptMove1.x - point.x) + (m_ptMove1.y - point.y) * (m_ptMove1.y - point.y)));
			//余弦定理计算旋转角度
			double theta = acos((a * a + b * b - c * c) / (2 * a * b));
			//坐标系旋转参数设定
			m_xForm.eM11 = float(cos(theta));
			m_xForm.eM12 = float(sin(theta));
			m_xForm.eM21 = float(-sin(theta));
			m_xForm.eM22 = float(cos(theta));
			m_xForm.eDx = float(m_ptMiddle.x - cos(theta) * m_ptMiddle.x + sin(theta) * m_ptMiddle.y);
			m_xForm.eDy = float(m_ptMiddle.y - cos(theta) * m_ptMiddle.y - sin(theta) * m_ptMiddle.x);
			//保存坐标系旋转更改
			float a1, b1, c1, d1, e1, f1;
			a1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
				+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
			b1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
				+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
			c1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
				+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
			d1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
				+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
			e1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
				+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21
				+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx;
			f1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
				+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22
				+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11 = a1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 = b1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21 = c1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22 = d1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx = e1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy = f1;
			RedrawWindow();
		}
		break;
	case 20:
		if (m_isSelect)
		{
			m_ptMiddle.x = (((CGraphic*)m_ptrArray.GetAt(num))->point1.x +//旋转中心
				((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2;
			m_ptMiddle.y = (((CGraphic*)m_ptrArray.GetAt(num))->point1.y +
				((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2;
			//点下去的始点到鼠标弹起的终点及旋转中心三点构成的三角形的三边长
			double theta = double(m_nAngle) *0.00556 * 3.14;
			//坐标系旋转参数设定
			m_xForm.eM11 = float(cos(theta));
			m_xForm.eM12 = float(sin(theta));
			m_xForm.eM21 = float(-sin(theta));
			m_xForm.eM22 = float(cos(theta));
			m_xForm.eDx = float(m_ptMiddle.x - cos(theta) * m_ptMiddle.x + sin(theta) * m_ptMiddle.y);
			m_xForm.eDy = float(m_ptMiddle.y - cos(theta) * m_ptMiddle.y - sin(theta) * m_ptMiddle.x);
			//保存坐标系旋转更改
			float a1, b1, c1, d1, e1, f1;
			a1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
				+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
			b1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
				+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
			c1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
				+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
			d1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
				+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
			e1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
				+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21
				+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx;
			f1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
				+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22
				+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11 = a1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 = b1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21 = c1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22 = d1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx = e1;
			((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy = f1;
			RedrawWindow();
		}
		break;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int sgn1, sgn2;
	LONG ptWid, ptLen;
	CClientDC dc(this);
	CPen pen(m_nLineStyle, m_nLineWidth, m_clr);//画笔
	dc.SelectObject(&pen);
	CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));//画刷
	dc.SelectObject(pBrush);
	m_ptMove2 = m_ptMove1;
	if (m_bDraw == TRUE)
	{
		switch (m_nDrawType)
		{
		case 1://绘制点
			dc.SetPixel(point, m_clr);
			break;
		case 2://绘制直线
			dc.SetROP2(R2_NOTXORPEN);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOld);
			m_ptOld = point;

			dc.SetROP2(R2_NOTXORPEN);
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(m_ptOld);
			break;
		case 3://绘制矩形、正方形
			dc.SetROP2(R2_NOTXORPEN);
			if (m_circle == TRUE)//绘制正方形
			{
				m_ptOld.y = m_ptOld.x - m_ptOrigin.x + m_ptOrigin.y;
				dc.Rectangle(CRect(m_ptOrigin, m_ptOld));

				point.y = point.x - m_ptOrigin.x + m_ptOrigin.y;
				dc.Rectangle(CRect(m_ptOrigin, point));
				m_ptOld = point;
			}
			else//绘制矩形
			{
				dc.Rectangle(CRect(m_ptOrigin, m_ptOld));
				dc.Rectangle(CRect(m_ptOrigin, point));
				m_ptOld = point;
			}

			break;
		case 4://绘制椭圆、圆
			dc.SetROP2(R2_NOTXORPEN);
			if (m_circle == true)//绘制圆
			{
				ptLen = long(sqrt((m_ptOld.x - m_ptOrigin.x) * (m_ptOld.x - m_ptOrigin.x) + (m_ptOld.y - m_ptOrigin.y) * (m_ptOld.y - m_ptOrigin.y)));
				m_ptOld.x = m_ptOrigin.x + ptLen;
				m_ptOld.y = m_ptOrigin.y - ptLen;
				m_ptOrigin.x = m_ptOrigin.x - ptLen;
				m_ptOrigin.y = m_ptOrigin.y + ptLen;
				dc.Ellipse(CRect(m_ptOrigin, m_ptOld));

				ptLen = long(sqrt((point.x - m_ptOrigin.x) * (point.x - m_ptOrigin.x) + (point.y - m_ptOrigin.y) * (point.y - m_ptOrigin.y)));
				point.x = m_ptOrigin.x + ptLen;
				point.y = m_ptOrigin.y - ptLen;
				m_ptOrigin.x = m_ptOrigin.x - ptLen;
				m_ptOrigin.y = m_ptOrigin.y + ptLen;
				dc.Ellipse(CRect(m_ptOrigin, point));
				m_ptOld = point;
			}
			else//绘制椭圆
			{
				dc.Ellipse(CRect(m_ptOrigin, m_ptOld));
				dc.Ellipse(CRect(m_ptOrigin, point));
				m_ptOld = point;
			}
			break;
		case 5://绘制连续直线（铅笔）
			dc.MoveTo(m_ptOld);
			dc.LineTo(point);
			m_ptOld = point;
			break;
		case 6://绘制三角形
			if (m_click % 3 == 2)//拖动绘制三角形的第一三、二三点连线
			{
				dc.SetROP2(R2_NOTXORPEN);
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(m_ptOld2);
				dc.MoveTo(m_ptEnd);
				dc.LineTo(m_ptOld2);
				m_ptOld2 = point;

				dc.SetROP2(R2_NOTXORPEN);
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(m_ptOld2);
				dc.MoveTo(m_ptEnd);
				dc.LineTo(m_ptOld2);
			}
			else if (m_click % 3 == 0)//拖动绘制三角形第一条边
			{
				dc.SetROP2(R2_NOTXORPEN);
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(m_ptOld);
				m_ptOld = point;

				dc.SetROP2(R2_NOTXORPEN);
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(m_ptOld);
			}
			break;
		case 8:	//平移及放大缩小
			if (m_isSelect)
			{
				if (((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 != 0)//若选中图形尚未旋转
					//||((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType==4)
					RedrawWindow();
				if (m_isSpin)//旋转坐标系
				{
					SetGraphicsMode(dc.m_hDC, GM_ADVANCED);
					SetWorldTransform(dc.m_hDC, &((CGraphic*)m_ptrArray.GetAt(num))->m_xForm);
					SetGraphicsMode(dc.m_hDC, GM_COMPATIBLE);
					//m_isSpin=FALSE;
				}
				CRect rect;
				CPoint v1(6, 6);
				m_ptMove2 = point;
				vector = m_ptMove2 - m_ptMove1;
				m_ptMove1 = m_ptMove2;
				{
					CBrush* pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
					dc.SelectObject(pBrush);
				}
				switch (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType)
				{
				case 2:
					if (m_isSpin)//旋转时小正方形的绘制
					{
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
						SpinDC();
					}
					else//未旋转时直线的平移
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point1);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point2);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
						(((CGraphic*)m_ptrArray.GetAt(num))->point1) += vector;
						(((CGraphic*)m_ptrArray.GetAt(num))->point2) += vector;
						dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point1);
						dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point2);
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
						dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
							CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
					}
					break;
				case 3:
					if (!flag)//矩形的平移
					{
						if (m_isSpin)//旋转后的平移
						{
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
							SpinDC();
						}
						else//未旋转时所做的平移
						{
							dc.SetROP2(R2_NOTXORPEN);
							dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
								((CGraphic*)m_ptrArray.GetAt(num))->point2));
							RectLocation(rect);
							MoveRect();
							dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
								((CGraphic*)m_ptrArray.GetAt(num))->point2));
							RectLocation(rect);
						}
					}
					else if (m_SelectOrigin == TRUE)//拉伸压缩（左上角点）			
					{
						if (m_SelectRatio)//设置按比例放大缩小时向量，下同
						{
							vector.y = vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1 += vector;
						RectRelation();
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
					}
					else if (m_SelectOld == TRUE)//拉伸压缩（右下角点）			
					{
						if (m_SelectRatio)
						{
							vector.y = vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point2 += vector;
						RectRelation();
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
					}
					else if (m_SelectOrigin2 == TRUE)//拉伸压缩（左下角点）			
					{
						if (m_SelectRatio)
						{
							vector.y = -vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.x += vector.x;
						((CGraphic*)m_ptrArray.GetAt(num))->point2.y += vector.y;
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point4) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectEnd2 == TRUE)	//拉伸压缩（右上角点）		
					{
						if (m_SelectRatio)
						{
							vector.y = -vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.y += vector.y;
						((CGraphic*)m_ptrArray.GetAt(num))->point2.x += vector.x;
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point5) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectTop == TRUE)//拉伸压缩（上边中点）		
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.y += vector.y;
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point6) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectBottom == TRUE)//拉伸压缩（下边中点）			
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point2.y += vector.y;
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point7) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectLeft == TRUE)	//拉伸压缩（左边中点）		
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.x += vector.x;
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point8) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectRight == TRUE)//拉伸压缩（右边中点）			
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point2.x += vector.x;
						dc.Rectangle(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point9) += vector;
						RectRelation();
						RectLocation(rect);
					}
					break;
				case 4:
					if (!flag)//椭圆的平移
					{
						if (m_isSpin)
						{
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
							SpinDC();
						}
						else
						{
							dc.SetROP2(R2_NOTXORPEN);
							dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
								((CGraphic*)m_ptrArray.GetAt(num))->point2));
							RectLocation(rect);
							MoveRect();
							dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
								((CGraphic*)m_ptrArray.GetAt(num))->point2));
							RectLocation(rect);
						}
					}
					else if (m_SelectOrigin == TRUE)//拉伸压缩（左上角点）
					{
						if (m_SelectRatio)
						{
							vector.y = vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						(((CGraphic*)m_ptrArray.GetAt(num))->point1) += vector;
						RectRelation();
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
					}
					else if (m_SelectOld == TRUE)//拉伸压缩（右下角点）			
					{
						if (m_SelectRatio)
						{
							vector.y = vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point2 += vector;
						RectRelation();
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
					}
					else if (m_SelectOrigin2 == TRUE)//拉伸压缩（左下角点）			
					{
						if (m_SelectRatio)
						{
							vector.y = -vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.x += vector.x;
						((CGraphic*)m_ptrArray.GetAt(num))->point2.y += vector.y;
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point4) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectEnd2 == TRUE)	//拉伸压缩（右上角点）		
					{
						if (m_SelectRatio)
						{
							vector.y = -vector.x / m_ratio;
						}
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.y += vector.y;
						((CGraphic*)m_ptrArray.GetAt(num))->point2.x += vector.x;
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point5) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectTop == TRUE)	//拉伸压缩（上边中点）		
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.y += vector.y;
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point6) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectBottom == TRUE)//拉伸压缩（下边中点）		
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point2.y += vector.y;
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point7) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectLeft == TRUE)	//拉伸压缩（左边中点）		
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point1.x += vector.x;
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point8) += vector;
						RectRelation();
						RectLocation(rect);
					}
					else if (m_SelectRight == TRUE)//拉伸压缩（右边中点）			
					{
						dc.SetROP2(R2_NOTXORPEN);
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						RectLocation(rect);
						((CGraphic*)m_ptrArray.GetAt(num))->point2.x += vector.x;
						dc.Ellipse(CRect(((CGraphic*)m_ptrArray.GetAt(num))->point1,
							((CGraphic*)m_ptrArray.GetAt(num))->point2));
						(((CGraphic*)m_ptrArray.GetAt(num))->point9) += vector;
						RectRelation();
						RectLocation(rect);
					}
					break;
				case 6:
					if (!flag)//三角形的平移
					{
						if (m_isSpin)
						{
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
							dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
								CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
							SpinDC();
						}
						else
						{
							DrawTriangle();
							TriangleLocation(rect);
							MoveTriangle();
							DrawTriangle();
							TriangleLocation(rect);
						}
					}
					else if (m_SelectOrigin2)//拉伸压缩（上点）
					{
						DrawTriangle();
						TriangleLocation(rect);
						TriangleRelation();
						((CGraphic*)m_ptrArray.GetAt(num))->point4 += vector;
						DrawTriangle();
						TriangleLocation(rect);
					}
					else if (m_SelectEnd2)//拉伸压缩（左点）
					{
						DrawTriangle();
						TriangleLocation(rect);
						TriangleRelation();
						((CGraphic*)m_ptrArray.GetAt(num))->point5 += vector;
						DrawTriangle();
						TriangleLocation(rect);
					}
					else if (m_SelectTop)//拉伸压缩（右点）
					{
						DrawTriangle();
						TriangleLocation(rect);
						TriangleRelation();
						((CGraphic*)m_ptrArray.GetAt(num))->point6 += vector;
						DrawTriangle();
						TriangleLocation(rect);
					}
					break;
				case 7://填充色保存
					CBrush pBrush(((CGraphic*)m_ptrArray.GetAt(num))->m_clr2);
					dc.SelectObject(&pBrush);
					if (((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 3 ||
						((CGraphic*)m_ptrArray.GetAt(num))->m_nDrawType == 4)
					{
						m_ptMiddle.x = (((CGraphic*)m_ptrArray.GetAt(num))->point1.x +
							((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2 + vector.x;
						m_ptMiddle.y = (((CGraphic*)m_ptrArray.GetAt(num))->point1.y +
							((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2 + vector.y;
						dc.ExtFloodFill(m_ptColor.x, m_ptColor.y, dc.GetPixel(m_ptColor), FLOODFILLSURFACE);
					}
					break;
				}
				break;
			}

		case 9://旋转
			if (m_isSelect)
			{
				m_ptMove2 = point;
				m_ptMiddle.x = (((CGraphic*)m_ptrArray.GetAt(num))->point1.x +//旋转中心
					((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2;
				m_ptMiddle.y = (((CGraphic*)m_ptrArray.GetAt(num))->point1.y +
					((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2;
				//点下去的始点到鼠标弹起的终点及旋转中心三点构成的三角形的三边长
				double a = sqrt(double((point.x - m_ptMiddle.x) * (point.x - m_ptMiddle.x) + (point.y - m_ptMiddle.y) * (point.y - m_ptMiddle.y)));
				double b = sqrt(double((m_ptMove1.x - m_ptMiddle.x) * (m_ptMove1.x - m_ptMiddle.x) + (m_ptMove1.y - m_ptMiddle.y) * (m_ptMove1.y - m_ptMiddle.y)));
				//double c=double ((point.x-m_ptMiddle.x)*(m_ptMove1.x-m_ptMiddle.x)+(point.y-m_ptMiddle.y)*(m_ptMove1.y-m_ptMiddle.y));
				//double theta=acos(c/(a*b));
				double c = sqrt(double((m_ptMove1.x - point.x) * (m_ptMove1.x - point.x) + (m_ptMove1.y - point.y) * (m_ptMove1.y - point.y)));
				//余弦定理计算旋转角度
				double theta = acos((a * a + b * b - c * c) / (2 * a * b));
				m_ptMove1 = m_ptMove2;
				//坐标系旋转参数
				m_xForm.eM11 = float(cos(theta));
				m_xForm.eM12 = float(sin(theta));
				m_xForm.eM21 = float(-sin(theta));
				m_xForm.eM22 = float(cos(theta));
				m_xForm.eDx = float(m_ptMiddle.x - cos(theta) * m_ptMiddle.x + sin(theta) * m_ptMiddle.y);
				m_xForm.eDy = float(m_ptMiddle.y - cos(theta) * m_ptMiddle.y - sin(theta) * m_ptMiddle.x);
				//保存坐标系旋转参数
				float a1, b1, c1, d1, e1, f1;
				a1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
					+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
				b1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
					+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
				c1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
					+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
				d1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
					+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
				e1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
					+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21
					+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx;
				f1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
					+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22
					+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11 = a1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 = b1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21 = c1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22 = d1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx = e1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy = f1;
				RedrawWindow();
			}
			break;
		case 20:
			if (m_isSelect)
			{
				m_ptMove2 = point;
				m_ptMiddle.x = (((CGraphic*)m_ptrArray.GetAt(num))->point1.x +//旋转中心
					((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2;
				m_ptMiddle.y = (((CGraphic*)m_ptrArray.GetAt(num))->point1.y +
					((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2;
				//点下去的始点到鼠标弹起的终点及旋转中心三点构成的三角形的三边长
				
				double theta = double(m_nAngle) * 0.00556 * 3.14;
				m_ptMove1 = m_ptMove2;
				//坐标系旋转参数
				m_xForm.eM11 = float(cos(theta));
				m_xForm.eM12 = float(sin(theta));
				m_xForm.eM21 = float(-sin(theta));
				m_xForm.eM22 = float(cos(theta));
				m_xForm.eDx = float(m_ptMiddle.x - cos(theta) * m_ptMiddle.x + sin(theta) * m_ptMiddle.y);
				m_xForm.eDy = float(m_ptMiddle.y - cos(theta) * m_ptMiddle.y - sin(theta) * m_ptMiddle.x);
				//保存坐标系旋转参数
				float a1, b1, c1, d1, e1, f1;
				a1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
					+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
				b1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
					+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
				c1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
					+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
				d1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
					+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
				e1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
					+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21
					+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx;
				f1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
					+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22
					+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11 = a1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 = b1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21 = c1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22 = d1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx = e1;
				((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy = f1;
				RedrawWindow();
			}
			break;
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void CDrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_SHIFT)//是否按下shift键
	{
		m_circle = TRUE;//可以开始绘制圆和正方形
		m_SelectRatio = TRUE;//可以进行按比例放大缩小
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDrawView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == VK_SHIFT)//判断shift键是否弹起
	{
		m_circle = FALSE;//停止绘制圆和正方形
		m_SelectRatio = FALSE;//停止按比例放缩
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnPrepareDC(&dc);  // TODO: 在此处添加消息处理程序代码
	OnDraw(&dc);	   // 不为绘图消息调用 CView::OnPaint()
}






void CDrawView::RectRelation()//矩形边界上八个小正方形的位置关系
{
	((CGraphic*)m_ptrArray.GetAt(num))->point5.y
		= ((CGraphic*)m_ptrArray.GetAt(num))->point6.y
		= ((CGraphic*)m_ptrArray.GetAt(num))->point1.y;
	((CGraphic*)m_ptrArray.GetAt(num))->point5.x
		= ((CGraphic*)m_ptrArray.GetAt(num))->point9.x
		= ((CGraphic*)m_ptrArray.GetAt(num))->point2.x;
	((CGraphic*)m_ptrArray.GetAt(num))->point4.x
		= ((CGraphic*)m_ptrArray.GetAt(num))->point8.x
		= ((CGraphic*)m_ptrArray.GetAt(num))->point1.x;
	((CGraphic*)m_ptrArray.GetAt(num))->point4.y
		= ((CGraphic*)m_ptrArray.GetAt(num))->point7.y
		= ((CGraphic*)m_ptrArray.GetAt(num))->point2.y;
	((CGraphic*)m_ptrArray.GetAt(num))->point6.x
		= (((CGraphic*)m_ptrArray.GetAt(num))->point1.x + ((CGraphic*)m_ptrArray.GetAt(num))->point5.x) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point7.x
		= (((CGraphic*)m_ptrArray.GetAt(num))->point4.x + ((CGraphic*)m_ptrArray.GetAt(num))->point2.x) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point8.y
		= (((CGraphic*)m_ptrArray.GetAt(num))->point4.y + ((CGraphic*)m_ptrArray.GetAt(num))->point1.y) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point9.y
		= (((CGraphic*)m_ptrArray.GetAt(num))->point5.y + ((CGraphic*)m_ptrArray.GetAt(num))->point2.y) / 2;
}

void CDrawView::RectLocation(CRect rect)//矩形边界上八个小正方形的绘制
{
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	CPoint v1(6, 6);
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point7, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point8, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point9, rect) + v1)));
}

void CDrawView::TriangleLocation(CRect rect)//三角形边界上六个点的绘制
{
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	CPoint v1(6, 6);
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point1, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point2, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point3, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point4, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point5, rect) + v1)));
	dc.Rectangle(CRect(CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) - v1),
		CPoint(Trans(((CGraphic*)m_ptrArray.GetAt(num))->point6, rect) + v1)));
}

void CDrawView::TriangleRelation()//三角形边界上六个点的位置关系
{
	((CGraphic*)m_ptrArray.GetAt(num))->point1.x
		= (((CGraphic*)m_ptrArray.GetAt(num))->point4.x + ((CGraphic*)m_ptrArray.GetAt(num))->point5.x) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point1.y
		= (((CGraphic*)m_ptrArray.GetAt(num))->point4.y + ((CGraphic*)m_ptrArray.GetAt(num))->point5.y) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point2.x
		= (((CGraphic*)m_ptrArray.GetAt(num))->point4.x + ((CGraphic*)m_ptrArray.GetAt(num))->point6.x) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point2.y
		= (((CGraphic*)m_ptrArray.GetAt(num))->point4.y + ((CGraphic*)m_ptrArray.GetAt(num))->point6.y) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point3.x
		= (((CGraphic*)m_ptrArray.GetAt(num))->point5.x + ((CGraphic*)m_ptrArray.GetAt(num))->point6.x) / 2;
	((CGraphic*)m_ptrArray.GetAt(num))->point3.y
		= (((CGraphic*)m_ptrArray.GetAt(num))->point5.y + ((CGraphic*)m_ptrArray.GetAt(num))->point6.y) / 2;
}

void CDrawView::DrawTriangle()//绘制三角形时的连线
{
	CClientDC dc(this);
	dc.SetROP2(R2_NOTXORPEN);
	dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point6);
	dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point4);
	dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point6);
	dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point5);
	dc.MoveTo(((CGraphic*)m_ptrArray.GetAt(num))->point4);
	dc.LineTo(((CGraphic*)m_ptrArray.GetAt(num))->point5);
}

void CDrawView::MoveTriangle()//平移三角形六个点的坐标
{
	(((CGraphic*)m_ptrArray.GetAt(num))->point1) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point2) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point3) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point4) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point5) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point6) += vector;
}

void CDrawView::MoveRect()//平移矩形的八个点的坐标
{
	(((CGraphic*)m_ptrArray.GetAt(num))->point1) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point2) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point4) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point5) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point6) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point7) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point8) += vector;
	(((CGraphic*)m_ptrArray.GetAt(num))->point9) += vector;
}

int CDrawView::RotateDC(HDC hDc, int iAngle, POINT centerPt)//恢复坐标系
{
	int nGraphicsMode = SetGraphicsMode(hDc, GM_ADVANCED);
	//XFORM xForm;
	if (iAngle != 0)
	{
		double fangle = (double)iAngle / 180. * 3.1415926;
		m_xForm.eM11 = (float)cos(fangle);
		m_xForm.eM12 = (float)sin(fangle);
		m_xForm.eM21 = (float)-sin(fangle);
		m_xForm.eM22 = (float)cos(fangle);
		m_xForm.eDx = (float)(centerPt.x - cos(fangle) * centerPt.x + sin(fangle) * centerPt.y);
		m_xForm.eDy = (float)(centerPt.y - cos(fangle) * centerPt.y - sin(fangle) * centerPt.x);
		SetWorldTransform(hDc, &m_xForm);
	}
	return nGraphicsMode;
}

void CDrawView::RestoreRotatedDC(HDC hDc, int nGraphicsMode)//旋转坐标系
{
	m_xForm.eM11 = (float)1.0;
	m_xForm.eM12 = (float)0;
	m_xForm.eM21 = (float)0;
	m_xForm.eM22 = (float)1.0;
	m_xForm.eDx = (float)0;
	m_xForm.eDy = (float)0;

	SetWorldTransform(hDc, &m_xForm);
	SetGraphicsMode(hDc, nGraphicsMode);
}

void CDrawView::SpinDC()//旋转后的平移过程
{
	float a2, b2;
	a2 = ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11 * vector.x
		+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 * vector.y;
	b2 = ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21 * vector.x
		+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22 * vector.y;
	m_xForm.eM11 = float(1);
	m_xForm.eM12 = float(0);
	m_xForm.eM21 = float(0);
	m_xForm.eM22 = float(1);
	m_xForm.eDx = a2;
	m_xForm.eDy = b2;
	float a1, b1, c1, d1, e1, f1;
	a1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
		+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
	b1 = m_xForm.eM11 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
		+ m_xForm.eM12 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
	c1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
		+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21;
	d1 = m_xForm.eM21 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
		+ m_xForm.eM22 * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22;
	e1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11
		+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21
		+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx;
	f1 = m_xForm.eDx * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12
		+ m_xForm.eDy * ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22
		+ ((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy;
	((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM11 = a1;
	((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM12 = b1;
	((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM21 = c1;
	((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eM22 = d1;
	((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDx = e1;
	((CGraphic*)m_ptrArray.GetAt(num))->m_xForm.eDy = f1;
}












