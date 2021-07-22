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
	entity(gfx, "src\\ModelFiles\\nano.gltf")
{
	entity.SetTransform(entity.GetTransform().Translate(float3{ 0.0f, -7.5f, 10.0f }));
	entity.SetTransform(entity.GetTransform().Rotate(float3{ PI / 2, 0, 0 }));
	light.SetTransform(light.GetTransform().Translate(float3{ -3, 4, 5 }));
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
	light.SpawnControllWindow("Sijalica");
	entity.SpawnControllWindow("NanoSuit");
}

void Application::Draw()
{
	light.Draw(gfx);
	light.Bind(gfx);
	entity.Draw(gfx);
}
