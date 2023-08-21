#pragma once


// CAngleChoose 对话框

class CAngleChoose : public CDialogEx
{
	DECLARE_DYNAMIC(CAngleChoose)

public:
	CAngleChoose(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAngleChoose();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAngleChoose };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UINT m_nAngle;
};
