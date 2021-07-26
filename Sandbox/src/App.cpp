#include "EntryPoint/EntryPoint.h"
#include <sstream>

class App : public Application
{
public:
	App()
		:
		Application("Mihajlo Engine 3D")
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
		pNano->SetTransform(pNano->GetTransform().Translate(float3{ 0, 0, 15 }));
		auto pNanoModel = LoadModel(gfx, "src\\Models\\nano.gltf", pLight.get());

		pNanoModel->SetTransform(pNanoModel->GetTransform().Rotate(float3{ PI / 2.0f, 0, PI }).Translate(float3{ 0, -8, 0 }));
		pNano->AddChild(std::move(pNanoModel));

		Node* pScene = new Node("Scena");

		pScene->AddChild(std::move(pNano));
		pScene->AddChild(std::move(pLight));
		pScene->AddChild(std::move(pSuzzane));

		SetActiveScene(pScene);
	}

	void HandleMouseEvents(const Mouse::Event& e) override
	{
		if (e.GetType() == Mouse::Event::Type::RPress)
			wnd.mouse.DisableCursor();
		else if (e.GetType() == Mouse::Event::Type::RRelease)
			wnd.mouse.EnableCursor();
	}
};

Application* GetApplication()
{
	return new App();
}