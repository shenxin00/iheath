#pragma once


// CVlcCtlDlg �Ի���

class CVlcCtlDlg : public CDialog
{
	DECLARE_DYNAMIC(CVlcCtlDlg)

public:
	CVlcCtlDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVlcCtlDlg();
	CBitmapButton ctlButton;
	bool	m_mounse_in;
// �Ի�������
	enum { IDD = IDD_DIALOG_CTL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual BOOL OnInitDialog();
	afx_msg void OnMouseLeave();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
