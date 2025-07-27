#pragma once

#include <string>
#include <wrl.h>

template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

void print(std::string s);
std::string WStringToString(const std::wstring& wstr);
std::string HrToString(HRESULT hr);