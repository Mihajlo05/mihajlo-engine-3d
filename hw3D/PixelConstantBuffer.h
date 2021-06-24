#pragma once

#include "ConstantBuffer.h"

template<class C>
class PixelConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pData;
	using Bindable::GetContext;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->PSSetConstantBuffers(0u, 1u, pData.GetAddressOf());
	}
};