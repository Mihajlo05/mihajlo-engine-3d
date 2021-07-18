#pragma once

#include "Math/Transform.h"
#include "Windows/Mouse.h"
#include "Windows/Keyboard.h"
#include "Graphics/Graphics.h"

class Entity
{
public:
	Entity() = default;
	Transform GetTransform() const;
	void SetTransform(const Transform& transf);
	virtual void SpawnControllWindow(const std::string& wndName);

	virtual void HandleMouseEvents(const Mouse::Event& e) { }
	virtual void HandleKeyboardEvents(const Keyboard::Event& e) { }
	virtual void Update(float dt, Keyboard& kbd, Mouse& mouse) { }
	virtual void Draw(Graphics& gfx) { }
private:
	Transform transf;
};