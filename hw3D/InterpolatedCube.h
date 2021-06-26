#pragma once

#include "DrawableBase.h"

class InterpolatedCube : public DrawableBase<InterpolatedCube>
{
public:
	InterpolatedCube(Graphics& gfx);
	void UpdateLogic(float dt) override;
	void UpdateGraphics(Graphics& gfx) override;
	DirectX::XMMATRIX GetTransformation() const override;
private:
	float time = 0.0f;
};