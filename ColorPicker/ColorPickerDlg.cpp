
// ColorPickerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "ColorPickerDlg.h"
#include "afxdialogex.h"
#include "ColorConvert.h"
#include "IniHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CColorPickerDlg 对话框



CColorPickerDlg::CColorPickerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_COLORPICKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CColorPickerDlg::~CColorPickerDlg()
{
	if (m_pColorDlg != nullptr)
		delete m_pColorDlg;
}

void CColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLOR_VALUE, m_edit);
	DDX_Control(pDX, IDC_COLOR_R, m_edit_r);
	DDX_Control(pDX, IDC_COLOR_G, m_edit_g);
	DDX_Control(pDX, IDC_COLOR_B, m_edit_b);
	DDX_Control(pDX, IDC_COLOR_HEX, m_edit_hex);
	//  DDX_Control(pDX, IDC_STATIC_PREVIEW, m_preview);
	//DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_color_control);
	DDX_Control(pDX, IDC_COLOR_LIST, m_color_list);
	DDX_Control(pDX, IDC_COLOR_STATIC, m_color_static);
	DDX_Control(pDX, IDC_COLOR_NEW_STATIC, m_new_color_static);
	DDX_Control(pDX, IDC_PICK_COLOR_BUTTON, m_btnColorSelect);
}

BEGIN_MESSAGE_MAP(CColorPickerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_SELECT_COLOR, &CColorPickerDlg::OnBnClickedSelectColor)
	ON_EN_CHANGE(IDC_COLOR_VALUE, &CColorPickerDlg::OnEnChangeColorValue)
	ON_EN_CHANGE(IDC_COLOR_R, &CColorPickerDlg::OnEnChangeColorR)
	ON_EN_CHANGE(IDC_COLOR_G, &CColorPickerDlg::OnEnChangeColorG)
	ON_EN_CHANGE(IDC_COLOR_B, &CColorPickerDlg::OnEnChangeColorB)
	ON_EN_CHANGE(IDC_COLOR_HEX, &CColorPickerDlg::OnEnChangeColorHex)
	ON_BN_CLICKED(IDC_ABOUT_BUTTON, &CColorPickerDlg::OnBnClickedAboutButton)
	//ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CColorPickerDlg::OnBnClickedMfccolorbutton1)
	ON_BN_CLICKED(IDC_ADD_COLOR_BUTTON, &CColorPickerDlg::OnBnClickedAddColorButton)
	ON_BN_CLICKED(IDC_DELETE_COLOR_BUTTON, &CColorPickerDlg::OnBnClickedDeleteColorButton)
	ON_MESSAGE(WM_STATIC_CLICKED, &CColorPickerDlg::OnStaticClicked)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_COLOR_DB_CLICKED, &CColorPickerDlg::OnColorDbClicked)
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_COPY_RGB_BUTTON, &CColorPickerDlg::OnBnClickedCopyRgbButton)
	ON_BN_CLICKED(IDC_COPY_HEX_BUTTON, &CColorPickerDlg::OnBnClickedCopyHexButton)
	ON_BN_CLICKED(IDC_PICK_COLOR_BUTTON, &CColorPickerDlg::OnBnClickedPickColorButton)
	ON_MESSAGE(WM_COLOR_SELECTED, &CColorPickerDlg::OnColorDialogSelected)
	ON_MESSAGE(WM_COLOR_PICK_CURSOR_MOVE, &CColorPickerDlg::OnColorPickCursorMove)
	ON_MESSAGE(WM_COLOR_DLG_CANCEL, &CColorPickerDlg::OnColorDlgCancel)
	ON_COMMAND(ID_HEX_LOWER_CASE, &CColorPickerDlg::OnHexLowerCase)
	ON_WM_INITMENU()
	ON_COMMAND(ID_APP_ABOUT, &CColorPickerDlg::OnAppAbout)
    ON_COMMAND(ID_SELECT_THEME_COLOR, &CColorPickerDlg::OnSelectThemeColor)
    ON_COMMAND(ID_ADD_GET_SYS_COLOR_TABLE, &CColorPickerDlg::OnAddGetSysColorTable)
END_MESSAGE_MAP()


// CColorPickerDlg 消息处理程序

void CColorPickerDlg::SetColorRefText()
{
	CString str;
	str.Format(_T("%u"), m_color);
	m_edit.SetWindowText(str);
}

void CColorPickerDlg::SetColorRText()
{
	CString str;
	str.Format(_T("%u"), m_color_r);
	m_edit_r.SetWindowText(str);
}

void CColorPickerDlg::SetColorGText()
{
	CString str;
	str.Format(_T("%u"), m_color_g);
	m_edit_g.SetWindowText(str);
}

void CColorPickerDlg::SetColorBText()
{
	CString str;
	str.Format(_T("%u"), m_color_b);
	m_edit_b.SetWindowText(str);
}

void CColorPickerDlg::SetColorHexText()
{
	CString str;
	str.Format(_T("%.6x"), m_color_hex);
	if(!m_hex_lowercase)
		str.MakeUpper();
	m_edit_hex.SetWindowText(str);
}

void CColorPickerDlg::SetPreview()
{
	//CDC* pDC = m_preview.GetDC();
	//CRect rect;
	//m_preview.GetClientRect(rect);
	//CBrush BGBrush, *pOldBrush;
	//BGBrush.CreateSolidBrush(m_color);
	//pOldBrush = pDC->SelectObject(&BGBrush);
	//pDC->FillRect(&rect, &BGBrush);
	//pDC->SelectObject(pOldBrush);
	//BGBrush.DeleteObject();
	//m_color_control.SetColor(m_color);
	m_color_static.SetFillColor(m_color);
}

void CColorPickerDlg::SetColor(COLORREF color)
{
	m_color = color;
	m_color_r = GetRValue(m_color);
	m_color_g = GetGValue(m_color);
	m_color_b = GetBValue(m_color);
	m_color_hex = CColorConvert::RGB2Hex(m_color_r, m_color_g, m_color_b);
	SetColorRefText();
	SetColorRText();
	SetColorGText();
	SetColorBText();
	SetColorHexText();
	SetPreview();

}

void CColorPickerDlg::SaveConfig() const
{
	CIniHelper ini(theApp.GetModleDir() + CONFIG_FILE_NAME);
	ini.WriteInt(L"Config", L"current_color", m_color);
	ini.WriteBool(L"Config", L"hex_lowercase", m_hex_lowercase);
	ini.Save();
}

void CColorPickerDlg::LoadConfig()
{
	CIniHelper ini(theApp.GetModleDir() + CONFIG_FILE_NAME);
	m_color = ini.GetInt(L"Config", L"current_color", 0);
	m_hex_lowercase = ini.GetBool(L"Config", L"hex_lowercase", false);
}


BOOL CColorPickerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	LoadConfig();
	m_color_backup = m_color;

	m_new_color_static.SetHandCursor(false);

	m_btnColorSelect.SetImage(IDB_AFXBARRES_COLOR_PICKER);
	m_btnColorSelect.SetFont(GetFont());

	//获取窗口初始大小
	CRect rect;
	GetWindowRect(rect);
	m_min_size = rect.Size();

	SetColorRefText();
	SetColorRText();
	SetColorGText();
	SetColorBText();
	SetColorHexText();

	m_edit.SetLimitText(8);
	m_edit_r.SetLimitText(3);
	m_edit_g.SetLimitText(3);
	m_edit_b.SetLimitText(3);
	m_edit_hex.SetLimitText(6);

	m_color_list.SetDrawColorRow(CLC_COLOR);
	m_color_list.LoadColors((theApp.GetModleDir() + CONFIG_FILE_NAME).c_str());		//从配置文件加载颜色表

	SetColor(m_color);

	m_pColorDlg = new CMyColorDlg();
	m_pColorDlg->Create(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CColorPickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CColorPickerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CColorPickerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CColorPickerDlg::OnBnClickedSelectColor()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CColorDialog colorDlg(m_color, 0, this);
//	if (colorDlg.DoModal() == IDOK)
//	{
//		m_color = colorDlg.GetColor();
//		m_color_r = GetRValue(m_color);
//		m_color_g = GetGValue(m_color);
//		m_color_b = GetBValue(m_color);
//		m_color_hex = RGB2Hex(m_color_r, m_color_g, m_color_b);
//		SetColorRefText();
//		SetColorRText();
//		SetColorGText();
//		SetColorBText();
//		SetColorHexText();
//		SetPreview();
//	}
//}


void CColorPickerDlg::OnEnChangeColorValue()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_edit.GetModify())
	{
		CString str;
		m_edit.GetWindowText(str);
		m_color = _wtoi(str);
		m_color_r = GetRValue(m_color);
		m_color_g = GetGValue(m_color);
		m_color_b = GetBValue(m_color);
		m_color_hex = CColorConvert::RGB2Hex(m_color_r, m_color_g, m_color_b);
		SetColorRText();
		SetColorGText();
		SetColorBText();
		SetColorHexText();
		SetPreview();
	}
}


void CColorPickerDlg::OnEnChangeColorR()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_edit_r.GetModify())
	{
		CString str;
		m_edit_r.GetWindowText(str);
		m_color_r = _wtoi(str);
		m_color = RGB(m_color_r, m_color_g, m_color_b);
		m_color_hex = CColorConvert::RGB2Hex(m_color_r, m_color_g, m_color_b);
		SetColorRefText();
		SetColorHexText();
		SetPreview();
	}
}


void CColorPickerDlg::OnEnChangeColorG()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_edit_g.GetModify())
	{
		CString str;
		m_edit_g.GetWindowText(str);
		m_color_g = _wtoi(str);
		m_color = RGB(m_color_r, m_color_g, m_color_b);
		m_color_hex = CColorConvert::RGB2Hex(m_color_r, m_color_g, m_color_b);
		SetColorRefText();
		SetColorHexText();
		SetPreview();
	}
}


void CColorPickerDlg::OnEnChangeColorB()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if (m_edit_b.GetModify())
	{
		CString str;
		m_edit_b.GetWindowText(str);
		m_color_b = _wtoi(str);
		m_color = RGB(m_color_r, m_color_g, m_color_b);
		m_color_hex = CColorConvert::RGB2Hex(m_color_r, m_color_g, m_color_b);
		SetColorRefText();
		SetColorHexText();
		SetPreview();
	}
}


void CColorPickerDlg::OnEnChangeColorHex()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	if(m_edit_hex.GetModify())
	{ 
		CString str;
		m_edit_hex.GetWindowText(str);
		m_color_hex = wcstoul(str, NULL, 16);
		m_color_r = CColorConvert::Hex2R(m_color_hex);
		m_color_g = CColorConvert::Hex2G(m_color_hex);
		m_color_b = CColorConvert::Hex2B(m_color_hex);
		m_color = RGB(m_color_r, m_color_g, m_color_b);
		SetColorRefText();
		SetColorRText();
		SetColorGText();
		SetColorBText();
		SetPreview();
	}
}


void CColorPickerDlg::OnBnClickedAboutButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


//void CColorPickerDlg::OnBnClickedMfccolorbutton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//}


void CColorPickerDlg::OnBnClickedAddColorButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString color_name;
	color_name.Format(_T("颜色 #%.6x"), m_color_hex);
	color_name.MakeUpper();

	if (m_color_list.AddColor(color_name.GetString(), m_color))
	{
		m_color_list.Edit(m_color_list.GetColorNum() - 1);
	}
	else
	{
		CString info;
		info.Format(_T("%s 已经存在于颜色表中！"), color_name.GetString());
		MessageBox(info, NULL, MB_ICONWARNING | MB_OK);
	}
}


void CColorPickerDlg::OnBnClickedDeleteColorButton()
{
	// TODO: 在此添加控件通知处理程序代码
	//int row = m_color_list.GetSelectionMark();
	std::vector<int> items_selected;
	m_color_list.GetItemSelected(items_selected);
	CString info;
	if (items_selected.size() == 1)
	{
		info.Format(_T("确实要删除 “%s” 吗？"), m_color_list.GetColorName(items_selected[0]).c_str());
	}
	else if(items_selected.size() > 1)
	{
		info.Format(_T("确实要删除选中的“%d”个颜色吗？"), items_selected.size());
	}
	if (!info.IsEmpty())
	{
		if(MessageBox(info, NULL, MB_ICONQUESTION | MB_YESNO)==IDYES)
		{
			m_color_list.DeleteColors(items_selected);
		}
	}
}


afx_msg LRESULT CColorPickerDlg::OnStaticClicked(WPARAM wParam, LPARAM lParam)
{
	//CMFCColorDialog dlg(m_color);

	m_color_backup = m_color;

	if ((CWnd*)wParam == &m_color_static)
	{
		m_pColorDlg->SetColor(m_color);
		m_pColorDlg->SetWindowVisible();

	}

	return 0;
}


BOOL CColorPickerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
		//屏蔽按回车键和ESC键退出
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}


void CColorPickerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_color_list.SaveColors((theApp.GetModleDir() + CONFIG_FILE_NAME).c_str());		//退出时将颜色表保存到配置文件
	SaveConfig();

	CDialog::OnClose();
}

afx_msg LRESULT CColorPickerDlg::OnColorDbClicked(WPARAM wParam, LPARAM lParam)
{
	SetColor((COLORREF)wParam);
	return 0;
}


void CColorPickerDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//限制窗口最小大小
	lpMMI->ptMinTrackSize.x = m_min_size.cx;		//设置最小宽度
	lpMMI->ptMinTrackSize.y = m_min_size.cy;		//设置最小高度

	CDialog::OnGetMinMaxInfo(lpMMI);
}


void CColorPickerDlg::OnBnClickedCopyRgbButton()
{
	// TODO: 在此添加控件通知处理程序代码
	wchar_t buff[64];
	swprintf_s(buff, L"%d, %d, %d", m_color_r, m_color_g, m_color_b);
	CCommon::CopyStringToClipboard(wstring(buff));
	MessageBox(_T("RGB 颜色值已经复制到剪贴板"), NULL, MB_ICONINFORMATION | MB_OK);
}


void CColorPickerDlg::OnBnClickedCopyHexButton()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_edit_hex.GetWindowText(str);
	CCommon::CopyStringToClipboard(wstring(str.GetString()));
	MessageBox(_T("十六进制颜色值已经复制到剪贴板"), NULL, MB_ICONINFORMATION | MB_OK);
}


void CColorPickerDlg::OnBnClickedPickColorButton()
{
	// TODO: 在此添加控件通知处理程序代码
	m_pColorDlg->OnColorSelect();
}

LRESULT CColorPickerDlg::OnColorDialogSelected(WPARAM wParam, LPARAM lParam)
{
	m_color = m_pColorDlg->GetColor();
	SetColor(m_color);
	return LRESULT();
}

LRESULT CColorPickerDlg::OnColorPickCursorMove(WPARAM wParam, LPARAM lParam)
{
	COLORREF color_tmp = wParam;
	m_new_color_static.SetFillColor(color_tmp);
	return LRESULT();
}

LRESULT CColorPickerDlg::OnColorDlgCancel(WPARAM wParam, LPARAM lParam)
{
	SetColor(m_color_backup);		//如果点击了颜色对话框的取消按钮，则恢复之前的颜色
	return LRESULT();
}


void CColorPickerDlg::OnHexLowerCase()
{
	// TODO: 在此添加命令处理程序代码
	m_hex_lowercase = !m_hex_lowercase;
	SetColorHexText();
}


void CColorPickerDlg::OnInitMenu(CMenu* pMenu)
{
	CDialog::OnInitMenu(pMenu);

	// TODO: 在此处添加消息处理程序代码
	pMenu->CheckMenuItem(ID_HEX_LOWER_CASE, MF_BYCOMMAND | (m_hex_lowercase ? MF_CHECKED : MF_UNCHECKED));
}


void CColorPickerDlg::OnAppAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CColorPickerDlg::OnSelectThemeColor()
{
    // TODO: 在此添加命令处理程序代码
    SetColor(CCommon::GetWindowsThemeColor());
}


void CColorPickerDlg::OnAddGetSysColorTable()
{
    // TODO: 在此添加命令处理程序代码
    const std::map<UINT, const wchar_t*> sys_color_index {
        {COLOR_3DDKSHADOW, L"COLOR_3DDKSHADOW"},
        {COLOR_3DFACE, L"COLOR_3DFACE"},
        {COLOR_3DHIGHLIGHT, L"COLOR_3DHIGHLIGHT"},
        {COLOR_3DHILIGHT, L"COLOR_3DHILIGHT"},
        {COLOR_3DLIGHT, L"COLOR_3DLIGHT"},
        {COLOR_3DSHADOW, L"COLOR_3DSHADOW"},
        {COLOR_ACTIVEBORDER, L"COLOR_ACTIVEBORDER"},
        {COLOR_ACTIVECAPTION, L"COLOR_ACTIVECAPTION"},
        {COLOR_APPWORKSPACE, L"COLOR_APPWORKSPACE"},
        {COLOR_BACKGROUND, L"COLOR_BACKGROUND"},
        {COLOR_BTNFACE, L"COLOR_BTNFACE"},
        {COLOR_BTNHIGHLIGHT, L"COLOR_BTNHIGHLIGHT"},
        {COLOR_BTNHILIGHT, L"COLOR_BTNHILIGHT"},
        {COLOR_BTNSHADOW, L"COLOR_BTNSHADOW"},
        {COLOR_BTNTEXT, L"COLOR_BTNTEXT"},
        {COLOR_CAPTIONTEXT, L"COLOR_CAPTIONTEXT"},
        {COLOR_DESKTOP, L"COLOR_DESKTOP"},
        {COLOR_GRADIENTACTIVECAPTION, L"COLOR_GRADIENTACTIVECAPTION"},
        {COLOR_GRADIENTINACTIVECAPTION, L"COLOR_GRADIENTINACTIVECAPTION"},
        {COLOR_GRAYTEXT, L"COLOR_GRAYTEXT"},
        {COLOR_HIGHLIGHT, L"COLOR_HIGHLIGHT"},
        {COLOR_HIGHLIGHTTEXT, L"COLOR_HIGHLIGHTTEXT"},
        {COLOR_HOTLIGHT, L"COLOR_HOTLIGHT"},
        {COLOR_INACTIVEBORDER, L"COLOR_INACTIVEBORDER"},
        {COLOR_INACTIVECAPTION, L"COLOR_INACTIVECAPTION"},
        {COLOR_INACTIVECAPTIONTEXT, L"COLOR_INACTIVECAPTIONTEXT"},
        {COLOR_INFOBK, L"COLOR_INFOBK"},
        {COLOR_INFOTEXT, L"COLOR_INFOTEXT"},
        {COLOR_MENU, L"COLOR_MENU"},
        {COLOR_MENUHILIGHT, L"COLOR_MENUHILIGHT"},
        {COLOR_MENUBAR, L"COLOR_MENUBAR"},
        {COLOR_MENUTEXT, L"COLOR_MENUTEXT"},
        {COLOR_SCROLLBAR, L"COLOR_SCROLLBAR"},
        {COLOR_WINDOW, L"COLOR_WINDOW"},
        {COLOR_WINDOWFRAME, L"COLOR_WINDOWFRAME"},
        {COLOR_WINDOWTEXT, L"COLOR_WINDOWTEXT"}
    };

    for (const auto& item : sys_color_index)
    {
        wstring name = item.second;
        COLORREF color = GetSysColor(item.first);
        m_color_list.AddColor2(name, color);
    }
}
