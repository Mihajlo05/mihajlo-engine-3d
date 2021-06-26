#pragma once

#include "DrawableBase.h"
#include "VertexConstantBuffer.h"

class InterpolatedPlane : public DrawableBase<InterpolatedPlane>
{
public:
	InterpolatedPlane(Graphics& gfx);
	void UpdateLogic(float dt) override;
	void UpdateGraphics(Graphics& gfx) override;
	DirectX::XMMATRIX GetTransformation() const override;
private:
	float time = 0.0f;
};