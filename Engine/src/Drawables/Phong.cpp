#include "Phong.h"
#include "Bindables/AllBindables.h"

namespace Drawables
{
	Phong::Phong(Graphics& gfx, IndexedTriangleList model, Material material)
		:
		gfx(gfx),
		material(material)
	{
		AddBindable<VertexBuffer>(gfx, model.vertices);
		AddIndexBuffer(gfx, model.indices);

		auto pcb = std::make_unique<ConstantBuffer<Material>>(gfx, ConstantBuffer<Material>::Type::Pixel, material, cbufSlot);
		pMaterialBuf = pcb.get();
		AddBindable(std::move(pcb));

		auto pvs = std::make_unique<VertexShader>(gfx, L"shaders-bin\\PhongVS.cso");
		VertexShader& vs = *pvs;
		AddBindable(std::move(pvs));
		AddBindable<PixelShader>(gfx, L"shaders-bin\\PhongPS.cso");

		AddBindable<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize());
		AddBindable<PrimitiveTopology>(model.d3dtype);

		AddBindable<TransformationConstantBuffer>(gfx, *this);
	}

	void Phong::Draw(Graphics& gfx) const
	{
		if (pLight != nullptr)
		{
			pLight->Bind(gfx);
		}
		Drawable::Draw(gfx);
	}

	void Phong::SetLight(const PointLight& pcb)
	{
		pLight = &pcb;
	}

	void Phong::SetMaterial(Material m)
	{
		assert(pMaterialBuf != nullptr);
		material = m;
		pMaterialBuf->Update(gfx, material);
	}

	Phong::Material Phong::GetMaterial() const
	{
		return material;
	}
}
