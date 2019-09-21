#pragma once

class CCommon
{
public:
	CCommon();
	~CCommon();

	//½«const char*×Ö·û´®×ª»»³É¿í×Ö·û×Ö·û´®
	static std::wstring StrToUnicode(const char* str, bool utf8 = false);

	static std::string UnicodeToStr(const wchar_t* wstr, bool utf8 = false);

	static void StringNormalize(std::wstring& str);

	static void SetDrawRect(CDC* pDC, CRect rect);

	//½«Ò»¸ö×Ö·û´®±£´æµ½¼ôÌù°å
	static bool CopyStringToClipboard(const std::wstring& str);

    static COLORREF GetWindowsThemeColor();

};

