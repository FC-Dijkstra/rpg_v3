#pragma once
#include "Window.h"

class Window;

class Game
{
public:
	virtual void init() {};
	virtual void input(Window* w) {};
	virtual void update(float interval) {};
	virtual void render(Window* w) {};

	virtual void clear() {};
};