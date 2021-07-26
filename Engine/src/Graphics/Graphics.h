#pragma once

#include "Windows/MihajloWin.h"
#include <d3d11.h>
#include "wrl.h"
#include "ErrorHandling/MihajloException.h"
#include "ErrorHandling/DxgiInfoManager.h"
#include "Math/MihajloMath.h"

class Graphics
{
	friend class Bindable;
public:
		class Exception : public MihajloException
		{
		public:
		Exception(const std::string& file, int line, HRESULT hr, const std::vector<std::string>& info) noexcept;
		Exception(const std::string& file, int line, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual std::string GetType() const noexcept override;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		long GetErrorCode() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info = "";
	};
	class DeviceRemovedException : public Exception
	{
	public:
		using Exception::Exception;
		std::string GetType() const noexcept override;
	};
	class InfoException : public MihajloException
	{
	public:
		InfoException(const std::string& file, int line, std::vector<std::string>& info) noexcept;
		std::string GetType() const noexcept override;
		const char* what() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
public:
	Graphics(HWND hWnd, uint32_t width, uint32_t height);
	Graphics& operator=(const Graphics&) = delete;
	Graphics(const Graphics&) = delete;
	~Graphics();
	void BeginFrame(float r, float g, float b);
	void EndFrame();
	void ClearBuffer(float r, float g, float b, float a=1.0f);
	void DrawIndexed(uint32_t count);
	void SetPerspective(const matrix& p);
	matrix GetPerspective() const;
	void SetCamera(fmatrix ct);
	matrix GetCamera() const;
	void EnableGui();
	void DisableGui();
	bool IsGuiEnabled() const;
	void OnResize(uint32_t width, uint32_t height);
	float2 GetRendererPos() const;
	float2 GetRendererSize() const;
private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
private:
	matrix perspective;
	matrix cameraTransf = DirectX::XMMatrixIdentity();
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pGuiTarget = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRendererTarget = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthStencilView = nullptr;
private:
	bool isGuiEnabled = true;
	const char* rendererWndName = "Renderer";
	float2 rndPos = { -1.0f, -1.0f };
	float2 rndSize = { -1.0f, -1.0f };
	float2 rndSizeContent = { -1.0f, -1.0f };
};

#define GFX_EXCEPT_NOINFO(hr) Graphics::Exception(__FILE__, __LINE__, (hr))
#define GFX_THROW_NOINFO(hr) if (FAILED(hr)) throw GFX_EXCEPT_NOINFO(hr)

#ifndef NDEBUG
#define GFX_EXCEPT(hr) Graphics::Exception(__FILE__, __LINE__, (hr), infoManager.GetMessages())
#define GFX_THROW(hr) infoManager.Set(); if (FAILED(hr)) throw GFX_EXCEPT(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__FILE__, __LINE__, (hr), infoManager.GetMessages())
#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); { auto msgs = infoManager.GetMessages(); if (!msgs.empty()) throw Graphics::InfoException(__FILE__, __LINE__, msgs); }
#else
#define GFX_EXCEPT(hr) GFX_EXCEPT_NOINFO(hr)
#define GFX_THROW(hr) GFX_THROW_NOINFO(hr)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__FILE__, __LINE__, (hr))
#define GFX_THROW_INFO_ONLY(call) (call)
#endif
