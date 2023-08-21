#pragma once
class CGraphic
{
public:
	XFORM m_xForm;
	CPoint point9;
	CPoint point8;
	CPoint point7;
	CPoint point6;
	CPoint point5;
	CPoint point4;
	CPoint m_ptColor;
	UINT m_nLineWidth;
	int m_nLineStyle;
	COLORREF m_clr2;
	COLORREF m_clr;
	CPoint point3;
	CPoint point2;
	CPoint point1;
	UINT m_nDrawType;
	CGraphic::CGraphic(UINT m_nDrawType, CPoint point1, CPoint point2, CPoint point3, CPoint point4,
		CPoint point5, CPoint point6, CPoint point7, CPoint point8, CPoint point9,
		CPoint m_ptColor, COLORREF m_clr, COLORREF m_clr2, int m_nLineStyle, UINT m_nLineWidth, XFORM m_xForm);
	virtual ~CGraphic();
};

