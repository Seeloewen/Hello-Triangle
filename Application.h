#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include <d3d11.h>
#include <dxgi1_3.h>
#include <DirectXMath.h>
#include <vector>

#include "VertexShader.h"
#include "PixelShader.h"
#include "InputLayout.h"

struct VertexPositionColor
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 color;
};

class Application
{

private:
	std::string title;
	int32_t width;
	int32_t height;
	int32_t posX;
	int32_t posY;
	GLFWwindow* window = nullptr;

	void update();
	void render();
	HRESULT init();
	HRESULT initWindow();
	HRESULT initD3D11();

public:
	Application(std::string title);
	~Application();
	void run();
	void terminate();
	HRESULT createSwapchainResources();
	void destroySwapchainResources();
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);

	ComPtr<IDXGIFactory2> dxgiFactory = nullptr;
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain1> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> renderTarget = nullptr;
	VertexShader* vertexShader = nullptr;
	PixelShader* pixelShader = nullptr;
	InputLayout* vertexInputLayout = nullptr;
	ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	std::vector<VertexPositionColor> vertices;

};

inline Application* instance;