#include "Game.h"

Game::Game()
	:
	wnd(800u, 600u, "Mihajlo Engine 3D")
{
	const int nBoxes = 10;
	boxes.reserve(nBoxes);
	for (int i = 0; i < nBoxes; i++)
	{
		boxes.push_back(std::make_unique<Box>(wnd.Gfx()));
	}
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
	for (auto& box : boxes)
	{
		box->Update(dt, wnd.Gfx());
	}
}

void Game::Draw(Graphics& gfx)
{
	for (auto& box : boxes)
		box->Draw(gfx);
}