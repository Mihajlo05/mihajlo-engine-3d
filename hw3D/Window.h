#pragma once
#include "MihajloWin.h"

class Window
{
private:
	class WindowRegister
	{
	public:
		WindowRegister();
		~WindowRegister() noexcept;
		static HINSTANCE GetInstance() noexcept;
		static const char* GetName() noexcept;
	private:
		static constexpr const char* className = "MihajloEngine3D";
		HINSTANCE hInst;
		static WindowRegister wndReg;
	};
public:
	Window(unsigned int width, unsigned int height, const char* wndName);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	static LRESULT CALLBACK WndProcSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	const char* wndName;
	unsigned int width;
	unsigned int height;
	HWND hWnd;
};