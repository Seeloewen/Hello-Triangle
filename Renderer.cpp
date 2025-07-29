#define GLFW_EXPOSE_NATIVE_WIN32
#define NANOTIME_IMPLEMENTATION

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <d3d11.h>
#include <chrono>

#include "nanotime.h"
#include "Renderer.h"
#include "Application.h"
#include "PrimitiveRenderer.h"
#include "Resolution.h"

HRESULT Renderer::init()
{
	HRESULT hr;

	//Create the D3D11 device (used for creating shaders, textures etc.) and the device context for draw calls to the graphics card
	const D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &deviceFeatureLevel, 1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
	if (FAILED(hr))
	{
		print("Could not create D3D11 device and device context");
		return hr;
	}
	print("Created D3D11 device and device context");

	//Create the DXGI factory, which is used for creating the swapchain later on
	hr = CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory));
	if (FAILED(hr))
	{
		print("Could not create DXGIFactory");
		return hr;
	}
	print("Created DXGIFactory");

	//Create swapchain description and actual thing
	DXGI_SWAP_CHAIN_DESC1 scd = {};
	scd.Width = width;
	scd.Height = height;
	scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Scaling = DXGI_SCALING_STRETCH;
	scd.Flags = {};

	hr = dxgiFactory->CreateSwapChainForHwnd(device.Get(), glfwGetWin32Window(instance->getWindow()), &scd, nullptr, nullptr, &swapChain);
	if (FAILED(hr))
	{
		print("Could not create Swapchain");
		return hr;
	}
	print("Created Swapchain");

	//Create backbuffer
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	if (FAILED(hr))
	{
		print("Could not get Back Buffer from Swapchain");
		return hr;
	}

	//Create Render Target View
	hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget);
	if (FAILED(hr))
	{
		print("Could not create Render Target View");
		return hr;
	}
	print("Created Render Target View");

	//Setup blending for transparency
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	device->CreateBlendState(&blendDesc, &blendState);

	//Setup the viewport
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	primitiveRenderer = new PrimitiveRenderer();
	hr = primitiveRenderer->init();

	return hr;
}

void Renderer::render()
{
	const float clearColor[] = { 0.243f, 0.898f, 0.941f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTarget.Get(), clearColor); //Clear target view
	deviceContext->RSSetViewports(1, &viewport);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	UINT sampleMask = 0xffffffff;
	deviceContext->OMSetBlendState(blendState.Get(), blendFactor, sampleMask);

	primitiveRenderer->render();

	swapChain->Present(0, 0);

	updateFrameStats();
}

void Renderer::updateFrameStats()
{
	//Calculate time passed since last stat call
	uint64_t now = nanotime_now();
	uint64_t dif = nanotime_interval(lastRender, now, nanotime_now_max());
	frames++;

	if (dif > 1000000000) //1 sec
	{
		//Print fps and frametime
		print(std::to_string(frames) + "fps (" + std::to_string(1000.0f / frames) + "ms)");
		lastRender = now;
		frames = 0;
	}
}

Renderer::~Renderer()
{
	renderTarget.Reset();

	delete primitiveRenderer;
}