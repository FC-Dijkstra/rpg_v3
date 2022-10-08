#pragma once
#include "../lib/glad/glad.h"
#include "lib/glm/glm.hpp"
#include "lib/GLFW/glfw3.h"
#include <string>
#include "IGame.h"
#include "Window.h"
#include <iostream>

class Window;
class Game;

class Engine
{
public:
	Engine(std::string windowTitle, int width, int height, bool vSync, Game* g);

	static Engine* instance;

	void init();
	void loop();
	void run();
	void shouldStop();

	Window* getWindow();

private:
	Window* window;
	Game* game;
	bool stop;

	const float TARGET_FPS = 60;
};

