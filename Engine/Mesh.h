#pragma once
#include "../lib/glad/glad.h"
#include <vector>
#include <GL/GL.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Mesh
{
public:
	Mesh(std::vector<float>* positions, std::vector<float>* colors, std::vector<int>* indices);
	void render();

	GLuint getVaoID();
	int getVertexCount();

	void flush();

private:
	GLuint vaoID;
	GLuint vboID;
	GLuint eboID;

	GLuint vertexCount;
	int colorOffset;
};

