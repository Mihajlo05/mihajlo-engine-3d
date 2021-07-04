#pragma once

#include "Graphics/Graphics.h"
#include "Windows/Keyboard.h"
#include "Windows/Mouse.h"

class Scene
{
public:
	virtual void HandleMouseEvents(const Mouse::Event& e) {}
	virtual void HandleKeyboardEvents(const Keyboard::Event& e) {}
	virtual void Update(float dt, Keyboard& kbd, Mouse& mouse) {}
	virtual void Draw() const {}
	virtual ~Scene() = default;
protected:
	Scene(Graphics& gfx) : gfx(gfx) {}
protected:
	Graphics& gfx;
};