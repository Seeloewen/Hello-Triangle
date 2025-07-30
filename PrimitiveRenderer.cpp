#include "PrimitiveRenderer.h"
#include "Application.h"
#include "ShaderLayout.h"

HRESULT PrimitiveRenderer::init()
{
	HRESULT hr;

	//Create shaders
	vertexShader = new VertexShader(L"Vertex.hlsl");
	hr = vertexShader->create();
	if (FAILED(hr))
	{
		print("Could not create shader!");
		return hr;
	}

	pixelShader = new PixelShader(L"Pixel.hlsl");
	hr = pixelShader->create();
	if (FAILED(hr))
	{
		print("Could not create shader!");
		return hr;
	}

	//Create input layout
	vertexInputLayout = new InputLayout();
	vertexInputLayout->addInfoElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, 12);
	vertexInputLayout->addInfoElement("COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT, 16);
	hr = vertexInputLayout->create(vertexShader);
	if (FAILED(hr)) return hr;

	vertexBuffer = new VertexBuffer(vertexInputLayout);

	return S_OK;
}

void PrimitiveRenderer::render()
{
	vertexBuffer->use();
	vertexShader->use();
	pixelShader->use();

	vertexBuffer->flush();
	instance->renderer->clearState();
}

void PrimitiveRenderer::drawRectangle(Rect rect, Color c)
{
	vertexBuffer->put(rect.x1, rect.y1, c.r, c.g, c.b, c.a);
	vertexBuffer->put(rect.x2, rect.y1, c.r, c.g, c.b, c.a);
	vertexBuffer->put(rect.x2, rect.y2, c.r, c.g, c.b, c.a);
	vertexBuffer->put(rect.x1, rect.y1, c.r, c.g, c.b, c.a);
	vertexBuffer->put(rect.x2, rect.y2, c.r, c.g, c.b, c.a);
	vertexBuffer->put(rect.x1, rect.y2, c.r, c.g, c.b, c.a);
}


void PrimitiveRenderer::drawTriangle(Triangle tri, Color c)
{
	vertexBuffer->put(tri.x1, tri.y1, c.r, c.g, c.b, c.a);
	vertexBuffer->put(tri.x2, tri.y2, c.r, c.g, c.b, c.a);
	vertexBuffer->put(tri.x3, tri.y3, c.r, c.g, c.b, c.a);
}

void PrimitiveRenderer::drawQuad(Quad quad, Color c)
{
	vertexBuffer->put(quad.x1, quad.y1, c.r, c.g, c.b, c.a);
	vertexBuffer->put(quad.x2, quad.y2, c.r, c.g, c.b, c.a);
	vertexBuffer->put(quad.x3, quad.y3, c.r, c.g, c.b, c.a);
	vertexBuffer->put(quad.x1, quad.y1, c.r, c.g, c.b, c.a);
	vertexBuffer->put(quad.x3, quad.y3, c.r, c.g, c.b, c.a);
	vertexBuffer->put(quad.x4, quad.y4, c.r, c.g, c.b, c.a);
}

PrimitiveRenderer::~PrimitiveRenderer()
{
	delete vertexShader;
	delete pixelShader;
	delete vertexInputLayout;
	delete vertexBuffer;
}