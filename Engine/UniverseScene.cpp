#include "UniverseScene.h"
#include "FlatCube.h"

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx),
	cube(std::make_unique<FlatCube>(gfx))
{}

void UniverseScene::Update(float dt)
{
	cube.Update(dt);
}

void UniverseScene::Draw() const
{
	cube.Draw();
}