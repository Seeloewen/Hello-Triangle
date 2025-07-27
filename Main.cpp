#include <iostream>
#include <GLFW/glfw3.h>
#include "Util.h"
#include "Application.h"

int main()
{
	print("Hello Weberich");

	Application* app = new Application("Hello Weberich");

	app->run();
	delete app;
}