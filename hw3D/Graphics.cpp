#include "Graphics.h"

#pragma comment(lib, "d3d11.lib")

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

	D3D11CreateDeviceAndSwapChain(
		nullptr, //not specifying graphics card
		D3D_DRIVER_TYPE_HARDWARE, //Hardware driver
		nullptr,
		0, //no flags
		nullptr,
		0, //not specifying feature levels
		D3D11_SDK_VERSION, //SDK version on device
		&scd,
		&pSwapChain,
		&pDevice,
		nullptr, //not specifying feature level,
		&pContext
	);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));

	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();
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
	pSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b, float a)
{
	const float color[] = { r, g, b, a };
	pContext->ClearRenderTargetView(pTarget, color);
}
