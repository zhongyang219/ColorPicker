#pragma once
#define WM_COLOR_SELECTED (WM_USER+101)
#define WM_COLOR_PICK_CURSOR_MOVE (WM_USER+102)
#define WM_COLOR_DLG_CANCEL (WM_USER+103)

// CMyColorDlg

class CMyColorDlg : public CMFCColorDialog
{
	//DECLARE_DYNAMIC(CMyColorDlg)

public:
	CMyColorDlg();
	virtual ~CMyColorDlg();

protected:
	bool m_visible{ false };

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();

public:
	BOOL Create(CWnd* pParentWnd = NULL);
	void OnColorSelect();
	void SetWindowVisible(bool visible = true);
	void SetColor(COLORREF rgb);
};


