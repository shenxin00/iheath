#pragma once


// CVlcMainDlg �Ի���

class CVlcMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CVlcMainDlg)

public:
	CVlcMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVlcMainDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_VLC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
