#pragma once

#include "Scene.h"
#include "RotatingObject.h"
#include "Camera.h"
#include <vector>

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt) override;
	void Draw() const override;
private:
	std::vector<RotatingObject> cubes;
	Camera cam;
	float simulationSpeed = 1.0f;
	bool isSimulationRunning = true;
};