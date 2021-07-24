#pragma once

#include "DrawableBase.h"
#include "Math/IndexedTriangleList.h"
#include "Bindables/PixelConstantBuffer.h"
#include "Nodes/PointLights/PointLight.h"

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
	void Draw(Graphics& gfx) const override;
	void SetLight(const PointLight& pcb);
	void SetMaterial(Material m);
	Material GetMaterial() const;
private:
	static constexpr uint32_t cbufSlot = 1u;
	PixelConstantBuffer<Material>* pMaterialBuf = nullptr;
	const PointLight* pLight = nullptr;
	Material material;
	Graphics& gfx;
};