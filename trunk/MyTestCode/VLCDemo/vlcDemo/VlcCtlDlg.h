#pragma once


// CVlcCtlDlg 对话框

class CVlcCtlDlg : public CDialog
{
	DECLARE_DYNAMIC(CVlcCtlDlg)

public:
	CVlcCtlDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVlcCtlDlg();
	CBitmapButton ctlButton;
	bool	m_mounse_in;
// 对话框数据
	enum { IDD = IDD_DIALOG_CTL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
