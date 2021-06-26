#include "Game.h"
#include <cassert>
#include "InterpolatedCubeScene.h"
#include "FlatCubeScene.h"

void ConfigureScenes(std::vector<std::unique_ptr<Scene>>& scenePtrs, Window& wnd)
{
	scenePtrs.push_back(std::make_unique<InterpolatedCubeScene>(wnd.Gfx()));
	scenePtrs.push_back(std::make_unique<FlatCubeScene>(wnd.Gfx()));
}

Game::Game()
	:
	wnd(800u, 600u, "Mihajlo Engine 3D")
{
	ConfigureScenes(scenePtrs, wnd);
	curScene = scenePtrs.front().get();
	assert(curScene != nullptr);
}

void Game::Go()
{
	const float dt = timer.Reset();
	wnd.Gfx().ClearBuffer(0.1f, 0.1f, 0.1f, 0.0f);
	while (!wnd.mouse.IsEmpty()) HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) HandleKeyboardEvents(wnd.kbd.ReadKey());
	Update(dt);
	Draw();
	wnd.Gfx().EndFrame();
}

void Game::HandleMouseEvents(const Mouse::Event& e)
{
	curScene->HandleMouseEvents(e);
}

void Game::HandleKeyboardEvents(const Keyboard::Event& e)
{
	if (e.GetType() == Keyboard::Event::Type::Pressed && e.GetCode() == VK_TAB)
		GoToNextScene();
	curScene->HandleKeyboardEvents(e);
}

void Game::Update(float dt)
{
	curScene->Update(dt);
}

void Game::Draw()
{
	curScene->Draw();
}

void Game::GoToScene(int index)
{
	curSceneIndex = index;
	curScene = scenePtrs[index].get();
}

void Game::GoToNextScene()
{
	if (++curSceneIndex < scenePtrs.size())
		curScene = scenePtrs[curSceneIndex].get();
	else
		curScene = scenePtrs[curSceneIndex = 0].get();
}
