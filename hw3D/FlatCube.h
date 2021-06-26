#pragma once

#include "DrawableBase.h"

class FlatCube : public DrawableBase<FlatCube>
{
public:
	FlatCube(Graphics& gfx);
	void UpdateLogic(float dt) override;
	void UpdateGraphics(Graphics& gfx) override;
	DirectX::XMMATRIX GetTransformation() const override;
private:
	float time = 0.0f;
};