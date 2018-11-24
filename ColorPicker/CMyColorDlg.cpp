// CMyColorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "CMyColorDlg.h"


// CMyColorDlg

//IMPLEMENT_DYNAMIC(CMyColorDlg, CMFCColorDialog)

CMyColorDlg::CMyColorDlg()
{

}

CMyColorDlg::~CMyColorDlg()
{
}


BEGIN_MESSAGE_MAP(CMyColorDlg, CMFCColorDialog)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()



// CMyColorDlg 消息处理程序




void CMyColorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	bool picker_mode = m_bPickerMode;
	CMFCColorDialog::OnLButtonDown(nFlags, point);

	if(picker_mode)
		::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_COLOR_SELECTED, 0, 0);
}

void CMyColorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CMFCColorDialog::OnMouseMove(nFlags, point);

	if(m_bPickerMode)
		::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_COLOR_PICK_CURSOR_MOVE, (WPARAM)m_NewColor, 0);
}

void CMyColorDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMFCColorDialog::OnRButtonDown(nFlags, point);

	if (m_bPickerMode)
		::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_COLOR_DLG_CANCEL, (WPARAM)GetSafeHwnd(), 0);
}

void CMyColorDlg::OnWindowPosChanging(WINDOWPOS * lpwndpos)
{
	if(!m_visible)
		lpwndpos->flags &= ~SWP_SHOWWINDOW;

	CMFCColorDialog::OnWindowPosChanging(lpwndpos);
}

BOOL CMyColorDlg::Create(CWnd* pParentWnd)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CMFCColorDialog::Create(IDD_AFXBARRES_COLOR_DLG, pParentWnd);
}


void CMyColorDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_COLOR_SELECTED, 0, 0);

	CMFCColorDialog::OnOK();
}

void CMyColorDlg::OnColorSelect()
{
	CMFCColorDialog::OnColorSelect();
}

void CMyColorDlg::SetWindowVisible(bool visible)
{
	m_visible = visible;
	SetWindowPos(nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
}

void CMyColorDlg::SetColor(COLORREF rgb)
{
	CMFCColorDialog::SetCurrentColor(rgb);
	SetPageOne(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
	SetPageTwo(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));

	m_wndColors.SetOriginalColor(rgb);
	m_wndColors.SetColor(rgb);
	m_wndColors.Invalidate();
	m_wndColors.UpdateWindow();
}


void CMyColorDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_COLOR_DLG_CANCEL, 0, 0);

	CMFCColorDialog::OnCancel();
}


BOOL CMyColorDlg::OnInitDialog()
{
	CMFCColorDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
