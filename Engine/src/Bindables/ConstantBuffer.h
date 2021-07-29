#pragma once

#include "Bindable.h"

template<class C>
class ConstantBuffer : public Bindable
{
public:
	enum class Type
	{
		Vertex,
		Pixel
	};
public:
	ConstantBuffer(Graphics& gfx, Type type, const C& cBuf, uint32_t slot = 0u)
		:
		slot(slot),
		gfx(gfx),
		type(type)
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
	ConstantBuffer(Graphics& gfx, Type type, uint32_t slot = 0u)
		:
		slot(slot),
		gfx(gfx),
		type(type)
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
	void Bind(Graphics& gfx) const override
	{
		switch (type)
		{
		case Type::Vertex:
			GetContext(gfx)->VSSetConstantBuffers(slot, 1u, pData.GetAddressOf());
			break;
		case Type::Pixel:
			GetContext(gfx)->PSSetConstantBuffers(slot, 1u, pData.GetAddressOf());
			break;
		default:
			assert("Unknown Constant Buffer type" && false);
			break;
		}
	}
	virtual ~ConstantBuffer() = default;
private:
	Type type;
	D3D11_BUFFER_DESC cbd = {};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pData;
	uint32_t slot;
	Graphics& gfx;
};