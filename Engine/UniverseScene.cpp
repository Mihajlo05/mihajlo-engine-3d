#include "UniverseScene.h"
#include "FlatCube.h"
#include "imgui/imgui.h"

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx)
{
	const int nCubes = 200;
	cubes.reserve(nCubes);
	for (int i = 0; i < nCubes; i++)
	{
		cubes.emplace_back(std::make_unique<FlatCube>(gfx));
	}
}

void UniverseScene::Update(float dt)
{
	if (ImGui::Begin("Kontrole simulacije"))
	{
		ImGui::SliderFloat("Brzina", &simulationSpeed, -2.0f, 2.0f);
		ImGui::Checkbox("Simulacija je pokrenuta", &isSimulationRunning);
		if (ImGui::Button("Resetuj"))
		{
			simulationSpeed = 1.0f;
			isSimulationRunning = true;
		}
	}
	ImGui::End();

	dt *= simulationSpeed * (int)isSimulationRunning;
	for (auto& cube : cubes)
		cube.Update(dt);
}

void UniverseScene::Draw() const
{
	for (const auto& cube : cubes)
		cube.Draw();
}