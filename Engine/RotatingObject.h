#pragma once

#include "GameObject.h"

class RotationObject : public GameObject
{
public:
	RotationObject(std::unique_ptr<Drawable> d)
		:
		GameObject(std::move(d))
	{
		Translate({ 0.0f, 0.0f, 4.0f });
	}
	void Update(float dt) override
	{
		Rotate({ dt, dt * 2, dt / 2.0f });
		GameObject::Update(dt);
	}
	void Draw() const override
	{
		GameObject::Draw();
	}
private:
	float time = 0.0f;
};