#pragma once

#include "DrawableBase.h"
#include "Math/IndexedTriangleList.h"

class PhongDrawable : public DrawableBase<PhongDrawable>
{
public:
	struct Material
	{
		float3 color;
		float specularIntensity;
		float specularPower;
		float padding[3];
	};
public:
	PhongDrawable(Graphics& gfx, IndexedTriangleList model, Material material);
private:
	static constexpr uint32_t cbufSlot = 1u;
};