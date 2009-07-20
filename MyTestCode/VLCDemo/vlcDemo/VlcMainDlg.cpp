// VlcMainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "vlcDemo.h"
#include "VlcMainDlg.h"
#include "otherFunction.h"

// CVlcMainDlg 对话框

IMPLEMENT_DYNAMIC(CVlcMainDlg, CDialog)

CVlcMainDlg::CVlcMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVlcMainDlg::IDD, pParent)
{

}

CVlcMainDlg::~CVlcMainDlg()
{
}

void CVlcMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVlcMainDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CVlcMainDlg 消息处理程序

void CVlcMainDlg::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDialog::OnPaint();
	//	::SetBkMode(vlc_dlg.GetSafeHwnd(),TRANSPARENT);
	//dc.SetBkMode(TRANSPARENT);



}
