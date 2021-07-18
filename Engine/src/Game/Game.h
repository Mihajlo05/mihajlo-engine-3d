#pragma once

#include "Windows/Window.h"
#include "Components/Timer.h"
#include "Entities/DrawableEntity.h"

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
	void Draw();
private:
	Window wnd;
	Graphics& gfx;
	Timer timer;
	DrawableEntity entity;
};
