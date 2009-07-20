// vlcDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "vlcDemo.h"
#include "vlcDemoDlg.h"
#include <stdio.h>
#include <stdlib.h>
#include "otherFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const char * const vlc_args[] = {
          "-I", "dummy", /* Don't use any interface */
          "--ignore-config", /* Don't use VLC's config */
         "--plugin-path=..\\plugins" 
		};


// CvlcDemoApp

BEGIN_MESSAGE_MAP(CvlcDemoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CvlcDemoApp construction

CvlcDemoApp::CvlcDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CvlcDemoApp object

CvlcDemoApp theApp;


// CvlcDemoApp initialization

BOOL CvlcDemoApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	CvlcDemoDlg dlg;
	m_pMainWnd = &dlg;

/******************/
    libvlc_exception_init (&ex);
    /* init vlc modules, should be done only once */
    inst = libvlc_new (sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args, &ex);
    raise (&ex);

    /* Create a media player playing environement */
    mp = libvlc_media_player_new (inst, &ex);
    raise (&ex);
/******************/

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

/****************************************/
	/* Stop playing */
	libvlc_media_player_stop (mp, &ex);

	/* Free the media_player */
	libvlc_media_player_release (mp);

	libvlc_release (inst);
	raise (&ex);
/****************************************/

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
