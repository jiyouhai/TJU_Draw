// AngleChoose.cpp: 实现文件
//

#include "pch.h"             // 包含预编译头文件
#include "Draw.h"            // 包含Draw项目的头文件
#include "AngleChoose.h"     // 包含CAngleChoose类的声明
#include "afxdialogex.h"     // 包含MFC对话框的扩展

// CAngleChoose 对话框

IMPLEMENT_DYNAMIC(CAngleChoose, CDialogEx) // 使用宏实现CAngleChoose类的动态创建

// 构造函数，接受一个父窗口指针，并调用基类构造函数初始化对话框资源ID和父窗口
CAngleChoose::CAngleChoose(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_CAngleChoose, pParent) // 初始化对话框资源ID
    , m_nAngle(0)                         // 初始化角度成员变量为0
{

}

// 析构函数
CAngleChoose::~CAngleChoose()
{
}

// DoDataExchange成员函数用于在控件和变量之间进行数据交换
void CAngleChoose::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);       // 调用基类的函数
    DDX_Text(pDX, IDC_EDIT1, m_nAngle);   // 关联编辑框控件IDC_EDIT1和成员变量m_nAngle
}

// 消息映射宏，定义消息处理程序的映射关系
BEGIN_MESSAGE_MAP(CAngleChoose, CDialogEx)
END_MESSAGE_MAP()

// CAngleChoose 消息处理程序
