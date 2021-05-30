#pragma once

#include "Window.h"

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void Update();
private:
	Window wnd;
};
