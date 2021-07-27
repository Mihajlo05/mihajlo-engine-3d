#include "EntryPoint/EntryPoint.h"
#include "Suzzane.h"

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

		auto pSuzzane = std::make_unique<Suzzane>(gfx, PI/3.0f, "Suzanne", *pLight);

		pSuzzane->SetTransform(pSuzzane->GetTransform().Translate(float3{ 0, 0, 10 }).Rotate(float3{ 0, PI, 0 }));

		auto pNano = std::make_unique<Node>("Nanosuit");
		pNano->SetTransform(pNano->GetTransform().Translate(float3{ 0, 0, 15 }));

		auto pNanoModel = LoadModel(gfx, "Models\\nano_textured\\nanosuit.obj", pLight.get());
		pNanoModel->SetTransform(pNanoModel->GetTransform().Rotate(float3{ 0, PI, 0 }).Translate(float3{ 0, -8, 0 }));

		pNano->AddChild(std::move(pNanoModel));

		auto pBed = std::make_unique<Node>("Krevet");

		auto pBedModel = LoadModel(gfx, "Models\\krevet.gltf", pLight.get());

		pBed->AddChild(std::move(pBedModel));

		Node* pScene = new Node("NanoSuzzane Scene");

		pScene->AddChild(std::move(pLight));
		pScene->AddChild(std::move(pNano));
		pScene->AddChild(std::move(pSuzzane));
		pScene->AddChild(std::move(pBed));

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