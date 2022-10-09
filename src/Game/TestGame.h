#pragma once
#include <glad/glad.h>
#include "../Engine/IGame.h"
#include "Engine/Mesh.h"
#include "Renderer.h"

class Engine; //d�claration anticip�e pour �viter une d�pendance circulaire.

class TestGame : public Game
{

public:
	TestGame();
	void init();
	void input(Window* w);
	void update(float interval);
	void render(Window* w);
	void flush();

private:
	Mesh* m;
	Renderer* r;

	Shader* shader;
};

