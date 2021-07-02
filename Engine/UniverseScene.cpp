#include "UniverseScene.h"
#include "FlatCube.h"
#include "imgui/imgui.h"

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx),
	cube(std::make_unique<FlatCube>(gfx), "Kocka", {0.0f, 0.0f, 10.0f})
{
}

void UniverseScene::Update(float dt, Keyboard& kbd, Mouse& mouse)
{
	cam.SpawnControllWindow("Kamera");
	gfx.SetCamera(cam.GetView());

	cube.Update(dt, kbd, mouse);
}

void UniverseScene::Draw() const
{
	cube.Draw();
}