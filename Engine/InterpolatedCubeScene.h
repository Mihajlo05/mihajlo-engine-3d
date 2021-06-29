#pragma once

#include "Scene.h"
#include "InterpolatedCube.h"

class InterpolatedCubeScene : public Scene
{
public:
	InterpolatedCubeScene(Graphics& gfx);
	void HandleMouseEvents(const Mouse::Event& e) override;
	void HandleKeyboardEvents(const Keyboard::Event& e) override;
	void Update(float dt) override;
	void Draw() const override;
private:
	InterpolatedCube cube;
};