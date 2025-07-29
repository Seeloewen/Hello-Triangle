#pragma once

#include <d3d11.h>
#include <dxgi1_3.h>
#include <vector>

#include "Util.h"
#include "ShaderLayout.h"

class PrimitiveRenderer;
class VertexShader;
class PixelShader;
class InputLayout;
class VertexBuffer;

class Renderer
{
public:
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;

	~Renderer();
	void render();
	HRESULT init();

	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
private:
	PrimitiveRenderer* primitiveRenderer = nullptr;

	ComPtr<IDXGIFactory2> dxgiFactory = nullptr;
	ComPtr<IDXGISwapChain1> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	VertexBuffer* vertexBuffer = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	InputLayout* vertexInputLayout = nullptr;
	std::vector<PrimitiveVertexLayout> vertices;


};