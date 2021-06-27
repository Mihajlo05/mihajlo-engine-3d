#pragma once

#include "ConstantBuffer.h"

template<class C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pData;
	using Bindable::GetContext;
	using ConstantBuffer<C>::slot;
public:
	using ConstantBuffer<C>::ConstantBuffer;
	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->VSSetConstantBuffers(slot, 1u, this->pData.GetAddressOf());
	}
};