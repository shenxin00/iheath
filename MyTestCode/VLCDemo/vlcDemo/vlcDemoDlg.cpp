// vlcDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "vlcDemo.h"
#include "vlcDemoDlg.h"
#include "otherFunction.h"
#include "VlcCtlDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CvlcDemoDlg dialog




CvlcDemoDlg::CvlcDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CvlcDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CvlcDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CvlcDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CvlcDemoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CvlcDemoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CvlcDemoDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CvlcDemoDlg message handlers

BOOL CvlcDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
/************************************/


	//::SetClassLong(vlc_dlg.GetSafeHwnd(),GCL_HBRBACKGROUND,(LONG)GetStockObject(BLACK_BRUSH));

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

	vlc_ctl_dlg.Create(IDD_DIALOG_CTL,this);

	long Save = GetWindowLong(vlc_ctl_dlg.GetSafeHwnd(), GWL_EXSTYLE);   //   set   transparent   backgroung  
	Save |= WS_EX_LAYERED;  
	SetWindowLong(vlc_ctl_dlg.GetSafeHwnd(), GWL_EXSTYLE, Save);   

	//SetLayeredWindowAttributes(vlc_ctl_dlg.GetSafeHwnd(), RGB(255,255,255), 255, LWA_COLORKEY|LWA_ALPHA);  
  
	//::SetLayeredWindowAttributes(vlc_ctl_dlg.GetSafeHwnd(), RGB(255,255,255), 100, LWA_ALPHA);  
  
	vlc_ctl_dlg.ShowWindow(SW_SHOW);
	vlc_ctl_dlg.MoveWindow(40,240,260,40);

	//vlc_dlg.SetWindowPos(HWND_BOTTOM,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	//vlc_ctl_dlg.SetWindowPos(HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	//::SetWindowPos(vlc_dlg.GetSafeHwnd(),HWND_BOTTOM,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	//::SetWindowPos(vlc_ctl_dlg.GetSafeHwnd(),HWND_TOPMOST,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);

	vlc_ctl_dlg.SetWindowPos(&vlc_dlg,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
/************************************/
	// TODO: Add extra initialization here


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CvlcDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CvlcDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

	this->vlc_dlg.OnPaint();
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CvlcDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CvlcDemoDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码


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



	m = libvlc_media_new (inst,FileName.GetBuffer(), &ex);
	raise (&ex);
   

    /* XXX: demo art and meta information fetching */
    libvlc_media_player_set_media(mp,m,&ex);
	raise (&ex);



    /* play the media_player */
    libvlc_media_player_play (mp, &ex);
    raise (&ex);

	vlc_dlg.SetWindowPos(&vlc_ctl_dlg,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	::SetLayeredWindowAttributes(vlc_ctl_dlg.GetSafeHwnd(),RGB(0,255,0),50,LWA_ALPHA);
}

void CvlcDemoDlg::OnBnClickedButton2()
{



	// TODO: 在此添加控件通知处理程序代码
	if(mp!=NULL){
	//	libvlc_media_player_stop(mp,&ex);
	}

	    /* play the media_player */
    libvlc_media_player_play (mp, &ex);
    raise (&ex);
}

void CvlcDemoDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	libvlc_media_player_pause(mp,&ex);
    raise (&ex);
}


