#include "Game.h"
#include "Drawables/SolidDrawable.h"
#include <cassert>

Game::Game()
	:
	wnd(1280u, 720u, "Mihajlo Engine 3D"),
	gfx(wnd.Gfx()),
	entity(std::make_unique<SolidDrawable>(gfx, IndexedTriangleList("src\\ModelFiles\\suzanne.obj")))
{ }

void Game::Go()
{
	const float dt = timer.Reset();
	gfx.BeginFrame(0.2f, 0.4f, 1.0f);
	while (!wnd.mouse.IsEmpty()) HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) HandleKeyboardEvents(wnd.kbd.ReadKey());
	Update(dt);
	Draw();
	gfx.EndFrame();
}

void Game::HandleMouseEvents(const Mouse::Event& e)
{
}

void Game::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void Game::Update(float dt)
{
	entity.SpawnControllWindow("Suzanne");
}

void Game::Draw()
{
	entity.Draw(gfx);
}
