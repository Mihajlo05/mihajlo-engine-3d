#pragma once

#include "Drawable.h"
#include "Mouse.h"
#include "Keyboard.h"

class GameObject
{
public:
	virtual void HandleMouseInput(const Mouse::Event& e) {}
	virtual void HandleKeyboardInput(const Keyboard::Event& e) {}
	virtual void Update(float dt);
	virtual void Draw() const;
	void Translate(DirectX::XMFLOAT3 delta);
	void Rotate(DirectX::XMFLOAT3 delta);
	void Rotate(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 delta);
	void Scale(DirectX::XMFLOAT3 delta);
	DirectX::XMFLOAT3 GetPos() const;
	DirectX::XMFLOAT3 GetRotation() const;
	DirectX::XMFLOAT3 GetScale() const;
	void SetPos(DirectX::XMFLOAT3 p);
protected:
	GameObject(std::unique_ptr<Drawable> model);
private:
	void AddToTransformation(DirectX::XMFLOAT3& t, DirectX::XMFLOAT3 delta);
private:
	std::unique_ptr<Drawable> model;
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 rotation = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };
};