
// ColorPickerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"
#include "ColorStatic.h"
#include "ColorListCtrl.h"
#include "CMyColorDlg.h"

// CColorPickerDlg 对话框
class CColorPickerDlg : public CDialog
{
// 构造
public:
	CColorPickerDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CColorPickerDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLORPICKER_DIALOG };
#endif

    void SetWindowVisible(bool visible);
    void UpdateMainFrameCmdState();

    void SaveConfig() const;
    void LoadConfig();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	COLORREF m_color;			//颜色的COLORREF值
	COLORREF m_color_backup;
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
	CColorStatic m_new_color_static;
	CMFCButton m_btnColorSelect;

	CSize m_min_size;
	CSize m_window_size{ -1, -1 };

	CMyColorDlg* m_pColorDlg;

	//选项设置数据
	bool m_hex_lowercase{};		//十六进制使用小写字母
    bool m_use_hex{};            //使用十六进制显示
    bool m_windowVisible{ true };      //窗口是否显示

protected:
	void SetColorRefText();
	void SetColorRText();
	void SetColorGText();
	void SetColorBText();
	void SetColorHexText();

	void SetPreview();

	void SetColor(COLORREF color);

    CString GetFormatStr() const;

    void ShowMessage(LPCTSTR text);

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
	afx_msg void OnBnClickedCopyRgbButton();
	afx_msg void OnBnClickedCopyHexButton();
	afx_msg void OnBnClickedPickColorButton();
	afx_msg LRESULT OnColorDialogSelected(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorPickCursorMove(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnColorDlgCancel(WPARAM wParam, LPARAM lParam);
	afx_msg void OnHexLowerCase();
	afx_msg void OnInitMenu(CMenu* pMenu);
	afx_msg void OnAppAbout();
    afx_msg void OnSelectThemeColor();
    afx_msg void OnAddGetSysColorTable();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLanguageFollowingSystem();
	afx_msg void OnLanguageEnglish();
	afx_msg void OnLanguageSimplifiedChinese();
    afx_msg void OnStnDblclickColorNewStatic();
    afx_msg void OnUseHex();
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
    afx_msg void OnDestroy();
    afx_msg void OnPickColor();
    afx_msg void OnCopyRgbValue();
    afx_msg void OnCopyHexValue();
};
