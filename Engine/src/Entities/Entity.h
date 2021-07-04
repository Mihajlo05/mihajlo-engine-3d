#pragma once

#include "Math/Transform.h"
#include "Windows/Mouse.h"
#include "Windows/Keyboard.h"

class Entity
{
public:
	Transform GetLocalTransform() const;
	Transform GetGlobalTransform() const;
	void SetLocalTransform(const Transform& t);
	void SetGlobalTransform(const Transform& t);
	void ResetLocalTransform();
	void ResetGlobalTransform();
	void ResetTransform();
	DirectX::XMMATRIX GetTransfMatrix() const;
	virtual ~Entity() = default;

	virtual void HandleMouseEvents(const Mouse::Event & e) {}
	virtual void HandleKeyboardEvents(const Keyboard::Event & e) {}
	virtual void Update(float dt, Keyboard& kbd, Mouse& mouse) {}
	virtual void Draw() const {}

	virtual void SpawnControllWindow(const std::string& wndName);
protected:
	Entity() = default;
private:
	Transform localTransf;
	Transform globalTransf;
};