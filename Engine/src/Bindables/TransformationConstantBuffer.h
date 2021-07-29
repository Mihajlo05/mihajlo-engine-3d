#pragma once

#include "Bindable.h"
#include "ConstantBuffer.h"
#include "Drawables/Drawable.h"
#include "Math/MihajloMath.h"

class TransformationConstantBuffer : public Bindable
{
public:
	TransformationConstantBuffer(Graphics& gfx, const Drawables::Drawable& parent, uint32_t slot = 0u);
	void Bind(Graphics& gfx) const override;
private:
	struct Data
	{
		matrix modelView;
		matrix modelViewProj;
	};
private:
	const Drawables::Drawable& parent;
	ConstantBuffer<Data> vConstBuf;
};