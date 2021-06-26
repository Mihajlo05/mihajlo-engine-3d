#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Mouse.h"

class Scene
{
public:
	virtual void HandleMouseEvents(const Mouse::Event& e) {}
	virtual void HandleKeyboardEvents(const Keyboard::Event& e) {}
	virtual void Update(float dt) {}
	virtual void Draw() const {}
	virtual ~Scene() = default;
protected:
	Scene(Graphics& gfx) : gfx(gfx) {}
protected:
	Graphics& gfx;
};