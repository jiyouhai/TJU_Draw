// Draw.h: Draw 应用程序的主头文件

#pragma once // 确保头文件只被编译一次

#ifndef __AFXWIN_H__
    #error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif
// 如果未包括MFC的头文件，则引发错误

#include "resource.h" // 包含主符号，通常用于资源（如图标，位图等）的定义

// CDrawApp:
// 有关此类的实现，请参阅 Draw.cpp
//

class CDrawApp : public CWinApp // CDrawApp类派生自MFC的CWinApp类，代表整个应用程序
{
public:
    CDrawApp() noexcept; // 构造函数，使用noexcept说明不抛出异常

// 重写
public:
    virtual BOOL InitInstance(); // 重写初始化实例函数，进行应用程序的初始化
    virtual int ExitInstance();  // 重写退出实例函数，在应用程序关闭时调用

// 实现
    afx_msg void OnAppAbout(); // "关于"对话框的消息处理函数
    DECLARE_MESSAGE_MAP()      // 声明消息映射宏，用于处理Windows消息
};

extern CDrawApp theApp; // 定义全局的应用程序对象
