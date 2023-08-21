// DrawDoc.cpp: CDrawDoc 类的实现
// 定义了文档类，该类可以存储、加载和处理文档相关的操作。

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 允许与 ATL 项目共享文档代码。
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

// CDrawDoc 构造/析构

CDrawDoc::CDrawDoc() noexcept
{
    // 一次性构造代码，你可以在此处添加初始化代码
}

CDrawDoc::~CDrawDoc()
{
}

BOOL CDrawDoc::OnNewDocument()
{
    if (!CDocument::OnNewDocument())
        return FALSE;

    // 重新初始化代码（SDI 文档将重用此文档）

    return TRUE;
}

// CDrawDoc 序列化

void CDrawDoc::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        // 存储代码，用于保存文档状态
    }
    else
    {
        // 加载代码，用于从文件加载文档状态
    }
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDrawDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
    // 绘制文档数据的缩略图
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

// 搜索处理程序的支持
void CDrawDoc::InitializeSearchContent()
{
    CString strSearchContent;
    // 设置搜索内容，内容部分应由“;”分隔
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

// CDrawDoc 诊断

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

// CDrawDoc 命令
