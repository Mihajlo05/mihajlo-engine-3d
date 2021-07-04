#pragma once

#include "Scene.h"
#include "Entities/ControllableEntity.h"
#include "Entities/Camera.h"
#include <vector>

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt, Keyboard& kbd, Mouse& mouse) override;
	void Draw() const override;
private:
	void SpawnFactory();
	void ControllCamera(float dt, Keyboard& kbd);
private:
	Camera cam;
	std::vector<ControllableEntity> ctrlbls;
	float camSpeed = 20.0f;
	float camRotSpeed = 1.0f;
};