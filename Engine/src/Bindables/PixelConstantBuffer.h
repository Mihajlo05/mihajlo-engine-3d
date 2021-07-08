#pragma once

#include "ConstantBuffer.h"

template<class C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pData;
	using Bindable::GetContext;
	using ConstantBuffer<C>::slot;
public:
	using ConstantBuffer<C>::SetData;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->PSSetConstantBuffers(slot, 1u, pData.GetAddressOf());
	}
};