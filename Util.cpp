#include <string>
#include <iostream>

#include "Util.h"
#include <Windows.h>

void print(std::string s)
{
	std::cout << s << std::endl;
}

std::string WStringToString(const std::wstring& wstr) //definitely written by me and not some ai
{
    if (wstr.empty())
        return {};

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &str[0], sizeNeeded, nullptr, nullptr);
    return str;
}

std::string HrToString(HRESULT hr)
{
    wchar_t* errorMsg = nullptr;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        hr,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&errorMsg,
        0,
        nullptr);

    std::wstring message = errorMsg ? errorMsg : L"Unknown error";
    LocalFree(errorMsg);
    return WStringToString(message);
}