#pragma once
#include "MyButton.h"
#include "shockwaveflash1.h"


// testDlg �Ի���

class testDlg : public CDialog
{
	DECLARE_DYNAMIC(testDlg)

public:
	testDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~testDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };	
	CMyButton			m_mybtn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CShockwaveflash1 myplayer;
	afx_msg void OnBnDoubleclickedButton3();
};
