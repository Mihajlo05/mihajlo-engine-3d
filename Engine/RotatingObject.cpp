#include "RotatingObject.h"

RotatingObject::RotatingObject(std::unique_ptr<Drawable> d)
	:
	GameObject(std::move(d))
{
	Translate({ 10.0f, 0.0f, 0.0f });

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> rotDist(0.1f, 2.0f);

	dalpha = rotDist(rng);
	dbeta = rotDist(rng);
	dgamma = rotDist(rng);
}

void RotatingObject::Update(float dt)
{
	Rotate({0.0f, 0.0f, 0.0f}, { dalpha* dt, dbeta* dt, dgamma* dt });
	GameObject::Update(dt);
}

void RotatingObject::Draw() const
{
	GameObject::Draw();
}
