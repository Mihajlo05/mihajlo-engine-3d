#include "Game.h"

#include <optional>

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	try
	{
		Game game;

		std::optional<int> ecode;

		while (!(ecode = Window::ProcessMessages()))
		{
			game.Go();
		}

		return *ecode;
	}
	catch (const MihajloException& e)
	{
		Window::CreateErrorMsgBox(e.GetType(), e.what());
	}
	catch (const std::exception& e)
	{
		Window::CreateErrorMsgBox("Standard Exception", e.what());
	}
	catch (...)
	{
		Window::CreateErrorMsgBox("Unknown Exception", "No details available");
	}

	return -1;
}