#pragma once

#include "Bindable.h"
#include "VertexConstantBuffer.h"
#include "Drawables/Drawable.h"
#include <DirectXMath.h>

class TransformationConstantBuffer : public Bindable
{
public:
	TransformationConstantBuffer(Graphics& gfx, const Drawable& parent, uint32_t slot = 0u);
	void Bind(Graphics& gfx) const override;
private:
	struct Data
	{
		DirectX::XMMATRIX modelView;
		DirectX::XMMATRIX modelViewProj;
	};
private:
	const Drawable& parent;
	VertexConstantBuffer<Data> vConstBuf;
};