// Draw.cpp: 定义应用程序的类行为。
//

#include "pch.h" // 预编译头文件
#include "framework.h" // 应用程序框架
#include "afxwinappex.h" // Windows应用程序类
#include "afxdialogex.h" // 对话框支持
#include "Draw.h" // 主头文件
#include "MainFrm.h" // 主框架窗口类

#include "DrawDoc.h" // 文档类
#include "DrawView.h" // 视图类

#ifdef _DEBUG
#define new DEBUG_NEW // 调试新运算符
#endif

// CDrawApp

BEGIN_MESSAGE_MAP(CDrawApp, CWinApp) // 消息映射开始
    ON_COMMAND(ID_APP_ABOUT, &CDrawApp::OnAppAbout) // "关于"命令映射
    ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew) // "新建"命令映射
    ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen) // "打开"命令映射
    ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup) // "打印设置"命令映射
END_MESSAGE_MAP() // 消息映射结束

// CDrawApp 构造

CDrawApp::CDrawApp() noexcept
{
    // 支持重新启动管理器
    m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
    // 公共语言运行时支持
    System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif
    SetAppID(_T("Draw.AppID.NoVersion")); // 设置应用程序ID
}

// 唯一的 CDrawApp 对象

CDrawApp theApp; // 应用程序对象

// CDrawApp 初始化

BOOL CDrawApp::InitInstance()
{
    // 初始化常见控件
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    // OLE库初始化
    if (!AfxOleInit())
    {
        AfxMessageBox(IDP_OLE_INIT_FAILED); // 错误消息框
        return FALSE;
    }

    AfxEnableControlContainer(); // 启用控件容器
    EnableTaskbarInteraction(FALSE); // 禁用任务栏交互
    SetRegistryKey(_T("应用程序向导生成的本地应用程序")); // 注册表键设置
    LoadStdProfileSettings(4);  // 加载标准INI文件选项

    // 注册文档模板
    CSingleDocTemplate* pDocTemplate;
    pDocTemplate = new CSingleDocTemplate(
        IDR_MAINFRAME,
        RUNTIME_CLASS(CDrawDoc),
        RUNTIME_CLASS(CMainFrame), // 主SDI框架窗口
        RUNTIME_CLASS(CDrawView));
    if (!pDocTemplate)
        return FALSE;
    AddDocTemplate(pDocTemplate);

    // 分析命令行参数
    CCommandLineInfo cmdInfo;
    ParseCommandLine(cmdInfo);

    // 处理Shell命令
    if (!ProcessShellCommand(cmdInfo))
        return FALSE;

    m_pMainWnd->ShowWindow(SW_SHOW); // 显示主窗口
    m_pMainWnd->UpdateWindow(); // 更新主窗口
    return TRUE;
}

int CDrawApp::ExitInstance()
{
    AfxOleTerm(FALSE); // 终止OLE库
    return CWinApp::ExitInstance(); // 退出实例
}

// CDrawApp 消息处理程序
// "关于"对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg() noexcept;

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX); // 数据交换支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CDrawApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CDrawApp 消息处理程序





