#include "UniverseScene.h"
#include "FlatCube.h"

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx)
{
	const int nCubes = 50;
	cubes.reserve(nCubes);
	for (int i = 0; i < nCubes; i++)
	{
		cubes.emplace_back(std::make_unique<FlatCube>(gfx));
	}
}

void UniverseScene::Update(float dt)
{
	for (auto& cube : cubes)
		cube.Update(dt);
}

void UniverseScene::Draw() const
{
	for (const auto& cube : cubes)
		cube.Draw();
}