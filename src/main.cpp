#include <glad/glad.h>
#include "Engine/Engine.h"
#include "Engine/IGame.h"
#include "Game/TestGame.h"
#include <GLFW/glfw3.h>

int main(void)
{
	bool vsync = true;
	Game* g = new TestGame();
	Engine* e = new Engine("test openGL", 800, 600, vsync, g);
	e->run();

    return 0;
}
