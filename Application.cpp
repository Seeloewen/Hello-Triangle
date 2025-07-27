#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <string>
#include <GLFW/glfw3native.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <iostream>

#include "InputLayout.h"
#include "Util.h"
#include "Application.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

Application::Application(std::string title)
{
	//Potentially allow input for pos and size later
	this->width = 1280;
	this->height = 720;
	this->posX = 100;
	this->posY = 100;
	this->title = title;
}

HRESULT Application::init()
{
	instance = this;
	if (FAILED(initWindow()) || FAILED(initD3D11())) return E_FAIL;
}

HRESULT Application::initD3D11()
{
	//Create the D3D11 device (used for creating shaders, textures etc.) and the device context for draw calls to the graphics card
	const D3D_FEATURE_LEVEL deviceFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		&deviceFeatureLevel,
		1,
		D3D11_SDK_VERSION,
		&device,
		nullptr,
		&deviceContext
	)))
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
	scd.Width = width;
	scd.Height = height;
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

	if (FAILED(dxgiFactory->CreateSwapChainForHwnd(
		device.Get(),
		glfwGetWin32Window(window),
		&scd,
		&scfd,
		nullptr,
		&swapChain)))
	{
		print("Could not create Swapchain");
		return E_FAIL;
	}
	print("Created Swapchain");

	//Create the swap chain resources
	if (FAILED(createSwapchainResources())) return E_FAIL;

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
	vertexInputLayout->addInfoElement("POSITION", DXGI_FORMAT_R32G32B32_FLOAT, offsetof(VertexPositionColor, position));
	vertexInputLayout->addInfoElement("COLOR", DXGI_FORMAT_R32G32B32_FLOAT, offsetof(VertexPositionColor, color));
	if (FAILED(vertexInputLayout->create(vertexShader->shaderBlob)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Application::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	vertices.push_back({ DirectX::XMFLOAT3{  x1,  y1, 0.0f }, DirectX::XMFLOAT3{ 0.25f, 0.39f, 0.19f } });
	vertices.push_back({ DirectX::XMFLOAT3{  x2,  y2, 0.0f }, DirectX::XMFLOAT3{ 0.25f, 0.39f, 0.19f } });
	vertices.push_back({ DirectX::XMFLOAT3{  x3,  y3, 0.0f }, DirectX::XMFLOAT3{ 0.25f, 0.39f, 0.19f } });
}

HRESULT Application::initWindow()
{
	//Initiliaze GLFW and exit if that fails
	if (!glfwInit())
	{
		print("Could not initialize GLFW");
		return E_FAIL;
	}
	print("Initiliazed GLFW");

	//Provide window hints and create window
	glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_FALSE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	window = glfwCreateWindow(width, height, "Hello Weberich", nullptr, nullptr);

	if (window == nullptr)
	{
		print("Could not create Window");
		return E_POINTER;
	}
	print("Created Window");

	glfwSetWindowPos(window, posX, posY);
}

void Application::run()
{
	if (FAILED(init()))
	{
		throw std::exception("Could not initialize window");
	}

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		render();
	}
}

void Application::update()
{
	vertices.clear();

	drawTriangle(0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f);

	/*vertices.push_back({DirectX::XMFLOAT3{0.0f,  0.5f, 0.0f}, DirectX::XMFLOAT3{0.25f, 0.39f, 0.19f}});
	vertices.push_back({ DirectX::XMFLOAT3{  0.5f, -0.5f, 0.0f }, DirectX::XMFLOAT3{ 0.44f, 0.75f, 0.35f } });
	vertices.push_back({ DirectX::XMFLOAT3{ -0.5f, -0.5f, 0.0f }, DirectX::XMFLOAT3{ 0.38f, 0.55f, 0.20f } });*/
}

void Application::render()
{
	//Create viewport
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	const float clearColor[] = { 0.243f, 0.898f, 0.941f, 1.0f };

	//Clear and set viewport and rendertarget
	deviceContext->ClearRenderTargetView(renderTarget.Get(), clearColor);

	//Render pipeline
	deviceContext->IASetInputLayout(vertexInputLayout->get().Get()); //Bind input layout
	UINT stride = sizeof(VertexPositionColor);
	UINT vertexOffset = 0;

	//Create buffer info and vertex buffer
	D3D11_BUFFER_DESC bufferInfo = {};
	bufferInfo.ByteWidth = vertices.size() * sizeof(VertexPositionColor);
	bufferInfo.Usage = D3D11_USAGE_IMMUTABLE;
	bufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA resourceData = {};
	resourceData.pSysMem = vertices.data();
	device->CreateBuffer(
		&bufferInfo,
		&resourceData,
		&vertexBuffer);

	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &vertexOffset); //Bind buffer
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); //How to interpret data (as triangles)
	deviceContext->RSSetViewports(1, &viewport); //Set viewport
	deviceContext->VSSetShader(vertexShader->get().Get(), nullptr, 0); //Set vertex shader
	deviceContext->PSSetShader(pixelShader->get().Get(), nullptr, 0); //Set pixel shader
	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);
	deviceContext->Draw(3, 0);

	swapChain->Present(0, 0);

}

HRESULT Application::createSwapchainResources()
{
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

	return S_OK;
}

void Application::destroySwapchainResources()
{
	renderTarget.Reset();
}

void Application::terminate()
{
	destroySwapchainResources();
	glfwDestroyWindow(window);
	glfwTerminate();
}

Application::~Application()
{
	terminate();
}