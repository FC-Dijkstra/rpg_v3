#include "TestGame.h"
#include <cmath>

TestGame::TestGame()
{
	//r = new Renderer();
}

void TestGame::init()
{
	//r->init();

	std::vector<float> pos =
	{
		-0.5f,  0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,  -0.5f, 0.0f
	};

	std::vector<float> col =
	{
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	std::vector<int> idx =
	{
		0, 1, 2, 2, 3, 0
	};

	m = new Mesh(&pos, &col, &idx);

	shader = new Shader("shaders/vertexShader.generic.glsl", "shaders/fragmentShader.generic.glsl");

	glEnable(GL_DEPTH_TEST);
}

void TestGame::input(Window* w)
{
	if (w->isKeyPressed(GLFW_KEY_ESCAPE))
	{
		Engine::instance->shouldStop();
	}
}

void TestGame::update(float interval)
{

}

void TestGame::render(Window* w)
{

	//w->setClearColor(sin(glfwGetTime()), cos(glfwGetTime()), cos(glfwGetTime() + 0.5), 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shader->bind();

	m->render();

	shader->unbind();
}

void TestGame::flush()
{
	//r->flush();
	m->flush();
}