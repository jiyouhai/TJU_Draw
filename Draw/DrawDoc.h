// DrawDoc.h: CDrawDoc 类的接口
// 定义应用程序的文档类，负责管理和存储文档状态。

#pragma once

// CDrawDoc类声明，继承自CDocument类
class CDrawDoc : public CDocument
{
protected:
    CDrawDoc() noexcept; // 默认构造函数，用于序列化
    DECLARE_DYNCREATE(CDrawDoc) // 动态创建类实例

// 公共成员变量
public:

// 公共成员函数
public:

// 虚拟重写函数
public:
    virtual BOOL OnNewDocument(); // 创建新文档时的处理
    virtual void Serialize(CArchive& ar); // 文档的序列化操作

#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent(); // 初始化文档搜索内容
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds); // 为文档绘制缩略图
#endif // SHARED_HANDLERS

// 析构函数
public:
    virtual ~CDrawDoc(); // 析构函数，清理资源

#ifdef _DEBUG
    virtual void AssertValid() const; // 调试时检查对象的有效性
    virtual void Dump(CDumpContext& dc) const; // 调试时转储对象状态
#endif

// 保护区域
protected:
    DECLARE_MESSAGE_MAP() // 消息映射宏，将消息映射到处理函数

#ifdef SHARED_HANDLERS
    void SetSearchContent(const CString& value); // 设置搜索内容的辅助函数
#endif // SHARED_HANDLERS
};
