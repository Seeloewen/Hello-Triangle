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
#include "Resolution.h"
#include "PrimitiveRenderer.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

Application::Application(std::string title)
{
	//Potentially allow input for pos and size later
	width = 1280;
	height = 720;
	this->posX = 100;
	this->posY = 100;
	this->title = title;
}

HRESULT Application::init()
{
	instance = this;

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

	renderer = new Renderer();
	HRESULT hr = renderer->init();
	return hr;
}

void Application::run()
{
	//Initialize everything rendering related (window, d3d11 pipeline)
	HRESULT hr = init();
	if (FAILED(hr))
	{
		print(HrToString(hr));
		throw std::exception("Could not initialize application");
	}
	print("Successfully initialized the application. Starting rendering...");

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		update();
		renderer->render();
	}
}

void Application::update()
{
	renderer->primitiveRenderer->drawTriangle({ 200, 10, 400, 10, 200, 200 }, { 0,255,0, 155 });
	renderer->primitiveRenderer->drawRectangle({ 600, 200, 700, 300 }, { 80, 60, 203, 255 });
	renderer->primitiveRenderer->drawRectangle({ 650, 200, 750, 300 }, { 80, 255, 20, 100 });
}

GLFWwindow* Application::getWindow()
{
	return window;
}

void Application::terminate()
{
	delete renderer;
	glfwDestroyWindow(window);
	glfwTerminate();
}

Application::~Application()
{
	terminate();
}