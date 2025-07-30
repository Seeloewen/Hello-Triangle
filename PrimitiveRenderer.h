#pragma once

#include "Util.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"
#include "Rect.h"
#include "Triangle.h"
#include "Quad.h"
#include "VertexBuffer.h"

class PrimitiveRenderer
{
public:
	~PrimitiveRenderer();

	void render();
	HRESULT init();

	void drawRectangle(Rect rect, Color c);
	void drawTriangle(Triangle tri, Color c);
	void drawQuad(Quad quad, Color c);

private:
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	InputLayout* vertexInputLayout = nullptr;
	VertexBuffer* vertexBuffer = nullptr;
};
