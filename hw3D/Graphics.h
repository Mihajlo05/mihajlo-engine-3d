#pragma once

#include "MihajloWin.h"
#include <d3d11.h>

class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics& operator=(const Graphics&) = delete;
	Graphics(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void ClearBuffer(float r, float g, float b, float a=1.0f);
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;
};