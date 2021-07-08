#pragma once

#include "Scene.h"
#include "Entities/ControllableEntity.h"
#include "Drawables/PhongDrawable.h"
#include "Entities/Camera.h"
#include "Entities/PointLight.h"
#include <vector>

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt, Keyboard& kbd, Mouse& mouse) override;
	void Draw() const override;
private:
	void ControllCamera(float dt, Keyboard& kbd);
private:
	Camera cam;
	PointLight pointLight;
	std::vector<ControllableEntity> ctrlbls;
	PhongDrawable floor;
	float camSpeed = 20.0f;
	float camRotSpeed = 1.0f;
};