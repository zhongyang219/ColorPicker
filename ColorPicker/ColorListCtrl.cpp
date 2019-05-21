#include "stdafx.h"
#include "ColorListCtrl.h"
#include "Common.h"
#include "ColorPicker.h"
#include "IniHelper.h"

IMPLEMENT_DYNAMIC(CColorListCtrl, CListCtrl)

CColorListCtrl::CColorListCtrl()
{
}


CColorListCtrl::~CColorListCtrl()
{
}

bool CColorListCtrl::AddColor(const std::wstring name, COLORREF color)
{
	if (!IsColorExist(color))
	{
		Item item;
		item.name = name;
		item.color = color;
		m_colors.push_back(item);
		InsertItem(m_colors.size(), name.c_str());
		return true;
	}
	else
	{
		return false;
	}
}

bool CColorListCtrl::DeleteColor(int row)
{
	if (row >= 0 && row < static_cast<int>(m_colors.size()))
	{
		m_colors.erase(m_colors.begin() + row);
		DeleteItem(row);
	}
	return false;
}

void CColorListCtrl::Edit(int row)
{
	EnsureVisible(row, FALSE);				//编辑一行时确保该行可见

	m_edit_row = row;
	CRect item_rect;
	GetSubItemRect(row, CLC_NAME, LVIR_LABEL, item_rect);	//取得子项的矩形

	CString text = GetItemText(row, CLC_NAME);		//取得子项的内容

	m_item_edit.SetWindowText(text);		//将子项的内容显示到编辑框中
	m_item_edit.ShowWindow(SW_SHOW);		//显示编辑框
	m_item_edit.MoveWindow(item_rect);		//将编辑框移动到子项上面，覆盖在子项上
	m_item_edit.SetFocus();					//使编辑框取得焦点
	m_item_edit.SetSel(0, -1);
}

int CColorListCtrl::GetColorNum() const
{
	return m_colors.size();
}

COLORREF CColorListCtrl::GetColor(int row) const
{
	if (row >= 0 && row < static_cast<int>(m_colors.size()))
		return m_colors[row].color;
	else
		return 0;
}

std::wstring CColorListCtrl::GetColorName(int row) const
{
	if (row >= 0 && row < static_cast<int>(m_colors.size()))
		return m_colors[row].name;
	else
		return std::wstring();
}

void CColorListCtrl::SaveColors(const wchar_t* path) const
{
	CIniHelper ini(path);
	ini.WriteInt(L"Color_table", L"color_num", m_colors.size());
	for (size_t i{}; i < m_colors.size(); i++)
	{
		wchar_t keyName[32];
		swprintf_s(keyName, L"color%d", i);
		ini.WriteInt(L"Color_table", keyName, m_colors[i].color);

		swprintf_s(keyName, L"name%d", i);
		ini.WriteString(L"Color_table", keyName, m_colors[i].name);

	}
	ini.Save();
}

void CColorListCtrl::LoadColors(const wchar_t* path)
{
	CIniHelper ini(path);
	int colorNum = ini.GetInt(L"Color_table", L"color_num", 0);
	for (int i{}; i < colorNum; i++)
	{
		wchar_t keyName[32];
		swprintf_s(keyName, L"color%d", i);
		int color = ini.GetInt(L"Color_table", keyName, 0);

		swprintf_s(keyName, L"name%d", i);
		std::wstring name = ini.GetString(L"Color_table", keyName, L"Error");

		AddColor(name, color);
	}
}


BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CColorListCtrl::OnNMCustomdraw)
	ON_EN_KILLFOCUS(IDC_ITEM_EDITBOX, &CColorListCtrl::OnEnKillfocusEdit1)

	ON_NOTIFY_REFLECT(NM_DBLCLK, &CColorListCtrl::OnNMDblclk)
	ON_NOTIFY_REFLECT(LVN_BEGINSCROLL, &CColorListCtrl::OnLvnBeginScroll)
END_MESSAGE_MAP()


bool CColorListCtrl::IsColorExist(COLORREF color) const
{
	bool exist{ false };
	for (const auto& item : m_colors)
	{
		if (item.color == color)
		{
			exist = true;
			break;
		}
	}
	return exist;
}

void CColorListCtrl::EndEdit()
{
	if (m_edit_row >= 0 && m_edit_row < static_cast<int>(m_colors.size()))
	{
		CString str;
		m_item_edit.GetWindowText(str);	//取得编辑框的内容
		SetItemText(m_edit_row, CLC_NAME, str);	//将该内容更新到CListCtrl中
		m_colors[m_edit_row].name = str;
	}
	m_item_edit.ShowWindow(SW_HIDE);//隐藏编辑框
}

void CColorListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = CDRF_DODEFAULT;
	LPNMLVCUSTOMDRAW lplvdr = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	NMCUSTOMDRAW& nmcd = lplvdr->nmcd;
	switch (lplvdr->nmcd.dwDrawStage)	//判断状态   
	{
	case CDDS_PREPAINT:
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
	case CDDS_ITEMPREPAINT:
		if (nmcd.dwItemSpec >= 0 && nmcd.dwItemSpec < m_colors.size())
		{
			CDC* pDC = CDC::FromHandle(nmcd.hdc);		//获取绘图DC
			CRect item_rect, draw_rect;
			GetSubItemRect(nmcd.dwItemSpec,m_draw_color_row, LVIR_BOUNDS, item_rect);	//获取绘图单元格的矩形区域
			CCommon::SetDrawRect(pDC, item_rect);		//设置绘图区域为当前列
			draw_rect = item_rect;
			draw_rect.DeflateRect(item_rect.Height() / 6, item_rect.Height() / 6);
			pDC->FillSolidRect(draw_rect, m_colors[nmcd.dwItemSpec].color);

			//当前列绘制完成后将绘图区域设置为左边的区域，防止当前列的区域被覆盖
			CRect rect1{ item_rect };
			rect1.left = 0;
			rect1.right = item_rect.left;
			CCommon::SetDrawRect(pDC, rect1);
		}
		*pResult = CDRF_DODEFAULT;
		break;
	}
}


void CColorListCtrl::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EDITLABELS);

	int width0, width1;
	CRect rect;
	GetWindowRect(rect);
	width0 = rect.Width()*4/7;
	width1 = rect.Width() - width0 - theApp.DPI(21);

	InsertColumn(CLC_NAME, _T("名称"), LVCFMT_LEFT, width0);		//插入第1列
	InsertColumn(CLC_COLOR, _T("颜色"), LVCFMT_LEFT, width1);		//插入第2列

	m_item_edit.Create(WS_BORDER, CRect(), this, IDC_ITEM_EDITBOX);
	m_item_edit.SetFont(GetFont());

	CListCtrl::PreSubclassWindow();
}

void CColorListCtrl::OnEnKillfocusEdit1()
{
	//当文本编辑控件控件失去焦点时响应
	EndEdit();
}


void CColorListCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//双击第一列时编辑名称
	if(pNMItemActivate->iSubItem == CLC_NAME)
		Edit(pNMItemActivate->iItem);

	int row = pNMItemActivate->iItem;
	if (pNMItemActivate->iSubItem == CLC_COLOR && (row >= 0 && row < static_cast<int>(m_colors.size())))
	{
		CWnd* pParent{ GetParent() };
		if (pParent != nullptr)
			pParent->SendMessage(WM_COLOR_DB_CLICKED, (WPARAM)GetColor(row));
	}

	*pResult = 0;
}


void CColorListCtrl::OnLvnBeginScroll(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 此功能要求 Internet Explorer 5.5 或更高版本。
	// 符号 _WIN32_IE 必须是 >= 0x0560。
	LPNMLVSCROLL pStateChanged = reinterpret_cast<LPNMLVSCROLL>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	EndEdit();

	*pResult = 0;
}
