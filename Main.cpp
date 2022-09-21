#include "lib/glad/glad.h"
#include "Engine/Engine.h"
#include "Engine/IGame.h"
#include "Game/TestGame.h"
#include <GLFW/glfw3.h>

void main(void)
{
	bool vsync = true;
	Game* g = new TestGame();
	Engine* e = new Engine("test openGL", 800, 600, vsync, g);
	e->run();
}


//Implémentation brute, ne pas prendre en compte
int main2(void)
{
	GLFWwindow* glfwHandle = nullptr;

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

	glfwHandle = glfwCreateWindow(800, 600, "test openGL", NULL, NULL);
	if (glfwHandle == NULL)
	{
		fprintf(stderr, "impossible de créer la fenêtre GLFW");
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(glfwHandle, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetFramebufferSizeCallback(glfwHandle, [](GLFWwindow* glfwWindow, int width, int height)
		{
			glViewport(0, 0, width, height);
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

	glfwSwapInterval(1);

	glfwShowWindow(glfwHandle);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	initFPSCounter();

	std::vector<float> positions =
	{
		-0.5f,  0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f,  -0.5f, 0.0f
	};

	std::vector<float> colors =
	{
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	std::vector<int> indices =
	{
		0, 1, 2, 2, 3, 0
	};

	GLuint vaoID, vboID, eboID;

	int vertexCount = indices.size();
	int colorOffset = sizeof(float) * positions.size();

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//on crée un vbo capable de contenir toutes les données de géométrie et couleur
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (positions.size() + colors.size()), NULL, GL_STATIC_DRAW);

	//on fusionne les données de position et couleur dans un seul buffer
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * positions.size(), positions.data());
	glBufferSubData(GL_ARRAY_BUFFER, colorOffset, sizeof(float) * colors.size(), colors.data());

	//on active les pointeurs pour les deux attributs (position et couleur)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//comme les deux tableaux sont mis l'un après l'autre, pour retrouver la couleur d'un vertex on décale de la taille 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)colorOffset);
	//glEnableVertexAttribArray(1);

	//on associe les indices d'utilisations des points.
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	Shader* shader = new Shader("shaders/vertexShader.generic.glsl", "shaders/fragmentShader.generic.glsl");

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(glfwHandle))
	{
		if (glfwGetKey(glfwHandle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(glfwHandle, GL_TRUE);
		}
		glClearColor(sin(glfwGetTime()), cos(glfwGetTime()), cos(glfwGetTime() + 0.5), 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader->bind();
		glBindVertexArray(vaoID);

		glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		shader->unbind();

		glfwSwapBuffers(glfwHandle);
		glfwPollEvents();

		displayFPS(glfwHandle);
	}

	glDeleteBuffers(1, &vboID);
	glDeleteBuffers(1, &eboID);
	glDeleteVertexArrays(1, &vaoID);
	delete shader;
	glfwTerminate();
	return 0;
}