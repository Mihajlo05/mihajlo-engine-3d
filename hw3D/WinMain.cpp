#include <Windows.h>
#include <string>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static std::string title;
	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_SHIFT)
			MoveWindow(hWnd, 100, 100, 100, 100, 0);
		if (wParam == 'E')
			SetWindowText(hWnd, "New and Better MihajloEngine3D");
		break;
	case WM_KEYUP:
		if (wParam == 'E')
			SetWindowText(hWnd, "lol");
		break;
	case WM_CHAR:
		if (wParam != VK_BACK)
		{
			title.push_back(wParam);
		}
		else if (title.size() != 0)
		{
			title.pop_back();
		}
		SetWindowText(hWnd, title.c_str());
		break;
	case WM_LBUTTONDBLCLK:
		SetWindowText(hWnd, "DBLCKL");
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	const char* className = "MihajloEngine3D";

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground =  nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(
		0, className, className,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInst, nullptr
	);
	ShowWindow(hWnd, SW_SHOW);

	MSG msg = { };
	BOOL gParam;
	while ((gParam = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	if (gParam == -1) return -1;
	else return msg.wParam;
}