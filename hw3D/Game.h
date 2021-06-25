#pragma once

#include "Window.h"
#include "Timer.h"

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void HandleMouseEvents(const Mouse::Event& e);
	void HandleKeyboardEvents(const Keyboard::Event& e);
	void Update(float dt);
	void Draw(Graphics& gfx);
private:
	Window wnd;
	Timer timer;
};
