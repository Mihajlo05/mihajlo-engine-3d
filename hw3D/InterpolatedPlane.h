#pragma once

#include "DrawableBase.h"
#include "VertexConstantBuffer.h"

class InterpolatedPlane : public DrawableBase<InterpolatedPlane>
{
public:
	InterpolatedPlane(Graphics& gfx);
	DirectX::XMMATRIX GetTransformation() const override;
	void Update(float dt) override;
private:
	float time = 0.0f;
};