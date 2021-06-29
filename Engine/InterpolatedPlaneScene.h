#pragma once

#include "Scene.h"
#include "InterpolatedPlane.h"

class InterpolatedPlaneScene : public Scene
{
public:
	InterpolatedPlaneScene(Graphics& gfx);
	void HandleMouseEvents(const Mouse::Event& e) override;
	void HandleKeyboardEvents(const Keyboard::Event& e) override;
	void Update(float dt) override;
	void Draw() const override;
private:
	InterpolatedPlane plane;
};