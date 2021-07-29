#include "EntryPoint/EntryPoint.h"
#include "Suzzane.h"

class App : public Application
{
public:
	App()
		:
		Application("Mihajlo Engine 3D")
	{
		auto pScene = std::make_unique<Node>("Scena");

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