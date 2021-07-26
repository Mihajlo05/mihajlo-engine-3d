#pragma once

#include "Windows/Window.h"
#include "Timer/Timer.h"
#include "Nodes/MeshInstance.h"
#include "Nodes/PointLight.h"
#include "Gui/Hierarchy.h"

class Application
{
public:
	Application();
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	void Go();
private:
	void HandleMouseEvents(const Mouse::Event& e);
	void HandleKeyboardEvents(const Keyboard::Event& e);
	void Update(float dt);
	void Draw();
private:
	Window wnd;
	Graphics& gfx;
	Timer timer;
	Gui::Hierarchy hierarchy;
	Node scene;
	bool isPlaying = false;
};
