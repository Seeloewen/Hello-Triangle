#pragma once

#include "Util.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "Rect.h"
#include "Triangle.h"
#include "VertexBuffer.h"

class PrimitiveRenderer
{
public:
	void render();
	HRESULT init();

	void drawRectangle(Rect rect, Color c);
	void drawTriangle(Triangle tri, Color c);
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	InputLayout* vertexInputLayout = nullptr;
	PrimitiveVertexBuffer* vertexBuffer = nullptr;
private:
	
};
