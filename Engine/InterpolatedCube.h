#pragma once

#include "DrawableBase.h"

class InterpolatedCube : public DrawableBase<InterpolatedCube>
{
public:
	InterpolatedCube(Graphics& gfx);
	DirectX::XMMATRIX GetTransformation() const override;
	void Update(float dt) override;
private:
	float time = 0.0f;
};