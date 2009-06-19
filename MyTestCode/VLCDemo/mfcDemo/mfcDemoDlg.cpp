
// mfcDemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcDemo.h"
#include "mfcDemoDlg.h"
#include "otherFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmfcDemoDlg 对话框




CmfcDemoDlg::CmfcDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfcDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, log);
}

BEGIN_MESSAGE_MAP(CmfcDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CmfcDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmfcDemoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CmfcDemoDlg 消息处理程序

BOOL CmfcDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	vlc_dlg.Create(IDD_DIALOG_VLC,this);
	vlc_dlg.ShowWindow(SW_SHOW);
	vlc_dlg.MoveWindow(20,20,300,280);
    /* This is a non working code that show how to hooks into a window,
     * if we have a window around */
     //libvlc_drawable_t drawable = xdrawable;
    /* or on windows */
	libvlc_drawable_t drawable = (libvlc_drawable_t)(vlc_dlg.GetSafeHwnd());
	libvlc_media_player_set_drawable (mp, drawable, &ex);
     raise (&ex);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmfcDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmfcDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmfcDemoDlg::OnBnClickedButton1()
{

	if(m != NULL){	
		libvlc_media_player_stop(mp,&ex);
		libvlc_media_release(m);
		raise (&ex);
	}

	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	//CFileDialog FileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,sFilter,NULL); 
	CFileDialog FileDialog(TRUE);
	if(FileDialog.DoModal()==IDOK)  
	{     
		FileName=FileDialog.GetPathName();  
	}


     /* Create a new item */
	//wstr2cstr( FileName.GetBuffer(), sz, FileName.GetLength() );
	this->log.SetWindowText(FileName);

	/* No need to keep the media now */
//	libvlc_media_release (m);
//	raise (&ex);


	m = libvlc_media_new (inst,FileName.GetBuffer(), &ex);
	raise (&ex);
   

    /* XXX: demo art and meta information fetching */
    libvlc_media_player_set_media(mp,m,&ex);
	raise (&ex);



    /* play the media_player */
    libvlc_media_player_play (mp, &ex);
    raise (&ex);

}

void CmfcDemoDlg::OnBnClickedButton2()
{

	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	   /* play the media_player */
    libvlc_media_player_set_media(mp,m,&ex);
	raise (&ex);

    libvlc_media_player_play (mp, &ex);
    raise (&ex);

}
