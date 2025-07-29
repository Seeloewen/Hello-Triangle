#include "Util.h"
#include "Application.h"

int main()
{
	print("Hello Triangle by Seeloewen");

	Application* app = new Application("Hello Triangle by Seeloewen");

	app->run();
	delete app;
}