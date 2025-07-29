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
	drawTriangle({0,0,0,0,0,0}, {0,0,0});

	vertexBuffer->use();

	vertexShader->use();
	pixelShader->use();

	instance->renderer->deviceContext->Draw(3, 0);
}

void PrimitiveRenderer::drawRectangle(Rect rect, Color c)
{

}


void PrimitiveRenderer::drawTriangle(Triangle tri, Color c)
{
	vertexBuffer->put(0.0f, 0.5f, 1.0f, 0.0f, 0.0f); // links unten, rot
	vertexBuffer->put(0.5f, -0.5f, 0.0f, 1.0f, 0.0f);  // rechts unten, grün
	vertexBuffer->put(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f);   // oben, blau
}