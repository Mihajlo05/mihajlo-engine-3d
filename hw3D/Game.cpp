#include "Game.h"
#include "Cube.h"
#include "DefaultVertex.h"

Game::Game()
	:
	wnd(800u, 600u, "Mihajlo Engine 3D"),
	fd(wnd.Gfx(), Cube::GetWrapped<DefaultVertex>())
{ }

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
	fd.UpdateLogic(dt);
}

void Game::Draw(Graphics& gfx)
{
	fd.UpdateGraphics(gfx);
	fd.Draw(gfx);
}