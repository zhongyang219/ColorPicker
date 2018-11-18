
// ColorPickerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"
#include "ColorStatic.h"
#include "ColorListCtrl.h"


// CColorPickerDlg 对话框
class CColorPickerDlg : public CDialog
{
// 构造
public:
	CColorPickerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORPICKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	COLORREF m_color;			//颜色的COLORREF值
	unsigned char m_color_r;	//颜色RGB中的红色值
	unsigned char m_color_g;	//颜色RGB中的绿色值
	unsigned char m_color_b;	//颜色RGB中的蓝色值
	unsigned int m_color_hex;	//颜色的十六进制值

	CEdit m_edit;		//颜色的COLORREF值控件
	CEdit m_edit_r;		//颜色RGB中的红色值控件
	CEdit m_edit_g;		//颜色RGB中的绿色值控件
	CEdit m_edit_b;		//颜色RGB中的蓝色值控件
	CEdit m_edit_hex;	//颜色十六进制值控件
//	CStatic m_preview;
//颜色预览控件

	//CMFCColorButton m_color_control;
	CColorListCtrl m_color_list;
	CColorStatic m_color_static;

	CSize m_min_size;

	void SetColorRefText();
	void SetColorRText();
	void SetColorGText();
	void SetColorBText();
	void SetColorHexText();

	void SetPreview();

	void SetColor(COLORREF color);

	void SaveConfig() const;
	void LoadConfig();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//	afx_msg void OnBnClickedSelectColor();
	afx_msg void OnEnChangeColorValue();
	afx_msg void OnEnChangeColorR();
	afx_msg void OnEnChangeColorG();
	afx_msg void OnEnChangeColorB();
	afx_msg void OnEnChangeColorHex();
	afx_msg void OnBnClickedAboutButton();
public:
	//afx_msg void OnBnClickedMfccolorbutton1();
	afx_msg void OnBnClickedAddColorButton();
	afx_msg void OnBnClickedDeleteColorButton();
protected:
	afx_msg LRESULT OnStaticClicked(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
protected:
	afx_msg LRESULT OnColorDbClicked(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};
