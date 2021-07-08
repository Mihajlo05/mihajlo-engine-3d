#pragma once

#include "Bindable.h"

template<class C>
class ConstantBuffer : public Bindable
{
public:
	ConstantBuffer(Graphics& gfx, const C& cBuf, uint32_t slot = 0u)
		:
		slot(slot),
		gfx(gfx)
	{
		BIND_INFOMAN(gfx);

		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(cBuf);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &cBuf;

		GFX_THROW(GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pData));
	}
	ConstantBuffer(Graphics& gfx, uint32_t slot = 0u)
		:
		slot(slot),
		gfx(gfx)
	{
		BIND_INFOMAN(gfx);

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(C);
		cbd.StructureByteStride = 0u;

		GFX_THROW(GetDevice(gfx)->CreateBuffer(&cbd, nullptr, &pData));
	}
	void Update(Graphics& gfx, const C& cBuf) const
	{
		BIND_INFOMAN(gfx);

		D3D11_MAPPED_SUBRESOURCE msr;
		GFX_THROW( GetContext(gfx)->Map(pData.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &msr) );

		memcpy(msr.pData, &cBuf, sizeof(cBuf));
		GetContext(gfx)->Unmap(pData.Get(), 0u);
	}
	void SetData(const C& cBuf)
	{
		BIND_INFOMAN(gfx);

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &cBuf;

		GFX_THROW(GetDevice(gfx)->CreateBuffer(&cbd, &csd, &pData));
	}
	virtual void Bind(Graphics& gfx) const override = 0;
	virtual ~ConstantBuffer() = default;
protected:
	D3D11_BUFFER_DESC cbd = {};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
	uint32_t slot;
private:
	Graphics& gfx;
};