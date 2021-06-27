#include "InterpolatedPlaneScene.h"

InterpolatedPlaneScene::InterpolatedPlaneScene(Graphics& gfx)
	:
	Scene(gfx),
	plane(gfx)
{ }

void InterpolatedPlaneScene::HandleMouseEvents(const Mouse::Event& e)
{
}

void InterpolatedPlaneScene::HandleKeyboardEvents(const Keyboard::Event& e)
{
}

void InterpolatedPlaneScene::Update(float dt)
{
	plane.UpdateLogic(dt);
	plane.UpdateGraphics(gfx);
}

void InterpolatedPlaneScene::Draw() const
{
	plane.Draw(gfx);
}
