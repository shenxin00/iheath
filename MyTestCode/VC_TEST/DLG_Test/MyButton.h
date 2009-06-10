#pragma once
#include "afxext.h"

class CMyButton :
	public CBitmapButton
{
public:
	CMyButton(void);
	~CMyButton(void);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	bool	m_mounse_in;
	bool	m_btn_down;

public:
	afx_msg void OnBnClicked();
	afx_msg void OnMouseLeave();
};
