#pragma once
#include "Window.h"
#include "resource.h"
#include <sstream>
#include "imgui\imgui_impl_win32.h"

#define WND_NOGFX_EXCEPT Window::NoGfxException(__FILE__, __LINE__)

Window::WindowRegister Window::WindowRegister::wndReg;

HINSTANCE Window::WindowRegister::GetInstance() noexcept
{
	return wndReg.hInst;
}

const char* Window::WindowRegister::GetName() noexcept
{
	return className;
}

Window::WindowRegister::WindowRegister()
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = className;
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));
	RegisterClassEx(&wc);
}

Window::WindowRegister::~WindowRegister() noexcept
{
	UnregisterClass(className, hInst);
}

Window::Window(unsigned int width, unsigned int height, const char* wndName)
	:
	width(width),
	height(height),
	name(wndName)
{
	int x = CW_USEDEFAULT;
	int y = CW_USEDEFAULT;
	RECT rect;
	rect.left = x; rect.right = x + width;
	rect.top = y; rect.bottom = y + height;
	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	if (AdjustWindowRect(&rect, style, FALSE) == FALSE)
	{
		throw WND_EXCEPTION;
	}
	
	hWnd = CreateWindowEx(
		0, WindowRegister::GetName(), name.c_str(),
		style,
		x, y, rect.right - rect.left, rect.bottom - rect.top,
		nullptr, nullptr, WindowRegister::GetInstance(), this);

	if (hWnd == nullptr)
	{
		throw WND_EXCEPTION;
	}

	ShowWindow(hWnd, SW_SHOW);

	ImGui_ImplWin32_Init(hWnd);

	pGfx = std::make_unique<Graphics>(hWnd, width, height);
}

Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	DestroyWindow(hWnd);
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_NCCREATE)
	{
		const CREATESTRUCTW* pCreateStruct = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = reinterpret_cast<Window*>(pCreateStruct->lpCreateParams);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgThunk));

		return pWnd->HandleMsg(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPCREATESTRUCTW pCreateStruct = reinterpret_cast<LPCREATESTRUCTW>(lParam);

	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	return pWnd->HandleMsg(hWnd, uMsg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}

	const auto& imio = ImGui::GetIO();

	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		kbd.ClearStates();
		mouse.Clear();
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (imio.WantCaptureKeyboard)
			break;
		if (!(lParam & 0x40000000) || kbd.IsAutorepeatEnabled())
			kbd.OnKeyPress(static_cast<unsigned char>(wParam));
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (imio.WantCaptureKeyboard)
			break;
		kbd.OnKeyRelease(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		if (imio.WantCaptureKeyboard)
			break;
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
	case WM_MOUSEMOVE:
		if (imio.WantCaptureMouse)
			break;
		const POINTS pos = MAKEPOINTS(lParam);
		if (pos.x < 0 || pos.x >= (int)width || pos.y < 0 || pos.y >= (int)height) //if mouse is outside
		{
			if (mouse.LeftIsPressed() || mouse.RightIsPressed())
			{
				mouse.Move(pos.x, pos.y);
			}
			else
			{
				if (ReleaseCapture() == FALSE) throw WND_EXCEPTION;
				mouse.OnMouseLeave();
			}
		}
		else
		{
			mouse.Move(pos.x, pos.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		mouse.Move(pos.x, pos.y);
		break;
	case WM_LBUTTONDOWN:
		if (imio.WantCaptureMouse)
			break;
		mouse.ChangeLeftState(true);
		break;
	case WM_LBUTTONUP:
		if (imio.WantCaptureMouse)
			break;
		mouse.ChangeLeftState(false);
		break;
	case WM_RBUTTONDOWN:
		if (imio.WantCaptureMouse)
			break;
		mouse.ChangeRightState(true);
		break;
	case WM_RBUTTONUP:
		if (imio.WantCaptureMouse)
			break;
		mouse.ChangeRightState(false);
		break;
	case WM_MOUSEWHEEL:
		if (imio.WantCaptureMouse)
			break;
		short delta = GET_WHEEL_DELTA_WPARAM(wParam);
		while (delta > WHEEL_DELTA)
		{
			mouse.OnWheelMove(true);
			delta -= WHEEL_DELTA;
		}
		while (delta < -WHEEL_DELTA)
		{
			mouse.OnWheelMove(false);
			delta += WHEEL_DELTA;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::CreateMsgBox(const std::string& title, const std::string& msg, UINT flags)
{
	MessageBox(nullptr, msg.c_str(), title.c_str(), flags);
}

void Window::CreateErrorMsgBox(const std::string& title, const std::string& msg)
{
	CreateMsgBox(title, msg, MB_OK | MB_ICONEXCLAMATION);
}

void Window::ChangeName(const std::string& name)
{
	this->name = name;
	if (SetWindowText(hWnd, this->name.c_str()) == FALSE) throw WND_EXCEPTION;
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return static_cast<int>(msg.wParam);
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return { };
}

Graphics& Window::Gfx()
{
	if (pGfx == nullptr)
		throw WND_NOGFX_EXCEPT;
	return *pGfx;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////EXCEPTION////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

Window::Exception::Exception(const std::string& file, int line, HRESULT hr) noexcept
	:
	MihajloException(file, line),
	hr(hr)
{ }

const char* Window::Exception::what() const noexcept
{
	std::ostringstream msg;
	msg << MihajloException::what() << std::endl;
	msg << "[Error Code] " << GetErrorCode() << std::endl;
	msg << "[Error Description] " << GetErrorString();

	whatBuffer = msg.str();
	return whatBuffer.c_str();
}

std::string Window::Exception::GetType() const noexcept
{
	return "Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* msgBuffer = nullptr;
	DWORD msgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&msgBuffer), 0, nullptr);

	if (msgLen == 0)
	{
		return "Unidentified Error Code";
	}

	std::string msg = msgBuffer;
	LocalFree(msgBuffer);
	return msg;
}

long Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}

std::string Window::NoGfxException::GetType() const noexcept
{
	return "Window Exception [No Graphics/GFX Exception]";
}
