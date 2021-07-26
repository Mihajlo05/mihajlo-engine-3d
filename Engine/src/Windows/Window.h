#pragma once
#include "MihajloWin.h"
#include "ErrorHandling/MihajloException.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics/Graphics.h"

#include <optional>
#include <memory>

class Window
{
public:
	class Exception : public MihajloException
	{
	public:
		Exception(const std::string& file, int line, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		std::string GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		long GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};
	class NoGfxException : public MihajloException
	{
	public:
		using MihajloException::MihajloException;
		std::string GetType() const noexcept override;
	};
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
	static void CreateMsgBox(const std::string& title, const std::string& msg, UINT flags);
	static void CreateErrorMsgBox(const std::string& title, const std::string& msg);
	void ChangeName(const std::string& name);
	static std::optional<int> ProcessMessages();
	Graphics& Gfx();
private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	Keyboard kbd;
	Mouse mouse;
private:
	unsigned int width;
	unsigned int height;
	std::string name;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx = nullptr;
	std::vector<BYTE> rawBuffer;
};

#define WND_EXCEPTION_H(hr) Window::Exception(__FILE__, __LINE__, hr)
#define WND_EXCEPTION WND_EXCEPTION_H(GetLastError())