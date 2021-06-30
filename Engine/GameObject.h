#pragma once

#include "Drawable.h"
#include "Mouse.h"
#include "Keyboard.h"

class GameObject
{
public:
	virtual void HandleMouseInput(const Mouse::Event& e) {}
	virtual void HandleKeyboardInput(const Keyboard::Event& e) {}
	virtual void Update(float dt)
	{
		model->ResetTransformations();
		model->AddTransformation(DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) * 
								DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
								DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
		model->Update(dt);
	}
	virtual void Draw() const
	{
		model->Draw();
	}
	void Translate(DirectX::XMFLOAT3 delta)
	{
		AddToTransformation(pos, delta);
	}
	void Rotate(DirectX::XMFLOAT3 delta)
	{
		AddToTransformation(rotation, delta);
	}
	void Scale(DirectX::XMFLOAT3 delta)
	{
		AddToTransformation(scale, delta);
	}
protected:
	GameObject(std::unique_ptr<Drawable> model)
		:
		model(std::move(model))
	{ }
private:
	void AddToTransformation(DirectX::XMFLOAT3& t, DirectX::XMFLOAT3 delta)
	{
		auto vec = DirectX::XMVectorSet(t.x, t.y, t.z, 1.0f);
		DirectX::XMStoreFloat3(&t, DirectX::XMVectorAdd(vec, DirectX::XMVectorSet(delta.x, delta.y, delta.z, 1.0f)));
	}
private:
	std::unique_ptr<Drawable> model;
	DirectX::XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 rotation = { 0.0f, 0.0f, 0.0f };
	DirectX::XMFLOAT3 scale = { 1.0f, 1.0f, 1.0f };
};