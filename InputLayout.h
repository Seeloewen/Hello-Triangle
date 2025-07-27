#pragma once

#include <dxgi.h>
#include <string>
#include <d3d11.h>
#include <vector>

#include "Util.h"

class InputLayout
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutInfo;
	ComPtr<ID3D11InputLayout> inputLayout;

public:
	void addInfoElement(const char* semanticName, DXGI_FORMAT format, size_t offset);
	HRESULT create(ComPtr<ID3DBlob> shaderBlob);
	ComPtr<ID3D11InputLayout>& get();
};