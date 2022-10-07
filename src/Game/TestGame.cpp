#include "TestGame.h"
#include <cmath>

TestGame::TestGame()
{
	//r = new Renderer();
	this->r = NULL;
	this->m = NULL;
	this->shader = NULL;
}

void TestGame::init()
{
	//r->init();

	std::vector<float>* pos = new std::vector<float>(
	{
		-0.5f,  0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,  -0.5f, 0.0f
	});

	std::vector<float>* col = new std::vector<float>(
	{
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	});

	std::vector<int>* idx = new std::vector<int>(
	{
		0, 1, 2, 2, 3, 0
	});

	this->m = new Mesh(pos, col, idx);

	shader = new Shader("shaders/vertexShader.generic.glsl", "shaders/fragmentShader.generic.glsl", nullptr);
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
	glEnable(GL_DEPTH_TEST);
	shader->bind();

	this->m->render();

	shader->unbind();
}

void TestGame::flush()
{
	//r->flush();
	m->flush();
}