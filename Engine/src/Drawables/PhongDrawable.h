#pragma once

#include "DrawableBase.h"
#include "Math/IndexedTriangleList.h"
#include "Bindables/PixelConstantBuffer.h"

class PhongDrawable : public DrawableBase<PhongDrawable>
{
public:
	struct Material
	{
		float3 color;
		float specularIntensity;
		float specularPower;
		float3 padding;
	};
public:
	PhongDrawable(Graphics& gfx, IndexedTriangleList model, Material material);
	void SetMaterial(Material m);
	Material GetMaterial() const;
private:
	static constexpr uint32_t cbufSlot = 1u;
	PixelConstantBuffer<Material>* pMaterialBuf = nullptr;
	Material material;
	Graphics& gfx;
};