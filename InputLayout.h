#pragma once

#include <dxgi.h>
#include <string>
#include <d3d11.h>
#include <vector>

#include "Shader.h"
#include "Util.h"

class InputLayout
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutInfo;
	ComPtr<ID3D11InputLayout> inputLayout;
	UINT size; //Total size in bytes of the data described by this info

public:
	void addInfoElement(const char* semanticName, DXGI_FORMAT format, size_t offset);
	HRESULT create(Shader* shader);
	ID3D11InputLayout* get();
	UINT getSize();
};