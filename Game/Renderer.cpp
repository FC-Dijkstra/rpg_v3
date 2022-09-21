#include "Renderer.h"

Renderer::Renderer()
{

}

void Renderer::init()
{
	shader = new Shader("shaders/vertexShader.generic.glsl", "shaders/fragmentShader.generic.glsl");
}

void Renderer::render(Window* w, Mesh* m)
{
	glClear(GL_COLOR_BUFFER_BIT);
	shader->bind();
	
	m->render();

	glBindVertexArray(0);
	shader->unbind();
}

void Renderer::flush()
{
	if (shader != nullptr)
	{
		delete shader;
	}
}