#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "utilities/FPSCounter.h"
#include "Engine.h"

class Engine; //déclaration anticipée pour éviter une dépendance circulaire.

class Window
{
public:
	Window(int width, int height, std::string title, bool vSync);

	int init();
	bool shouldClose();
	void setShouldClose(bool value);
	bool isKeyPressed(int keyCode);
	void update();
	void clear();

	int getWidth();
	int getHeight();
	std::string getTitle();
	GLFWwindow* getHandle();

	bool isResized();
	bool isvSync();

	void setResized(bool value);
	void setHeight(int value);
	void setWidth(int value);
	void setClearColor(float r, float g, float b, float alpha);
	void setvSync(bool value);
	
private:
	GLFWwindow* glfwHandle;
	int width;
	int height;
	std::string title;
	bool resized;
	bool vSync;

	float Z_NEAR = 0.01f;
	float Z_FAR = 1000.0f;
	float FOV = glm::radians(60.0f);
	glm::mat4 projectionMatrix;
};

