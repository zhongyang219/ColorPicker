
// ColorPicker.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "ColorPickerDlg.h"
#include "IniHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CColorPickerApp

BEGIN_MESSAGE_MAP(CColorPickerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CColorPickerApp 构造

CColorPickerApp::CColorPickerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	CWindowDC dc(NULL);
	HDC hDC = dc.GetSafeHdc();
	m_dpi = GetDeviceCaps(hDC, LOGPIXELSY);
}

int CColorPickerApp::DPI(int pixel)
{
	return m_dpi * pixel / 96;
}

void CColorPickerApp::SaveConfig()
{
	CIniHelper ini(GetModleDir() + CONFIG_FILE_NAME);
	ini.WriteInt(_T("config"), _T("language"), static_cast<int>(m_language));
	ini.Save();
}

void CColorPickerApp::LoadConfig()
{
	CIniHelper ini(GetModleDir() + CONFIG_FILE_NAME);
	m_language = static_cast<Language>(ini.GetInt(_T("config"), _T("language"), 0));
}


void CColorPickerApp::InitThreadLanguage()
{
	switch (m_language)
	{
	case Language::ENGLISH: SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)); break;
	case Language::SIMPLIFIED_CHINESE: SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)); break;
	default: break;
	}
}

// 唯一的一个 CColorPickerApp 对象

CColorPickerApp theApp;


// CColorPickerApp 初始化

BOOL CColorPickerApp::InitInstance()
{
	//替换掉对话框程序的默认类名
	WNDCLASS wc;
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc);	//MFC默认的所有对话框的类名为#32770
	wc.lpszClassName = _T("ColorPicker-2rW332K9");	//将对话框的类名修改为新类名
	AfxRegisterClass(&wc);

	//检查是否已有实例正在运行（Debug时不检查）
#ifndef _DEBUG
	HANDLE hMutex = ::CreateMutex(NULL, TRUE, _T("c1A0pd1NE1v7"));		//使用一个随机的字符串创建一个互斥量
	if (hMutex != NULL)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)		//互斥量创建失败，说明已经有一个程序的实例正在运行
		{
			HWND handle = FindWindow(_T("ColorPicker-2rW332K9"), NULL);		//根据类名查找已运行实例窗口的句柄
			if (handle != NULL)
			{
				ShowWindow(handle, SW_SHOWNORMAL);		//显示正在运行的窗口
				SetForegroundWindow(handle);
				return FALSE;		//退出当前程序
			}
		}
	}
#endif

	//获取当前程序路径
	wchar_t buff[MAX_PATH];
	GetModuleFileNameW(NULL, buff, MAX_PATH);
	size_t index;
	m_modle_dir = buff;
	index = m_modle_dir.rfind(L'\\');
	m_modle_dir = m_modle_dir.substr(0, index + 1);

	//初始化界面语言
	LoadConfig();
	switch (m_language)
	{
	case Language::ENGLISH: SetThreadUILanguage(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)); break;
	case Language::SIMPLIFIED_CHINESE: SetThreadUILanguage(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)); break;
	default: break;
	}

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	//SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

#ifdef _WINDLL
    CColorPickerDlg* pDlg = new CColorPickerDlg();
    m_pMainWnd = pDlg;
    pDlg->Create(IDD_COLORPICKER_DIALOG);

    return TRUE;

#else
	CColorPickerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
#endif
}

#ifdef _WINDLL

ColorPicker* pIns = nullptr;
ColorPicker* ColorPicker::Instance()
{
    return pIns;
}

IMainFrame* ColorPicker::GetMainFrame() const
{
    return m_pMainFrame;
}

void ColorPicker::InitInstance()
{
    int nReturnCode = -1;
    CWinThread* pThread = AfxGetThread();
    CWinApp* pApp = AfxGetApp();

    // AFX internal initialization
    if (!AfxWinInit(GetModuleHandle(_T("ColorPicker")), nullptr, _T(""), SW_SHOW))
        return;

    // App global initializations (rare)
    if (pApp != NULL && !pApp->InitApplication())
        return;

    // Perform specific initializations
    if (pThread != nullptr && !pThread->InitInstance())
    {
        if (pThread->m_pMainWnd != NULL)
        {
            TRACE(traceAppMsg, 0, "Warning: Destroying non-NULL m_pMainWnd\n");
            pThread->m_pMainWnd->DestroyWindow();
        }
    }
    //nReturnCode = pThread->Run();
}

void ColorPicker::UnInitInstance()
{
    int nReturnCode = -1;
    CWinThread* pThread = AfxGetThread();
    if (pThread != nullptr)
        nReturnCode = pThread->ExitInstance();
#ifdef _DEBUG
    // Check for missing AfxLockTempMap calls
    if (AfxGetModuleThreadState()->m_nTempMapLock != 0)
    {
        TRACE(traceAppMsg, 0, "Warning: Temp map lock count non-zero (%ld).\n",
            AfxGetModuleThreadState()->m_nTempMapLock);
    }
    AfxLockTempMaps();
    AfxUnlockTempMaps(-1);
#endif

    AfxWinTerm();
}

void ColorPicker::UiInitComplete(IMainFrame* pMainFrame)
{
    m_pMainFrame = pMainFrame;
    //显示主窗口
    CColorPickerDlg* pDlg = dynamic_cast<CColorPickerDlg*>(theApp.m_pMainWnd);
    pDlg->SetWindowVisible(true);
    pDlg->UpdateMainFrameCmdState();
}

void* ColorPicker::GetMainWindow()
{
    HWND hWnd = theApp.m_pMainWnd->GetSafeHwnd();
    return hWnd;
}

IModule::eMainWindowType ColorPicker::GetMainWindowType() const
{
    return IModule::MT_HWND;
}

const char* ColorPicker::GetModuleName()
{
    return "ColorPicker";
}

#define DECLARE_COMMAND_TRIGGER(cmdString, id) \
if (cmd == cmdString) \
{ \
    theApp.m_pMainWnd->SendMessage(WM_COMMAND, id); \
} \


void ColorPicker::OnCommand(const char* strCmd, bool checked)
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    std::string cmd = strCmd;
    DECLARE_COMMAND_TRIGGER("UseHex", ID_USE_HEX)
    DECLARE_COMMAND_TRIGGER("HexLowerCase", ID_HEX_LOWER_CASE)
    DECLARE_COMMAND_TRIGGER("LanguageFollowingSystem", ID_LANGUAGE_FOLLOWING_SYSTEM)
    DECLARE_COMMAND_TRIGGER("LanguageEnglish", ID_LANGUAGE_ENGLISH)
    DECLARE_COMMAND_TRIGGER("LanguageSimplifiedChinese", ID_LANGUAGE_SIMPLIFIED_CHINESE)
    DECLARE_COMMAND_TRIGGER("SelectThemeColor", ID_SELECT_THEME_COLOR)
    DECLARE_COMMAND_TRIGGER("AddGetSysColorTable", ID_ADD_GET_SYS_COLOR_TABLE)
    DECLARE_COMMAND_TRIGGER("ColorPickerAppAbout", ID_APP_ABOUT)
    DECLARE_COMMAND_TRIGGER("PickColor", ID_PICK_COLOR)
    DECLARE_COMMAND_TRIGGER("CopyRgbValue", ID_COPY_RGB_VALUE)
    DECLARE_COMMAND_TRIGGER("CopyGexValue", ID_COPY_HEX_VALUE)
}

IModule* CreateInstance()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    pIns = new ColorPicker();
    return pIns;
}
#endif
