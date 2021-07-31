#include "Application.h"
#include "Gui/imgui/imgui.h"

float Application::dt;

Application::Application(const std::string& name)
	:
	wnd(1280u, 720u, name.c_str()),
	gfx(wnd.Gfx()),
	cam(720.0f/1280.0f)
{
	gfx.BindCamera(cam);
}

void Application::Go()
{
	dt = timer.Reset();
	gfx.BeginFrame(0.2f, 0.4f, 1.0f);
	Gui::Hierarchy::Get().SpawnWindow();
	while (!wnd.mouse.IsEmpty()) _HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) _HandleKeyboardEvents(wnd.kbd.ReadKey());
	_Update(dt);
	_Draw();
	gfx.EndFrame();
}

float Application::GetDeltaTime()
{
	return dt;
}

void Application::SetActiveScene(std::unique_ptr<Node> pScene)
{
	this->pScene = std::move(pScene);
	Gui::Hierarchy::Get().SetRoot(*this->pScene.get());
}

void Application::HandleMouseEvents(const Mouse::Event& e)
{
}

void Application::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void Application::Update(float dt)
{
}

void Application::_HandleMouseEvents(const Mouse::Event& e)
{
	if (!wnd.mouse.IsCursorEnabled())
	{
		cam.HandleMouseInput(e);
	}

	HandleMouseEvents(e);
	if (pScene)
	{
		pScene->HandleMouseEvents(e);
	}
}

void Application::_HandleKeyboardEvents(const Keyboard::Event& e)
{
	HandleKeyboardEvents(e);
	if (pScene)
	{
		pScene->HandleKeyboardEvents(e);
	}
}

void Application::_Update(float dt)
{
	cam.Update(dt, wnd.kbd);
	Update(dt);
	if (pScene)
	{
		pScene->Update(dt);
	}
}

void Application::_Draw()
{
	if (pScene) pScene->Draw(gfx);
}
