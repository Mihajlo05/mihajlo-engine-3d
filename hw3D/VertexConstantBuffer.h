#pragma once

#include "ConstantBuffer.h"

template<class C>
class VertexConstantBuffer : public ConstantBuffer<C>
{
	using ConstantBuffer<C>::pData;
	using Bindable::GetContext;
public:
	using ConstantBuffer::ConstantBuffer;
	void Bind(Graphics& gfx) const override
	{
		GetContext(gfx)->VSSetConstantBuffers(0u, 1u, pData.GetAdressOf());
	}
};