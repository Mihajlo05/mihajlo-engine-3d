#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	try
	{
		Window wnd(640u, 480u, "Mihajlo Engine 3D");

		return Window::ProcessWindows();
	}
	catch (const MihajloException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType().c_str(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "unidentified exception caught", "wut", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
}