#pragma once

#include "Scene.h"
#include "FlatCube.h"

class UniverseScene : public Scene
{
public:
	UniverseScene(Graphics& gfx)
		:
		Scene(gfx),
		cube(gfx)
	{}
	void HandleMouseEvents(const Mouse::Event& e) override {}
	void HandleKeyboardEvents(const Keyboard::Event& e) override {}
	void Update(float dt) override
	{
		time += dt;
		cube.Update(dt);

		cube.ResetTransformations();
		cube.AddTransformation(DirectX::XMMatrixRotationRollPitchYaw(time, time * 2, time / 2));
		cube.AddTransformation(DirectX::XMMatrixTranslation(0.0f, 0.0f, 4.0f));
	}
	void Draw() const override
	{
		cube.Draw();
	}
private:
	FlatCube cube;
	float time = 0.0f;
};