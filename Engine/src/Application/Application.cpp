#include "Application.h"
#include "Drawables/PhongDrawable.h"
#include <cassert>
#include "Math/IndexedTriangleList.h"

//{ {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f},
//1.0f,
//1.0f, 0.045f, 0.075f }

Application::Application()
	:
	wnd(1280u, 720u, "Mihajlo Engine 3D"),
	gfx(wnd.Gfx()),
	suzanne("Suzanne")
{
	suzanne.SetTransform(suzanne.GetTransform().Translate(float3{ 0, 0, 10 }));
	suzanne.AddChild(std::make_unique<MeshInstance>(gfx, IndexedTriangleList("src\\Models\\suzanne.obj"), "Model"));
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
	suzanne.Update(dt);
}

void Application::Draw()
{
	suzanne.Draw(gfx);
}
