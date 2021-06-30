#pragma once

#include "Scene.h"
#include "RotatingObject.h"

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt) override;
	void Draw() const override;
private:
	RotatingObject cube;
};