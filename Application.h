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
#include "Renderer.h"

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

public:
	Application(std::string title);
	~Application();
	void run();
	void terminate();

	Renderer* renderer = nullptr;

	UINT getWidth();
	UINT getHeight();
	GLFWwindow* getWindow();
};

inline Application* instance;