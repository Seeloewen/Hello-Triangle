#include "PrimitiveRenderer.h"
#include "Application.h"
#include "ShaderLayout.h"

HRESULT PrimitiveRenderer::init()
{
	//Create shaders
	vertexShader = new VertexShader(L"Vertex.hlsl");
	if (FAILED(vertexShader->create()))
	{
		print("Could not create shader!");
		return E_FAIL;
	}

	pixelShader = new PixelShader(L"Pixel.hlsl");
	if (FAILED(pixelShader->create()))
	{
		print("Could not create shader!");
		return E_FAIL;
	}

	//Create input layout
	vertexInputLayout = new InputLayout();
	vertexInputLayout->addInfoElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 12);
	vertexInputLayout->addInfoElement("COLOR", DXGI_FORMAT_R32G32B32_FLOAT, 12);
	if (FAILED(vertexInputLayout->create(vertexShader)))
	{
		return E_FAIL;
	}

	vertexBuffer = new VertexBuffer(vertexInputLayout);

	return S_OK;
}

void PrimitiveRenderer::render()
{
	drawTriangle({ 200, 10, 400, 10, 200, 200 }, { 0,255,0 });
	drawRectangle({ 600, 200, 700, 300 }, { 150, 162, 44 });

	vertexBuffer->use();

	vertexShader->use();
	pixelShader->use();

	vertexBuffer->flush();
}

void PrimitiveRenderer::drawRectangle(Rect rect, Color c)
{
	vertexBuffer->put(rect.x1, rect.y1, c.r, c.g, c.b);
	vertexBuffer->put(rect.x2, rect.y1, c.r, c.g, c.b);
	vertexBuffer->put(rect.x2, rect.y2, c.r, c.g, c.b);
	vertexBuffer->put(rect.x1, rect.y1, c.r, c.g, c.b);
	vertexBuffer->put(rect.x2, rect.y2, c.r, c.g, c.b);
	vertexBuffer->put(rect.x1, rect.y2, c.r, c.g, c.b);
}


void PrimitiveRenderer::drawTriangle(Triangle tri, Color c)
{
	vertexBuffer->put(tri.x1, tri.y1, c.r, c.g, c.b);
	vertexBuffer->put(tri.x2, tri.y2, c.r, c.g, c.b);
	vertexBuffer->put(tri.x3, tri.y3, c.r, c.g, c.b);
}