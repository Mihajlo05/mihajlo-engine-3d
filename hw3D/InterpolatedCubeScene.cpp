#include "InterpolatedCubeScene.h"

InterpolatedCubeScene::InterpolatedCubeScene(Graphics& gfx)
	:
	Scene(gfx),
	cube(gfx)
{ }

void InterpolatedCubeScene::HandleMouseEvents(const Mouse::Event& e)
{
}

void InterpolatedCubeScene::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void InterpolatedCubeScene::Update(float dt)
{
	cube.Update(dt);
}

void InterpolatedCubeScene::Draw() const
{
	cube.Draw();
}