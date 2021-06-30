#pragma once

#include "Bindable.h"
#include "VertexConstantBuffer.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformationConstantBuffer : public Bindable
{
public:
	TransformationConstantBuffer(Graphics& gfx, const Drawable& parent, uint32_t slot = 0u);
	void Bind(Graphics& gfx) const override;
private:
	const Drawable& parent;
	VertexConstantBuffer<DirectX::XMMATRIX> vConstBuf;
};