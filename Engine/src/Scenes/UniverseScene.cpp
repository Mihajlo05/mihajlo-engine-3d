#include "UniverseScene.h"
#include "imgui/imgui.h"
#include "Models/CubeModel.h"
#include "Models/SphereModel.h"
#include "Models/FromFileModel.h"

namespace dx = DirectX;

UniverseScene::UniverseScene(Graphics& gfx)
	:
	Scene(gfx),
	pointLight(DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
		{Color(50, 50, 50), Color(255, 255, 255),
		1.0f,
		1.0f, 0.045f, 0.075f},
		gfx),
	floor(gfx, CubeModel::MakeIndependent<PhongDrawable::Vertex>().SetNormalsIndependentFlat(),
		{ {1.0f, 1.0f, 1.0f}, 0.1f, 9.0f })
{
	ctrlbls.emplace_back(std::make_unique<PhongDrawable>(gfx, CubeModel::MakeIndependent<PhongDrawable::Vertex>().SetNormalsIndependentFlat(),
		PhongDrawable::MaterialData{ { 1.0f, 0.0f, 0.0f }, 1.0f, 30.0f }), "Kocka 1", DirectX::XMFLOAT3{0.0f, 0.0f, 0.0f});
	ctrlbls.emplace_back(std::make_unique<PhongDrawable>(gfx, SphereModel::MakeWithNormals<PhongDrawable::Vertex>(),
		PhongDrawable::MaterialData{ { 0.0f, 1.0f, 0.0f }, 4.0f, 80.0f }), "Sfera 1", DirectX::XMFLOAT3{ 5.0f, 5.0f, 5.0f });
	ctrlbls.emplace_back(std::make_unique<PhongDrawable>(gfx, FromFileModel::MakeWithNormals<PhongDrawable::Vertex>("src\\ModelFiles\\suzanne.obj"),
		PhongDrawable::MaterialData{ { 1.0f, 1.0f, 1.0f }, 4.0f, 80.0f }), "Suzanne 1", DirectX::XMFLOAT3{ 5.0f, 5.0f, 5.0f });

	cam.SetLocalTransform(cam.GetLocalTransform().Translate(DirectX::XMFLOAT3{ 0.0f, 0.0f, -10.0f }));
	floor.AddTransformation(DirectX::XMMatrixScaling(100, 1, 100));
	floor.AddTransformation(DirectX::XMMatrixTranslation(0.0f, -5.0f, 0.0f));
}

void UniverseScene::Update(float dt, Keyboard& kbd, Mouse& mouse)
{
	ControllCamera(dt, kbd);
	gfx.SetCamera(cam.GetView());

	pointLight.SpawnControllWindow("Svetlost");

	for (auto& ctrlbl : ctrlbls)
	{
		ctrlbl.Update(dt, kbd, mouse);
	}
}

void UniverseScene::Draw() const
{
	pointLight.Draw();
	pointLight.Bind(gfx, cam.GetView());
	for (const auto& ctrlbl : ctrlbls)
	{
		ctrlbl.Draw();
	}
	floor.Draw();
}

void UniverseScene::ControllCamera(float dt, Keyboard& kbd)
{
	if (ImGui::Begin("Kamera"))
	{
		ImGui::SliderFloat("Brzina", &camSpeed, 20.0f, 100.0f);
		ImGui::SliderAngle("Brzine Rotacije", &camRotSpeed, 0.0f, 360.0f);
	}
	ImGui::End();

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
