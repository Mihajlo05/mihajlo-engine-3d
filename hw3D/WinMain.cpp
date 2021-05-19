#include "Window.h"

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	Window wnd = Window(640u, 480u, "Mihajlo Engine 3D");

	MSG msg;
	BOOL gParam;
	while ((gParam = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gParam == -1) return -1;
	else			  return msg.wParam;
}