#pragma once

#include "MihajloWin.h"
#include <d3d11.h>
#include "wrl.h"
#include "MihajloException.h"

class Graphics
{
private:
	class Exception : public MihajloException
	{
	public:
		Exception(const std::string& file, int line, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual std::string GetType() const noexcept override;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		long GetErrorCode() const noexcept;
	private:
		HRESULT hr;
	};
	class DeviceRemovedException : public Exception
	{
	public:
		using Exception::Exception;
		std::string GetType() const noexcept override;
	};
public:
	Graphics(HWND hWnd);
	Graphics& operator=(const Graphics&) = delete;
	Graphics(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float r, float g, float b, float a=1.0f);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget = nullptr;
};