// VlcCtlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "vlcDemo.h"
#include "VlcCtlDlg.h"


// CVlcCtlDlg 对话框

IMPLEMENT_DYNAMIC(CVlcCtlDlg, CDialog)

CVlcCtlDlg::CVlcCtlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVlcCtlDlg::IDD, pParent)
{
	m_mounse_in = false;
}

CVlcCtlDlg::~CVlcCtlDlg()
{
}

void CVlcCtlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVlcCtlDlg, CDialog)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_MOUSEACTIVATE()
	ON_WM_MOUSELEAVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CVlcCtlDlg 消息处理程序

void CVlcCtlDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnMouseMove(nFlags, point);

	if( !m_mounse_in){
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		m_mounse_in =true;
		ctlButton.ShowWindow(SW_SHOW);
	}
}

void CVlcCtlDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CDialog::OnPaint();
}

int CVlcCtlDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	this->MessageBox("test");
	ctlButton.ShowWindow(SW_SHOW);
	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CVlcCtlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	ctlButton.AutoLoad(IDC_BUTTON_CTL,this); 
	ctlButton.LoadBitmaps(IDB_BITMAP1); 
	ctlButton.RedrawWindow();


	ctlButton.MoveWindow(0,0,64,38);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CVlcCtlDlg::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_mounse_in = false;
	ctlButton.ShowWindow(SW_HIDE);

	this->OnPaint();
	CDialog::OnMouseLeave();
}

BOOL CVlcCtlDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//return true;
	return CDialog::OnEraseBkgnd(pDC);
}
