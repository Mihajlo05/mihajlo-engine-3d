#pragma once

#include "Windows/Window.h"
#include "Timer/Timer.h"
#include "Nodes/MeshInstance.h"
#include "Nodes/PointLight.h"
#include "Gui/Hierarchy.h"
#include "Drawables/Phong.h"
#include <cassert>
#include "Math/IndexedTriangleList.h"
#include "Models/Model.h"
#include <memory>
#include "Camera/EditorCamera.h"

class Application
{
public:
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	void Go();
	virtual ~Application();
	static float GetDeltaTime();
protected:
	Application(const std::string& name);
	void SetActiveScene(Node* pScene);
protected:
	virtual void HandleMouseEvents(const Mouse::Event& e);
	virtual void HandleKeyboardEvents(const Keyboard::Event& e);
	virtual void Update(float dt);
private:
	void _HandleMouseEvents(const Mouse::Event& e);
	void _HandleKeyboardEvents(const Keyboard::Event& e);
	void _Update(float dt);
	void _Draw();
protected:
	Window wnd;
	Graphics& gfx;
private:
	Timer timer;
	Gui::Hierarchy hierarchy;
	bool isPlaying = false;
	Node* pScene = nullptr;
	EditorCamera cam;
	static float dt;
};

Application* GetApplication(); //defiend by client (in some project that produces .exe file)
