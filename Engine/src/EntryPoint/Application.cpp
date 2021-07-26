#include "Application.h"

float Application::dt;

Application::Application(const std::string& name)
	:
	wnd(1280u, 720u, name.c_str()),
	gfx(wnd.Gfx()),
	cam(720.0f/1280.0f)
{
	gfx.BindCamera(cam);
}

void Application::SetActiveScene(Node* pScene)
{
	this->pScene = pScene;
	hierarchy.SetRoot(*pScene);
}

void Application::Go()
{
	dt = timer.Reset();
	gfx.BeginFrame(0.2f, 0.4f, 1.0f);
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::ArrowButton("Play", ImGuiDir_Right))
		{
			isPlaying = !isPlaying;
		}
	} ImGui::EndMainMenuBar();
	hierarchy.SpawnWindow();
	while (!wnd.mouse.IsEmpty()) _HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) _HandleKeyboardEvents(wnd.kbd.ReadKey());
	_Update(dt);
	_Draw();
	gfx.EndFrame();
}

Application::~Application()
{
	delete pScene;
	pScene = nullptr;
}

float Application::GetDeltaTime()
{
	return dt;
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
	if (isPlaying && pScene)
	{
		pScene->HandleMouseEvents(e);
	}
}

void Application::_HandleKeyboardEvents(const Keyboard::Event& e)
{
	HandleKeyboardEvents(e);
	if (isPlaying && pScene)
	{
		pScene->HandleKeyboardEvents(e);
	}
}

void Application::_Update(float dt)
{
	cam.Update(dt, wnd.kbd);
	Update(dt);
	if (isPlaying && pScene)
	{
		pScene->Update(dt);
	}
}

void Application::_Draw()
{
	if (pScene) pScene->Draw(gfx);
}
