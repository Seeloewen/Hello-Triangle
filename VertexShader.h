#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader(const std::wstring fileName) : Shader(fileName) {};
	HRESULT create() override;
	ComPtr<ID3D11VertexShader> get();
};