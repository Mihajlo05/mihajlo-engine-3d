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

		return Window::ProcessMessages();
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