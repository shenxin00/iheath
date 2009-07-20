// VlcCtlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "vlcDemo.h"
#include "VlcCtlDlg.h"


// CVlcCtlDlg �Ի���

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


// CVlcCtlDlg ��Ϣ�������

void CVlcCtlDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnMouseMove(nFlags, point);

	if( !m_mounse_in){
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		m_mounse_in =true;
		ctlButton.ShowWindow(SW_SHOW);
	}
}

void CVlcCtlDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CDialog::OnPaint();
}

int CVlcCtlDlg::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	this->MessageBox("test");
	ctlButton.ShowWindow(SW_SHOW);
	return CDialog::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CVlcCtlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ctlButton.AutoLoad(IDC_BUTTON_CTL,this); 
	ctlButton.LoadBitmaps(IDB_BITMAP1); 
	ctlButton.RedrawWindow();


	ctlButton.MoveWindow(0,0,64,38);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CVlcCtlDlg::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_mounse_in = false;
	ctlButton.ShowWindow(SW_HIDE);

	this->OnPaint();
	CDialog::OnMouseLeave();
}

BOOL CVlcCtlDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//return true;
	return CDialog::OnEraseBkgnd(pDC);
}
