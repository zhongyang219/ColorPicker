
// ColorPicker.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "Common.h"
#ifdef _WINDLL
#include "../include/moduleinterface.h"
#endif

// CColorPickerApp: 
// 有关此类的实现，请参阅 ColorPicker.cpp
//

class CColorPickerApp : public CWinApp
{
public:
	CColorPickerApp();

	int DPI(int pixel);
	std::wstring GetModleDir() const { return m_modle_dir; }
	void InitThreadLanguage();

public:
	Language m_language;

public:
	void SaveConfig();

private:
	void LoadConfig();

// 重写
public:
	virtual BOOL InitInstance();

private:
	int m_dpi{ 96 };
	std::wstring m_modle_dir;

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CColorPickerApp theApp;

#ifdef _WINDLL
//////////////////////////////////////////////////////////////////////////////////////
class ColorPicker : public IModule
{
public:

    // 通过 IModule 继承
    virtual void InitInstance() override;
    virtual void UnInitInstance() override;
    virtual void UiInitComplete(IMainFrame* pMainFrame) override;
    virtual void* GetMainWindow() override;
    virtual eMainWindowType GetMainWindowType() const override;
    virtual const char* GetModuleName() override;
    virtual void OnCommand(const char* strCmd, bool checked) override;
};
#ifdef __cplusplus
extern "C" {
#endif
    //导出一个名为CreateInstance的函数以创建对象
    __declspec(dllexport) IModule* CreateInstance();

#ifdef __cplusplus
}
#endif

#endif
