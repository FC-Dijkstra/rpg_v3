#include "Window.h"


Window::Window(int width, int height, std::string title, bool vSync)
{
	this->width = width;
	this->height = height;
	this->title = title;
	this->resized = false;
	this->vSync = vSync;
}

int Window::init()
{
	if (!glfwInit())
	{
		fprintf(stderr, "impossible d'initaliser l'application");
		return -1;
	}
	glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3.);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->glfwHandle = glfwCreateWindow(this->width, this->height, this->title.c_str(), NULL, NULL);
	if (glfwHandle == NULL)
	{
		fprintf(stderr, "impossible de créer la fenêtre GLFW");
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(glfwHandle, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetFramebufferSizeCallback(glfwHandle, [](GLFWwindow* glfwWindow, int width, int height)
		{
			Window* w = Engine::instance->getWindow();
			w->setWidth(width);
			w->setHeight(height);
			w->setResized(true);
		});

	glfwMakeContextCurrent(glfwHandle);

	//glewExperimental = true;
	//if (glewInit() != GLEW_OK)
	//{
		//fprintf(stderr, "impossible d'initialiser GLEW");
		//glfwTerminate();
		//return -1;
	//}

	if (!gladLoadGL())
	{
		throw new std::exception("Impossible d'initialiser GLAD");
	}

	if (isvSync())
	{
		glfwSwapInterval(1);
	}

	glfwShowWindow(glfwHandle);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	initFPSCounter();
	return 0;
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(glfwHandle);
}

void Window::update()
{
	if (isResized())
	{
		glViewport(0, 0, this->width, this->height);
		setResized(false);
	}

	glfwSwapBuffers(glfwHandle);
	glfwPollEvents();

	displayFPS(glfwHandle);
}

void Window::setShouldClose(bool value)
{
	glfwSetWindowShouldClose(glfwHandle, GL_TRUE);
}

void Window::setClearColor(float r, float g, float b, float alpha)
{
	glClearColor(r, g, b, alpha);
}


bool Window::isKeyPressed(int keyCode)
{
	return glfwGetKey(glfwHandle, keyCode) == GLFW_PRESS;
}

int Window::getWidth()
{
	return this->width;
}

int Window::getHeight()
{
	return this->height;
}

std::string Window::getTitle()
{
	return this->title;
}

void Window::setResized(bool value)
{
	this->resized = value;
}

void Window::setWidth(int value)
{
	this->width = width;
}

void Window::setHeight(int value)
{
	this->height = height;
}

void Window::setvSync(bool value)
{
	this->vSync = value;
}

bool Window::isResized()
{
	return this->resized;
}


bool Window::isvSync()
{
	return this->vSync;
}