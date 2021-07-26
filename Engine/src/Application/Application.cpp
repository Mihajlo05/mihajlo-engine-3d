#include "Application.h"
#include "Drawables/PhongDrawable.h"
#include <cassert>
#include "Math/IndexedTriangleList.h"
#include "Models/Model.h"

Application::Application()
	:
	wnd(1280u, 720u, "Mihajlo Engine 3D"),
	gfx(wnd.Gfx()),
	scene("Scena")
{
	auto pLight = std::make_unique<PointLight>(gfx, PointLight::Data{ {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f},
											1.0f, 1.0f, 0.045f, 0.075f }, "Sijalica");

	pLight->SetTransform(pLight->GetTransform().Translate(float3{ -2, 2, 5 }));

	auto pSuzzaneMesh = std::make_shared<PhongDrawable>(
		gfx,
		IndexedTriangleList("src\\Models\\suzanne.obj"),
		PhongDrawable::Material{ {1, 1, 1}, 4.0f, 100.0f }
	);
	pSuzzaneMesh->SetLight(*pLight);

	auto pSuzzane = std::make_unique<MeshInstance>(std::move(pSuzzaneMesh), "Suzanne");

	pSuzzane->SetTransform(pSuzzane->GetTransform().Translate(float3{ 0, 0, 10 }).Rotate(float3{ 0, PI, 0 }));

	auto pNano = std::make_unique<Node>("Nanosuit");
	pNano->AddChild(LoadModel(gfx, "src\\Models\\nano.gltf", pLight.get()));

	scene.AddChild(std::move(pNano));
	scene.AddChild(std::move(pLight));
	scene.AddChild(std::move(pSuzzane));

	hierarchy.SetRoot(scene);
}

void Application::Go()
{
	const float dt = timer.Reset();
	gfx.BeginFrame(0.2f, 0.4f, 1.0f);
	hierarchy.SpawnWindow();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::ArrowButton("Play", ImGuiDir_Right))
		{
			isPlaying = !isPlaying;
		}
	}
	ImGui::EndMainMenuBar();

	while (!wnd.mouse.IsEmpty()) HandleMouseEvents(wnd.mouse.Read());
	while (!wnd.kbd.IsKeyEmpty()) HandleKeyboardEvents(wnd.kbd.ReadKey());
	Update(dt);
	Draw();
	gfx.EndFrame();
}

void Application::HandleMouseEvents(const Mouse::Event& e)
{
	if (isPlaying)
	{
		scene.HandleMouseEvents(e);
	}
}

void Application::HandleKeyboardEvents(const Keyboard::Event& e)
{
	if (isPlaying)
	{
		scene.HandleKeyboardEvents(e);
	}
}

void Application::Update(float dt)
{
	if (isPlaying)
	{
		scene.Update(dt);
	}
}

void Application::Draw()
{
	scene.Draw(gfx);
}
