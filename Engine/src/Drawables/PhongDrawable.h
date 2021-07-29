#pragma once

#include "Drawable.h"
#include "Math/IndexedTriangleList.h"
#include "Bindables/PixelConstantBuffer.h"
#include "Nodes/PointLight.h"

class PhongDrawable : public Drawable
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