#include "Phong.h"
#include "Bindables/AllBindables.h"

using namespace Binds;

namespace Drawables
{
	Phong::Phong(Graphics& gfx, IndexedTriangleList model, Material material)
		:
		gfx(gfx),
		material(material)
	{
		AddBind(std::make_shared<VertexBuffer>(gfx, model.vertices));
		AddBind(std::make_shared<IndexBuffer>(gfx, model.indices));

		auto pcb = std::make_shared<ConstantBuffer<Material>>(gfx, ConstantBuffer<Material>::Type::Pixel, material, cbufSlot);
		pMaterialBuf = pcb.get();
		AddBind(std::move(pcb));

		auto pvs = std::make_shared<VertexShader>(gfx, L"shaders-bin\\PhongVS.cso");
		VertexShader& vs = *pvs;
		AddBind(std::move(pvs));
		AddBind(std::make_shared<PixelShader>(gfx, L"shaders-bin\\PhongPS.cso"));

		AddBind(std::make_shared<InputLayout>(gfx, model.vertices.GetLayout().GetD3DLayout(), vs.GetBytecode(), vs.GetBytecodeSize()));
		AddBind(std::make_shared<PrimitiveTopology>(model.d3dtype));

		AddBind(std::make_shared<TransformationConstantBuffer>(gfx, *this));
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
