#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <d3d11.h>

#include "Renderer.h"
#include "Application.h"
#include "PrimitiveRenderer.h"

HRESULT Renderer::init()
{
	//Create the D3D11 device (used for creating shaders, textures etc.) and the device context for draw calls to the graphics card
	const D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &deviceFeatureLevel, 1, D3D11_SDK_VERSION, &device, nullptr, &deviceContext)))
	{
		print("Could not create D3D11 device and device context");
		return E_FAIL;
	}
	print("Created D3D11 device and device context");

	//Create the DXGI factory, which is used for creating the swapchain later on
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory))))
	{
		print("Could not create DXGIFactory");
		return E_FAIL;
	}
	print("Created DXGIFactory");

	//Create swapchain description and actual thing
	DXGI_SWAP_CHAIN_DESC1 scd = {};
	scd.Width = instance->getWidth();
	scd.Height = instance->getHeight();
	scd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Scaling = DXGI_SCALING_STRETCH;
	scd.Flags = {};

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC scfd = {};
	scfd.Windowed = true;

	if (FAILED(dxgiFactory->CreateSwapChainForHwnd(device.Get(), glfwGetWin32Window(instance->getWindow()), &scd, &scfd, nullptr, &swapChain)))
	{
		print("Could not create Swapchain");
		return E_FAIL;
	}
	print("Created Swapchain");

	//Create backbuffer
	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	if (FAILED(swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
	{
		print("Could not get Back Buffer from Swapchain");
		return E_FAIL;
	}

	//Create Render Target View
	if (FAILED(device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget)))
	{
		print("Could not create Render Target View");
		return E_FAIL;
	}
	print("Created Render Target View");

	primitiveRenderer = new PrimitiveRenderer();
	primitiveRenderer->init();

	return S_OK;
}

void Renderer::render()
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = instance->getWidth();
	viewport.Height = instance->getHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	const float clearColor[] = { 0.243f, 0.898f, 0.941f, 1.0f };
	deviceContext->ClearRenderTargetView(renderTarget.Get(), clearColor); //Clear target view
	deviceContext->RSSetViewports(1, &viewport);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //
	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);

	primitiveRenderer->render();

	swapChain->Present(0, 0);
}

Renderer::~Renderer()
{
	renderTarget.Reset();

	delete primitiveRenderer;
}