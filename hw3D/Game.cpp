#include "Game.h"

Game::Game()
	:
	wnd(800u, 600u, "Mihajlo Engine 3D")
{ }

void Game::Go()
{
	wnd.Gfx().ClearBuffer(0.2f, 0.2f, 0.2f);
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
}

void Game::Draw(Graphics& gfx)
{
}