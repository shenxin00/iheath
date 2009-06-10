#include "StdAfx.h"
#include "MyButton.h"
#include "test2.h"
CMyButton::CMyButton(void)
{
		m_mounse_in = false;
		m_btn_down = false;
		
}

CMyButton::~CMyButton(void)
{
}
BEGIN_MESSAGE_MAP(CMyButton, CBitmapButton)
	ON_WM_MOUSEMOVE()
	ON_CONTROL_REFLECT(BN_CLICKED, &CMyButton::OnBnClicked)
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if( !m_mounse_in){
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE;
		_TrackMouseEvent(&tme);
		// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
		m_mounse_in =true;
		LoadBitmaps(IDB_BITMAP1);  
		RedrawWindow(); 
	}
}

void CMyButton::OnBnClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_btn_down){
		m_btn_down = false;
		LoadBitmaps(IDB_BITMAP5);  
		RedrawWindow(); 
	}else{
		m_btn_down = true;
		LoadBitmaps(IDB_BITMAP7);  
		RedrawWindow(); 
	}
}

void CMyButton::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_mounse_in = false;
	LoadBitmaps(IDB_BITMAP2);  
	RedrawWindow();


	CBitmapButton::OnMouseLeave();
}
