#pragma once

#include "Bindable.h"
#include "VertexConstantBuffer.h"
#include "Drawable.h"
#include <DirectXMath.h>

class TransformationConstantBuffer : public Bindable
{
public:
	TransformationConstantBuffer(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) const override;
private:
	const Drawable& parent;
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVConstBuf;
};