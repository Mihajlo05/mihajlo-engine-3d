#include "Application.h"
#include "Drawables/PhongDrawable.h"
#include <cassert>

Application::Application()
	:
	wnd(1280u, 720u, "Mihajlo Engine 3D"),
	gfx(wnd.Gfx()),
	light(gfx, { {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f},
		1.0f,
		1.0f, 0.045f, 0.075f } ),
	entity(std::make_unique<PhongDrawable>(gfx, IndexedTriangleList("src\\ModelFiles\\suzanne.obj"),
		PhongDrawable::Material{ {1.0f, 1.0f, 1.0f}, 3.5f, 100.0f }))
{
	
}

void Application::Go()
{
	const float dt = timer.Reset();
	gfx.BeginFrame(0.2f, 0.4f, 1.0f);
	while (!wnd.mouse.IsEmpty()) HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) HandleKeyboardEvents(wnd.kbd.ReadKey());
	Update(dt);
	Draw();
	gfx.EndFrame();
}

void Application::HandleMouseEvents(const Mouse::Event& e)
{
}

void Application::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void Application::Update(float dt)
{
	entity.SpawnControllWindow("Suzanne");
	light.SpawnControllWindow("Sijalica");
}

void Application::Draw()
{
	light.Draw(gfx);
	light.Bind(gfx);
	entity.Draw(gfx);
}
