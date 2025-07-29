#pragma once

#include "Shader.h"

class VertexShader : public Shader
{
public:
	VertexShader(const std::wstring fileName) : Shader(fileName) {};
	HRESULT create() override;
	void use() override;
};