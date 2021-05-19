#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	Window wnd = Window(640u, 480u, "Mihajlo Engine 3D");

	return Window::ProcessWindows();
}