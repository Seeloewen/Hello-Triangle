#pragma once

#include "Shader.h"

class PixelShader : public Shader
{
public:
	PixelShader(const std::wstring fileName) : Shader(fileName) {};
	HRESULT create() override;
	void use() override;
};