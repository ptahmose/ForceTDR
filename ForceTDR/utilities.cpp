#include "stdafx.h"
#include "utilities.h"
#include <locale>
#include <codecvt>

std::string convertToCurrentLocale(const wchar_t* sz)
{
	UINT stdOutCodepage = GetConsoleOutputCP();
	int size = WideCharToMultiByte(stdOutCodepage, 0, sz, -1, NULL, 0, NULL, NULL);

	std::string retString;
	retString.reserve(size);
	int r = WideCharToMultiByte(stdOutCodepage, 0, sz, -1, &retString[0], size, NULL, NULL);
	return retString;
}