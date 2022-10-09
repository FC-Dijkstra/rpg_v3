#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include "IGame.h"
#include "Window.h"
#include <iostream>
#include <Engine/UI.h>

class Window; //déclaration anticipée pour éviter d'avoir une dépendance circulaire.
class Game; //déclaration anticipée pour éviter d'avoir une dépendance circulaire

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
	UI* ui;
	Game* game;
	bool stop;

	const float TARGET_FPS = 60;
};

