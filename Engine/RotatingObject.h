#pragma once

#include "GameObject.h"
#include <random>

class RotatingObject : public GameObject
{
public:
	RotatingObject(std::unique_ptr<Drawable> d);
	void Update(float dt) override;
	void Draw() const override;
private:
	float dalpha = 0.0f;
	float dbeta = 0.0f;
	float dgamma = 0.0f;
};