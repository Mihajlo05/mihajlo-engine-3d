#include "Sampler.h"

Sampler::Sampler(Graphics& gfx, uint32_t slot)
	:
	slot(slot)
{
	BIND_INFOMAN(gfx);

	D3D11_SAMPLER_DESC sd = {};
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	GFX_THROW(GetDevice(gfx)->CreateSamplerState(&sd, &pData));
}

void Sampler::Bind(Graphics& gfx) const
{
	GetContext(gfx)->PSSetSamplers(slot, 1u, pData.GetAddressOf());
}