#pragma once

#include "Scene.h"
#include "FlatCube.h"
#include "RotatingObject.h"

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx)
		:
		Scene(gfx),
		cube(std::make_unique<FlatCube>(gfx))
	{}
	void HandleMouseEvents(const Mouse::Event& e) override {}
	void HandleKeyboardEvents(const Keyboard::Event& e) override {}
	void Update(float dt) override
	{
		time += dt;
		cube.Update(dt);
	}
	void Draw() const override
	{
		cube.Draw();
	}
private:
	RotationObject cube;
	float time = 0.0f;
};