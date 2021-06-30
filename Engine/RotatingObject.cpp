#include "RotatingObject.h"

RotatingObject::RotatingObject(std::unique_ptr<Drawable> d)
	:
	GameObject(std::move(d))
{
	Translate({ 0.0f, 0.0f, 4.0f });
}

void RotatingObject::Update(float dt)
{
	Rotate({ dt, dt * 2, dt / 2.0f });
	GameObject::Update(dt);
}

void RotatingObject::Draw() const
{
	GameObject::Draw();
}
