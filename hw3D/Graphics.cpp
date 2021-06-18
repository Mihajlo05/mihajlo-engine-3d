#include "Graphics.h"
#include "dxerr.h"
#include <sstream>

#pragma comment(lib, "d3d11.lib")

#define GFX_EXCEPTION(hr) Graphics::Exception(__FILE__, __LINE__, hr)
#define THROW_IF_ERROR_GFX_EXCEPTION(hr) if (FAILED(hr)) throw GFX_EXCEPTION(hr)
#define GFX_DEVICE_REMOVED_EXCEPTION(hr) Graphics::DeviceRemovedException(__FILE__, __LINE__, hr)

using namespace Microsoft::WRL;

Graphics::Graphics(HWND hWnd)
{
	//swap chain descriptor
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferDesc.Width = 0; //width and height are the same as window
	scd.BufferDesc.Height = 0;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0; //not setting refresh rate
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //not setting scaling
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //not setting scaling order
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0; //no anti-aliasing
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 1; //double-boufer
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags = 0; //not setting any flags (yet)

	THROW_IF_ERROR_GFX_EXCEPTION (
	D3D11CreateDeviceAndSwapChain(
		nullptr, //not specifying graphics card
		D3D_DRIVER_TYPE_HARDWARE, //Hardware driver
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		nullptr,
		0, //not specifying feature levels
		D3D11_SDK_VERSION, //SDK version on device
		&scd,
		&pSwapChain,
		&pDevice,
		nullptr, //not specifying feature level,
		&pContext
	) );

	ComPtr<ID3D11Resource> pBackBuffer = nullptr;
	THROW_IF_ERROR_GFX_EXCEPTION( pSwapChain->GetBuffer(0,
		__uuidof(ID3D11Resource),
		&pBackBuffer) );

	THROW_IF_ERROR_GFX_EXCEPTION( pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget) );
}

Graphics::~Graphics()
{
	if (pTarget != nullptr) pTarget->Release();
	if (pSwapChain != nullptr) pSwapChain->Release();
	if (pContext != nullptr) pContext->Release();
	if (pDevice != nullptr) pDevice->Release();
}

void Graphics::EndFrame()
{
	HRESULT hr;
	hr = pSwapChain->Present(1u, 0u);
	if (FAILED(hr))
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GFX_DEVICE_REMOVED_EXCEPTION(pDevice->GetDeviceRemovedReason());
		else
			throw GFX_EXCEPTION(hr);
}

void Graphics::ClearBuffer(float r, float g, float b, float a)
{
	const float color[] = { r, g, b, a };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
}

Graphics::Exception::Exception(const std::string& file, int line, HRESULT hr) noexcept
	:
	MihajloException(file, line),
	hr(hr)
{ }

const char* Graphics::Exception::what() const noexcept
{
	std::ostringstream msg;
	msg << "[Type] " << GetType() << std::endl;
	msg << GetLocation() << std::endl << std::endl;
	
	msg << "[Error Code] " << GetErrorCode() << std::endl;
	msg << "[Error Name] " << GetErrorString() << std::endl;
	msg << "[Error Description] " << GetErrorDescription() << std::endl;

	whatBuffer = msg.str();
	return whatBuffer.c_str();
}

std::string Graphics::Exception::GetType() const noexcept
{
	return "Graphics Exception";
}

std::string Graphics::Exception::GetErrorString() const noexcept
{
	return DXGetErrorString(hr);
}

std::string Graphics::Exception::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription(hr, buf, sizeof(buf));
	return std::string(buf);
}

long Graphics::Exception::GetErrorCode() const noexcept
{
	return static_cast<long>(hr);
}

std::string Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "Graphics Exception [Device Removed]";
}
