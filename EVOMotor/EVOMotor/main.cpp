#include "Platform/debug.h"
#include "Platform/Window.h"
#include "Platform/Texture.h"
#include "Include/Engine.h"

float getTotalTime();

int main(void)
{
    /* Initialize the library */

	Window* window = new Window();
	window->createWindow(Engine::windowWidth,Engine::windowHeight,"I made dis");
	Engine* engine;
	engine = new Engine();
	engine->init();

	float deltaTime = 0.0f;
	float newTime = 0.0f;
	float oldTime = 0.0f;

    /* Create a windowed mode window and its OpenGL context */
	while(window->isOpen())
	{
		oldTime = newTime;
		newTime = getTotalTime();
		deltaTime = newTime - oldTime;
		window->pollEvents();
		engine->update();
		engine->draw();
		window->SwapBuffers();
		//std::cout << deltaTime <<std::endl;
	}

	delete engine;
	delete window;
    return 0;
}


float getTotalTime()
{
	return glfwGetTime();
}