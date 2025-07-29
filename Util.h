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

	Color(UINT r, UINT g, UINT b, UINT a = 255) : r(r / 255.0f), g(g / 255.0f), b(b / 255.0f), a(a / 255.0f) {};
	Color(UINT c, UINT a = 255.0f) : r(c / 255.0f), g(c / 255.0f), b(c / 255.0f), a(a / 255.0f) {};
};