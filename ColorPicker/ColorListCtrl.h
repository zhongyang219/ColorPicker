#pragma once
#include "afxcmn.h"

#define IDC_ITEM_EDITBOX 1991
#define WM_COLOR_DB_CLICKED (WM_USER + 1002)		//当双击颜色列时向父窗口发送的消息


enum ColorListColumn		//列表的列
{
	CLC_NAME,
	CLC_COLOR,
	CLC_MAX
};

class CColorListCtrl :
	public CListCtrl
{
DECLARE_DYNAMIC(CColorListCtrl)
public:
	CColorListCtrl();
	~CColorListCtrl();

	void SetDrawColorRow(int row) { m_draw_color_row = row; }			//设置要绘制颜色的列，注意此列必须为最右边的列，否则，此列右边的所有列将无法显示
	bool AddColor(const std::wstring name, COLORREF color);				//添加一行颜色（如果颜色已经存在，则添加失败）
	bool DeleteColor(int row);		//删除指定行的颜色

	void Edit(int row);			//编辑指定行的第一列
	int GetColorNum() const;

	COLORREF GetColor(int row) const;
	std::wstring GetColorName(int row) const;

	void SaveColors(const wchar_t* path) const;
	void LoadColors(const wchar_t* path);

protected:
	struct Item
	{
		std::wstring name;
		COLORREF color;
	};

	int m_draw_color_row{};		//需要绘制颜色的列
	std::vector<Item> m_colors;	//用于表示行绘制的颜色

	CEdit m_item_edit;
	int m_edit_row{};

protected:
	bool IsColorExist(COLORREF color) const;
	void EndEdit();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void PreSubclassWindow();
	afx_msg void OnEnKillfocusEdit1();

public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnBeginScroll(NMHDR *pNMHDR, LRESULT *pResult);
};

