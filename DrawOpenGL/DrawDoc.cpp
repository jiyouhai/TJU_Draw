
// DrawDoc.cpp : implementation of the CDrawDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDrawDoc

IMPLEMENT_DYNCREATE(CDrawDoc, CDocument)

BEGIN_MESSAGE_MAP(CDrawDoc, CDocument)
END_MESSAGE_MAP()


// CDrawDoc construction/destruction

CDrawDoc::CDrawDoc() noexcept
{
	// TODO: add one-time construction code here

}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDrawDoc serialization

void CDrawDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDrawDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDrawDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDrawDoc diagnostics

#ifdef _DEBUG
void CDrawDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDrawDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDrawDoc commands



// cpen function
void CDrawDoc::line_cpen(CDC* pDC, COLORREF color, CPoint p1, CPoint p2, int size)
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

	pDC->MoveTo(p1);
	pDC->LineTo(p2);

	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}




void CDrawDoc::circle_cpen(CDC* pDC, COLORREF color, CPoint p0, int radius, int size) 
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	pDC->Arc(CRect(p0.x - radius, p0.y - radius, p0.x + radius, p0.y + radius), CPoint(0, 0), CPoint(0, 0));
	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}



void CDrawDoc::ellipse_cpen(CDC* pDC, COLORREF color, float x0, float y0, float a, float b, double angle, int size)
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

	int i;
	float x, y;
	double dx, dy, di, aa, bb, sinA, cosA;
	double arc = pi / 180.0 * angle; //转弧度制
	cosA = cos(arc);
	sinA = sin(arc);
	aa = a * a;
	bb = b * b;
	float flX[4], flY[4];
	x = 0;
	y = b;
	dx = 0;
	dy = 2 * aa * y;
	di = bb - aa * b + aa / 4;
	flX[0] = x0 + x * cosA - y * sinA;
	flX[1] = x0 + x * cosA + y * sinA;
	flX[2] = x0 - x * cosA - y * sinA;
	flX[3] = x0 - x * cosA + y * sinA;
	flY[0] = y0 + y * cosA + x * sinA;
	flY[1] = y0 - y * cosA + x * sinA;
	flY[2] = y0 + y * cosA - x * sinA;
	flY[3] = y0 - y * cosA - x * sinA;
	i = 0;
	while (dx < dy)
	{
		i++;
		if (i == 5)
		{
			pDC->MoveTo(flX[0], flY[0]);
			pDC->LineTo(x0 + x * cosA - y * sinA, y0 + y * cosA + x * sinA);
			pDC->MoveTo(flX[1], flY[1]);
			pDC->LineTo(x0 + x * cosA + y * sinA, y0 - y * cosA + x * sinA);
			pDC->MoveTo(flX[2], flY[2]);
			pDC->LineTo(x0 - x * cosA - y * sinA, y0 + y * cosA - x * sinA);
			pDC->MoveTo(flX[3], flY[3]);
			pDC->LineTo(x0 - x * cosA + y * sinA, y0 - y * cosA - x * sinA);
			flX[0] = x0 + x * cosA - y * sinA;
			flX[1] = x0 + x * cosA + y * sinA;
			flX[2] = x0 - x * cosA - y * sinA;
			flX[3] = x0 - x * cosA + y * sinA;
			flY[0] = y0 + y * cosA + x * sinA;
			flY[1] = y0 - y * cosA + x * sinA;
			flY[2] = y0 + y * cosA - x * sinA;
			flY[3] = y0 - y * cosA - x * sinA;
			i = 0;
		}
		x++;
		dx += 2 * bb;
		di += dx + bb;
		if (di >= 0)
		{
			dy -= 2 * aa;
			di -= dy;
			y--;
		}
	}
	pDC->MoveTo(flX[0], flY[0]);
	pDC->LineTo(x0 + x * cosA - y * sinA, y0 + y * cosA + x * sinA);
	pDC->MoveTo(flX[1], flY[1]);
	pDC->LineTo(x0 + x * cosA + y * sinA, y0 - y * cosA + x * sinA);
	pDC->MoveTo(flX[2], flY[2]);
	pDC->LineTo(x0 - x * cosA - y * sinA, y0 + y * cosA - x * sinA);
	pDC->MoveTo(flX[3], flY[3]);
	pDC->LineTo(x0 - x * cosA + y * sinA, y0 - y * cosA - x * sinA);

	di += int((3 * (aa - bb) - 2 * (dx - dy)) / 4 + 0.5);
	flX[0] = x0 + x * cosA - y * sinA;
	flX[1] = x0 + x * cosA + y * sinA;
	flX[2] = x0 - x * cosA - y * sinA;
	flX[3] = x0 - x * cosA + y * sinA;
	flY[0] = y0 + y * cosA + x * sinA;
	flY[1] = y0 - y * cosA + x * sinA;
	flY[2] = y0 + y * cosA - x * sinA;
	flY[3] = y0 - y * cosA - x * sinA;
	i = 0;
	while (y >= 0)
	{
		i++;
		if (i == 5)
		{
			pDC->MoveTo(flX[0], flY[0]);
			pDC->LineTo(x0 + x * cosA - y * sinA, y0 + y * cosA + x * sinA);
			pDC->MoveTo(flX[1], flY[1]);
			pDC->LineTo(x0 + x * cosA + y * sinA, y0 - y * cosA + x * sinA);
			pDC->MoveTo(flX[2], flY[2]);
			pDC->LineTo(x0 - x * cosA - y * sinA, y0 + y * cosA - x * sinA);
			pDC->MoveTo(flX[3], flY[3]);
			pDC->LineTo(x0 - x * cosA + y * sinA, y0 - y * cosA - x * sinA);
			flX[0] = x0 + x * cosA - y * sinA;
			flX[1] = x0 + x * cosA + y * sinA;
			flX[2] = x0 - x * cosA - y * sinA;
			flX[3] = x0 - x * cosA + y * sinA;
			flY[0] = y0 + y * cosA + x * sinA;
			flY[1] = y0 - y * cosA + x * sinA;
			flY[2] = y0 + y * cosA - x * sinA;
			flY[3] = y0 - y * cosA - x * sinA;
			i = 0;
		}
		y--;
		dy -= 2 * aa;
		di += aa - dy;
		if (di < 0)
		{
			dx += 2 * bb;
			di += dx;
			x++;
		}
	}
	pDC->MoveTo(flX[0], flY[0]);
	pDC->LineTo(x0 + x * cosA - y * sinA, y0 + y * cosA + x * sinA);
	pDC->MoveTo(flX[1], flY[1]);
	pDC->LineTo(x0 + x * cosA + y * sinA, y0 - y * cosA + x * sinA);
	pDC->MoveTo(flX[2], flY[2]);
	pDC->LineTo(x0 - x * cosA - y * sinA, y0 + y * cosA - x * sinA);
	pDC->MoveTo(flX[3], flY[3]);
	pDC->LineTo(x0 - x * cosA + y * sinA, y0 - y * cosA - x * sinA);
	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
	return;
}


void CDrawDoc::polygon_cpen(CDC* pDC, d_polygon p, COLORREF color, int size)
{

	if (p.ps.size() == 0)
		return;
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);

	pDC->MoveTo(p.ps[0]);
	for (int i = 0; i < p.ps.size(); i++) 
		pDC->LineTo(p.ps[i]);
	pDC->LineTo(p.ps[0]);

	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
}

void CDrawDoc::rectangle_cpen(CDC* pDC, COLORREF color, CPoint x0, CPoint y0, int size)
{
	// TODO: Add your implementation code here.
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	
	//pDC->MoveTo(x0);
	//pDC->LineTo(CPoint(x0.x, y0.y));
	//pDC->MoveTo(CPoint(x0.x, y0.y));
	//pDC->LineTo(y0);
	//pDC->MoveTo(y0);
	//pDC->LineTo(CPoint(y0.x, x0.y));
	//pDC->MoveTo(CPoint(y0.x, x0.y));
	//pDC->LineTo(x0);

	pDC->Rectangle(CRect(x0, y0));
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CDrawDoc::triangle_cpen(CDC* pDC, COLORREF color, CPoint points[3], int size)
{
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Polygon(points, 3);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}






// draw a dot (CPen)
void CDrawDoc::dot(CDC* pDC, COLORREF color, int x, int y, int size)
{
	// TODO: Add your implementation code here.
	CPen cpen;
	cpen.CreatePen(PS_SOLID, size, color);
	CPen* pOldPen = (CPen*)pDC->SelectObject(&cpen);
	pDC->MoveTo(x, y);
	pDC->LineTo(x, y);
	pDC->SelectObject(pOldPen);
	cpen.DeleteObject();
	return;
}



// get rotated point
CPoint CDrawDoc::get_rotated_point(CPoint p, CPoint p0, int angle)
{
	double arc = pi / 180.0 * angle;
	double pxx = p0.x + (p.x - p0.x) * std::cos(arc) - (p.y - p0.y) * std::sin(arc);
	double pyy = p0.y + (p.x - p0.x) * std::sin(arc) + (p.y - p0.y) * std::cos(arc);
	return CPoint(pxx, pyy);
}

// select a shape
void CDrawDoc::select_shape(CDC* pDC, CPoint point)
{
	// TODO: Add your implementation code here.
	int sl = select_line(point);
	int sc = select_circle(point);
	int se = select_ellipse(point);
	int sp = select_polygon(point);

	COLORREF co = RGB(255, 0, 128);

	// line
	if (sl != -1)
	{
		line_cpen(pDC, co, v_line[sl].p1, v_line[sl].p2, v_line[sl].size);

	}
	if (selected_line != -1 && selected_line != sl)
	{
		int msl = selected_line;
		line_cpen(pDC, v_line[msl].color, v_line[msl].p1, v_line[msl].p2, v_line[msl].size);
	}

	// circle
	if (sc != -1)
	{
		circle_cpen(pDC, co, v_circle[sc].p0, v_circle[sc].radius, v_circle[sc].size);
		se = sp = -1;
	}
	if (selected_circle != -1 && selected_circle != sc)
	{
		int mspc = selected_circle;
		circle_cpen(pDC, v_circle[mspc].color, v_circle[mspc].p0, v_circle[mspc].radius, v_circle[mspc].size);
	}

	// ellipse
	if (se != -1)
	{
		ellipse_cpen(pDC, co, v_ellipse[se].p0.x, v_ellipse[se].p0.y, v_ellipse[se].a, v_ellipse[se].b, v_ellipse[se].angle, v_ellipse[se].size);
		sp = -1;
	}
	if (selected_ellipse != -1 && selected_ellipse != se)
	{
		ellipse_cpen(pDC, v_ellipse[selected_ellipse].color, v_ellipse[selected_ellipse].p0.x, v_ellipse[selected_ellipse].p0.y, v_ellipse[selected_ellipse].a, v_ellipse[selected_ellipse].b, v_ellipse[selected_ellipse].angle, v_ellipse[selected_ellipse].size);
	}

	// polygon
	if (sp != -1) {
		polygon_cpen(pDC, v_polygon[sp], co, v_polygon[sp].size);
	}
	if (selected_polygon != -1 && selected_polygon != sp) {
		polygon_cpen(pDC, v_polygon[selected_polygon], v_polygon[selected_polygon].color, v_polygon[selected_polygon].size);
	}

	selected_point = sp;
	selected_line = sl;
	selected_circle = sc;
	selected_ellipse = se;
	selected_polygon = sp;
}


int CDrawDoc::select_line(CPoint pos)
{
	// TODO: Add your implementation code here.
	double am = 0.0, bm = 0.0, ab = 0.0;
	for (int i = 0; i < v_line.size(); i++)
	{
		am = sqrt((v_line[i].p1.x - pos.x) * (v_line[i].p1.x - pos.x) + (v_line[i].p1.y - pos.y) * (v_line[i].p1.y - pos.y));
		bm = sqrt((v_line[i].p2.x - pos.x) * (v_line[i].p2.x - pos.x) + (v_line[i].p2.y - pos.y) * (v_line[i].p2.y - pos.y));
		ab = sqrt((v_line[i].p1.x - v_line[i].p2.x) * (v_line[i].p1.x - v_line[i].p2.x) + (v_line[i].p1.y - v_line[i].p2.y) * (v_line[i].p1.y - v_line[i].p2.y));
		if (abs(am + bm - ab) < 5.0)
			return i;
	}
	return -1;
}


int CDrawDoc::select_circle(CPoint pos)
{
	// TODO: Add your implementation code here.
	double dis = 0.0;
	for (int i = 0; i < v_circle.size(); i++)
	{
		dis = sqrt((v_circle[i].p0.x - pos.x) * (v_circle[i].p0.x - pos.x) + (v_circle[i].p0.y - pos.y) * (v_circle[i].p0.y - pos.y));
		if (abs(dis - v_circle[i].radius) < (v_circle[i].size / 2.0 + 5.0))
			return i;
	}
	
	return -1;
}








int CDrawDoc::select_ellipse(CPoint pos)
{
	// TODO: Add your implementation code here.
	CPoint poss;
	double check = 0.0, t1 = 0.0, t2 = 0.0;
	for (int i = 0; i < v_ellipse.size(); i++)
	{
		poss = get_rotated_point(pos, v_ellipse[i].p0, v_ellipse[i].angle);
		t1 = poss.x - v_ellipse[i].p0.x;
		t2 = poss.y - v_ellipse[i].p0.y;
		check = ((double)(t1 * t1) / (double)(v_ellipse[i].a * v_ellipse[i].a)) + ((double)(t2 * t2) / (double)(v_ellipse[i].b * v_ellipse[i].b));

		if (check >= 0.8 && check <= 1.2)
			return i;
	}

	return -1;
}


int CDrawDoc::select_polygon(CPoint pos)
{
	// TODO: Add your implementation code here.
	double am = 0.0, bm = 0.0, ab = 0.0;
	for (int i = 0; i < v_polygon.size(); i++)
	{
		for (int j = 0; j < v_polygon[i].ps.size() - 1; j++)
		{
			am = sqrt((v_polygon[i].ps[j].x - pos.x) * (v_polygon[i].ps[j].x - pos.x) + (v_polygon[i].ps[j].y - pos.y) * (v_polygon[i].ps[j].y - pos.y));
			bm = sqrt((v_polygon[i].ps[j + 1].x - pos.x) * (v_polygon[i].ps[j + 1].x - pos.x) + (v_polygon[i].ps[j + 1].y - pos.y) * (v_polygon[i].ps[j + 1].y - pos.y));
			ab = sqrt((v_polygon[i].ps[j].x - v_polygon[i].ps[j + 1].x) * (v_polygon[i].ps[j].x - v_polygon[i].ps[j + 1].x) + (v_polygon[i].ps[j].y - v_polygon[i].ps[j + 1].y) * (v_polygon[i].ps[j].y - v_polygon[i].ps[j + 1].y));
			if (abs(am + bm - ab) < 5.0)
				return i;
		}
		am = sqrt((v_polygon[i].ps[0].x - pos.x) * (v_polygon[i].ps[0].x - pos.x) + (v_polygon[i].ps[0].y - pos.y) * (v_polygon[i].ps[0].y - pos.y));
		bm = sqrt((v_polygon[i].ps[v_polygon[i].ps.size() - 1].x - pos.x) * (v_polygon[i].ps[v_polygon[i].ps.size() - 1].x - pos.x) + (v_polygon[i].ps[v_polygon[i].ps.size() - 1].y - pos.y) * (v_polygon[i].ps[v_polygon[i].ps.size() - 1].y - pos.y));
		ab = sqrt((v_polygon[i].ps[v_polygon[i].ps.size() - 1].x - v_polygon[i].ps[0].x) * (v_polygon[i].ps[v_polygon[i].ps.size() - 1].x - v_polygon[i].ps[0].x) + (v_polygon[i].ps[v_polygon[i].ps.size() - 1].y - v_polygon[i].ps[0].y) * (v_polygon[i].ps[v_polygon[i].ps.size() - 1].y - v_polygon[i].ps[0].y));
		if (abs(am + bm - ab) < 5.0)
			return i;
	}
	return -1;
}

// flush
void CDrawDoc::flush_all(CDC* pDC)
{
	// TODO: Add your implementation code here.
	for (int i = 0; i < v_line.size(); i++)
		line_cpen(pDC, v_line[i].color, v_line[i].p1, v_line[i].p2, v_line[i].size);

	for (int i = 0; i < v_circle.size(); i++)
		circle_cpen(pDC, v_circle[i].color, v_circle[i].p0, v_circle[i].radius, v_circle[i].size);

	for (int i = 0; i < v_ellipse.size(); i++)
		ellipse_cpen(pDC, v_ellipse[i].color, v_ellipse[i].p0.x, v_ellipse[i].p0.y, v_ellipse[i].a, v_ellipse[i].b, v_ellipse[i].angle, v_ellipse[i].size);

	for (int i = 0; i < v_polygon.size(); i++)
		polygon_cpen(pDC, v_polygon[i], v_polygon[i].color, v_polygon[i].size);
}


// fill
void CDrawDoc::fill_brush(CDC* pDC, COLORREF color, COLORREF color_cleared, CPoint point)
{
	// TODO: Add your implementation code here.
	CBrush cbrush;
	cbrush.CreateSolidBrush(color);
	CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&cbrush);

	pDC->ExtFloodFill(point.x, point.y, color_cleared, FLOODFILLSURFACE);

	pDC->SelectObject(pOldBrush);
	cbrush.DeleteObject();

	return;
}


// transform function

// translate
void CDrawDoc::translate_line(std::vector<d_line>& v_line, int index, CPoint point)
{
	// TODO: Add your implementation code here.
	int xm = (v_line[index].p1.x + v_line[index].p2.x) / 2,
		ym = (v_line[index].p1.y + v_line[index].p2.y) / 2;
	int delta_x = point.x - xm,
		delta_y = point.y - ym;
	v_line[index].p1.x += delta_x;
	v_line[index].p1.y += delta_y;
	v_line[index].p2.x += delta_x;
	v_line[index].p2.y += delta_y;
	return;
}


void CDrawDoc::translate_circle(std::vector<d_circle>& v_circle, int index, CPoint point)
{
	// TODO: Add your implementation code here.
	v_circle[index].p0.x = point.x;
	v_circle[index].p0.y = point.y;
	return;
}



void CDrawDoc::translate_ellipse(std::vector<d_ellipse>& v_ellipse, int index, CPoint point)
{
	// TODO: Add your implementation code here.
	v_ellipse[index].p0.x = point.x;
	v_ellipse[index].p0.y = point.y;
	return;
}


void CDrawDoc::translate_polygon(std::vector<d_polygon>& v_polygon, int index, CPoint point)
{
	// TODO: Add your implementation code here.
	int mid_x = 0, mid_y = 0;
	for (int i = 0; i < v_polygon[index].ps.size(); i++)
	{
		mid_x += v_polygon[index].ps[i].x;
		mid_y += v_polygon[index].ps[i].y;
	}
	mid_x /= v_polygon[index].ps.size();
	mid_y /= v_polygon[index].ps.size();
	int delta_x = point.x - mid_x,
		delta_y = point.y - mid_y;
	for (int i = 0; i < v_polygon[index].ps.size(); i++)
	{
		v_polygon[index].ps[i].x += delta_x;
		v_polygon[index].ps[i].y += delta_y;
	}
	return;
}



// rotate
void CDrawDoc::rotate_line(std::vector<d_line>& v_line, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int x1 = (v_line[index].p1.x + v_line[index].p2.x) / 2;
	int y1 = (v_line[index].p1.y + v_line[index].p2.y) / 2;
	double a = sqrt((x1 - point.x) * (x1 - point.x) + (y1 - point.y) * (y1 - point.y));
	double b = sqrt((oldpoint.x - point.x) * (oldpoint.x - point.x) + (oldpoint.y - point.y) * (oldpoint.y - point.y));
	double c = sqrt((x1 - oldpoint.x) * (x1 - oldpoint.x) + (y1 - oldpoint.y) * (y1 - oldpoint.y));
	double angle = (acos((a * a + c * c - b * b) / (2 * a * c)) / pi * 180.0);
	double angle_judge = (oldpoint.x - x1) * (point.y - y1) - (point.x - x1) * (oldpoint.y - y1); // >0顺时针，<0逆时针
	angle = (angle_judge >= 0.0 ? angle : -angle);
	v_line[index].p1 = get_rotated_point(v_line[index].p1, CPoint(x1, y1), angle);
	v_line[index].p2 = get_rotated_point(v_line[index].p2, CPoint(x1, y1), angle);
	return;
}


void CDrawDoc::rotate_ellipse(std::vector<d_ellipse>& v_ellipse, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int x1 = v_ellipse[index].p0.x;
	int y1 = v_ellipse[index].p0.y;
	double a = sqrt((x1 - point.x) * (x1 - point.x) + (y1 - point.y) * (y1 - point.y));
	double b = sqrt((oldpoint.x - point.x) * (oldpoint.x - point.x) + (oldpoint.y - point.y) * (oldpoint.y - point.y));
	double c = sqrt((x1 - oldpoint.x) * (x1 - oldpoint.x) + (y1 - oldpoint.y) * (y1 - oldpoint.y));
	double angle = (acos((a * a + c * c - b * b) / (2 * a * c)) / pi * 180.0);
	double angle_judge = (oldpoint.x - x1) * (point.y - y1) - (point.x - x1) * (oldpoint.y - y1); // >0顺时针，<0逆时针
	angle = (angle_judge >= 0.0 ? angle : -angle);
	v_ellipse[index].angle += angle;
	return;
}


void CDrawDoc::rotate_polygon(std::vector<d_polygon>& v_polygon, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int mid_x = 0, mid_y = 0;
	for (int i = 0; i < v_polygon[index].ps.size(); i++)
	{
		mid_x += v_polygon[index].ps[i].x;
		mid_y += v_polygon[index].ps[i].y;
	}
	mid_x /= v_polygon[index].ps.size();
	mid_y /= v_polygon[index].ps.size();

	double a = sqrt((mid_x - point.x) * (mid_x - point.x) + (mid_y - point.y) * (mid_y - point.y)),
		b = sqrt((oldpoint.x - point.x) * (oldpoint.x - point.x) + (oldpoint.y - point.y) * (oldpoint.y - point.y)),
		c = sqrt((mid_x - oldpoint.x) * (mid_x - oldpoint.x) + (mid_y - oldpoint.y) * (mid_y - oldpoint.y));
	double angle = (acos((a * a + c * c - b * b) / (2 * a * c)) / pi * 180.0);
	double angle_judge = (oldpoint.x - mid_x) * (point.y - mid_y) - (point.x - mid_x) * (oldpoint.y - mid_y); //>0顺时针，<0逆时针
	angle = (angle_judge >= 0.0 ? angle : -angle);
	for (int i = 0; i < v_polygon[index].ps.size(); i++)
		v_polygon[index].ps[i] = get_rotated_point(v_polygon[index].ps[i], CPoint(mid_x, mid_y), angle);
	return;
}



// scale
void CDrawDoc::scale_line(std::vector<d_line>& v_line, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int x1 = (v_line[index].p1.x + v_line[index].p2.x) / 2,
		y1 = (v_line[index].p1.y + v_line[index].p2.y) / 2;
	double dis1 = sqrt((oldpoint.x - x1) * (oldpoint.x - x1) + (oldpoint.y - y1) * (oldpoint.y - y1)),
		dis2 = sqrt((point.x - x1) * (point.x - x1) + (point.y - y1) * (point.y - y1));
	double rate = dis2 / dis1;
	v_line[index].p1.x = (v_line[index].p1.x - x1) * rate + x1;
	v_line[index].p1.y = (v_line[index].p1.y - y1) * rate + y1;
	v_line[index].p2.x = (v_line[index].p2.x - x1) * rate + x1;
	v_line[index].p2.y = (v_line[index].p2.y - y1) * rate + y1;
	return;
}


void CDrawDoc::scale_circle(std::vector<d_circle>& v_circle, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int x1 = v_circle[index].p0.x,
		y1 = v_circle[index].p0.y;
	double dis1 = sqrt((oldpoint.x - x1) * (oldpoint.x - x1) + (oldpoint.y - y1) * (oldpoint.y - y1)),
		dis2 = sqrt((point.x - x1) * (point.x - x1) + (point.y - y1) * (point.y - y1));
	double rate = dis2 / dis1;
	v_circle[index].radius *= rate;
	return;
}


void CDrawDoc::scale_ellipse(std::vector<d_ellipse>& v_ellipse, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int x1 = v_ellipse[index].p0.x,
		y1 = v_ellipse[index].p0.y;
	double dis1 = sqrt((oldpoint.x - x1) * (oldpoint.x - x1) + (oldpoint.y - y1) * (oldpoint.y - y1)),
		dis2 = sqrt((point.x - x1) * (point.x - x1) + (point.y - y1) * (point.y - y1));
	double rate = dis2 / dis1;
	v_ellipse[index].a *= rate;
	v_ellipse[index].b *= rate;
	return;
}


void CDrawDoc::scale_polygon(std::vector<d_polygon>& v_polygon, int index, CPoint oldpoint, CPoint point)
{
	// TODO: Add your implementation code here.
	int mid_x = 0, mid_y = 0;
	for (int i = 0; i < v_polygon[index].ps.size(); i++) {
		mid_x += v_polygon[index].ps[i].x;
		mid_y += v_polygon[index].ps[i].y;
	}
	mid_x /= v_polygon[index].ps.size();
	mid_y /= v_polygon[index].ps.size();
	double dis1 = sqrt((oldpoint.x - mid_x) * (oldpoint.x - mid_x) + (oldpoint.y - mid_y) * (oldpoint.y - mid_y)),
		dis2 = sqrt((point.x - mid_x) * (point.x - mid_x) + (point.y - mid_y) * (point.y - mid_y));
	double rate = dis2 / dis1;
	for (int i = 0; i < v_polygon[index].ps.size(); i++) {
		v_polygon[index].ps[i].x = (v_polygon[index].ps[i].x - mid_x) * rate + mid_x;
		v_polygon[index].ps[i].y = (v_polygon[index].ps[i].y - mid_y) * rate + mid_y;
	}
	return;
}



// change border color
void CDrawDoc::changecolor_line(std::vector<d_line>& v_line, int index, COLORREF m_newcolor)
{
	// TODO: Add your implementation code here.
	v_line[index].color = m_newcolor;
}

void CDrawDoc::changecolor_circle(std::vector<d_circle>& v_circle, int index, COLORREF m_newcolor)
{
	// TODO: Add your implementation code here.
	v_circle[index].color = m_newcolor;
}

void CDrawDoc::changecolor_ellipse(std::vector<d_ellipse>& v_ellipse, int index, COLORREF m_newcolor)
{
	// TODO: Add your implementation code here.
	v_ellipse[index].color = m_newcolor;
}

void CDrawDoc::changecolor_polygon(std::vector<d_polygon>& v_polygon, int index, COLORREF m_newcolor)
{
	// TODO: Add your implementation code here.
	v_polygon[index].color = m_newcolor;
}
