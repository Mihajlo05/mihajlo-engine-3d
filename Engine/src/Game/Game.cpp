#include "Game.h"
#include <cassert>

Game::Game()
	:
	wnd(1280u, 720u, "Mihajlo Engine 3D")
{ }

void Game::Go()
{
	const float dt = timer.Reset();
	wnd.Gfx().BeginFrame(0.2f, 0.4f, 1.0f);
	while (!wnd.mouse.IsEmpty()) HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) HandleKeyboardEvents(wnd.kbd.ReadKey());
	Update(dt);
	Draw();
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

void Game::Draw()
{
}
