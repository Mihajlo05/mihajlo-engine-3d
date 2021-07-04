#include "UniverseScene.h"
#include "Drawables/FlatCube.h"
#include "imgui/imgui.h"

namespace dx = DirectX;

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx)
{
	ctrlbls.emplace_back(std::make_unique<FlatCube>(gfx), "Obojena Kocka 1", DirectX::XMFLOAT3{ 0.0f, 0.0f, 0.0f });
	cam.SetLocalTransform(cam.GetLocalTransform().Translate(DirectX::XMFLOAT3{ 0.0f, 0.0f, -10.0f }));
}

void UniverseScene::Update(float dt, Keyboard& kbd, Mouse& mouse)
{
	ControllCamera(dt, kbd);
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
	static char buf[512] = "";
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

void UniverseScene::ControllCamera(float dt, Keyboard& kbd)
{
	dx::XMVECTOR camVel = dx::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	if (kbd.IsKeyPressed('W'))
	{
		camVel = dx::XMVectorAdd(camVel, dx::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f));
	}
	if (kbd.IsKeyPressed('S'))
	{
		camVel = dx::XMVectorAdd(camVel, dx::XMVectorSet(0.0f, 0.0f, -1.0, 0.0f));
	}
	if (kbd.IsKeyPressed('D'))
	{
		camVel = dx::XMVectorAdd(camVel, dx::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f));
	}
	if (kbd.IsKeyPressed('A'))
	{
		camVel = dx::XMVectorAdd(camVel, dx::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f));
	}

	if (kbd.IsKeyPressed(VK_RIGHT))
	{
		cam.SetLocalTransform(cam.GetLocalTransform().Rotate(dx::XMFLOAT3{ 0.0f, -camRotSpeed * dt, 0.0f }));
	}
	if (kbd.IsKeyPressed(VK_LEFT))
	{
		cam.SetLocalTransform(cam.GetLocalTransform().Rotate(dx::XMFLOAT3{ 0.0f, camRotSpeed * dt, 0.0f }));
	}
	if (kbd.IsKeyPressed(VK_DOWN))
	{
		cam.SetLocalTransform(cam.GetLocalTransform().Rotate(dx::XMFLOAT3{ -camRotSpeed * dt, 0.0f, 0.0f }));
	}
	if (kbd.IsKeyPressed(VK_UP))
	{
		cam.SetLocalTransform(cam.GetLocalTransform().Rotate(dx::XMFLOAT3{ camRotSpeed * dt, 0.0f, 0.0f }));
	}

	camVel = dx::XMVector3Normalize(camVel);
	dx::XMVECTOR rotInv = cam.GetLocalTransform().rot;
	rotInv = dx::XMVectorScale(rotInv, -1.0f);
	camVel = dx::XMVector3Transform(camVel, dx::XMMatrixRotationRollPitchYawFromVector(rotInv));
	camVel = dx::XMVectorScale(camVel, camSpeed * dt);

	cam.SetLocalTransform(cam.GetLocalTransform().Translate(camVel));

}
