
#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>

#include "vlc/vlc.h"


static void raise(libvlc_exception_t * ex);
LRESULT CALLBACK WndProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
	);
LRESULT CALLBACK WndProc_player(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
	);

const char* vlc_args[] = {
          "-I", "dummy", /* Don't use any interface */
          "--ignore-config", /* Don't use VLC's config */
         "--plugin-path=..\\plugins" 
		};

libvlc_exception_t ex;
libvlc_instance_t * inst;
libvlc_media_player_t *mp;
libvlc_media_t *m;


static void raise(libvlc_exception_t * ex)
{
    if (libvlc_exception_raised (ex))
    {
         fprintf (stderr, "[test]error: %s\n", libvlc_exception_get_message(ex));
         exit (-1);
    }
}

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow
				   )
{

	inst=NULL;
	mp=NULL;
	m=NULL;
	   

	//1.注册窗口类
	static TCHAR szAppName[] = TEXT ("Win32Demo") ;		//窗口类名称

	//定制"窗口类"结构
	WNDCLASS     wndclass ;
	wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass.lpfnWndProc   = WndProc ;				//关联消息处理函数  
 	wndclass.cbClsExtra    = 0 ;
	wndclass.cbWndExtra    = 0 ;
	wndclass.hInstance     = hInstance ;			//实例句柄
	wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;	//图标
	wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;		//光标
 	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);	//画刷
	wndclass.lpszMenuName  = NULL ;
	wndclass.lpszClassName = szAppName;				//类名称
	//注册
	if (!RegisterClass (&wndclass))
	{
		MessageBox (NULL, TEXT ("RegisterClass Fail!"), 
 			szAppName, MB_ICONERROR) ;
		return 0 ;
	}

	//建立窗口
	HWND hwnd ;
	hwnd = CreateWindow (szAppName,		//窗口类名称
		TEXT ("The Hello Program"),		//窗口标题 
		WS_OVERLAPPEDWINDOW,		//窗口风格
		200,
 		200,
		600,
		600,
		NULL,
		NULL,
		hInstance,			//实例句柄
		NULL);
	

	ShowWindow (hwnd, nCmdShow) ;
	UpdateWindow (hwnd) ;


	//2.注册窗口类
	static TCHAR szAppName_palyer[] = TEXT ("Win32Player") ;		//窗口类名称

	//定制"窗口类"结构
	WNDCLASS     wndclass_palyer ;
	wndclass_palyer.style         = CS_HREDRAW | CS_VREDRAW ;
	wndclass_palyer.lpfnWndProc   = WndProc_player ;				//关联消息处理函数  
 	wndclass_palyer.cbClsExtra    = 0 ;
	wndclass_palyer.cbWndExtra    = 0 ;
	wndclass_palyer.hInstance     = hInstance ;			//实例句柄
	wndclass_palyer.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;	//图标
	wndclass_palyer.hCursor       = LoadCursor (NULL, IDC_ARROW) ;		//光标
 	wndclass_palyer.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);	//画刷
	wndclass_palyer.lpszMenuName  = NULL ;
	wndclass_palyer.lpszClassName = szAppName_palyer;				//类名称
	//注册
	if (!RegisterClass (&wndclass_palyer))
	{
		MessageBox (NULL, TEXT ("RegisterClass Fail!"), 
 			szAppName_palyer, MB_ICONERROR) ;
		return 0 ;
	}

	//建立窗口
	HWND hwnd_player ;
	hwnd_player = CreateWindow (szAppName_palyer,		//窗口类名称
		TEXT ("The Hello Program"),		//窗口标题 
		WS_CHILDWINDOW |WS_BORDER,					//窗口风格
		100,
 		100,
		300,
		280,
		hwnd,
		NULL,
		hInstance,			//实例句柄
		NULL);
	

	ShowWindow (hwnd_player, SW_SHOW) ;
	UpdateWindow (hwnd_player) ;

    libvlc_exception_init (&ex);
    /* init vlc modules, should be done only once */
    inst = libvlc_new (sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args, &ex);
    raise (&ex);
 
    /* Create a new item */
    m = libvlc_media_new (inst, "demo.trp", &ex);
    raise (&ex);
   
    /* XXX: demo art and meta information fetching */
   
    /* Create a media player playing environement */
    mp = libvlc_media_player_new_from_media (m, &ex);
    raise (&ex);
    
    /* No need to keep the media now */
    libvlc_media_release (m);

#if 1
    /* This is a non working code that show how to hooks into a window,
     * if we have a window around */
     //libvlc_drawable_t drawable = xdrawable;
    /* or on windows */
     libvlc_drawable_t drawable = (libvlc_drawable_t)hwnd_player;

     libvlc_media_player_set_drawable (mp, drawable, &ex);
     raise (&ex);
#endif

    /* play the media_player */
    libvlc_media_player_play (mp, &ex);
    raise (&ex);
#if 0 
	_sleep (10*1000); /* Let it play a bit */
   
#endif

	//消息循环
	MSG          msg ;
 	while (GetMessage (&msg, NULL, 0, 0))	//从消息队列中取消息 
	{
		TranslateMessage (&msg) ;		//转换消息
		DispatchMessage (&msg) ;		//派发消息
	}
	return msg.wParam ;

}

LRESULT CALLBACK WndProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
	){
	libvlc_state_t state;

	switch (uMsg)
 	{
		case WM_DESTROY:
			//当用户关闭窗口，窗口销毁，程序需结束，发退出消息，以退出消息循环
			PostQuitMessage (0) ;
			/* Stop playing */
			libvlc_media_player_stop (mp, &ex);

			/* Free the media_player */
			libvlc_media_player_release (mp);

			libvlc_release (inst);
			raise (&ex);

			return 0 ;
	}
#if 0
	if(m != NULL){
		state = libvlc_media_get_state(m,&ex);
		if(state == libvlc_Stopped){
			libvlc_media_player_play (mp, &ex);
		}
	}
#endif
	//其他消息交给由系统提供的缺省处理函数
	return ::DefWindowProc (hwnd, uMsg, wParam, lParam) ;
}

LRESULT CALLBACK WndProc_player(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
	){

	//其他消息交给由系统提供的缺省处理函数
	return ::DefWindowProc (hwnd, uMsg, wParam, lParam) ;
}
