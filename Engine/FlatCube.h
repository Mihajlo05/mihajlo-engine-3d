#pragma once

#include "DrawableBase.h"

class FlatCube : public DrawableBase<FlatCube>
{
public:
	FlatCube(Graphics& gfx);
	DirectX::XMMATRIX GetTransformation() const override;
	void Update(float dt) override;
private:
	float time = 0.0f;
};