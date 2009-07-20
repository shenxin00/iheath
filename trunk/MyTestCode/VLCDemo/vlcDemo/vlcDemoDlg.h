// vlcDemoDlg.h : header file
//

#pragma once


#include "VlcCtlDlg.h"
#include "VlcMainDlg.h"
// CvlcDemoDlg dialog
class CvlcDemoDlg : public CDialog
{
// Construction
public:
	CvlcDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VLCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
public:	
  CString FileName;
  CVlcMainDlg	vlc_dlg;
  CVlcCtlDlg	vlc_ctl_dlg;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
