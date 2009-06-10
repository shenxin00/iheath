// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test2.h"
#include "testDlg.h"
#include "MyButton.h"

// testDlg 对话框

IMPLEMENT_DYNAMIC(testDlg, CDialog)

testDlg::testDlg(CWnd* pParent /*=NULL*/)
	: CDialog(testDlg::IDD, pParent)
{

}

testDlg::~testDlg()
{
}

void testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, myplayer);
}


BEGIN_MESSAGE_MAP(testDlg, CDialog)
	ON_WM_DRAWITEM()
	ON_BN_DOUBLECLICKED(IDC_BUTTON3, &testDlg::OnBnDoubleclickedButton3)
END_MESSAGE_MAP()


// testDlg 消息处理程序

BOOL testDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	m_mybtn.AutoLoad(IDC_BUTTON3,this); 
	m_mybtn.LoadBitmaps(IDB_BITMAP5); 
	m_mybtn.RedrawWindow();
	

	return TRUE;
}


void testDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void testDlg::OnBnDoubleclickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBeep(0);
	CString str = CString("D:\TechInfo\11.swf");
	myplayer.put_Movie(LPCTSTR(L"D:\\TechInfo\\11.swf"));
	//myplayer.LoadMovie( 0,(LPCTSTR)"D:\TechInfo\11.swf");
	//
	//myplayer.Play();
	
}
