#pragma once

#include <string>
#include <wrl.h>

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

void print(std::string s);
std::string WStringToString(const std::wstring& wstr);
std::string HrToString(HRESULT hr);

struct Color
{
	float r, g, b, a;

	Color(UINT r, UINT g, UINT b, UINT a = 255) : r(r / 255), g(g / 255), b(b / 255), a(a / 255) {};
	Color(UINT c, UINT a = 255) : r(c / 255), g(c / 255), b(c / 255), a(a / 255) {};
};