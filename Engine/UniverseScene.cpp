#include "UniverseScene.h"
#include "FlatCube.h"
#include "imgui/imgui.h"

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx)
{
	ctrlbls.emplace_back(std::make_unique<FlatCube>(gfx), "Obojena Kocka 1", DirectX::XMFLOAT3{ 0.0f, 0.0f, 0.0f });
	cam.SetLocalTransform(cam.GetLocalTransform().Translate(DirectX::XMFLOAT3{ 0.0f, 0.0f, -10.0f }));
}

void UniverseScene::Update(float dt, Keyboard& kbd, Mouse& mouse)
{
	cam.SpawnControllWindow("Kamera");
	gfx.SetCamera(cam.GetView());

	SpawnFactory();

	for (auto& ctrlbl : ctrlbls)
	{
		ctrlbl.Update(dt, kbd, mouse);
	}
}

void UniverseScene::Draw() const
{
	for (const auto& ctrlbl : ctrlbls)
	{
		ctrlbl.Draw();
	}
}

void UniverseScene::SpawnFactory()
{
	static char buf[512] = "Ovde upisi ime Objekta pre stvaranja\0";
	if (ImGui::Begin("Fabrika"))
	{
		ImGui::InputText("Ime Objekta", buf, IM_ARRAYSIZE(buf));

		if (ImGui::Button("Obojena Kocka"))
		{
			ctrlbls.emplace_back(std::make_unique<FlatCube>(gfx), buf, DirectX::XMFLOAT3{ 0.0f, 0.0f, 0.0f });
		}
	}
	ImGui::End();
}
