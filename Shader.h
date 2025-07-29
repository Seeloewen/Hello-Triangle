#pragma once

#include <string>
#include <d3dcommon.h>
#include <wrl.h>
#include <d3d11.h>

#include "Util.h"

class Shader
{
public:
	ComPtr<ID3DBlob> shaderBlob = nullptr;
	Shader(const std::wstring fileName);
	virtual HRESULT create() = 0;
	virtual void use() = 0;
	ID3D11DeviceChild* get();
protected:
	std::wstring fileName;
	ComPtr<ID3D11DeviceChild> shader = nullptr;
	ComPtr<ID3DBlob> compile(const std::wstring fileName, const std::string profile);
};