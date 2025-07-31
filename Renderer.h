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

	PrimitiveRenderer* primitiveRenderer = nullptr;

	~Renderer();
	void render();
	HRESULT init();
	void clearState();
	void drawTests();

private:
	void updateFrameStats();

	HRESULT initDevice();
	HRESULT initSwapChain();
	HRESULT initBlending();
	HRESULT initRenderTargetView();

	ComPtr<IDXGIFactory2> dxgiFactory = nullptr;
	ComPtr<IDXGISwapChain1> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	ComPtr<ID3D11BlendState> blendState = nullptr;
	ComPtr<ID3D11Debug> debugLayer = nullptr;

	D3D11_VIEWPORT viewport = {};

	uint64_t lastRender = 0;
	int frames;
};