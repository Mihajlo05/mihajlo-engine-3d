#pragma once

#include "Drawable.h"
#include "Math/IndexedTriangleList.h"
#include "Bindables/ConstantBuffer.h"
#include "Nodes/PointLight.h"

namespace Drawables
{
	class Phong : public Drawable
	{
	public:
		struct Material
		{
			float3 color = { 1.0f, 1.0f, 1.0f };
			float specularIntensity = 2.0f;
			float specularPower = 70.0f;
			float3 padding;
		};
	public:
		Phong(Graphics& gfx, IndexedTriangleList model, Material material);
		void Draw(Graphics& gfx) const override;
		void SetLight(const PointLight& pcb);
		void SetMaterial(Material m);
		Material GetMaterial() const;
	private:
		static constexpr uint32_t cbufSlot = 1u;
		Binds::ConstantBuffer<Material>* pMaterialBuf = nullptr;
		const PointLight* pLight = nullptr;
		Material material;
		Graphics& gfx;
	};
}
