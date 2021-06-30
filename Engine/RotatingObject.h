#pragma once

#include "GameObject.h"

class RotatingObject : public GameObject
{
public:
	RotatingObject(std::unique_ptr<Drawable> d);
	void Update(float dt) override;
	void Draw() const override;
private:
};