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
	int posX;
	int posY;

	GLFWwindow* window = nullptr;

	void update();
	void render();
	HRESULT init();

public:
	Renderer* renderer = nullptr;

	Application(std::string title);
	~Application();
	void run();
	void terminate();
	GLFWwindow* getWindow();
};

inline Application* instance;