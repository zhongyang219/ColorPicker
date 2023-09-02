#pragma once
#include "CVariant.h"
#include <vector>
#include <string>

//语言
enum class Language
{
	FOLLOWING_SYSTEM,		//跟随系统
	ENGLISH,				//英语
	SIMPLIFIED_CHINESE		//简体中文
};

class CCommon
{
public:
	CCommon();
	~CCommon();

	//将const char*字符串转换成宽字符字符串
	static std::wstring StrToUnicode(const char* str, bool utf8 = false);

	static std::string UnicodeToStr(const wchar_t* wstr, bool utf8 = false);

	static void StringNormalize(std::wstring& str);

	static void SetDrawRect(CDC* pDC, CRect rect);

	//将一个字符串保存到剪贴板
	static bool CopyStringToClipboard(const std::wstring& str);

    //读取剪贴板中的字符串
    static std::wstring GetClipboardString();

    static COLORREF GetWindowsThemeColor();

	//从资源文件载入字符串。其中，front_str、back_str为载入字符串时需要在前面或后面添加的字符串
	static CString LoadText(UINT id, LPCTSTR back_str = nullptr);
	static CString LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str = nullptr);

	//安全的格式化字符串，将format_str中形如<%序号%>的字符串替换成初始化列表paras中的元素，元素支持int/double/LPCTSTR/CString格式，序号从1开始
	static CString StringFormat(LPCTSTR format_str, const std::initializer_list<CVariant>& paras);

	//从资源文件中载入字符串，并将资源字符串中形如<%序号%>的字符串替换成可变参数列表中的参数
	static CString LoadTextFormat(UINT id, const std::initializer_list<CVariant>& paras);

    //将字符串转换成数字，支持自动识别十六进制、八进制和十进制
    static unsigned int StringToNumber(const CString& str);

    //将一个字符串分割成若干个字符串
    //str: 原始字符串
    //div_ch: 用于分割的字符
    //result: 接收分割后的结果
    static void StringSplit(const std::wstring& str, wchar_t div_ch, std::vector<std::wstring>& results, bool skip_empty = true, bool trim = true);

    static bool IsCharHex(char ch);

    static bool IsStringHex(std::wstring& strHex);
};

