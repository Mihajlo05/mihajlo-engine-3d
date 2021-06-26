#include "Game.h"
#include "FlatCube.h"

Game::Game()
	:
	wnd(800u, 600u, "Mihajlo Engine 3D")
{
	drawablePtrs.push_back(std::make_unique<FlatCube>(wnd.Gfx()));
}

void Game::Go()
{
	wnd.Gfx().ClearBuffer(0.1f, 0.1f, 0.1f, 0.0f);
	const float dt = timer.Reset();
	while (!wnd.mouse.IsEmpty()) HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) HandleKeyboardEvents(wnd.kbd.ReadKey());
	Update(dt);
	Draw(wnd.Gfx());
	wnd.Gfx().EndFrame();
}

void Game::HandleMouseEvents(const Mouse::Event& e)
{
}

void Game::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void Game::Update(float dt)
{
	for (auto& pDrawable : drawablePtrs)
		pDrawable->UpdateLogic(dt);
}

void Game::Draw(Graphics& gfx)
{
	for (auto& pDrawable : drawablePtrs)
	{
		pDrawable->UpdateGraphics(gfx);
		pDrawable->Draw(gfx);
	}
}