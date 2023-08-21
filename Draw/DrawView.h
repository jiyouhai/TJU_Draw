
// DrawView.h: CDrawView 类的接口
//

#pragma once


class CDrawView : public CView
{
protected: // 仅从序列化创建
	CDrawView() noexcept;
	DECLARE_DYNCREATE(CDrawView)

// 特性
public:
	CDrawDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDrawView();
	void SpinDC();
	void RestoreRotatedDC(HDC hDc, int nGraphicsMode);
	int RotateDC(HDC hDc, int iAngle, POINT centerPt);
	void MoveRect();
	void MoveTriangle();
	void DrawTriangle();
	void TriangleRelation();
	void TriangleLocation(CRect rect);
	void RectLocation(CRect rect);
	void RectRelation();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
private:
	BOOL m_isRedraw;
	BOOL m_isSpin;
	CPoint m_ptCenter;
	COLORREF m_clr3;
	CPoint m_ptSpin;
	XFORM m_xForm;
	BOOL flag;
	BOOL m_SelectRatio;
	int m_ratio;
	CPoint m_ptScale2;
	BOOL m_SelectTop;
	BOOL m_SelectRight;
	BOOL m_SelectLeft;
	BOOL m_SelectBottom;
	BOOL m_SelectOld2;
	BOOL m_SelectEnd2;
	BOOL m_SelectOrigin2;
	BOOL m_SelectOld;
	CPoint m_ptScale;
	BOOL m_SelectOrigin;
	CPoint m_ptMove3;
	CPoint m_ptMove2;
	BOOL m_isSelect;
	BOOL m_isMove;
	CPoint m_ptMiddle;
	CPoint vector;
	CPoint vector1;
	CPoint vector2;
	CPoint vector3;
	CPoint m_center;
	UINT num;
	BOOL m_reDraw;
	COLORREF m_pixelColor;
	CPoint m_ptMove1;
	CPoint m_ptColor;
	CPtrArray m_ptrArray;
	COLORREF m_clr2;
	CPoint m_ptEnd;
	int m_click;
	CPoint m_ptOld2;
	BOOL m_circle;
	CString m_strFontName;
	CFont m_font;
	CPoint m_ptOld;
	CPoint m_ptOld1;
	BOOL m_bDraw;
	COLORREF m_clr;
	int m_nLineStyle;
	UINT m_nLineWidth;
	CPoint m_ptOrigin;
	UINT m_nDrawType;
public:
	afx_msg void OnDot();
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnEllipse();
	afx_msg void OnTriangle();
	afx_msg void OnMove();
	afx_msg void OnRotate();
	afx_msg void OnSetting();
	afx_msg void OnColor();
	afx_msg void OnFill();
	afx_msg void OnLcolor();
	afx_msg void OnFont();
	afx_msg void OnClear();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnIso();
	afx_msg void OnEqual();
private:
	UINT m_nAngle;
	
	
public:
	afx_msg void OnSettingangle();
	afx_msg void OnGudingrotate();
	afx_msg void OnRight();
	afx_msg void OnCircle();
	afx_msg void OnSquare();
	afx_msg void On32809();
	afx_msg void OnMove1();
	afx_msg void OnRatio();
private:
	float ratio;
};

#ifndef _DEBUG  // DrawView.cpp 中的调试版本
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

