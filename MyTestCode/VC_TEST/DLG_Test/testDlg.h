#pragma once
#include "MyButton.h"
#include "shockwaveflash1.h"


// testDlg 对话框

class testDlg : public CDialog
{
	DECLARE_DYNAMIC(testDlg)

public:
	testDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~testDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };	
	CMyButton			m_mybtn;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CShockwaveflash1 myplayer;
	afx_msg void OnBnDoubleclickedButton3();
};
