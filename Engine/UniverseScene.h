#pragma once

#include "Scene.h"
#include "ControllableEntity.h"
#include "Camera.h"

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt, Keyboard& kbd, Mouse& mouse) override;
	void Draw() const override;
private:
	Camera cam;
	ControllableEntity cube;
};