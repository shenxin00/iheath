#pragma once


// CVlcMainDlg 对话框

class CVlcMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CVlcMainDlg)

public:
	CVlcMainDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVlcMainDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_VLC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
