#pragma once

#include <d3d11.h>

#include "Util.h"
#include "Application.h"
#include "ShaderLayout.h"

class VertexBuffer
{
private:
	ComPtr<ID3D11Buffer> buffer = nullptr;
	InputLayout* inputLayout = nullptr;
	std::vector<float> vertices;
public:
	VertexBuffer(InputLayout* inputLayout);
    ID3D11Buffer* get();
	void put(float x, float y, float r, float g, float b);
    void use();
	void flush();
};