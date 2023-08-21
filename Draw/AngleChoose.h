#pragma once // 防止头文件重复包含

// CAngleChoose 对话框

class CAngleChoose : public CDialogEx // CAngleChoose类派生自CDialogEx，用于创建对话框
{
    DECLARE_DYNAMIC(CAngleChoose) // 宏，用于在运行时支持动态创建对象

public:
    CAngleChoose(CWnd* pParent = nullptr); // 标准构造函数，可以接受父窗口指针，默认为nullptr
    virtual ~CAngleChoose();               // 虚析构函数，确保适当的析构

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_CAngleChoose }; // 枚举值，定义了与这个类关联的对话框资源的ID
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV支持，用于控件与成员变量之间的数据交换

    DECLARE_MESSAGE_MAP() // 宏，声明用于消息映射的函数，例如响应按钮点击等事件
public:
    UINT m_nAngle; // 公共成员变量，存储与对话框关联的角度值
};
