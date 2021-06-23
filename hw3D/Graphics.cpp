#include "Graphics.h"
#include "dxerr.h"
#include <sstream>

#pragma comment(lib, "d3d11.lib")

using namespace Microsoft::WRL;

Graphics::Graphics(HWND hWnd, uint32_t width, uint32_t height)
{
	//swap chain descriptor
	DXGI_SWAP_CHAIN_DESC scd = { 0 };
	scd.BufferDesc.Width = width;
	scd.BufferDesc.Height = height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.RefreshRate.Numerator = 0; //not setting refresh rate
	scd.BufferDesc.RefreshRate.Denominator = 0;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED; //not setting scaling
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED; //not setting scaling order
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0; //no anti-aliasing
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount = 2; //double-boufer
	scd.OutputWindow = hWnd;
	scd.Windowed = TRUE;
	scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	scd.Flags = 0; //not setting any flags (yet)

	UINT deviceSwapChainFlags;

#ifdef NDEBUG
	deviceSwapChainFlags = 0;
#else
	deviceSwapChainFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif


	GFX_THROW( D3D11CreateDeviceAndSwapChain(
		nullptr, //not specifying graphics card
		D3D_DRIVER_TYPE_HARDWARE, //Hardware driver
		nullptr,
		deviceSwapChainFlags,
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
	GFX_THROW( pSwapChain->GetBuffer(0,
		__uuidof(ID3D11Resource),
		&pBackBuffer) );

	GFX_THROW( pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget) );

	ComPtr<ID3D11DepthStencilState> pDepthStencilState;
	D3D11_DEPTH_STENCIL_DESC dsd = {};
	dsd.DepthEnable = TRUE;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;

	GFX_THROW(pDevice->CreateDepthStencilState(&dsd, &pDepthStencilState));
	pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 0u);

	ComPtr<ID3D11Texture2D> pTexture;
	D3D11_TEXTURE2D_DESC t2d = {};
	t2d.Width = width;
	t2d.Height = height;
	t2d.MipLevels = 0u;
	t2d.ArraySize = 1u;
	t2d.Format = DXGI_FORMAT_D32_FLOAT;
	t2d.SampleDesc.Count = 1u;
	t2d.SampleDesc.Quality = 0u;
	t2d.Usage = D3D11_USAGE_DEFAULT;
	t2d.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	t2d.MiscFlags = 0u;
	t2d.CPUAccessFlags = 0u;

	GFX_THROW(pDevice->CreateTexture2D(&t2d, nullptr, &pTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd = {};
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Texture2D.MipSlice = 0u;

	GFX_THROW(pDevice->CreateDepthStencilView(pTexture.Get(), &dsvd, &pDepthStencilView));
}

void Graphics::EndFrame()
{
#ifndef NDEBUG
	infoManager.Set();
#endif
	HRESULT hr;
	hr = pSwapChain->Present(1u, 0u);
	if (FAILED(hr))
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
			throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
		else
			throw GFX_EXCEPT(hr);
}

void Graphics::ClearBuffer(float r, float g, float b, float a)
{
	const float color[] = { r, g, b, a };
	pContext->ClearRenderTargetView(pTarget.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

//EXCEPTION

Graphics::Exception::Exception(const std::string& file, int line, HRESULT hr, const std::vector<std::string>& infos) noexcept
	:
	MihajloException(file, line),
	hr(hr)
{
	for (const auto& is : infos)
	{
		info += is;
		info += "\n";
	}
	if (!info.empty()) info.pop_back();
}

Graphics::Exception::Exception(const std::string& file, int line, HRESULT hr) noexcept
	:
	MihajloException(file, line),
	hr(hr)
{ }

const char* Graphics::Exception::what() const noexcept
{
	std::ostringstream msg;
	msg << MihajloException::what() << std::endl;
	
	msg << "[Error Code] " << GetErrorCode() << std::endl;
	msg << "[Error String] " << GetErrorString() << std::endl;
	msg << "[Error Description] " << GetErrorDescription() << std::endl;
#ifndef NDEBUG
	msg << "[Error Info]\n" << GetErrorInfo();
#endif

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

std::string Graphics::Exception::GetErrorInfo() const noexcept
{
	return info;
}

std::string Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}

Graphics::InfoException::InfoException(const std::string& file, int line, std::vector<std::string>& infos) noexcept
	:
	MihajloException(file, line)
{
	for (const auto& is : infos)
	{
		info += is;
		info += "\n";
	}
	if (!info.empty()) info.pop_back();
}

std::string Graphics::InfoException::GetType() const noexcept
{
	return "Graphics Exception [INFO_ONLY]";
}

const char* Graphics::InfoException::what() const noexcept
{
	std::ostringstream msg;
	msg << MihajloException::what() << std::endl;
#ifndef NDEBUG
	msg << "[Error Info]\n" << GetErrorInfo();
#endif

	whatBuffer = msg.str();
	return whatBuffer.c_str();
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept
{
	return info;
}
