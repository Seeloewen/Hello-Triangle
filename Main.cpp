#include "Util.h"
#include "Application.h"

int main()
{
	print("Hello Triangle by Seeloewen");
	print("Third-party libraries:");
	print("nanotime (https://github.com/nightmareci/nanotime)");
	print("GLFW (https://github.com/glfw/glfw)");

	Application* app = new Application("Hello Triangle by Seeloewen");

	app->run();
	delete app;
}