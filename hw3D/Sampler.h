#pragma once

#include "Bindable.h"

class Sampler : public Bindable
{
public:
	Sampler(Graphics& gfx, uint32_t slot = 0u);
	void Bind(Graphics& gfx) const override;
private:
	Microsoft::WRL::ComPtr<ID3D11SamplerState> pData;
	uint32_t slot;
};