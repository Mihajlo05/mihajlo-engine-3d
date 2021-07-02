#pragma once

#include "Scene.h"

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx);
	void Update(float dt) override;
	void Draw() const override;
};