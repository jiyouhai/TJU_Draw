
// DrawView.cpp : implementation of the CDrawView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawView

IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CDrawView construction/destruction

CDrawView::CDrawView() noexcept
{
	// TODO: add construction code here
	

}

CDrawView::~CDrawView()
{
	m_Doc = NULL;
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDrawView drawing

void CDrawView::OnDraw(CDC* pDC)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (!m_Doc) 
		m_Doc = GetDocument();

	m_Doc->flush_all(pDC);

	// TODO: add draw code for native data here
}



void CDrawView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CView::OnPaint() for painting messages
	OnPrepareDC(&dc);
	OnDraw(&dc);

}
// CDrawView printing

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDrawView diagnostics

#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawView message handlers
std::vector<CPoint> polygon_vtx;
CPoint oldpoint, newpoint, originpoint;
CPoint tp1(0, 0), tp2(0, 0);
CDrawDoc::d_polygon tpolygon(polygon_vtx, 1, RGB(0, 0, 0));
double oldradius = 0.0;
int ta = 0, tb = 0;






void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC();
	int index = -1;

	switch (m_Doc->m_type)
	{
	case 0:
		m_Doc->select_shape(dc1, point);

		break;
	case 2:
		oldpoint = point;
		newpoint = point;
		
		break;
	case 3:
		oldpoint = point;
		newpoint = point;
		
		break;
	case 41:
		if (m_Doc->is_d_polygon == FALSE && m_Doc->tri_vtx == 0)
		{
			originpoint = point;
			oldpoint = point;
			newpoint = point;
			m_Doc->is_d_polygon = TRUE;
			polygon_vtx.clear();
			polygon_vtx.push_back(originpoint);
			m_Doc->tri_vtx = 1;
		}
		else if (m_Doc->is_d_polygon == TRUE && m_Doc->tri_vtx == 1)
		{
			m_Doc->tri_vtx = 2;
		}
		else if (m_Doc->is_d_polygon == TRUE && m_Doc->tri_vtx == 2)
		{
			m_Doc->tri_vtx = 3;

		}
		
		break;
	case 42:
		oldpoint = point;
		newpoint = point;

		break;
	case 43:
		oldpoint = point;
		newpoint = point;

		break;
	case 44:
	{
		CPoint tri_ver[3] = { CPoint(point.x + 100 * sqrt(3), point.y + 100), CPoint(point.x - 100 * sqrt(3), point.y + 100), CPoint(point.x, point.y - 200) };

		m_Doc->triangle_cpen(dc1, m_Doc->m_color, tri_ver, m_Doc->m_size);
		polygon_vtx.clear();
		polygon_vtx.push_back(CPoint(point.x + 100 * sqrt(3), point.y + 100));
		polygon_vtx.push_back(CPoint(point.x - 100 * sqrt(3), point.y + 100));
		polygon_vtx.push_back(CPoint(point.x, point.y - 200));
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	case 5:
		if (!m_Doc->is_d_polygon)
		{
			originpoint = point;
			oldpoint = point;
			newpoint = point;
			m_Doc->is_d_polygon = TRUE;
			polygon_vtx.clear();
			polygon_vtx.push_back(originpoint);
		}
		else
		{
			newpoint = point;
			polygon_vtx.push_back(newpoint);
		}

		break;
	case 6:
		oldpoint = point;
		newpoint = point;

		break;
	case 7:
		oldpoint = point;
		newpoint = point;

		break;
	case 8:
		m_Doc->rectangle_cpen(dc1, m_Doc->m_color, CPoint(point.x - 100, point.y + 100), CPoint(point.x + 100, point.y - 100), m_Doc->m_size);
		polygon_vtx.clear();
		polygon_vtx.push_back(CPoint(point.x - 100, point.y + 100));
		polygon_vtx.push_back(CPoint(point.x - 100, point.y - 100));
		polygon_vtx.push_back(CPoint(point.x + 100, point.y - 100));
		polygon_vtx.push_back(CPoint(point.x + 100, point.y + 100));
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));

		break;
	case 101:
	{
		if (m_Doc->selected_line != -1)
		{
			index = m_Doc->selected_line;
			int xm = (m_Doc->v_line[index].p1.x + m_Doc->v_line[index].p2.x) / 2,
				ym = (m_Doc->v_line[index].p1.y + m_Doc->v_line[index].p2.y) / 2;
			point.x = xm + m_Doc->rl_move;
			point.y = ym + m_Doc->ud_move;
			m_Doc->translate_line(m_Doc->v_line, index, point);
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, m_Doc->v_line[index].p1, m_Doc->v_line[index].p2, m_Doc->v_line[index].size);
			
			m_Doc->selected_line = -1;
		}
		else if (m_Doc->selected_circle != -1)
		{
			index = m_Doc->selected_circle;
			point.x = m_Doc->v_circle[index].p0.x + m_Doc->rl_move;
			point.y = m_Doc->v_circle[index].p0.y + m_Doc->ud_move;
			m_Doc->translate_circle(m_Doc->v_circle, index, point);
			m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, m_Doc->v_circle[index].radius, m_Doc->v_circle[index].size);
		}
		else if (m_Doc->selected_ellipse != -1)
		{
			index = m_Doc->selected_ellipse;
			point.x = m_Doc->v_ellipse[index].p0.x + m_Doc->rl_move;
			point.y = m_Doc->v_ellipse[index].p0.y + m_Doc->ud_move;
			m_Doc->translate_ellipse(m_Doc->v_ellipse, index, point);
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
		}
		else if (m_Doc->selected_polygon != -1)
		{
			index = m_Doc->selected_polygon;
			int mid_x = 0, mid_y = 0;
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++)
			{
				mid_x += m_Doc->v_polygon[index].ps[i].x;
				mid_y += m_Doc->v_polygon[index].ps[i].y;
			}
			mid_x /= m_Doc->v_polygon[index].ps.size();
			mid_y /= m_Doc->v_polygon[index].ps.size();
			point.x = mid_x + m_Doc->rl_move;
			point.y = mid_y + m_Doc->ud_move;
			m_Doc->translate_polygon(m_Doc->v_polygon, index, point);
			m_Doc->polygon_cpen(dc1, m_Doc->v_polygon[index], m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
		}
		m_Doc->m_type = 0;
		Invalidate(TRUE);
		break;
	}
	case 200:
		oldpoint = point;

		break;
	case 201:
	{
		if (m_Doc->selected_line != -1)
		{
			index = m_Doc->selected_line;
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);

			int x1 = (m_Doc->v_line[index].p1.x + m_Doc->v_line[index].p2.x) / 2;
			int y1 = (m_Doc->v_line[index].p1.y + m_Doc->v_line[index].p2.y) / 2;
			
			tp1 = m_Doc->get_rotated_point(m_Doc->v_line[index].p1, CPoint(x1, y1), m_Doc->r_angle);
			tp2 = m_Doc->get_rotated_point(m_Doc->v_line[index].p2, CPoint(x1, y1), m_Doc->r_angle);

			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);
			oldpoint = CPoint(x1 + 100, y1);
			point = m_Doc->get_rotated_point(oldpoint, CPoint(x1, y1), m_Doc->r_angle);
			m_Doc->rotate_line(m_Doc->v_line, index, oldpoint, point);
			m_Doc->selected_line = -1;
			tp1 = tp2 = CPoint(0, 0);

		}
		else if (m_Doc->selected_ellipse != -1)
		{
			index = m_Doc->selected_ellipse;
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
			oldpoint = CPoint(m_Doc->v_ellipse[index].p0.x + 100, m_Doc->v_ellipse[index].p0.y);
			point = m_Doc->get_rotated_point(oldpoint, m_Doc->v_ellipse[index].p0, m_Doc->r_angle);
			m_Doc->rotate_ellipse(m_Doc->v_ellipse, index, oldpoint, point);
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);

		}
		else if (m_Doc->selected_polygon != -1)
		{
			index = m_Doc->selected_polygon;
			m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);

			int mid_x = 0, mid_y = 0;
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++)
			{
				mid_x += m_Doc->v_polygon[index].ps[i].x;
				mid_y += m_Doc->v_polygon[index].ps[i].y;
			}
			mid_x /= m_Doc->v_polygon[index].ps.size();
			mid_y /= m_Doc->v_polygon[index].ps.size();


			tpolygon = m_Doc->v_polygon[index];
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++)
				tpolygon.ps[i] = m_Doc->get_rotated_point(tpolygon.ps[i], CPoint(mid_x, mid_y), m_Doc->r_angle);

			m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
			oldpoint = CPoint(mid_x + 100, mid_y);
			point = m_Doc->get_rotated_point(oldpoint, CPoint(mid_x, mid_y), m_Doc->r_angle);
			m_Doc->rotate_polygon(m_Doc->v_polygon, index, oldpoint, point);
			m_Doc->selected_polygon = -1;
			tpolygon.ps.clear();
			tpolygon.size = 1;
			tpolygon.color = RGB(0, 0, 0);
		}
		m_Doc->m_type = 0;
		Invalidate(TRUE);

		break;
	}
	case 300:
		oldpoint = point;

		break;
	case 301:
	{
		if (m_Doc->selected_line != -1)
		{
			index = m_Doc->selected_line;
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);
			int x1 = (m_Doc->v_line[index].p1.x + m_Doc->v_line[index].p2.x) / 2,
				y1 = (m_Doc->v_line[index].p1.y + m_Doc->v_line[index].p2.y) / 2;
			tp1.x = (m_Doc->v_line[index].p1.x - x1) * m_Doc->s_rate + x1;
			tp1.y = (m_Doc->v_line[index].p1.y - y1) * m_Doc->s_rate + y1;
			tp2.x = (m_Doc->v_line[index].p2.x - x1) * m_Doc->s_rate + x1;
			tp2.y = (m_Doc->v_line[index].p2.y - y1) * m_Doc->s_rate + y1;
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);
			oldpoint = CPoint(x1 + 100, y1 + 100);
			point.x = (oldpoint.x - x1) * m_Doc->s_rate + x1;
			point.y = (oldpoint.y - y1) * m_Doc->s_rate + y1;
			m_Doc->scale_line(m_Doc->v_line, index, oldpoint, point);
			
			m_Doc->selected_line = -1;
			tp1 = CPoint(0, 0);
			tp2 = CPoint(0, 0);

		}
		else if (m_Doc->selected_circle != -1)
		{
			index = m_Doc->selected_circle;
			m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, oldradius, m_Doc->v_circle[index].size);
			int x1 = m_Doc->v_circle[index].p0.x,
				y1 = m_Doc->v_circle[index].p0.y;
			oldradius = m_Doc->v_circle[index].radius * m_Doc->s_rate;
			m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, oldradius, m_Doc->v_circle[index].size);
			oldpoint = CPoint(x1 + 100, y1 + 100);
			point.x = (oldpoint.x - x1) * m_Doc->s_rate + x1;
			point.y = (oldpoint.y - y1) * m_Doc->s_rate + y1;
			m_Doc->scale_circle(m_Doc->v_circle, index, oldpoint, point);
			m_Doc->selected_circle = -1;
			oldradius = 0.0;
		}
		else if (m_Doc->selected_ellipse != -1)
		{
			index = m_Doc->selected_ellipse;
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, ta, tb, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
			int x1 = m_Doc->v_ellipse[index].p0.x,
				y1 = m_Doc->v_ellipse[index].p0.y;
			ta = m_Doc->v_ellipse[index].a * m_Doc->s_rate;
			tb = m_Doc->v_ellipse[index].b * m_Doc->s_rate;
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, ta, tb, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
			oldpoint = CPoint(x1 + 100, y1 + 100);
			point.x = (oldpoint.x - x1) * m_Doc->s_rate + x1;
			point.y = (oldpoint.y - y1) * m_Doc->s_rate + y1;
			m_Doc->scale_ellipse(m_Doc->v_ellipse, index, oldpoint, point);
			m_Doc->selected_ellipse = -1;
			ta = tb = 0;
		}
		else if (m_Doc->selected_polygon != -1)
		{
			index = m_Doc->selected_polygon;
			m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
			int mid_x = 0, mid_y = 0;
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++) {
				mid_x += m_Doc->v_polygon[index].ps[i].x;
				mid_y += m_Doc->v_polygon[index].ps[i].y;
			}
			mid_x /= m_Doc->v_polygon[index].ps.size();
			mid_y /= m_Doc->v_polygon[index].ps.size();
			tpolygon = m_Doc->v_polygon[index];
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++) {
				tpolygon.ps[i].x = (m_Doc->v_polygon[index].ps[i].x - mid_x) * m_Doc->s_rate + mid_x;
				tpolygon.ps[i].y = (m_Doc->v_polygon[index].ps[i].y - mid_y) * m_Doc->s_rate + mid_y;
			}
			m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
			oldpoint = CPoint(mid_x + 100, mid_y + 100);
			point.x = (oldpoint.x - mid_x) * m_Doc->s_rate + mid_x;
			point.y = (oldpoint.y - mid_y) * m_Doc->s_rate + mid_y;
			m_Doc->scale_polygon(m_Doc->v_polygon, index, oldpoint, point);
			m_Doc->selected_polygon = -1;
			tpolygon.ps.clear();
			tpolygon.size = 1;
			tpolygon.color = RGB(0, 0, 0);
		}
		m_Doc->m_type = 0;
		Invalidate(TRUE);

		break;

	}
	case 500:
	{
		if (m_Doc->selected_line != -1)
		{
			index = m_Doc->selected_line;
			m_Doc->changecolor_line(m_Doc->v_line, index, m_Doc->m_newcolor);
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, m_Doc->v_line[index].p1, m_Doc->v_line[index].p2, m_Doc->v_line[index].size);
		}
		else if (m_Doc->selected_circle != -1)
		{
			index = m_Doc->selected_circle;
			m_Doc->changecolor_circle(m_Doc->v_circle, index, m_Doc->m_newcolor);
			m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, m_Doc->v_circle[index].radius, m_Doc->v_circle[index].size);
		}
		else if (m_Doc->selected_ellipse != -1)
		{
			index = m_Doc->selected_ellipse;
			m_Doc->changecolor_ellipse(m_Doc->v_ellipse, index, m_Doc->m_newcolor);
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
		}
		else if (m_Doc->selected_polygon != -1)
		{
			index = m_Doc->selected_polygon;
			m_Doc->changecolor_polygon(m_Doc->v_polygon, index, m_Doc->m_newcolor);
			m_Doc->polygon_cpen(dc1, m_Doc->v_polygon[index], m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
		}

		m_Doc->m_type = 0;
		Invalidate(TRUE);

	}

	}

	ReleaseDC(dc1);

	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC(), * dc2 = GetDC();
	int index = -1;
	dc1->SetROP2(R2_NOT);

	switch (m_Doc->m_type)
	{
	case 2:
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);

		m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, point, m_Doc->m_size);
		m_Doc->v_line.push_back(CDrawDoc::d_line(oldpoint, newpoint, m_Doc->m_size, m_Doc->m_color));

		break;
	case 3:
	{
		int radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + ((newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y)));

		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y + radius, oldpoint.x + radius, oldpoint.y - radius), CPoint(0, 0), CPoint(0, 0));

		m_Doc->circle_cpen(dc2, m_Doc->m_color, oldpoint, radius, m_Doc->m_size);
		m_Doc->v_circle.push_back(CDrawDoc::d_circle(oldpoint, radius, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	case 41:
		if (m_Doc->tri_vtx == 1 && m_Doc->is_d_polygon == TRUE)
		{
			dc1->MoveTo(oldpoint);
			dc1->LineTo(newpoint);

			m_Doc->dot(dc2, m_Doc->m_color, newpoint.x, newpoint.y, m_Doc->m_size);
			m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
			polygon_vtx.push_back(newpoint);
			oldpoint = newpoint;
		}
		else if (m_Doc->tri_vtx == 2 && m_Doc->is_d_polygon == TRUE)
		{
			dc1->MoveTo(oldpoint);
			dc1->LineTo(newpoint);
			m_Doc->dot(dc2, m_Doc->m_color, newpoint.x, newpoint.y, m_Doc->m_size);
			m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
			polygon_vtx.push_back(newpoint);
			oldpoint = newpoint;
		}
		else if (m_Doc->tri_vtx == 3 && m_Doc->is_d_polygon == TRUE)
		{
			dc1->MoveTo(oldpoint);
			dc1->LineTo(newpoint);
			m_Doc->dot(dc2, m_Doc->m_color, newpoint.x, newpoint.y, m_Doc->m_size);
			m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
			polygon_vtx.push_back(newpoint);
			m_Doc->line_cpen(dc2, m_Doc->m_color, newpoint, originpoint, m_Doc->m_size);
			m_Doc->tri_vtx = 1;
			m_Doc->is_d_polygon = FALSE;

			m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));
		}

		break;
	case 42:
	{
		CPoint tri_ver[3] = { oldpoint, newpoint, CPoint(oldpoint.x, newpoint.y) };
		// dc1->Polygon(tri_ver, 3);

		m_Doc->triangle_cpen(dc2, m_Doc->m_color, tri_ver, m_Doc->m_size);
		polygon_vtx.clear();
		polygon_vtx.push_back(oldpoint);
		polygon_vtx.push_back(newpoint);
		polygon_vtx.push_back(CPoint(oldpoint.x, newpoint.y));
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	case 43:
	{
		CPoint tri_ver[3] = { oldpoint, newpoint, CPoint(2 * oldpoint.x - newpoint.x, newpoint.y) };
		m_Doc->triangle_cpen(dc2, m_Doc->m_color, tri_ver, m_Doc->m_size);
		polygon_vtx.clear();
		polygon_vtx.push_back(oldpoint);
		polygon_vtx.push_back(newpoint);
		polygon_vtx.push_back(CPoint(2 * oldpoint.x - newpoint.x, newpoint.y));
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	case 5:
		if (m_Doc->is_d_polygon == TRUE)
		{
			dc1->MoveTo(oldpoint);
			dc1->LineTo(newpoint);

			m_Doc->dot(dc2, m_Doc->m_color, newpoint.x, newpoint.y, m_Doc->m_size);
			m_Doc->line_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
			oldpoint = newpoint;
		}

		break;
	case 6:
	{
		dc1->Arc(CRect(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y), CPoint(0, 0), CPoint(0, 0));
		int x0 = (oldpoint.x + newpoint.x) / 2;
		int y0 = (oldpoint.y + newpoint.y) / 2;
		CPoint p0 = CPoint(x0, y0);
		int a = std::abs(x0 - oldpoint.x);
		int b = std::abs(y0 - oldpoint.y);
		m_Doc->ellipse_cpen(dc2, m_Doc->m_color, x0, y0, a, b, 0, m_Doc->m_size);
		m_Doc->v_ellipse.push_back(CDrawDoc::d_ellipse(p0, a, b, 0, m_Doc->m_size, m_Doc->m_color));

		break;
	}
	case 7:
		dc1->Rectangle(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y);

		m_Doc->rectangle_cpen(dc2, m_Doc->m_color, oldpoint, newpoint, m_Doc->m_size);
		polygon_vtx.clear();
		polygon_vtx.push_back(oldpoint);
		polygon_vtx.push_back(CPoint(oldpoint.x, newpoint.y));
		polygon_vtx.push_back(newpoint);
		polygon_vtx.push_back(CPoint(newpoint.x, oldpoint.y));
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));

		break;
	case 50:
		m_Doc->fill_brush(dc2, m_Doc->m_color, GetDC()->GetPixel(point.x, point.y), point);
		m_Doc->v_fill.push_back(CDrawDoc::d_fill(point, m_Doc->m_color));

		break;

	case 100:
	{
		if ((index = m_Doc->selected_line) != -1)
		{
			m_Doc->translate_line(m_Doc->v_line, index, point);
			m_Doc->selected_line = -1;
		}
		else if ((index = m_Doc->selected_circle) != -1)
		{
			m_Doc->translate_circle(m_Doc->v_circle, index, point);
			m_Doc->selected_circle = -1;
		}
		else if ((index = m_Doc->selected_ellipse) != -1)
		{
			m_Doc->translate_ellipse(m_Doc->v_ellipse, index, point);
			m_Doc->selected_ellipse = -1;
		}
		else if ((index = m_Doc->selected_polygon) != -1)
		{
			m_Doc->translate_polygon(m_Doc->v_polygon, index, point);
			m_Doc->selected_polygon = -1;
		}

		m_Doc->m_type = 0;
		Invalidate(TRUE);
		break;
	}
	case 200:
	{
		if ((index = m_Doc->selected_line) != -1)
		{
			m_Doc->rotate_line(m_Doc->v_line, index, oldpoint, point);
			m_Doc->selected_line = -1;
			tp1 = tp2 = CPoint(0, 0);
		}
		else if ((index = m_Doc->selected_ellipse) != -1)
		{
			m_Doc->rotate_ellipse(m_Doc->v_ellipse, index, oldpoint, point);
			m_Doc->selected_ellipse = -1;
		}
		else if ((index = m_Doc->selected_polygon) != -1)
		{
			m_Doc->rotate_polygon(m_Doc->v_polygon, index, oldpoint, point);
			m_Doc->selected_polygon = -1;
			tpolygon.ps.clear();
			tpolygon.size = 1;
			tpolygon.color = RGB(0, 0, 0);
		}
		m_Doc->m_type = 0;
		Invalidate(TRUE);
		break;
	}
	case 300:
	{
		if ((index = m_Doc->selected_line) != -1)
		{
			m_Doc->scale_line(m_Doc->v_line, index, oldpoint, point);
			m_Doc->selected_line = -1;
			tp1 = CPoint(0, 0);
			tp2 = CPoint(0, 0);
		}
		else if ((index = m_Doc->selected_circle) != -1)
		{
			m_Doc->scale_circle(m_Doc->v_circle, index, oldpoint, point);
			m_Doc->selected_circle = -1;
			oldradius = 0.0;
		}
		else if ((index = m_Doc->selected_ellipse) != -1)
		{
			m_Doc->scale_ellipse(m_Doc->v_ellipse, index, oldpoint, point);
			m_Doc->selected_ellipse = -1;
			ta = tb = 0;
		}
		else if ((index = m_Doc->selected_polygon) != -1)
		{
			m_Doc->scale_polygon(m_Doc->v_polygon, index, oldpoint, point);
			m_Doc->selected_polygon = -1;
			tpolygon.ps.clear();
			tpolygon.size = 1;
			tpolygon.color = RGB(0, 0, 0);
		}

		m_Doc->m_type = 0;
		Invalidate(TRUE);
		break;
	}
	}
	


	ReleaseDC(dc2);
	ReleaseDC(dc1);
	CView::OnLButtonUp(nFlags, point);
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC();
	int index = -1;
	dc1->SetROP2(R2_NOT);

	if (nFlags == MK_LBUTTON && m_Doc->m_type == 2)
	{
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
		newpoint = point;
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 3)
	{
		int radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + (newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y));
		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y + radius, oldpoint.x + radius, oldpoint.y - radius), CPoint(0, 0), CPoint(0, 0));
		newpoint = point;
		radius = std::sqrt((newpoint.x - oldpoint.x) * (newpoint.x - oldpoint.x) + (newpoint.y - oldpoint.y) * (newpoint.y - oldpoint.y));
		dc1->Arc(CRect(oldpoint.x - radius, oldpoint.y + radius, oldpoint.x + radius, oldpoint.y - radius), CPoint(0, 0), CPoint(0, 0));
	}
	else if (m_Doc->is_d_polygon == TRUE && m_Doc->m_type == 41)
	{
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
		newpoint = point;
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 42)
	{
		CPoint tri_ver[3] = { oldpoint, newpoint, CPoint(oldpoint.x, newpoint.y) };
		dc1->Polygon(tri_ver, 3);
		newpoint = point;
		dc1->Polygon(tri_ver, 3);
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 43)
	{
		CPoint tri_ver[3] = { oldpoint, newpoint, CPoint(2 * oldpoint.x - newpoint.x, newpoint.y) };
		dc1->Polygon(tri_ver, 3);
		newpoint = point;
		dc1->Polygon(tri_ver, 3);
	}
	else if (m_Doc->is_d_polygon == TRUE && m_Doc->m_type == 5)
	{
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
		newpoint = point;
		dc1->MoveTo(oldpoint);
		dc1->LineTo(newpoint);
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 6)
	{
		dc1->Arc(CRect(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y), CPoint(0, 0), CPoint(0, 0));
		newpoint = point;
		dc1->Arc(CRect(oldpoint.x, oldpoint.y, newpoint.x, newpoint.y), CPoint(0, 0), CPoint(0, 0));
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 7)
	{
		dc1->Rectangle(CRect(oldpoint, newpoint));
		newpoint = point;
		dc1->Rectangle(CRect(oldpoint, newpoint));
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 100)
	{
		if (m_Doc->selected_line != -1)
		{
			index = m_Doc->selected_line;
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, m_Doc->v_line[index].p1, m_Doc->v_line[index].p2, m_Doc->v_line[index].size);
			m_Doc->translate_line(m_Doc->v_line, index, point);
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, m_Doc->v_line[index].p1, m_Doc->v_line[index].p2, m_Doc->v_line[index].size);
		}
		else if (m_Doc->selected_circle != -1)
		{
			index = m_Doc->selected_circle;
			m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, m_Doc->v_circle[index].radius, m_Doc->v_circle[index].size);
			m_Doc->translate_circle(m_Doc->v_circle, index, point);
			m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, m_Doc->v_circle[index].radius, m_Doc->v_circle[index].size);
		}
		else if (m_Doc->selected_ellipse != -1)
		{
			index = m_Doc->selected_ellipse;
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
			m_Doc->translate_ellipse(m_Doc->v_ellipse, index, point);
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
		}
		else if (m_Doc->selected_polygon != -1)
		{
			index = m_Doc->selected_polygon;
			m_Doc->polygon_cpen(dc1, m_Doc->v_polygon[index], m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
			m_Doc->translate_polygon(m_Doc->v_polygon, index, point);
			m_Doc->polygon_cpen(dc1, m_Doc->v_polygon[index], m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
		}
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 200)
	{
		if (m_Doc->selected_line != -1)
		{
			index = m_Doc->selected_line;
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);

			int x1 = (m_Doc->v_line[index].p1.x + m_Doc->v_line[index].p2.x) / 2;
			int y1 = (m_Doc->v_line[index].p1.y + m_Doc->v_line[index].p2.y) / 2;
			double a = sqrt((x1 - point.x) * (x1 - point.x) + (y1 - point.y) * (y1 - point.y));
			double b = sqrt((oldpoint.x - point.x) * (oldpoint.x - point.x) + (oldpoint.y - point.y) * (oldpoint.y - point.y));
			double c = sqrt((x1 - oldpoint.x) * (x1 - oldpoint.x) + (y1 - oldpoint.y) * (y1 - oldpoint.y));
			double angle = (acos((a * a + c * c - b * b) / (2 * a * c)) / m_Doc->pi * 180.0);
			double angle_judge = (oldpoint.x - x1) * (point.y - y1) - (point.x - x1) * (oldpoint.y - y1); // >0Ë³Ê±Õë£¬<0ÄæÊ±Õë
			angle = (angle_judge >= 0.0 ? angle : -angle);
			tp1 = m_Doc->get_rotated_point(m_Doc->v_line[index].p1, CPoint(x1, y1), angle);
			tp2 = m_Doc->get_rotated_point(m_Doc->v_line[index].p2, CPoint(x1, y1), angle);
			m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);
		}
		else if (m_Doc->selected_ellipse != -1)
		{
			index = m_Doc->selected_ellipse;
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
			m_Doc->rotate_ellipse(m_Doc->v_ellipse, index, oldpoint, point);
			oldpoint = point;
			m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, m_Doc->v_ellipse[index].a, m_Doc->v_ellipse[index].b, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);

		}
		else if (m_Doc->selected_polygon != -1)
		{
			index = m_Doc->selected_polygon;
			m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);

			int mid_x = 0, mid_y = 0;
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++)
			{
				mid_x += m_Doc->v_polygon[index].ps[i].x;
				mid_y += m_Doc->v_polygon[index].ps[i].y;
			}
			mid_x /= m_Doc->v_polygon[index].ps.size();
			mid_y /= m_Doc->v_polygon[index].ps.size();

			double a = sqrt((mid_x - point.x) * (mid_x - point.x) + (mid_y - point.y) * (mid_y - point.y)),
				b = sqrt((oldpoint.x - point.x) * (oldpoint.x - point.x) + (oldpoint.y - point.y) * (oldpoint.y - point.y)),
				c = sqrt((mid_x - oldpoint.x) * (mid_x - oldpoint.x) + (mid_y - oldpoint.y) * (mid_y - oldpoint.y));
			double angle = (acos((a * a + c * c - b * b) / (2 * a * c)) / m_Doc->pi * 180.0);
			double angle_judge = (oldpoint.x - mid_x) * (point.y - mid_y) - (point.x - mid_x) * (oldpoint.y - mid_y); //>0Ë³Ê±Õë£¬<0ÄæÊ±Õë
			angle = (angle_judge >= 0.0 ? angle : -angle);
			tpolygon = m_Doc->v_polygon[index];
			for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++)
				tpolygon.ps[i] = m_Doc->get_rotated_point(tpolygon.ps[i], CPoint(mid_x, mid_y), angle);

			m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
		}
	}
	else if (nFlags == MK_LBUTTON && m_Doc->m_type == 300)
		{
			if (m_Doc->selected_line != -1)
			{
				index = m_Doc->selected_line;
				m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);
				int x1 = (m_Doc->v_line[index].p1.x + m_Doc->v_line[index].p2.x) / 2,
					y1 = (m_Doc->v_line[index].p1.y + m_Doc->v_line[index].p2.y) / 2;
				double dis1 = sqrt((oldpoint.x - x1) * (oldpoint.x - x1) + (oldpoint.y - y1) * (oldpoint.y - y1)),
					dis2 = sqrt((point.x - x1) * (point.x - x1) + (point.y - y1) * (point.y - y1));
				double rate = dis2 / dis1;
				tp1.x = (m_Doc->v_line[index].p1.x - x1) * rate + x1;
				tp1.y = (m_Doc->v_line[index].p1.y - y1) * rate + y1;
				tp2.x = (m_Doc->v_line[index].p2.x - x1) * rate + x1;
				tp2.y = (m_Doc->v_line[index].p2.y - y1) * rate + y1;
				m_Doc->line_cpen(dc1, m_Doc->v_line[index].color, tp1, tp2, m_Doc->v_line[index].size);
				
			}
			else if (m_Doc->selected_circle != -1)
			{
				index = m_Doc->selected_circle;
				m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, oldradius, m_Doc->v_circle[index].size);
				int x1 = m_Doc->v_circle[index].p0.x,
					y1 = m_Doc->v_circle[index].p0.y;
				double dis1 = sqrt((oldpoint.x - x1) * (oldpoint.x - x1) + (oldpoint.y - y1) * (oldpoint.y - y1)),
					dis2 = sqrt((point.x - x1) * (point.x - x1) + (point.y - y1) * (point.y - y1));
				double rate = dis2 / dis1;
				oldradius = m_Doc->v_circle[index].radius * rate;
				m_Doc->circle_cpen(dc1, m_Doc->v_circle[index].color, m_Doc->v_circle[index].p0, oldradius, m_Doc->v_circle[index].size);
			}
			else if (m_Doc->selected_ellipse != -1)
			{
				index = m_Doc->selected_ellipse;
				m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, ta, tb, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
				int x1 = m_Doc->v_ellipse[index].p0.x,
					y1 = m_Doc->v_ellipse[index].p0.y;
				double dis1 = sqrt((oldpoint.x - x1) * (oldpoint.x - x1) + (oldpoint.y - y1) * (oldpoint.y - y1)),
					dis2 = sqrt((point.x - x1) * (point.x - x1) + (point.y - y1) * (point.y - y1));
				double rate = dis2 / dis1;
				ta = m_Doc->v_ellipse[index].a * rate;
				tb = m_Doc->v_ellipse[index].b * rate;
				m_Doc->ellipse_cpen(dc1, m_Doc->v_ellipse[index].color, m_Doc->v_ellipse[index].p0.x, m_Doc->v_ellipse[index].p0.y, ta, tb, m_Doc->v_ellipse[index].angle, m_Doc->v_ellipse[index].size);
			}
			else if (m_Doc->selected_polygon != -1)
			{
				index = m_Doc->selected_polygon;
				m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
				int mid_x = 0, mid_y = 0;
				for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++) {
					mid_x += m_Doc->v_polygon[index].ps[i].x;
					mid_y += m_Doc->v_polygon[index].ps[i].y;
				}
				mid_x /= m_Doc->v_polygon[index].ps.size();
				mid_y /= m_Doc->v_polygon[index].ps.size();
				double dis1 = sqrt((oldpoint.x - mid_x) * (oldpoint.x - mid_x) + (oldpoint.y - mid_y) * (oldpoint.y - mid_y)),
					dis2 = sqrt((point.x - mid_x) * (point.x - mid_x) + (point.y - mid_y) * (point.y - mid_y));
				double rate = dis2 / dis1;
				tpolygon = m_Doc->v_polygon[index];
				for (int i = 0; i < m_Doc->v_polygon[index].ps.size(); i++) {
					tpolygon.ps[i].x = (m_Doc->v_polygon[index].ps[i].x - mid_x) * rate + mid_x;
					tpolygon.ps[i].y = (m_Doc->v_polygon[index].ps[i].y - mid_y) * rate + mid_y;
				}
				m_Doc->polygon_cpen(dc1, tpolygon, m_Doc->v_polygon[index].color, m_Doc->v_polygon[index].size);
			}
		}

	ReleaseDC(dc1);
	CView::OnMouseMove(nFlags, point);
}


void CDrawView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDC* dc1 = GetDC();
	if (m_Doc->m_type == 41 || m_Doc->m_type == 5)
	{
		m_Doc->line_cpen(dc1, m_Doc->m_color, newpoint, originpoint, m_Doc->m_size);
		m_Doc->tri_vtx = 1;
		m_Doc->is_d_polygon = FALSE;
		m_Doc->v_polygon.push_back(CDrawDoc::d_polygon(polygon_vtx, m_Doc->m_size, m_Doc->m_color));
	}

	ReleaseDC(dc1);
	CView::OnLButtonDblClk(nFlags, point);
}
