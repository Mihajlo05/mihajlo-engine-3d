#pragma once

#include "Window.h"
#include "Timer.h"
#include "Scene.h"

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
	void GoToScene(int index);
	void GoToNextScene();
private:
	Window wnd;
	Timer timer;
	std::vector<std::unique_ptr<Scene>> scenePtrs;
	int curSceneIndex = 0;
	Scene* curScene = nullptr;
};
