#include "Engine.h"
using namespace std;

Engine* Engine::instance = 0;

Engine::Engine(string windowTitle, int width, int height, bool vSync, Game* g)
{
	this->stop = false;
	this->window = new Window(width, height, windowTitle, vSync);
	this->ui = new UI();
	this->game = g;

	Engine::instance = this;
}

void Engine::run()
{
	init();
	loop();
}

void Engine::init()
{
	window->init();
	ui->init(window->getHandle());
	game->init();
}

void Engine::loop()
{
	stop = false;

	std::cout << "--- started rendering ---" << std::endl;

	while (stop != true && window->shouldClose() == false)
	{
		game->input(window);
		game->update(TARGET_FPS);
		game->render(window);
		ui->render();
		window->update();
	}

	game->clear();
	ui->clear();
	window->clear();

	exit(0);
}

void Engine::shouldStop()
{
	this->stop = true;
	window->setShouldClose(true);
}

Window* Engine::getWindow()
{
	return this->window;
}