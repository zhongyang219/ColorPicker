#include "stdafx.h"
#include "Common.h"
#include <dwmapi.h>


CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

std::wstring CCommon::StrToUnicode(const char * str, bool utf8)
{
	std::wstring result;
	int size;
	size = MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, NULL, 0);
	if (size <= 0) return std::wstring();
	wchar_t* str_unicode = new wchar_t[size + 1];
	MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, str_unicode, size);
	result.assign(str_unicode);
	delete[] str_unicode;
	return result;
}

std::string CCommon::UnicodeToStr(const wchar_t * wstr, bool utf8)
{
	std::string result;
	int size{ 0 };
	size = WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, NULL, 0, NULL, NULL);
	if (size <= 0) return std::string();
	char* str = new char[size + 1];
	WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, str, size, NULL, NULL);
	result.assign(str);
	delete[] str;
	return result;
}

void CCommon::StringNormalize(std::wstring & str)
{
	if (str.empty()) return;

	int size = str.size();	//字符串的长度
	if (size < 0) return;

	int index1 = 0;		//字符串中第1个不是空格或控制字符的位置
	int index2 = size - 1;	//字符串中最后一个不是空格或控制字符的位置
	while (index1 < size && str[index1] >= 0 && str[index1] <= 32)
		index1++;
	while (index2 >= 0 && str[index2] >= 0 && str[index2] <= 32)
		index2--;
	if (index1 > index2)	//如果index1 > index2，说明字符串全是空格或控制字符
		str.clear();
	else if (index1 == 0 && index2 == size - 1)	//如果index1和index2的值分别为0和size - 1，说明字符串前后没有空格或控制字符，直接返回
		return;
	else
		str = str.substr(index1, index2 - index1 + 1);

}

void CCommon::SetDrawRect(CDC * pDC, CRect rect)
{
	CRgn rgn;
	rgn.CreateRectRgnIndirect(rect);
	pDC->SelectClipRgn(&rgn);
}

bool CCommon::CopyStringToClipboard(const std::wstring & str)
{
	if (OpenClipboard(NULL))
	{
		HGLOBAL clipbuffer;
		EmptyClipboard();
		size_t size = (str.size() + 1) * 2;
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, size);
		memcpy_s(GlobalLock(clipbuffer), size, str.c_str(), size);
		GlobalUnlock(clipbuffer);
		if (SetClipboardData(CF_UNICODETEXT, clipbuffer) == NULL)
			return false;
		CloseClipboard();
		return true;
	}
	else return false;
}

std::wstring CCommon::GetClipboardString()
{
    std::wstring clipboardString;
    if (OpenClipboard(NULL))
    {
        HGLOBAL hClip = GetClipboardData(CF_UNICODETEXT);
        if (hClip)
        {
            const wchar_t* pBuff = (const wchar_t*)GlobalLock(hClip);
            GlobalUnlock(hClip);
            clipboardString = pBuff;
        }
        CloseClipboard();
    }
    return clipboardString;
}

COLORREF CCommon::GetWindowsThemeColor()
{
    DWORD crColorization;
    BOOL fOpaqueBlend;
    COLORREF theme_color{};
    HRESULT result = DwmGetColorizationColor(&crColorization, &fOpaqueBlend);
    if (result == S_OK)
    {
        BYTE r, g, b;
        r = (crColorization >> 16) % 256;
        g = (crColorization >> 8) % 256;
        b = crColorization % 256;
        theme_color = RGB(r, g, b);
    }
    return theme_color;
}

CString CCommon::LoadText(UINT id, LPCTSTR back_str)
{
	CString str;
	str.LoadString(id);
	if (back_str != nullptr)
		str += back_str;
	return str;
}

CString CCommon::LoadText(LPCTSTR front_str, UINT id, LPCTSTR back_str)
{
	CString str;
	str.LoadString(id);
	if (back_str != nullptr)
		str += back_str;
	if (front_str != nullptr)
		str = front_str + str;
	return str;
}

CString CCommon::StringFormat(LPCTSTR format_str, const std::initializer_list<CVariant>& paras)
{
	CString str_rtn = format_str;
	int index = 1;
	for (const auto& para : paras)
	{
		CString para_str = para.ToString();
		CString format_para;
		format_para.Format(_T("<%%%d%%>"), index);
		str_rtn.Replace(format_para, para_str);

		index++;
	}
	return str_rtn;
}

CString CCommon::LoadTextFormat(UINT id, const std::initializer_list<CVariant>& paras)
{
	CString str;
	str.LoadString(id);
	return StringFormat(str.GetString(), paras);
}

unsigned int CCommon::StringToNumber(const CString& str)
{
    //判断进制
    int radix{ 10 };
    if (str.GetLength() >= 3 && str[0] == _T('0') && (str[1] == _T('x') || str[1] == _T('X')))
    {
        radix = 16;
    }
    else if (str.GetLength() >= 2 && str[0] == _T('0'))
    {
        radix = 8;
    }
    TCHAR* end_ptr{};
    return _tcstoul(str.GetString(), &end_ptr, radix);
}

void CCommon::StringSplit(const std::wstring& str, wchar_t div_ch, std::vector<std::wstring>& results, bool skip_empty, bool trim)
{
    results.clear();
    size_t split_index = -1;
    size_t last_split_index = -1;
    while (true)
    {
        split_index = str.find(div_ch, split_index + 1);
        std::wstring split_str = str.substr(last_split_index + 1, split_index - last_split_index - 1);
        if (trim)
            StringNormalize(split_str);
        if (!split_str.empty() || !skip_empty)
            results.push_back(split_str);
        if (split_index == std::wstring::npos)
            break;
        last_split_index = split_index;
    }
}

bool CCommon::IsCharHex(char ch)
{
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

bool CCommon::IsStringHex(std::wstring& strHex)
{
    StringNormalize(strHex);
    if (strHex.empty())
        return false;
    if (strHex[0] == L'#')
        strHex = strHex.substr(1);
    for (auto& ch : strHex)
    {
        if (!IsCharHex(ch))
            return false;
    }
    return true;
}
