#pragma once

#include "Scene.h"
#include "FlatCube.h"

class FlatCubeScene : public Scene
{
public:
	FlatCubeScene(Graphics& gfx);
	void HandleMouseEvents(const Mouse::Event& e) override;
	void HandleKeyboardEvents(const Keyboard::Event& e) override;
	void Update(float dt) override;
	void Draw() const override;
private:
	FlatCube cube;
};