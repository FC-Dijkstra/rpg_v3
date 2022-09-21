#include "Window.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "-----------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


	//création de la fenêtre
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

	if (!gladLoadGL())
	{
		throw new std::exception("Impossible d'initialiser GLAD");
	}

	if (isvSync())
	{
		glfwSwapInterval(1);
	}

	//vérification de l'activation du débogage openGL
	int flags;
	glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		std::cout << "Débogage openGL actif" << std::endl;
	}
	else {
		std::cout << "Débogage openGL inactif" << std::endl;
	}

	glfwShowWindow(glfwHandle);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

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


