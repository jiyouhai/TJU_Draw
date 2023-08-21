#include "pch.h"
#include "Graphic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// 构造函数，初始化图形对象
CGraphic::CGraphic(UINT m_nDrawType, CPoint point1, CPoint point2, CPoint point3, CPoint point4,
    CPoint point5, CPoint point6, CPoint point7, CPoint point8, CPoint point9,
    CPoint m_ptColor, COLORREF m_clr, COLORREF m_clr2, int m_nLineStyle, UINT m_nLineWidth, XFORM m_xForm)
{
    // 设置基本绘图属性
    this->m_nDrawType = m_nDrawType;
    this->m_nLineStyle = m_nLineStyle;
    this->m_nLineWidth = m_nLineWidth;
    this->m_clr = m_clr;
    this->m_clr2 = m_clr2;
    
    // 初始化变换矩阵
    this->m_xForm = m_xForm;
    this->m_xForm.eM11 = (float)1.0;
    this->m_xForm.eM12 = (float)0;
    this->m_xForm.eM21 = (float)0;
    this->m_xForm.eM22 = (float)1.0;
    this->m_xForm.eDx = (float)0;
    this->m_xForm.eDy = (float)0;

    // 根据图形类型选择相应的点
    switch (m_nDrawType)
    {
    case 2:
        this->point1 = point1;
        this->point2 = point2;
        break;
    case 3:
    case 4:
        this->point1 = point1;
        this->point2 = point2;
        this->point4 = point4;
        this->point5 = point5;
        this->point6 = point6;
        this->point7 = point7;
        this->point8 = point8;
        this->point9 = point9;
        break;
    case 6:
        this->point1 = point1;
        this->point2 = point2;
        this->point3 = point3;
        this->point4 = point4;
        this->point5 = point5;
        this->point6 = point6;
        break;
    case 7:
        this->m_ptColor = m_ptColor;
        // 中点坐标可以用下面的代码计算
        // this->m_ptColor.x=(point1.x+point2.x)/2;
        // this->m_ptColor.y=(point1.y+point2.y)/2;
        break;
    }
}

// 析构函数
CGraphic::~CGraphic()
{
    // 资源清理（如有需要）
}
