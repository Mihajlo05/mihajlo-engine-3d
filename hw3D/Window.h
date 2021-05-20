#pragma once
#include "MihajloWin.h"
#include "MihajloException.h"

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
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static int ProcessWindows();
private:
	unsigned int width;
	unsigned int height;
	const char* wndName;
	HWND hWnd;
};