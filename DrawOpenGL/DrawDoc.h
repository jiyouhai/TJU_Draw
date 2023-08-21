
// DrawDoc.h : interface of the CDrawDoc class
//


#pragma once


class CDrawDoc : public CDocument
{
protected: // create from serialization only
	CDrawDoc() noexcept;
	DECLARE_DYNCREATE(CDrawDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDrawDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
// Custom data structure


	// vertex of polygon
	struct vertex
	{
		int x, y;
		vertex() {}
		vertex(int xx, int yy)
		{
			this->x = xx;
			this->y = yy;
		}
	};


	// polygon
	struct polygon
	{
		int vertex_num;
		std::vector<vertex> vertexes;

		polygon() {}
		polygon(int n, std::vector<vertex> v)
		{
			this->vertex_num = n;
			this->vertexes = v;
		}
	};


	
	// data structure of drawing directly
	struct d_line
	{
		CPoint p1, p2;
		int size;
		COLORREF color;

		d_line() {}
		d_line(CPoint p1, CPoint p2, int size, COLORREF color) 
		{
			this->p1 = p1;
			this->p2 = p2;
			this->size = size;
			this->color = color;
		}

	};

	struct d_circle
	{
		CPoint p0;
		int radius;
		int size;
		COLORREF color;

		d_circle() {}
		d_circle(CPoint p0, int radius, int size, COLORREF color) 
		{
			this->p0 = p0;
			this->radius = radius;
			this->size = size;
			this->color = color;
		}
	};

	struct d_polygon
	{
		std::vector<CPoint> ps;
		int size;
		COLORREF color;

		d_polygon() {}
		d_polygon(std::vector<CPoint> ps, int size, COLORREF color)
		{
			this->ps = ps;
			this->size = size;
			this->color = color;
		}
	};

	struct d_ellipse
	{
		CPoint p0;
		int a, b;
		int angle;
		COLORREF color;
		int size;

		d_ellipse() {};
		d_ellipse(CPoint p0, int a, int b, int angle,  int size, COLORREF color)
		{
			this->p0 = p0;
			this->a = a;
			this->b = b;
			this->angle = angle;
			this->size = size;
			this->color = color;
		}
	};

	struct d_fill
	{
		CPoint p;
		COLORREF color;

		d_fill() {}
		d_fill(CPoint p, COLORREF color)
		{
			this->p = p;
			this->color = color;
		}
	};





public:
	
	double pi = acos(-1.0);

	// Store all drawing content

	std::vector<d_line> v_line;
	std::vector<d_circle> v_circle;
	std::vector<d_polygon> v_polygon;
	std::vector<d_ellipse> v_ellipse;
	std::vector<d_fill> v_fill;

	// 1 = point, 2 = line, 3 = circle
	// 41 = random triangle, 42 = right triangle, 43 = isosceles, 44 = equilateral
	// 5 = polygon, 6 = ellipse, 7 = rectangle, 8 = square
	// 50 = fill
	// 100 = translate, 101 = translate (exact)
	// 200 = rotate, 201 = rotate (exact)
	// 300 = scale, 301 = scale (exact)
	// 500 = border color
	int m_type;

	// color
	COLORREF m_color;
	COLORREF m_newcolor;

	// thickness
	int m_size;

	// rotate angle
	int r_angle;

	// scale rate
	double s_rate;

	// translate movement
	int rl_move;
	int ud_move;

	// is drawing polygon?
	BOOL is_d_polygon = FALSE;

	// vertex num of triangle
	int tri_vtx = 0;

	// get rotated point
	CPoint get_rotated_point(CPoint p, CPoint p0, int angle);

	// cpen function
	void line_cpen(CDC* pDC, COLORREF color, CPoint p1, CPoint p2, int size);
	void circle_cpen(CDC* pDC, COLORREF color, CPoint p0, int radius, int size);
	void ellipse_cpen(CDC* pDC, COLORREF color, float x0, float y0, float a, float b, double angle, int size);
	void triangle_cpen(CDC* pDC, COLORREF color, CPoint points[3], int size);


	// selected shape
	int selected_point = -1, selected_line = -1, selected_circle = -1, selected_ellipse = -1;
	int selected_polygon = -1;



	

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	void dot(CDC* pDC, COLORREF color, int x, int y, int size);
	void rectangle_cpen(CDC* pDC, COLORREF color, CPoint x0, CPoint y0, int size);
	void polygon_cpen(CDC* pDC, d_polygon p, COLORREF color, int size);
	int select_line(CPoint pos);
	int select_circle(CPoint pos);
	void select_shape(CDC* pDC, CPoint point);
	int select_ellipse(CPoint pos);
	int select_polygon(CPoint pos);
	void translate_line(std::vector<d_line>& v_line, int index, CPoint point);
	void flush_all(CDC* pDC);
	void fill_brush(CDC* pDC, COLORREF color, COLORREF color_cleared, CPoint point);
	void translate_circle(std::vector<d_circle>& v_circle, int index, CPoint point);
	void translate_ellipse(std::vector<d_ellipse>& v_ellipse, int index, CPoint point);
	void translate_polygon(std::vector<d_polygon>& v_polygon, int index, CPoint point);
	void rotate_line(std::vector<d_line>& v_line, int index, CPoint oldpoint, CPoint point);
	void rotate_ellipse(std::vector<d_ellipse>& v_ellipse, int index, CPoint oldpoint, CPoint point);
	void rotate_polygon(std::vector<d_polygon>& v_polygon, int index, CPoint oldpoint, CPoint point);
	void scale_line(std::vector<d_line>& v_line, int index, CPoint oldpoint, CPoint point);
	void scale_circle(std::vector<d_circle>& v_circle, int index, CPoint oldpoint, CPoint point);
	void scale_ellipse(std::vector<d_ellipse>& v_ellipse, int index, CPoint oldpoint, CPoint point);
	void scale_polygon(std::vector<d_polygon>& v_polygon, int index, CPoint oldpoint, CPoint point);
	void changecolor_line(std::vector<d_line>& v_line, int index, COLORREF m_newcolor);
	void changecolor_circle(std::vector<d_circle>& v_circle, int index, COLORREF m_newcolor);
	void changecolor_ellipse(std::vector<d_ellipse>& v_ellipse, int index, COLORREF m_newcolor);
	void changecolor_polygon(std::vector<d_polygon>& v_polygon, int index, COLORREF m_newcolor);
};
