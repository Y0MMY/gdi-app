#pragma once

#include <string>
#include <vector>
#include "../stdafx.h"


class Helper
{
public:
	static bool isPointInRect(int x, int y, RectF rect);
	static bool isPointInRect(int x, int y, RECT rect);
	static bool isPointInRect(int x, int y, int x2, int y2);
	static bool isPointInRect(int x, int y, Rect rect);
	static std::wstring GetWC(const std::string str)
	{
		const char* c = str.c_str();
		const size_t cSize = str.size() + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, c, cSize);
		std::wstring w_string(wc);
		delete[] wc;
		return w_string;
	}
	static std::wstring ConvertUtf8ToWide(const std::string& str)
	{
		int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
		std::wstring wstr(count, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &wstr[0], count);
		return wstr;
	}
	
	static std::wstring ConvertStringToWstring(const std::string& str)
	{
		if (str.empty())
		{
			return std::wstring();
		}
		int num_chars = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), str.length(), NULL, 0);
		std::wstring wstrTo;
		if (num_chars)
		{
			wstrTo.resize(num_chars);
			if (MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), str.length(), &wstrTo[0], num_chars))
			{
				return wstrTo;
			}
		}
		return std::wstring();
	}
};