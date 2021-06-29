#include "FlatCubeScene.h"

FlatCubeScene::FlatCubeScene(Graphics& gfx)
	:
	Scene(gfx),
	cube(gfx)
{ }

void FlatCubeScene::HandleMouseEvents(const Mouse::Event& e)
{
}

void FlatCubeScene::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void FlatCubeScene::Update(float dt)
{
	cube.Update(dt);
}

void FlatCubeScene::Draw() const
{
	cube.Draw();
}
