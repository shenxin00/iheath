// VlcMainDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "vlcDemo.h"
#include "VlcMainDlg.h"
#include "otherFunction.h"

// CVlcMainDlg �Ի���

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


// CVlcMainDlg ��Ϣ�������

void CVlcMainDlg::OnPaint()
{
	
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CDialog::OnPaint();
	//	::SetBkMode(vlc_dlg.GetSafeHwnd(),TRANSPARENT);
	//dc.SetBkMode(TRANSPARENT);



}
