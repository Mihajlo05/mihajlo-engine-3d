#pragma once

#include "Windows/MihajloWin.h"
#include "Graphics/Graphics.h"
#include <d3d11.h>
#include "ErrorHandling/DxgiInfoManager.h"

class Bindable
{
public:
	virtual void Bind(Graphics& gfx) const = 0;
	virtual ~Bindable() = default;
protected:
	ID3D11Device* GetDevice(Graphics& gfx) const;
	ID3D11DeviceContext* GetContext(Graphics& gfx) const;
#ifndef NDEBUG
	DxgiInfoManager& GetInfoManager(Graphics& gfx) const;
#endif
};

#ifndef  NDEBUG
#define BIND_INFOMAN(gfx) DxgiInfoManager& infoManager = GetInfoManager(gfx)
#else
#define BIND_INFOMAN(gfx)
#endif