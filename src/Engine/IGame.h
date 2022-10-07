#pragma once
#include "Window.h"

class Window;

class Game
{
public:
	virtual void init() = 0;
	virtual void input(Window* w) = 0;
	virtual void update(float interval) = 0;
	virtual void render(Window* w) = 0;

	virtual void flush() = 0;
};