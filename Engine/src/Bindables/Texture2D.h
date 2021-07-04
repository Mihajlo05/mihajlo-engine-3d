#pragma once

#include "Bindable.h"
#include "Graphics/Surface.h"

class Texture2D : public Bindable
{
public:
	Texture2D(Graphics& gfx, const Surface& surf, uint32_t slot = 0u);
	void Bind(Graphics& gfx) const override;
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> pData;
	uint32_t slot;
};