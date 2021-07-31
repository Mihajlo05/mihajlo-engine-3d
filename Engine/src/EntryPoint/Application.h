#pragma once

#include "Windows/Window.h"
#include "Timer/Timer.h"
#include "Gui/Hierarchy.h"
#include "Camera/EditorCamera.h"
#include "Gui/ImGui/ImGuiManager.h"

class Application
{
public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	void Go();
	virtual ~Application() = default;
	static float GetDeltaTime();
	void SetActiveScene(std::unique_ptr<Node> pScene);
protected:
	Application(const std::string& name);
protected:
	virtual void HandleMouseEvents(const Mouse::Event& e);
	virtual void HandleKeyboardEvents(const Keyboard::Event& e);
	virtual void Update(float dt);
private:
	void _HandleMouseEvents(const Mouse::Event& e);
	void _HandleKeyboardEvents(const Keyboard::Event& e);
	void _Update(float dt);
	void _Draw();
private:
	ImGuiManager igm; //all variables HAVE to be bellow ImGuiManager, as it has to be initialized first
protected:
	Window wnd;
	Graphics& gfx;
private:
	Timer timer;
	EditorCamera cam;
	static float dt;
	std::unique_ptr<Node> pScene = nullptr;
};

std::unique_ptr<Application> GetApplication(); //defiend by client (in some project that produces .exe file)
