#pragma once

#include "Scene.h"
#include "ControllableEntity.h"
#include "Camera.h"
#include <vector>

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt, Keyboard& kbd, Mouse& mouse) override;
	void Draw() const override;
private:
	void SpawnFactory();
private:
	Camera cam;
	std::vector<ControllableEntity> ctrlbls;
};