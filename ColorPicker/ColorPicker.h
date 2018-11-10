
// ColorPicker.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CColorPickerApp: 
// 有关此类的实现，请参阅 ColorPicker.cpp
//

class CColorPickerApp : public CWinApp
{
public:
	CColorPickerApp();

	int DPI(int pixel);
	void GetDPI(CWnd* pWnd);
	std::wstring GetModleDir() const { return m_modle_dir; }

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