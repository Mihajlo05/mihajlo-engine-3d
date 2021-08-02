#include "EntryPoint/EntryPoint.h"
#include "Meshes.h"
#include "Drawables/Phong.h"
#include "Nodes/PointLight.h"
#include "Models/Model.h"

class App : public Application
{
public:
	App()
		:
		Application("Mihajlo Engine 3D")
	{
		auto pScene = std::make_unique<Node>("Scena");
		auto pLight = std::make_unique<PointLight>(gfx, PointLight::Data{ {0.2f, 0.2f, 0.2f}, {1.0f, 1.0f, 1.0f},
										1.0f, 1.0f, 0.045f, 0.075f }, "Osvetljenje");

		auto pCubeMesh = std::make_shared<Drawables::Phong>(gfx, Meshes::cube, Drawables::Phong::Material{});
		pCubeMesh->SetLight(*pLight);

		auto pCube = std::make_unique<MeshInstance>(std::move(pCubeMesh), "Kocka");
		pCube->SetTransform(Transform({ 3, 3, 3 }));

		auto pSphereMesh = std::make_shared<Drawables::Phong>(gfx, Meshes::sphere, Drawables::Phong::Material{});
		pSphereMesh->SetLight(*pLight);

		auto pSphere = std::make_unique<MeshInstance>(std::move(pSphereMesh), "Sfera");
		pSphere->SetTransform(Transform({ -3, -3, -3 }));

		auto pNano = std::make_unique<Node>("NanoSuit");
		pNano->AddChild(LoadModel(gfx, "Models\\nano.gltf", pLight.get()));

		auto pNanoM = std::make_unique<Node>("NanoSuit Material");
		pNanoM->AddChild(LoadModel(gfx, "Models\\nano_textured\\nanosuit.obj", pLight.get()));

		pScene->AddChild(std::move(pLight));
		pScene->AddChild(std::move(pCube));
		pScene->AddChild(std::move(pSphere));
		pScene->AddChild(std::move(pNano));
		pScene->AddChild(std::move(pNanoM));

		SetActiveScene(std::move(pScene));
	}

	void HandleMouseEvents(const Mouse::Event& e) override
	{
		if (e.GetType() == Mouse::Event::Type::RPress)
			wnd.mouse.DisableCursor();
		else if (e.GetType() == Mouse::Event::Type::RRelease)
			wnd.mouse.EnableCursor();
	}
};

std::unique_ptr<Application> GetApplication()
{
	return std::make_unique<App>();
}