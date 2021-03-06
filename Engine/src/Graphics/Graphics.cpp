#include "Graphics.h"
#include "ErrorHandling/dxerr.h"
#include <sstream>
#include "Gui/imgui/imgui_impl_dx11.h"
#include "Gui/imgui/imgui_impl_win32.h"
#include "Surface.h"

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

	GFX_THROW( pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pGuiTarget) );

	ImGui_ImplDX11_Init(pDevice.Get(), pContext.Get());
}

Graphics::~Graphics()
{
	ImGui_ImplDX11_Shutdown();
}

void Graphics::BeginFrame(float r, float g, float b)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport();

	if (pRendererTarget == nullptr) //this will init pRenderTarget at the beginning and when screen is resized (genius)
	{
		D3D11_TEXTURE2D_DESC textureDesc = {};

		ImGui::Begin(rendererWndName);
		rndPos.x = ImGui::GetWindowPos().x;
		rndPos.y = ImGui::GetWindowPos().y;
		rndSizeContent.x = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
		rndSizeContent.y = ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y;
		rndSize.x = ImGui::GetWindowWidth();
		rndSize.y = ImGui::GetWindowHeight();
		ImGui::End();

		textureDesc.Width = (UINT)rndSizeContent.x;
		textureDesc.Height = (UINT)rndSizeContent.y;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		ComPtr<ID3D11Texture2D> pTexture;
		GFX_THROW(pDevice->CreateTexture2D(&textureDesc, nullptr, &pTexture));

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};
		renderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		GFX_THROW(pDevice->CreateRenderTargetView(pTexture.Get(), &renderTargetViewDesc, &pRendererTarget));

		ComPtr<ID3D11DepthStencilState> pDepthStencilState;
		D3D11_DEPTH_STENCIL_DESC dsd = {};
		dsd.DepthEnable = TRUE;
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsd.DepthFunc = D3D11_COMPARISON_LESS;

		GFX_THROW(pDevice->CreateDepthStencilState(&dsd, &pDepthStencilState));
		pContext->OMSetDepthStencilState(pDepthStencilState.Get(), 0u);

		D3D11_TEXTURE2D_DESC t2d = {};
		t2d.Width = (UINT)rndSizeContent.x;
		t2d.Height = (UINT)rndSizeContent.y;
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

		D3D11_VIEWPORT dvp;
		dvp.Width = rndSizeContent.x;
		dvp.Height = rndSizeContent.y;
		dvp.MinDepth = 0.0f;
		dvp.MaxDepth = 1.0f;
		dvp.TopLeftX = 0u;
		dvp.TopLeftY = 0u;
		pContext->RSSetViewports(1, &dvp);
	}

	ClearBuffer(r, g, b);
}

void Graphics::EndFrame()
{
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	ComPtr<ID3D11Resource> pRendTexture;
	pRendererTarget->GetResource(&pRendTexture);

	ComPtr<ID3D11ShaderResourceView> pView;
	GFX_THROW(pDevice->CreateShaderResourceView(pRendTexture.Get(), &shaderResourceViewDesc, &pView));

	ImGui::Begin(rendererWndName);
	{
		rndPos.x = ImGui::GetWindowPos().x;
		rndPos.y = ImGui::GetWindowPos().y;
		rndSizeContent.x = ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x;
		rndSizeContent.y = ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y;
		rndSize.x = ImGui::GetWindowWidth();
		rndSize.y = ImGui::GetWindowHeight();

		if (IsCameraBound())
			pCamera->SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, rndSizeContent.y / rndSizeContent.x, 0.5f, 100.0f));

		ImGui::Image((ImTextureID)pView.Get(), ImVec2(rndSizeContent.x, rndSizeContent.y)); //Render the frame on ImGui window
	}
	ImGui::End();

	pContext->OMSetRenderTargets(1u, pGuiTarget.GetAddressOf(), nullptr);
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

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
	const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	pContext->ClearRenderTargetView(pGuiTarget.Get(), black);
	pContext->ClearRenderTargetView(pRendererTarget.Get(), color);
	pContext->ClearDepthStencilView(pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawIndexed(uint32_t count)
{
	pContext->OMSetRenderTargets(1u, pRendererTarget.GetAddressOf(), pDepthStencilView.Get());
	GFX_THROW_INFO_ONLY( pContext->DrawIndexed(count, 0u, 0u) );
}

const ICamera& Graphics::GetCamera() const
{
	assert(IsCameraBound());
	return *pCamera;
}

void Graphics::BindCamera(ICamera& cam)
{
	pCamera = &cam;
}

void Graphics::UnbindCamera()
{
	pCamera = nullptr;
}

bool Graphics::IsCameraBound() const
{
	return pCamera != nullptr;
}

void Graphics::OnResize(uint32_t width, uint32_t height)
{
	assert(pSwapChain != nullptr);

	pContext->OMSetRenderTargets(0, nullptr, nullptr);

	pGuiTarget = nullptr;
	pRendererTarget = nullptr;
	pDepthStencilView = nullptr;

	GFX_THROW(pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));

	ComPtr<ID3D11Texture2D> pBuffer;
	GFX_THROW(pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		&pBuffer));

	GFX_THROW(pDevice->CreateRenderTargetView(pBuffer.Get(), nullptr,
		&pGuiTarget));

	//the rest is being handeld in BeginFrame, since pRendererTarget is nullptr
}

float2 Graphics::GetRendererPos() const
{
	return rndPos;
}

float2 Graphics::GetRendererSize() const
{
	return rndSize;
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
